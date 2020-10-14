#pragma once
#include "../../splc/ext/node.h"
#include "../symtable/symtable.h"

struct visitor {
    static void program(NODE* self) {
        init();
        ext_def_list(self->children[0]);
    }

    static void ext_def_list(NODE* self) {
        if (self && self->rule == 1) {
            ext_def(self->children[0]);
            ext_def_list(self->children[1]);
        }
    }

    static void ext_def(NODE* self) {
        Type* type = specifier(self->children[0]);
        if (self->rule == 1) {
            auto fields = ext_dec_list(self->children[1], type);
            for (auto field : fields) {
                insert(new Entry(field), self->lineno);
            }
        } else if (self->rule == 2 && type->category == Category::STRUCT) {
            insert(new Entry(type), self->lineno);
        } else if (self->rule == 3) {
            specifier(self->children[0]);
            fun_dec(self->children[1]);
            comp_st(self->children[2]);
        }
    }

    static void fun_dec(NODE* self) {}
    static void comp_st(NODE* self) {}

    static std::vector<Field*> ext_dec_list(NODE* self, Type* type) {
        Field* field = var_dec(self->children[0], type);
        auto head = std::vector<Field*>{field};
        if (self->rule == 2) {
            auto tail = ext_dec_list(self->children[2], type);
            head.insert(head.end(), tail.begin(), tail.end());
        }
        return head;
    }
    static Type* specifier(NODE* self) {
        if (self->rule == 1) {
            return type(self->children[0]);
        } else if (self->rule == 2) {
            return struct_specifier(self->children[0]);
        }
        return NULL;
    }
    static Type* struct_specifier(NODE* self) {
        Struct* structure = new Struct;
        structure->name = id(self->children[1]);

        if (self->rule == 1)
            structure->fields = def_list(self->children[3]);
        else if (self->rule == 2)
            structure->fields = std::vector<Field*>();

        return new Type(structure);
    }

    static std::vector<Field*> def_list(NODE* self) {
        auto head = std::vector<Field*>();
        if (self && self->rule == 1) {
            head = def(self->children[0]);
            auto tail = def_list(self->children[1]);
            head.insert(head.end(), tail.begin(), tail.end());
        }
        return head;
    }

    static std::vector<Field*> def(NODE* self) {
        Type* type = specifier(self->children[0]);
        return dec_list(self->children[1], type);
    }

    static std::vector<Field*> dec_list(NODE* self, Type* type) {
        Field* field = dec(self->children[0], type);
        auto head = std::vector<Field*>{field};
        if (self->rule == 2) {
            auto tail = dec_list(self->children[2], type);
            head.insert(head.end(), tail.begin(), tail.end());
        }
        return head;
    }

    static Field* dec(NODE* self, Type* type) {
        Field* field = var_dec(self->children[0], type);
        // TODO: Check validity.
        return field;
    }

    static Field* var_dec(NODE* self, Type* type) {
        if (self->rule == 1) {
            return new Field{self->children[0]->node_val, type};
        } else if (self->rule == 2) {
            return new Field{
                self->children[0]->node_val,
                new Type(new Array{type, _int(self->children[2])})};
        } else
            return NULL;
    }

    static Type* type(NODE* self) { return new Type((Primitive)self->type); }
    static std::string id(NODE* self) { return self->node_val; }
    static int _int(NODE* self) { return strtol(self->node_val, NULL, 10); }
};