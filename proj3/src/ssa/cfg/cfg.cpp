#include "cfg.h"
using namespace std;

pair<set<string>, set<string>> val_analysis(IRList irs) {
    set<string> lval, rval;
    for (auto ir : irs) {
        switch (ir.type) {
            case IRType::ADD:
            case IRType::SUB:
            case IRType::MUL:
            case IRType::DIV: {
                lval.insert(ir.args[0]);
                rval.insert(ir.args[1]);
                rval.insert(ir.args[2]);
                break;
            }
            case IRType::RDEREF:
            case IRType::ASSIGN: {
                lval.insert(ir.args[0]);
                rval.insert(ir.args[1]);
                break;
            }
            case IRType::IF: {
                rval.insert(ir.args[0]);
                rval.insert(ir.args[2]);
                break;
            }
            case IRType::LDEREF: {
                rval.insert(ir.args[0]);
                rval.insert(ir.args[1]);
                break;
            }
            case IRType::RET:
            case IRType::GOTO:
            case IRType::ARG:
            case IRType::WRITE: {
                rval.insert(ir.args[0]);
                break;
            }
            default:
                break;
        }
    }

    return {lval, rval};
}

vector<IRList> gen_function(IRList irs) {
    vector<IRList> functions;
    vector<IRList::const_iterator> leaders;
    for (auto ir = irs.cbegin(); ir != irs.cend(); ir++) {
        switch ((*ir).type) {
            case IRType::FUNCTION:
                leaders.push_back(ir);
                break;
        }
    }
    leaders.push_back(irs.end());
    for (auto iiter = leaders.begin(); iiter != leaders.end() - 1; iiter++) {
        if (*iiter == *(iiter + 1))
            continue;
        IRList block(*iiter, *(iiter + 1));
        functions.push_back(block);
    }
    for (auto f = functions.begin(); f < functions.end(); f++) {
        int last_size = 0;
        while (last_size != (*f).size()) {
            last_size = (*f).size();
            auto [lval, rval] = val_analysis(*f);
            set<string> dead_val;
            set_difference(lval.begin(), lval.end(), rval.begin(), rval.end(),
                           std::inserter(dead_val, dead_val.end()));
            for (auto ir_iter = (*f).begin(); ir_iter < (*f).end(); ir_iter++) {
                for (auto arg : ir_iter->args) {
                    if (arg[0] != '#' && dead_val.find(arg) != dead_val.end()) {
                        ir_iter = (*f).erase(ir_iter);
                        break;
                    }
                }
            }
        }
    }
    return functions;
}
pair<vector<IRList>, vector<pair<int, int>>> gen_block(IRList irs) {
    vector<pair<int, int>> edges;
    vector<IRList> blocks;
    vector<IRList::const_iterator> leaders;
    leaders.push_back(irs.begin());
    for (auto ir = irs.cbegin(); ir != irs.cend(); ir++) {
        switch ((*ir).type) {
            case IRType::LABEL:
                leaders.push_back(ir);
                break;
            case IRType::IF:
            case IRType::GOTO:
                leaders.push_back(ir + 1);
                break;
        }
    }
    leaders.push_back(irs.end());
    for (auto iiter = leaders.begin(); iiter != leaders.end() - 1; iiter++) {
        if (*iiter == *(iiter + 1))
            continue;
        IRList block(*iiter, *(iiter + 1));
        blocks.push_back(block);
    }
    for (auto block = blocks.begin(); block != blocks.end(); block++) {
        IR first_ir = *(*block).begin();
        IR last_ir = *(*block).rbegin();
        int s = distance(blocks.begin(), block);
        switch (last_ir.type) {
            case IRType::GOTO: {
                auto end = find_if(blocks.begin(), blocks.end(), [=](IRList x) {
                    return x.begin()->type == IRType::LABEL &&
                           x.begin()->args[0] == last_ir.args[0];
                });
                int e = distance(blocks.begin(), end);
                edges.push_back({s, e});
                break;
            }
            case IRType::IF: {
                auto end = find_if(blocks.begin(), blocks.end(), [=](IRList x) {
                    return x.begin()->type == IRType::LABEL &&
                           x.begin()->args[0] == last_ir.args[3];
                });
                int e = distance(blocks.begin(), end);
                edges.push_back({s, e});
                /* Deliberately Fallthrough */
            }
            default:
                if (last_ir.type != IRType::RET)
                    edges.push_back({s, s + 1});
        }
    }
    return {blocks, edges};
}

string to_str(IRList irs) {
    string res = "";
    for (auto ir : irs) {
        res += ir.str() + "\n";
    }
    return res;
}

IRList draw_cfg(IRList irs, string cfg_path, string dag_folder) {
    string res = "digraph {";
    auto funcs = gen_function(irs);
    int fcnt = 0;
    int bcnt = 0;
    for (auto func : funcs) {
        int offset = bcnt;
        res += "subgraph cluster_" + to_string(fcnt) + " {";
        auto [blocks, edges] = gen_block(func);
        char buffer[2000];
        for (auto block : blocks) {
            draw_dag(block, dag_folder + "BLOCK_" + to_string(bcnt) + ".dot");
            sprintf(buffer, "BLOCK_%d [label=\"%s\"]\n", bcnt,
                    to_str(block).c_str());
            res += buffer;
            bcnt++;
        }
        for (auto edge : edges) {
            sprintf(buffer, "BLOCK_%d -> BLOCK_%d;\n", offset + edge.first,
                    offset + edge.second);
            res += buffer;
        }
        res += "}";
        fcnt++;
    }
    res += "}";
    ofstream fout(cfg_path, ios::out);
    fout << res;
    IRList final_irs = {};
    for (auto func : funcs) {
        final_irs = extend(final_irs, func);
    }
    return final_irs;
}