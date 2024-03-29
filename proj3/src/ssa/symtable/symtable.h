#pragma once
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../../splc/ext/ce.h"
#include "type.h"
enum class EntryType { TYPE = 0, FUNC = 1, FIELD = 2 };
extern int CNT;
struct Entry {
    EntryType entry_type;
    int lineno;  // 行号
    int id;      // 区分不同层级的同名变量
    union {
        Type* type;
        Field* field;
        Func* func;
    };
    bool ref;
    Entry(Field* field, bool ref = true)
        : field(field),
          lineno(field->lineno),
          entry_type(EntryType::FIELD),
          id(CNT++),
          ref(ref) {}
    Entry(Func* func, int lineno)
        : func(func), lineno(lineno), entry_type(EntryType::FUNC), id(CNT++) {}
    Entry(Type* type, int lineno)
        : type(type), lineno(lineno), entry_type(EntryType::TYPE), id(CNT++) {}
    std::string original_name() {
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
    std::string name() {
        if (this->entry_type == EntryType::FIELD) {
            if (this->field->type->category != Category::PRIMITIVE && this->ref)
                return "&v_" + this->field->name + "_" + std::to_string(id);
            else
                return "v_" + this->field->name + "_" + std::to_string(id);
        } else if (this->entry_type == EntryType::FUNC)
            return "v_" + this->func->name + "_" + std::to_string(id);
        else if (this->entry_type == EntryType::TYPE &&
                 this->type->category == Category::STRUCT)
            return "v_" + this->type->structure->name + "_" +
                   std::to_string(id);
        else
            return "";
    }
};
typedef std::unordered_map<std::string, std::array<Entry*, 3>> SymTable;
void init();
void enter(Type* ret_type);
void exit();
void print_symtable();
void insert(Entry* entry);
std::string to_str(Func* func, int);
std::string to_str(Field* field, int);
std::string to_str(Struct* type, int);
std::string to_str(Type* type);
std::string temp_var();
std::string temp_label();
std::string temp_pointer();
Entry* lookup(std::string name, EntryType entry_type);
