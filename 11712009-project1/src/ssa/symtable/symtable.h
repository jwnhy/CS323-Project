#pragma once

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include "../../splc/ext/ce.h"
#include "type.h"
enum class EntryType { TYPE = 0, FUNC = 1, FIELD = 2 };
struct Entry {
    EntryType entry_type;
    union {
        Type* type;
        Field* field;
        Func* func;
    };
    Entry(Field* field) {
        this->entry_type = EntryType::FIELD;
        this->field = field;
    }
    Entry(Func* func) {
        this->entry_type = EntryType::FUNC;
        this->func = func;
    }
    Entry(Type* type) {
        this->entry_type = EntryType::TYPE;
        this->type = type;
    }
    std::string name() {
        if (this->entry_type == EntryType::FIELD)
            return this->field->name;
        else if (this->entry_type == EntryType::FUNC)
            return this->func->name;
        else if (this->entry_type == EntryType::TYPE &&
                 this->type->category == Category::STRUCT)
            return this->type->structure->name;
        else
            return "";
    }
};
typedef std::unordered_map<std::string, std::array<Entry*, 3>> SymTable;
void init();
void enter();
void exit();
void print_symtable();
void insert(Entry* field, int lineno);
Entry* lookup(std::string name);
