#include "dag.h"
using namespace std;
Node* exist_or_insert(vector<Node*>& nodes, string val) {
    auto iter = find_if(nodes.rbegin(), nodes.rend(),
                        [=](Node* x) { return x->contains(val); });
    if (iter == nodes.rend()) {
        auto node = new Node{{val}};
        nodes.push_back(node);
        return node;
    } else {
        return *iter;
    }
}

Node* common_sub_exp(vector<Node*> nodes,
                     unordered_map<Node*, vector<Node*>> edges,
                     IR ir) {
    for (auto iter = nodes.rbegin(); iter != nodes.rend(); iter++) {
        auto node = *iter;
        if (node->type() == ir.type && edges.find(node) != edges.end()) {
            auto out = edges[node];
            bool flag = true;
            for (int i = 0; i < out.size(); i++) {
                /* Check it has the required child */
                if (!out[i]->contains(ir.args[i + 1])) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return node;
        } else {
            for (auto arg : ir.args) {
                if (node->contains(arg))
                    return nullptr;
            }
        }
    }
    return nullptr;
}

Node* common_func_call(vector<Node*> nodes,
                       unordered_map<Node*, vector<Node*>> edges,
                       string func_name,
                       vector<string> args) {
    for (auto iter = nodes.rbegin(); iter != nodes.rend(); iter++) {
        auto node = *iter;
        if (func_name == node->func_name && node->type() == IRType::CALL &&
            edges.find(node) != edges.end()) {
            auto out = edges[node];
            bool flag = true;
            for (int i = 0; i < out.size(); i++) {
                /* Check it has the required child */
                if (!out[i]->contains(args[i])) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return node;
        } else {
            for (auto arg : args) {
                if (node->contains(arg))
                    return nullptr;
            }
        }
    }
    return nullptr;
}

IRList opt_DAG(IRList irs) {
    IRList n_irs;
    auto function = gen_function(irs);
    for (auto func : function) {
        auto block = gen_block(func).first;
        for (auto b : block) {
            n_irs = extend(n_irs, block_DAG(b));
        }
    }
    return n_irs;
}

IRList block_DAG(IRList block) {
    IRList body;
    IRList head, tail;
    for (auto ir : block) {
        if (ir.type == IRType::FUNCTION || ir.type == IRType::LABEL ||
            ir.type == IRType::PARAM || ir.type == IRType::ALLOC) {
            head.push_back(ir);
        }
    }
    for (auto iter = block.rbegin(); iter < block.rend(); iter++) {
        if ((*iter).type == IRType::GOTO) {
            tail.push_back(*iter);
        }
    }
    auto [nodes, edges] = gen_DAG(block);
    for (auto node : nodes) {
        auto out_iter = edges.find(node);
        switch (node->op) {
            case IRType::NIR:
                continue;
            case IRType::ADD:
            case IRType::SUB:
            case IRType::DIV:
            case IRType::MUL: {
                auto out = (*out_iter).second;
                body.push_back(
                    IR{node->op, {node->val(), out[0]->val(), out[1]->val()}});
                break;
            }
            case IRType::LDEREF: {
                auto out = (*out_iter).second;
                body.push_back(IR{node->op, {out[0]->val(), out[1]->val()}});
                break;
            }
            case IRType::ASSIGN:
            case IRType::REF:
            case IRType::RDEREF: {
                auto out = (*out_iter).second;
                body.push_back(IR{node->op, {node->val(), out[0]->val()}});
                break;
            }
            case IRType::CALL: {
                auto out = (*out_iter).second;
                for (auto o : out) {
                    body.push_back(IR{IRType::ARG, {o->val()}});
                }
                body.push_back(
                    IR{IRType::CALL, {node->val(), node->func_name}});
                break;
            }
            case IRType::READ: {
                body.push_back(IR{node->op, {node->val()}});
                break;
            }
            case IRType::WRITE:
            case IRType::RET: {
                auto out = (*out_iter).second;
                body.push_back(IR{node->op, {out[0]->val()}});
                break;
            }
            case IRType::IF: {
                auto out = (*out_iter).second;
                body.push_back(IR{node->op,
                                  {out[0]->val(), node->val_list[0],
                                   out[1]->val(), node->val_list[1]}});
                break;
            }
        }
    }
    return extend(extend(head, body), tail);
}

vector<Node*> parent(Node* node, unordered_map<Node*, vector<Node*>> edges) {
    vector<Node*> res;
    for (auto edge : edges) {
        auto endnodes = edge.second;
        if (find(endnodes.begin(), endnodes.end(), node) != endnodes.end()) {
            res.push_back(edge.first);
        }
    }
    return res;
}

pair<vector<Node*>, unordered_map<Node*, vector<Node*>>> gen_DAG(IRList block) {
    vector<Node*> nodes;
    unordered_map<Node*, vector<Node*>> edges;
    vector<string> arg_stack;
    for (auto ir : block) {
        switch (ir.type) {
            case IRType::ASSIGN: {
                /* temp_var is ensured to be just used once in program */
                /* hence if it appears in assignment we can just shortcut it */
                if (ir.args[1][0] == 't') {
                    auto rhs = exist_or_insert(nodes, ir.args[1]);
                    rhs->val_list = {ir.args[0]};
                } else {
                    auto rhs = exist_or_insert(nodes, ir.args[1]);
                    auto lhs = new Node{ir.type, {ir.args[0]}};
                    if (edges.find(lhs) == edges.end()) {
                        edges[lhs] = {rhs};
                    } else {
                        edges[lhs].push_back(rhs);
                    }
                    nodes.push_back(lhs);
                }
                break;
            }
            case IRType::ADD:
            case IRType::SUB:
            case IRType::DIV:
            case IRType::MUL: {
                auto lhs = common_sub_exp(nodes, edges, ir);
                if (lhs != nullptr) {
                    lhs->val_list.push_back(ir.args[0]);
                } else {
                    lhs = new Node{ir.type, {ir.args[0]}};
                    auto l_term = exist_or_insert(nodes, ir.args[1]);
                    auto r_term = exist_or_insert(nodes, ir.args[2]);
                    nodes.push_back(lhs);
                    if (edges.find(lhs) == edges.end()) {
                        edges[lhs] = {l_term, r_term};
                    } else {
                        edges[lhs].push_back(l_term);
                        edges[lhs].push_back(r_term);
                    }
                }
                break;
            }
            case IRType::LDEREF: {
                auto node = new Node{ir.type, {}};
                auto lhs = exist_or_insert(nodes, ir.args[0]);
                auto rhs = exist_or_insert(nodes, ir.args[1]);
                nodes.push_back(node);
                if (edges.find(lhs) == edges.end()) {
                    edges[node] = {lhs, rhs};
                } else {
                    edges[node].push_back(lhs);
                    edges[node].push_back(rhs);
                }
                break;
            }
            case IRType::REF:
            case IRType::RDEREF: {
                auto lhs = common_sub_exp(nodes, edges, ir);
                if (lhs != nullptr) {
                    lhs->val_list.push_back(ir.args[0]);
                } else {
                    lhs = new Node{ir.type, {ir.args[0]}};
                    auto rhs = exist_or_insert(nodes, ir.args[1]);
                    nodes.push_back(lhs);
                    if (edges.find(lhs) == edges.end()) {
                        edges[lhs] = {rhs};
                    } else {
                        edges[lhs].push_back(rhs);
                    }
                }
                break;
            }
            case IRType::ARG: {
                arg_stack.push_back(ir.args[0]);
                break;
            }
            case IRType::READ: {
                nodes.push_back(new Node{ir.type, {ir.args[0]}});
                break;
            }
            case IRType::CALL: {
                auto lhs =
                    common_func_call(nodes, edges, ir.args[1], arg_stack);
                if (lhs != nullptr) {
                    lhs->val_list.push_back(ir.args[0]);
                } else {
                    lhs = new Node{ir.type, {ir.args[0]}, ir.args[1]};
                    for (auto arg : arg_stack) {
                        auto rhs = exist_or_insert(nodes, arg);
                        if (edges.find(lhs) == edges.end()) {
                            edges[lhs] = {rhs};
                        } else {
                            edges[lhs].push_back(rhs);
                        }
                    }
                    nodes.push_back(lhs);
                }
                arg_stack.clear();
                break;
            }
            /* Pure dependent nodes, we do not look for common
             * subexpression
             */
            case IRType::WRITE:
            case IRType::RET: {
                auto rhs = exist_or_insert(nodes, ir.args[0]);
                auto lhs = new Node{ir.type, {ir.args[0]}};
                nodes.push_back(lhs);
                if (edges.find(lhs) == edges.end()) {
                    edges[lhs] = {rhs};
                } else {
                    edges[lhs].push_back(rhs);
                }
                break;
            }
            case IRType::IF: {
                auto node = new Node{ir.type, {ir.args[1], ir.args[3]}};
                nodes.push_back(node);
                auto l_term = exist_or_insert(nodes, ir.args[0]);
                auto r_term = exist_or_insert(nodes, ir.args[2]);
                if (edges.find(node) == edges.end()) {
                    edges[node] = {l_term, r_term};
                } else {
                    edges[node].push_back(l_term);
                    edges[node].push_back(r_term);
                }
                break;
            }
        }
    }
    return {nodes, edges};
}

void draw_dag(IRList block, string output) {
    auto [nodes, edges] = gen_DAG(block);
    string res = "digraph {";
    for (auto node : nodes) {
        char buffer[2000];
        sprintf(buffer, "NODE_%x [label=\"%s\"]\n", node, node->str().c_str());
        res += buffer;
        if (edges.find(node) != edges.end()) {
            for (auto out : edges[node]) {
                sprintf(buffer, "NODE_%x -> NODE_%x;\n", node, out);
                res += buffer;
            }
        }
    }
    res += "}";
    ofstream fout(output, ios::out);
    fout << res;
}