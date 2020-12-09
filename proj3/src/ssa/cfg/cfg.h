#pragma once
#include <algorithm>
#include <fstream>
#include <set>
#include <vector>
#include "../dag/dag.h"
#include "../ir/ir.h"
IRList draw_cfg(IRList irs, std::string cfg_path, std::string dag_folder);
std::pair<std::vector<IRList>, std::vector<std::pair<int, int>>> gen_block(
    IRList irs);
std::vector<IRList> gen_function(IRList irs);
