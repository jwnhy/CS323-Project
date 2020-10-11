#include "node.h"
NODE *new_node(const char *name,const char *val, int type, int lineno)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (val)
    {
        char *val_buf;
        int val_len = strlen(val) + 1;
        val_buf = (char *)malloc(sizeof(char) * val_len);
        strncpy(val_buf, val, val_len);
        node->node_val = val_buf;
    } else {
        node->node_val = NULL;
    }
    node->lineno = lineno;
    node->type = type;
    node->name = name;

    node->child = NULL;
    node->brother = NULL;
    return node;
}

void insert(NODE *parent, NODE *child)
{
    NODE *cur = parent->child;
    if (!cur)
        parent->child = child;
    else
    {
        while (cur->brother)
            cur = cur->brother;
        cur->brother = child;
    }
}

void print_node(NODE *node, int indent)
{
    printf("%*s", indent, "");
    if (node->type == NON_TER)
        printf("%s (%d)", node->name, node->lineno);
    else if (node->type == TYPE || node->type == INT || node->type == FLOAT || node->type == ID)
        printf("%s: %s", node->name, node->node_val);
    else if (node->type == CHAR) 
        printf("%s: %s", node->name, node->node_val);
    else if (node->type != EMPTY)
        printf("%s", node->name);
    else
        return;
    printf("\n");
    fflush(stdout);
}

void print_tree(NODE *root, int indent)
{
    if (!root)
        return;
    print_node(root, indent);

    NODE *child = root->child;
    print_tree(child, indent + 2);

    NODE *brother = root->brother;
    print_tree(brother, indent);
}