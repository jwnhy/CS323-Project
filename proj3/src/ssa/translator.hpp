#pragma once
#include "../splc/ext/node.h"
#include "ir/ir.h"
#include "symtable/symtable.h"
struct translator {
    static int _type_size(Type *s) {
        if (s->category == Category::PRIMITIVE) {
            if (s->primitive == Primitive::CHAR)
                return 2;
            else
                return 4;
        } 
        else if(s->category == Category::ARRAY)
            return _type_size(s->array->base) * s->array->size;
        else if (s->category == Category::STRUCT) {
            int sum = 0;
            for (auto member: s->structure->fields)
                sum += _type_size(member->type);
            return sum;
        }
    }
    static void program() { IRList.push_back(IR{IRType::FUNCTION, {"main"}}); }
    static void func_dec(Func *func) {
        IRList.push_back(IR{IRType::FUNCTION, {func->name}});
        for (auto param : func->params) {
            IRList.push_back(IR{IRType::PARAM, {param->name}});
        }
    }
    static void dec(Entry *entry) {
        if (entry->entry_type != EntryType::FIELD) {
            std::cout << "NOT A FIELD";
        }
        switch (entry->field->type->category) {
            case Category::PRIMITIVE:
                break;                  // No action for primitive
            case Category::ARRAY:
                IRList.push_back(IR{IRType::ALLOC, {entry->name(), std::to_string(_type_size(entry->field->type))}});
            case Category::STRUCT:
                IRList.push_back(IR{IRType::ALLOC, {entry->name(), std::to_string(_type_size(entry->field->type))}});
        }
    }
    static void assign(Entry *lhs, int i) {
        IRList.push_back(IR{IRType::ASSIGN, {lhs->name(), "#"+std::to_string(i)}});
    }
    static void assign(Entry *lhs, float f) {
        IRList.push_back(IR{IRType::ASSIGN, {lhs->name(), "#"+std::to_string(*(int*)(&f))}});
    }
    static void assign(Entry *lhs, char c) {
        IRList.push_back(IR{IRType::ASSIGN, {lhs->name(), "#"+std::to_string((int)c)}});
    }
    static void assign(Entry *lhs, Entry *rhs) {

    }
};