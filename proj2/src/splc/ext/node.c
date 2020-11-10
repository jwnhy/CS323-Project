#include "node.h"
NODE *root;

void set_root(NODE *new_root)
{
    root = new_root;
}

NODE *get_root()
{
    return root;
}

NODE *new_leaf(const char *name, char const *const val, int type, int lineno)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    char *val_buf;
    int val_len = strlen(val) + 1;
    val_buf = (char *)malloc(sizeof(char) * val_len);
    strncpy(val_buf, val, val_len);
    val_buf[val_len] = '\0';
    node->node_val = val_buf;

    node->rule = 0;
    node->lineno = lineno;
    node->type = type;
    node->name = name;

    node->children = (NODE **)malloc(MAX_CHILD * (sizeof(NODE *)));
    node->child_num = 0;
    return node;
}

NODE *new_node(const char *name, int rule, int type, int lineno)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->rule = rule;
    node->lineno = lineno;
    node->type = type;
    node->name = name;

    node->children = (NODE **)malloc(MAX_CHILD * (sizeof(NODE *)));
    node->child_num = 0;
    return node;
}

void insert(NODE *parent, NODE *child)
{   
    parent->children[parent->child_num++] = child;
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

    for (int i = 0; i < root->child_num; i++)
        print_tree(root->children[i], indent + 2);
}