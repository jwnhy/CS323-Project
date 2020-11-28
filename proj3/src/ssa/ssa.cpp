#include "ssa.h"

IRList semantic_analysis(NODE* root) {
    return visitor::program(root);
}