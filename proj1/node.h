#pragma once
#include <stddef.h>
#include <stdlib.h>
typedef union {
    int int_val;
    float float_val;
    char char_val;
    char* string_val;
}NODE_VAL;
typedef struct NODE {
    NODE_VAL node_val;
    int lineno;
    int type;

    struct NODE* child;
    struct NODE* brother;
    int child_cnt;
}NODE;
void insert(NODE* parent, NODE* child);
struct NODE* new_node(NODE_VAL val, int type, int lineno);

