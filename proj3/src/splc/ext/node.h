#pragma once
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gen/spl.tab.h"
#define MAX_CHILD 32
typedef struct NODE {
    char* node_val;
    const char* name;
    
    int lineno;
    int type;
    int rule;
    int child_num;

    struct NODE** children;
}NODE;

NODE *get_root();
void set_root(NODE* new_root);
void insert(NODE* parent, NODE* child);
void print_tree(NODE* root, int indent);
struct NODE* new_leaf(const char* name, const char* val, int type, int lineno);
struct NODE* new_node(const char* name, int rule, int type, int lineno);