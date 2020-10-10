#pragma once
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gen/spl.tab.h"
typedef struct NODE {
    char* node_val;
    int lineno;
    int type;
    const char* name;

    struct NODE* child;
    struct NODE* brother;
}NODE;
void insert(NODE* parent, NODE* child);
void print_tree(NODE* root, int indent);
struct NODE* new_node(const char* name, const char* val, int type, int lineno);

