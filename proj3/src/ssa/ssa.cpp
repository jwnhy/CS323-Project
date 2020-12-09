#include "ssa.h"
using namespace std;
IRList semantic_analysis(NODE* root) {
    IRList irs = visitor::program(root);
    irs = opt_DAG(irs);
    irs = draw_cfg(irs, "figs/f.dot", "figs/dag/");
    return irs;
}