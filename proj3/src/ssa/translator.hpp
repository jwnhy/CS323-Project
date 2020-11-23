#pragma once
#include "../splc/ext/node.h"
#include "ir/ir.h"
#include "symtable/symtable.h"
struct translator {
    static void program() { IRList.push_back(IR{IRType::FUNCTION, {"main"}}); }
};