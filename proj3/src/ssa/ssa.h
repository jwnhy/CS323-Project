#pragma once
#include <fstream>
#include "cfg/cfg.h"
#include "dag/dag.h"
#include "symtable/symtable.h"
#include "visitor.hpp"
IRList semantic_analysis(NODE* root);