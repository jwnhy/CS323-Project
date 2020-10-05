#include "node.h"
NODE* new_node(NODE_VAL val, int type, int lineno) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->node_val = val;
    node->lineno = lineno;
    node->type = type;

    node->child_cnt = 0;
    node->child = NULL;
    node->brother = NULL;
    return node;
}

void insert(NODE* parent, NODE* child) {
    NODE* cur = parent->child;
    if(!cur) {
        parent->child = child;
        parent->child_cnt++;
    } else {
        while(!cur->brother)
            cur = cur->brother;
        cur->child = child;
        cur->child_cnt++;
    }
}