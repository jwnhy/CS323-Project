#pragma once
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spl.tab.h"
typedef struct NODE {
    char* node_val;
    int lineno;
    int type;
    char* name;

    struct NODE* child;
    struct NODE* brother;
}NODE;
void insert(NODE* parent, NODE* child);
void print_tree(NODE* root, int indent);
struct NODE* new_node(char* name, char* val, int type, int lineno);

