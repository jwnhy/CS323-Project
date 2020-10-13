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
        val_buf[val_len] = '\0';
        node->node_val = val_buf;
    } else {
        node->node_val = NULL;
    }
    node->lineno = lineno;
    node->type = type;
    node->name = name;

    node->child = NULL;
    node->brother = (NODE**)malloc(MAX_CHILD * (sizeof(NODE*)));
    node->brother_num = 0;
    return node;
}

void insert(NODE *parent, NODE *child)
{
    if (!parent->child)
        parent->child = child;
    else
        parent->brother[parent->brother_num++] = child;
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

    for (int i = 0; i < root->brother_num; i++) {
        print_tree(root->brother[i], indent + 2);
    }
}