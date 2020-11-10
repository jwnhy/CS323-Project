#include "ssa.h"

void semantic_analysis(NODE* root) {
    visitor::program(root);
}