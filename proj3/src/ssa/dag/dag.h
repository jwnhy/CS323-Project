#pragma once
#include <algorithm>
#include <fstream>
#include <set>
#include <vector>
#include "../cfg/cfg.h"
#include "../ir/ir.h"
struct Node {
    IRType type() { return this->op; }
    bool contains(std::string val) {
        return find(this->val_list.begin(), this->val_list.end(), val) !=
               this->val_list.end();
    }
    std::string val() { return val_list[0]; }
    Node(IRType op,
         std::vector<std::string> val_list,
         std::string func_name = "")
        : op(op), val_list(val_list), func_name(func_name){};
    Node(std::vector<std::string> val_list)
        : op(IRType::NIR), val_list(val_list){};
    std::string str() {
        std::string res = to_str(op);
        res += "\n";
        for (auto val : val_list) {
            res += val;
            res += "\n";
        }
        return res;
    }
    IRType op;
    std::vector<std::string> val_list;
    std::string func_name;
};

std::pair<std::vector<Node*>, std::unordered_map<Node*, std::vector<Node*>>>
gen_DAG(IRList block);
void draw_dag(IRList block, std::string output);
IRList opt_DAG(IRList block);
IRList block_DAG(IRList block);
