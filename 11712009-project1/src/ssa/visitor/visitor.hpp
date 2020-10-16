#pragma once
#include "../../splc/ext/node.h"
#include "../symtable/symtable.h"

struct visitor {
    static void _type_exist(Type* type, int lineno) {
        if (type->category == Category::STRUCT &&
            lookup(type->structure->name, EntryType::TYPE) == NULL) {
            add_err(SEMANTIC, lineno, "Type not exist",
                    type->structure->name.c_str());
            return;
        }
    }
    static std::vector<Field*> _repeat_struct_field(
        std::vector<Field*> fields) {
        std::unordered_set<std::string> s;
        std::vector<Field*> res{};
        for (auto f : fields) {
            if (s.find(f->name) != s.end()) {
                res.push_back(f);
            }
            s.insert(f->name);
        }
        return res;
    }
    static bool _is_equivalent(Type* s1, Type* s2) {
        if (s1->category == Category::PRIMITIVE &&
            s2->category == Category::PRIMITIVE) {
            return s1->primitive == s2->primitive;
        } else if (s1->category == Category::STRUCT &&
                   s2->category == Category::STRUCT) {
            auto fields_1 = s1->structure->fields;
            auto fields_2 = s2->structure->fields;
            if (fields_1.size() == fields_2.size()) {
                int s = fields_1.size();
                for (int i = 0; i < s; i++) {
                    if (!_is_equivalent(fields_1[i]->type, fields_2[i]->type))
                        return false;
                }
            } else
                return false;
        } else if (s1->category == Category::ARRAY &&
                   s2->category == Category::ARRAY)
            return _is_equivalent(s1->array->base, s2->array->base) &&
                   s1->array->size == s2->array->size;
        else
            return false;
        return true;
    }
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
            _type_exist(type, self->lineno);
            auto fields = ext_dec_list(self->children[1], type);
            for (auto field : fields) {
                insert(new Entry(field));
            }
        } else if (self->rule == 2) {
            Type* type = specifier(self->children[0]);
            if (type->category == Category::STRUCT) {
                insert(new Entry(type, self->lineno));
            }
        } else if (self->rule == 3) {
            _type_exist(type, self->lineno);
            Func* func = fun_dec(self->children[1], type);
            insert(new Entry(func, self->lineno));
            comp_st(self->children[2], type, func->params);
        }
    }

    static Func* fun_dec(NODE* self, Type* ret_type) {
        std::string name = id(self->children[0]);
        auto param_list = std::vector<Field*>();
        if (self->rule == 1) {
            param_list = var_list(self->children[2]);
            for (auto param : param_list)
                _type_exist(param->type, param->lineno);
        }
        return new Func{name, param_list, ret_type};
    }

    static void comp_st(NODE* self,
                        Type* ret_type,
                        std::vector<Field*> params = std::vector<Field*>()) {
        enter(ret_type);
        for (auto param : params) {
            insert(new Entry(param));
        }
        def_list(self->children[1], true);
        stmt_list(self->children[2], ret_type);
        exit();
    }

    static void stmt_list(NODE* self, Type* ret_type) {
        if (self && self->rule == 1) {
            stmt(self->children[0], ret_type);
            stmt_list(self->children[1], ret_type);
        }
    }

    static void stmt(NODE* self, Type* ret_type) {
        auto c = self->children;
        switch (self->rule) {
            case 1:
                exp(c[2]);
                stmt(c[4], ret_type);
                break;
            case 2:
            case 8:
                exp(c[2]);
                stmt(c[4], ret_type);
                stmt(c[6], ret_type);
                break;
            case 3:
            case 9:
                exp(c[2]);
                exp(c[4]);
                exp(c[6]);
                stmt(c[8], ret_type);
                break;
            case 4:
            case 10:
                exp(c[2]);
                stmt(c[4], ret_type);
                break;
            case 5:
                exp(c[0]);
                break;
            case 6:
                comp_st(c[0], ret_type);
                break;
            case 7: {
                Field* ret = exp(c[1]);
                if (!_is_equivalent(ret->type, ret_type)) {
                    add_err(SEMANTIC, self->lineno, "Invalid return type", "");
                }
                break;
            }
            default:
                break;
        }
    }
    static Field* exp(NODE* self) {
        auto c = self->children;
        auto default_exp =
            new Field{"Exp", new Type(Primitive::INT), self->lineno};
        switch (self->rule) {
            case 0:
                /* Null Exp */
                return default_exp;
            case 1:
            case 2:
            case 3: {
                auto oprand_1 = exp(c[0]);
                auto oprand_2 = exp(c[2]);
                auto category_1 = oprand_1->type->category;
                auto category_2 = oprand_2->type->category;
                if (category_1 != Category::PRIMITIVE ||
                    category_2 != Category::PRIMITIVE) {
                    add_err(
                        SEMANTIC, self->lineno,
                        "Derived type can not be used in arithemetic operator",
                        "");
                    return default_exp;
                }
                auto primitive_1 = oprand_1->type->primitive;
                auto primitive_2 = oprand_2->type->primitive;
                if (primitive_1 == Primitive::CHAR ||
                    primitive_2 == Primitive::CHAR) {
                    add_err(SEMANTIC, self->lineno,
                            "CHAR type can not be used in arithmetic operator",
                            "");
                    return default_exp;
                }
                return new Field{"Exp", new Type(*oprand_1->type),
                                 self->lineno};
            }
            case 4: {
                auto oprand_1 = exp(c[0]);
                auto oprand_2 = exp(c[2]);
                if (!_is_equivalent(oprand_1->type, oprand_2->type)) {
                    std::string msg =
                        to_str(oprand_1->type) + "!=" + to_str(oprand_2->type);
                    add_err(SEMANTIC, self->lineno,
                            "Two sides of assignment are not of the same type",
                            msg.c_str());
                }
                return new Field{"Exp", new Type(*oprand_1->type),
                                 self->lineno};
            }
            case 5:
            case 6: {
                auto oprand_1 = exp(c[0]);
                auto oprand_2 = exp(c[2]);
                auto category_1 = oprand_1->type->category;
                auto category_2 = oprand_2->type->category;
                if (category_1 != Category::PRIMITIVE ||
                    category_2 != Category::PRIMITIVE) {
                    add_err(SEMANTIC, self->lineno,
                            "Derived type can not be used in boolean operator",
                            "");
                    return default_exp;
                }
                auto primitive_1 = oprand_1->type->primitive;
                auto primitive_2 = oprand_2->type->primitive;
                if (primitive_1 != Primitive::INT ||
                    primitive_2 != Primitive::INT) {
                    add_err(SEMANTIC, self->lineno,
                            "Only INT type can not be used in boolean operator",
                            "");
                    return default_exp;
                }
                return new Field{"Exp", new Type(*oprand_1->type),
                                 self->lineno};
            }
            case 7:
            case 8: {
                auto oprand = exp(c[1]);
                if (oprand->type->category != Category::PRIMITIVE) {
                    add_err(SEMANTIC, self->lineno,
                            "Derived type can not be used in negative operator",
                            "");
                    return default_exp;
                } else if (self->rule == 7 &&
                           oprand->type->primitive == Primitive::CHAR) {
                    add_err(SEMANTIC, self->lineno,
                            "CHAR type can not be used in negative operator",
                            "");
                    return default_exp;
                } else if (self->rule == 8 &&
                           oprand->type->primitive != Primitive::INT) {
                    add_err(SEMANTIC, self->lineno,
                            "Only INT type can be used in negative operator",
                            "");
                    return default_exp;
                }
                return new Field{"Exp", new Type(*oprand->type), self->lineno};
            }
            case 9:
            case 10: {
                std::string func_name = id(c[0]);
                Entry* func_entry = lookup(func_name, EntryType::FUNC);
                if (func_entry == NULL) {
                    add_err(SEMANTIC, self->lineno, "Function not found",
                            func_name.c_str());
                    return default_exp;
                }
                Func* func = func_entry->func;
                std::vector<Field*> arguments{};
                if (self->rule == 9)
                    arguments = args(c[2]);
                if (func->params.size() != arguments.size()) {
                    add_err(SEMANTIC, self->lineno,
                            "Argument number does not equal",
                            func_name.c_str());
                    return new Field{"Exp", new Type(*func->ret), self->lineno};
                }
                for (int i = 0; i < arguments.size(); i++) {
                    if (!_is_equivalent(func->params[i]->type,
                                        arguments[i]->type)) {
                        add_err(SEMANTIC, self->lineno,
                                "Argument type does not match",
                                func_name.c_str());
                        return new Field{"Exp", new Type(*func->ret),
                                         self->lineno};
                    }
                }
                return new Field{"Exp", new Type(*func->ret), self->lineno};
            }
            case 11: {
                std::string array_name = id(c[0]);
                Entry* array_entry = lookup(array_name, EntryType::FIELD);
                if (array_entry == NULL) {
                    add_err(SEMANTIC, self->lineno, "Variable not found",
                            array_name.c_str());
                    return default_exp;
                }
                if (array_entry->field->type->category != Category::ARRAY) {
                    add_err(SEMANTIC, self->lineno, "Not Array",
                            array_name.c_str());
                    return default_exp;
                }
                Array* arr = array_entry->field->type->array;
                Field* idx = exp(c[2]);
                if (idx->type->category != Category::PRIMITIVE ||
                    idx->type->primitive != Primitive::INT) {
                    add_err(SEMANTIC, self->lineno, "Non-INT index",
                            array_name.c_str());
                    return default_exp;
                }
                return new Field{"Exp", new Type(*arr->base), self->lineno};
            }
            case 12: {
                Field* s = exp(c[0]);
                std::string field_name = id(c[2]);
                if (s->type->category != Category::STRUCT) {
                    add_err(SEMANTIC, self->lineno, "Not Structure",
                            s->name.c_str());
                    return default_exp;
                }
                auto fields = s->type->structure->fields;
                auto field_iter = std::find_if(
                    fields.begin(), fields.end(),
                    [field_name](Field* x) { return x->name == field_name; });
                if (field_iter == fields.end()) {
                    add_err(SEMANTIC, self->lineno, "Field not exist",
                            field_name.c_str());
                    return default_exp;
                }
                return new Field{"Exp", new Type(*(*field_iter)->type),
                                 (*field_iter)->lineno};
            }
            case 13: {
                auto e = exp(c[1]);
                return new Field{"Exp", new Type(*(e->type)), e->lineno};
            }
            case 14: {
                std::string var_name = id(c[0]);
                Entry* var_entry = lookup(var_name, EntryType::FIELD);
                if (var_entry == NULL) {
                    add_err(SEMANTIC, self->lineno,
                            "Variable not found in scope", var_name.c_str());
                    return default_exp;
                }
                return new Field{*var_entry->field};
            }
            case 15: {
                return new Field{"Exp", new Type(Primitive::FLOAT),
                                 self->lineno};
            }
            case 16: {
                return new Field{"Exp", new Type(Primitive::CHAR),
                                 self->lineno};
            }
            case 17: {
                return new Field{"Exp", new Type(Primitive::INT), self->lineno};
            }
        }
        return default_exp;
    }

    static std::vector<Field*> args(NODE* self) {
        Field* e = exp(self->children[0]);
        auto head = std::vector<Field*>{e};
        if (self->rule == 2) {
            auto tail = args(self->children[2]);
            head.insert(head.end(), tail.begin(), tail.end());
        }
        return head;
    }

    static std::vector<Field*> var_list(NODE* self) {
        Field* field = param_dec(self->children[0]);
        auto head = std::vector<Field*>{field};
        if (self->rule == 2) {
            auto tail = var_list(self->children[2]);
            head.insert(head.end(), tail.begin(), tail.end());
        }
        return head;
    }

    static Field* param_dec(NODE* self) {
        Type* type = specifier(self->children[0]);
        return var_dec(self->children[1], type);
    }

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
        structure->fields = std::vector<Field*>();

        if (self->rule == 1) {
            structure->fields = def_list(self->children[3]);

            for (auto repeat_f : _repeat_struct_field(structure->fields)) {
                add_err(SEMANTIC, repeat_f->lineno,
                        "Repeated field name inside structure",
                        repeat_f->name.c_str());
            }
        }

        return new Type(structure);
    }

    static std::vector<Field*> def_list(NODE* self, bool insert_now = false) {
        auto head = std::vector<Field*>();
        if (self && self->rule == 1) {
            head = def(self->children[0]);
            for (int i = 0; i < head.size() && insert_now; i++) {
                insert(new Entry(head[i]));
            }
            auto tail = def_list(self->children[1]);
            head.insert(head.end(), tail.begin(), tail.end());
        }
        return head;
    }

    static std::vector<Field*> def(NODE* self) {
        Type* type = specifier(self->children[0]);
        _type_exist(type, self->lineno);
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
        if (self->rule == 2) {
            Field* e = exp(self->children[2]);
            if (!_is_equivalent(e->type, type)) {
                add_err(SEMANTIC, self->lineno,
                        "Two sides of assignment have inconsistent type", "");
            }
        }
        return field;
    }

    static Field* var_dec(NODE* self, Type* type) {
        if (self->rule == 1) {
            return new Field{self->children[0]->node_val, type, self->lineno};
        } else if (self->rule == 2) {
            return new Field{self->children[0]->node_val,
                             new Type(new Array{type, _int(self->children[2])}),
                             self->lineno};
        } else
            return NULL;
    }

    static Type* type(NODE* self) {
        if (self->type == TYPE) {
            if (std::string(self->node_val) == "int")
                return new Type(Primitive::INT);
            else if (std::string(self->node_val) == "float")
                return new Type(Primitive::FLOAT);
            else if (std::string(self->node_val) == "char")
                return new Type(Primitive::CHAR);
        }
        return new Type((Primitive)self->type);
    }
    static std::string id(NODE* self) { return self->node_val; }
    static int _int(NODE* self) { return strtol(self->node_val, NULL, 10); }
};