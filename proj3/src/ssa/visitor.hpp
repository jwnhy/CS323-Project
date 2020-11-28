#pragma once
#include "../splc/ext/node.h"
#include "ir/ir.h"
#include "symtable/symtable.h"
const std::unordered_map<int, IRType> arithmetic_op{{PLUS, IRType::ADD},
                                                    {MINUS, IRType::SUB},
                                                    {MUL, IRType::MUL},
                                                    {DIV, IRType::DIV}};
const std::unordered_map<int, std::string> relation_op{
    {LT, "<"}, {LE, "<="}, {GT, ">"}, {GE, ">="}, {NE, "!="}, {EQ, "=="}};
struct visitor {
    static IRList _if_stmt(IRList irs,
                           std::string lhs,
                           std::string relop,
                           std::string rhs,
                           std::string lb_t,
                           std::string lb_f,
                           std::string ret = "") {
        if (ret != "") {
            auto l_1 = temp_label();
            auto l_2 = temp_label();
            irs.push_back(IR{IRType::ASSIGN, {ret, "#0"}});
            irs.push_back(IR{IRType::IF, {lhs, relop, rhs, l_1}});
            irs.push_back(IR{IRType::GOTO, {l_2}});
            irs.push_back(IR{IRType::LABEL, {l_1}});
            irs.push_back(IR{IRType::ASSIGN, {ret, "#1"}});
            irs.push_back(IR{IRType::LABEL, {l_2}});
        }
        if (lb_t != "") {
            irs.push_back(IR{IRType::IF, {lhs, relop, rhs, lb_t}});
            if (lb_f != "") {
                irs.push_back(IR{IRType::GOTO, {lb_f}});
            }
        }
        return irs;
    }
    static IRList extend(IRList irs_a, IRList irs_b) {
        irs_a.insert(irs_a.end(), irs_b.begin(), irs_b.end());
        return irs_a;
    }
    static IR trans_dec(Entry* entry) {
        auto type = entry->field->type;
        switch (type->category) {
            case Category::PRIMITIVE:
                return IR{IRType::ASSIGN, {entry->name(), "#0"}};
            case Category::ARRAY:
                return IR{
                    IRType::ALLOC,
                    {entry->name(), std::to_string(_type_size(type->array))}};
            case Category::STRUCT:
                return IR{IRType::ALLOC,
                          {entry->name(),
                           std::to_string(_type_size(type->structure))}};
        }
        return IR{};
    }
    static Type* _type_exist(Type* type, int lineno) {
        if (type->category == Category::STRUCT) {
            Entry* t = lookup(type->structure->name, EntryType::TYPE);
            if (t == NULL) {
                add_err(ErrorType::STRUCT_NO_DEF, lineno, "Type not exist",
                        type->structure->name.c_str());
                return NULL;
            }
            return t->type;
        }
        return NULL;
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
            return s1->array->size == s2->array->size &&
                   _is_equivalent(s1->array->base, s2->array->base);
        else
            return false;
        return true;
    }
    static IRList program(NODE* self) {
        init();
        return ext_def_list(self->children[0]);
    }

    static IRList ext_def_list(NODE* self) {
        if (self && self->rule == 1) {
            auto irs = ext_def(self->children[0]);
            return extend(irs, ext_def_list(self->children[1]));
        }
        return IRList();
    }

    static IRList ext_def(NODE* self) {
        Type* type = specifier(self->children[0]);
        if (self->rule == 1) {
            _type_exist(type, self->lineno);
            auto [fields, irs] = ext_dec_list(self->children[1], type);
            for (auto field : fields) {
                auto entry = new Entry(field);
                insert(entry);
                irs.push_back(trans_dec(entry));
            }
            return irs;
        } else if (self->rule == 2) {
            if (type->category == Category::STRUCT) {
                insert(new Entry(type, self->lineno));
            }
        } else if (self->rule == 3) {
            _type_exist(type, self->lineno);
            auto [func, irs_a] = fun_dec(self->children[1], type);
            insert(new Entry(func, self->lineno));
            auto irs_b = comp_st(self->children[2], type, func->params);
            return extend(irs_a, irs_b);
        }
        return IRList();
    }

    static std::pair<Func*, IRList> fun_dec(NODE* self, Type* ret_type) {
        std::string name = id(self->children[0]);
        IRList irs;
        auto param_list = std::vector<Field*>();
        if (self->rule == 1) {
            param_list = var_list(self->children[2]);
            irs.push_back(IR{IRType::FUNCTION, {name}});
            for (auto param : param_list) {
                _type_exist(param->type, param->lineno);
            }
        }
        return {new Func{name, param_list, ret_type}, irs};
    }

    static IRList comp_st(NODE* self,
                          Type* ret_type,
                          std::vector<Field*> params = std::vector<Field*>()) {
        IRList irs;
        enter(ret_type);
        for (auto param : params) {
            auto entry = new Entry(param);
            insert(entry);
            irs.push_back(IR{IRType::PARAM, {entry->name()}});
        }
        irs = extend(irs, def_list(self->children[1], true).second);
        irs = extend(irs, stmt_list(self->children[2], ret_type));
        exit();
        return irs;
    }

    static IRList stmt_list(NODE* self, Type* ret_type) {
        IRList irs;
        if (self && self->rule == 1) {
            irs = extend(irs, stmt(self->children[0], ret_type));
            irs = extend(irs, stmt_list(self->children[1], ret_type));
        }
        return irs;
    }

    static IRList stmt(NODE* self, Type* ret_type) {
        auto irs = IRList();
        auto c = self->children;
        auto lb_t = temp_label(), lb_f = temp_label(), lb_end = temp_label(),
             lb_start = temp_label();
        switch (self->rule) {
            case 1: {
                auto tp = exp(c[2], {lb_t, lb_f});
                irs = extend(irs, std::get<1>(tp));
                irs.push_back(IR{IRType::LABEL, {lb_t}});
                irs = extend(irs, stmt(c[4], ret_type));
                irs.push_back(IR{IRType::LABEL, {lb_f}});
                break;
            }
            case 2:
            case 8: {
                auto tp = exp(c[2], {lb_t, lb_f});
                irs = extend(irs, std::get<1>(tp));
                irs.push_back(IR{IRType::LABEL, {lb_t}});
                irs = extend(irs, stmt(c[4], ret_type));
                irs.push_back(IR{IRType::GOTO, {lb_end}});
                irs.push_back(IR{IRType::LABEL, {lb_f}});
                irs = extend(irs, stmt(c[6], ret_type));
                irs.push_back(IR{IRType::LABEL, {lb_end}});
                break;
            }
            case 3:
            case 9:
                exp(c[2]);
                exp(c[4]);
                exp(c[6]);
                stmt(c[8], ret_type);
                break;
            case 4:
            case 10: {
                auto tp = exp(c[2], {lb_t, lb_f});
                irs.push_back(IR{IRType::LABEL, {lb_start}});
                irs = extend(irs, std::get<1>(tp));
                irs.push_back(IR{IRType::LABEL, {lb_t}});
                irs = extend(irs, stmt(c[4], ret_type));
                irs.push_back(IR{IRType::GOTO, {lb_start}});
                irs.push_back(IR{IRType::LABEL, {lb_f}});
                break;
            }
            case 5:
                irs = extend(irs, std::get<1>(exp(c[0])));
                break;
            case 6:
                irs = extend(irs, comp_st(c[0], ret_type));
                break;
            case 7: {
                auto [ret, irs_1, t_1] = exp(c[1]);
                if (!_is_equivalent(ret->type, ret_type)) {
                    add_err(ErrorType::UNMATCH_RET, self->lineno,
                            "Invalid return type", "");
                }
                irs = extend(irs, irs_1);
                irs.push_back(IR{IRType::RET, {t_1}});
                break;
            }
            default:
                break;
        }
        return irs;
    }
    static std::tuple<Field*, IRList, std::string> exp(
        NODE* self,
        std::array<std::string, 2> lbs = {"", ""}) {
        auto c = self->children;
        auto default_exp =
            new Field{"NEXP", new Type(Primitive::NEXP), self->lineno};
        auto irs = IRList();
        auto [lb_t, lb_f] = lbs;
        switch (self->rule) {
            case 0:
                /* Null Exp */
                return {default_exp, irs, ""};
            case 1:
            case 2:
            case 3: {
                /* Init Part */
                auto [oprand_1, irs_1, t_1] = exp(c[0]);
                auto [oprand_2, irs_2, t_2] = exp(c[2]);
                /* SSA Part */
                auto category_1 = oprand_1->type->category;
                auto category_2 = oprand_2->type->category;
                if (category_1 != Category::PRIMITIVE ||
                    category_2 != Category::PRIMITIVE) {
                    add_err(ErrorType::UNMATCH_OP, self->lineno,
                            "Derived type can not be used in arithemetic "
                            "operator",
                            "");
                    return {default_exp, irs, ""};
                }
                auto primitive_1 = oprand_1->type->primitive;
                auto primitive_2 = oprand_2->type->primitive;
                if (primitive_1 == Primitive::CHAR ||
                    primitive_2 == Primitive::CHAR) {
                    add_err(ErrorType::UNMATCH_OP, self->lineno,
                            "CHAR type can not be used in arithmetic "
                            "operator",
                            "");
                    return {default_exp, irs, ""};
                }
                /* Translation Part */
                irs = extend(irs, irs_1);
                irs = extend(irs, irs_2);
                auto t = temp_var();
                if (arithmetic_op.find(c[1]->type) != arithmetic_op.end()) {
                    auto it = arithmetic_op.find(c[1]->type);
                    irs.push_back(IR{it->second, {t, t_1, t_2}});
                    irs = _if_stmt(irs, t, "!=", "#0", lb_t, lb_f);
                } else if (relation_op.find(c[1]->type) != relation_op.end()) {
                    auto it = relation_op.find(c[1]->type);
                    irs = _if_stmt(irs, t_1, it->second, t_2, lb_t, lb_f, t);
                }
                return {new Field{"RValue", new Type(*oprand_1->type),
                                  self->lineno},
                        irs, t};
            }
            case 4: {
                /* Init Part */
                auto [oprand_1, irs_1, t_1] = exp(c[0]);
                auto [oprand_2, irs_2, t_2] = exp(c[2]);
                /* SSA Part */
                if (oprand_1->name == "") {
                    add_err(ErrorType::RVAL_ON_LEFT, self->lineno,
                            "LHS of assignment is not a left value", "");
                }
                if (!_is_equivalent(oprand_1->type, oprand_2->type)) {
                    std::string msg =
                        to_str(oprand_1->type) + "!=" + to_str(oprand_2->type);
                    add_err(ErrorType::UNMATCH_ASS, self->lineno,
                            "Two sides of assignment are not of the "
                            "same type",
                            msg.c_str());
                }
                /* Translation Part */
                irs = extend(irs, irs_1);
                irs = extend(irs, irs_2);
                irs.push_back(IR{IRType::ASSIGN, {t_1, t_2}});
                irs = _if_stmt(irs, t_1, "!=", "#0", lb_t, lb_f);
                return {new Field{"", new Type(*oprand_1->type), self->lineno},
                        irs, t_1};
            }
            case 5:
            case 6: {
                /* Init Part */
                auto l = temp_label();
                std::tuple<Field*, IRList, std::string> tp_1, tp_2;
                if (c[1]->type == AND) {
                    tp_1 = exp(c[0], {l, lb_f});
                    tp_2 = exp(c[2], {lb_t, lb_f});
                } else {
                    tp_1 = exp(c[0], {lb_t, l});
                    tp_2 = exp(c[2], {lb_t, lb_f});
                }
                auto [oprand_1, irs_1, t_1] = tp_1;
                auto [oprand_2, irs_2, t_2] = tp_2;
                /* SSA Part */
                auto category_1 = oprand_1->type->category;
                auto category_2 = oprand_2->type->category;
                if (category_1 != Category::PRIMITIVE ||
                    category_2 != Category::PRIMITIVE) {
                    add_err(ErrorType::UNMATCH_OP, self->lineno,
                            "Derived type can not be used in boolean "
                            "operator",
                            "");
                    return {default_exp, irs, ""};
                }
                auto primitive_1 = oprand_1->type->primitive;
                auto primitive_2 = oprand_2->type->primitive;
                if (primitive_1 != Primitive::INT ||
                    primitive_2 != Primitive::INT) {
                    add_err(ErrorType::UNMATCH_OP, self->lineno,
                            "Only INT type can not be used in boolean "
                            "operator",
                            "");
                    return {default_exp, irs, ""};
                }
                /* Translation Part */
                irs = extend(irs, irs_1);
                irs.push_back(IR{IRType::LABEL, {l}});
                irs = extend(irs, irs_2);

                return {new Field{"", new Type(*oprand_1->type), self->lineno},
                        irs, t_1};
            }
            case 7:
            case 8: {
                /* Init Part */
                std::tuple<Field*, IRList, std::string> tp_1;
                if (self->rule == 8)
                    tp_1 = exp(c[0], {lb_f, lb_t});
                else {
                    tp_1 = exp(c[0]);
                }
                auto [oprand_1, irs_1, t_1] = tp_1;
                /* SSA Part */
                if (oprand_1->type->category != Category::PRIMITIVE) {
                    add_err(ErrorType::UNMATCH_OP, self->lineno,
                            "Derived type can not be used in negative "
                            "operator",
                            "");
                    return {default_exp, irs, ""};
                } else if (self->rule == 7 &&
                           oprand_1->type->primitive == Primitive::CHAR) {
                    add_err(ErrorType::UNMATCH_OP, self->lineno,
                            "CHAR type can not be used in negative "
                            "operator",
                            "");
                    return {default_exp, irs, ""};
                } else if (self->rule == 8 &&
                           oprand_1->type->primitive != Primitive::INT) {
                    add_err(ErrorType::UNMATCH_OP, self->lineno,
                            "Only INT type can be used in negative "
                            "operator",
                            "");
                    return {default_exp, irs, ""};
                }
                /* Translation Part */
                auto t = temp_var();
                if (self->rule == 7) {
                    irs = extend(irs, irs_1);
                    irs.push_back(IR{IRType::SUB, {t, "#0", t_1}});
                    irs = _if_stmt(irs, t_1, "!=", "#0", lb_t, lb_f);
                    return {
                        new Field{"", new Type(*oprand_1->type), self->lineno},
                        irs, t};
                } else if (self->rule == 8) {
                    irs = extend(irs, irs_1);
                    return {
                        new Field{"", new Type(*oprand_1->type), self->lineno},
                        irs, t_1};
                }
            }
            case 9:
            case 10: {
                /* Init Part */
                std::tuple<std::vector<std::pair<Field*, std::string>>, IRList>
                    tp_1;
                std::string func_name = id(c[0]);
                /* SSA Part */
                Entry* func_entry = lookup(func_name, EntryType::FUNC);
                if (func_entry == NULL) {
                    add_err(ErrorType::FUNC_NO_DEF, self->lineno,
                            "Function not found", func_name.c_str());
                    return {default_exp, irs, ""};
                }
                Func* func = func_entry->func;
                if (self->rule == 9) {
                    tp_1 = args(c[2]);
                }
                auto [arguments, irs_1] = tp_1;
                if (func->params.size() != arguments.size()) {
                    add_err(ErrorType::UNMATCH_PARAM, self->lineno,
                            "Argument number does not equal",
                            func_name.c_str());
                    return {
                        new Field{"NEXP", new Type(*func->ret), self->lineno},
                        irs, temp_var()};
                }
                for (int i = 0; i < arguments.size(); i++) {
                    if (!_is_equivalent(func->params[i]->type,
                                        arguments[i].first->type)) {
                        add_err(ErrorType::UNMATCH_PARAM, self->lineno,
                                "Argument type does not match",
                                func_name.c_str());
                        return {new Field{"NEXP", new Type(*func->ret),
                                          self->lineno},
                                irs, temp_var()};
                    }
                }
                /* Translation Part */
                irs = extend(irs, irs_1);
                for (auto arg = arguments.rbegin(); arg != arguments.rend();
                     arg++) {
                    irs.push_back(IR{IRType::ARG, {arg->second}});
                }
                auto t = temp_var();
                irs.push_back(IR{IRType::CALL, {t, func_entry->name()}});
                return {new Field{"", new Type(*func->ret), self->lineno}, irs,
                        t};
            }
            case 11: {
                /* Init Part */
                auto [field, irs_1, t_1] = exp(c[0]);
                auto [idx, irs_2, t_2] = exp(c[2]);
                /* SSA Part */
                if (field->type->category != Category::ARRAY) {
                    add_err(ErrorType::NON_ARR, self->lineno, "Not Array",
                            field->name.c_str());
                    return {default_exp, irs, ""};
                }
                Array* arr = field->type->array;
                if (idx->type->category != Category::PRIMITIVE ||
                    idx->type->primitive != Primitive::INT) {
                    add_err(ErrorType::NON_IDX, self->lineno, "Non-INT index",
                            field->name.c_str());
                    return {default_exp, irs, ""};
                }
                /* Translation Part */
                irs = extend(irs, irs_1);
                auto ret = temp_var(), t_idx = temp_var();
                int arr_size = _type_size(arr);
                irs.push_back(
                    IR{IRType::MUL, {t_2, std::to_string(arr_size), t_2}});
                irs.push_back(IR{IRType::ADD, {t_idx, t_1, t_2}});
                irs.push_back(IR{IRType::RDEREF, {ret, t_idx}});
                irs = _if_stmt(irs, ret, "!=", "#0", lb_t, lb_f);
                return {new Field{field->name + "[" + idx->name + "]",
                                  new Type(*arr->base), self->lineno},
                        irs, ret};
            }
            case 12: {
                /* Init Part */
                auto [s, irs_1, t_1](exp(c[0]));
                std::string field_name = id(c[2]);
                /* SSA Part */
                if (s->type->category != Category::STRUCT) {
                    add_err(ErrorType::NON_STRUCT, self->lineno,
                            "Not Structure", s->name.c_str());
                    return {default_exp, irs, ""};
                }
                auto fields = s->type->structure->fields;
                auto field_iter = std::find_if(
                    fields.begin(), fields.end(),
                    [field_name](Field* x) { return x->name == field_name; });
                if (field_iter == fields.end()) {
                    add_err(ErrorType::MEM_NO_DEF, self->lineno,
                            "Field not exist", field_name.c_str());
                    return {default_exp, irs, ""};
                }
                /* Translation Part */
                irs = extend(irs, irs_1);
                int offset = 0;
                for (auto f : fields) {
                    if (f->name == field_name)
                        break;
                    offset += _type_size(f->type);
                }
                auto ret = temp_var(), t_idx = temp_var();
                irs.push_back(
                    IR{IRType::ADD, {t_idx, t_1, std::to_string(offset)}});
                irs.push_back(IR{IRType::RDEREF, {ret, t_idx}});
                irs = _if_stmt(irs, ret, "!=", "#0", lb_t, lb_f);
                return {new Field{s->name + "." + field_name,
                                  new Type(*(*field_iter)->type),
                                  (*field_iter)->lineno},
                        irs, ret};
            }
            case 13: {
                auto [e, irs_1, t_1](exp(c[0]));
                irs = extend(irs, irs_1);
                irs = _if_stmt(irs, t_1, "!=", "#0", lb_t, lb_f);
                return {new Field{e->name, new Type(*(e->type)), e->lineno},
                        irs, t_1};
            }
            case 14: {
                std::string var_name = id(c[0]);
                Entry* var_entry = lookup(var_name, EntryType::FIELD);
                if (var_entry == NULL) {
                    add_err(ErrorType::VAR_NO_DEF, self->lineno,
                            "Variable not found in scope", var_name.c_str());
                    return {default_exp, irs, ""};
                }
                irs = _if_stmt(irs, var_entry->name(), "!=", "#0", lb_t, lb_f);
                return {new Field{var_name, new Type(*var_entry->field->type),
                                  var_entry->field->lineno},
                        irs, var_entry->name()};
            }
            case 15: {
                float x = atof(c[0]->node_val);
                int i = *(int*)(&x);
                irs = _if_stmt(irs, "#" + std::to_string(i), "!=", "#0", lb_t,
                               lb_f);
                return {new Field{"", new Type(Primitive::FLOAT), self->lineno},
                        irs, "#" + std::to_string(i)};
            }
            case 16: {
                int x;
                if (strlen(c[0]->node_val) == 3) {
                    x = c[0]->node_val[0];
                } else {
                    x = strtol(c[0]->node_val + 3, NULL, 16);
                }
                irs = _if_stmt(irs, "#" + std::to_string(x), "!=", "#0", lb_t,
                               lb_f);
                return {new Field{"", new Type(Primitive::CHAR), self->lineno},
                        irs, "#" + std::to_string(x)};
            }
            case 17: {
                irs = _if_stmt(irs, "#" + std::string(c[0]->node_val),
                               "!=", "#0", lb_t, lb_f);
                return {new Field{"", new Type(Primitive::INT), self->lineno},
                        irs, "#" + std::string(c[0]->node_val)};
            }
        }
        return {default_exp, irs, ""};
    }

    static std::tuple<std::vector<std::pair<Field*, std::string>>, IRList> args(
        NODE* self) {
        auto [e_1, irs_1, t_1] = exp(self->children[0]);
        std::vector<std::pair<Field*, std::string>> head = {{e_1, t_1}};
        if (self->rule == 2) {
            auto [tail, irs_2] = args(self->children[2]);
            head.insert(head.end(), tail.begin(), tail.end());
            irs_1 = extend(irs_1, irs_2);
        }
        return {head, irs_1};
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

    static std::pair<std::vector<Field*>, IRList> ext_dec_list(NODE* self,
                                                               Type* type) {
        Field* field = var_dec(self->children[0], type);
        auto head = std::vector<Field*>{field};
        if (self->rule == 2) {
            auto [tail, irs] = ext_dec_list(self->children[2], type);
            head.insert(head.end(), tail.begin(), tail.end());
        }
        return std::pair<std::vector<Field*>, IRList>(head, IRList());
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
            structure->fields = def_list(self->children[3]).first;
            for (auto repeat_f : _repeat_struct_field(structure->fields)) {
                add_err(ErrorType::MEM_REDEF, repeat_f->lineno,
                        "Repeated field name inside structure",
                        repeat_f->name.c_str());
            }
        }

        return new Type(structure);
    }

    static std::pair<std::vector<Field*>, IRList> def_list(
        NODE* self,
        bool insert_now = false) {
        auto head = std::vector<Field*>();
        if (self && self->rule == 1) {
            auto [vars, irs] = def(self->children[0]);
            for (int i = 0; i < vars.size(); i++) {
                auto [field, t] = vars[i];
                if (insert_now) {
                    auto entry = new Entry(field);
                    insert(entry);
                    irs.push_back(trans_dec(entry));
                    if (t != "") {
                        irs.push_back(IR{IRType::ASSIGN, {entry->name(), t}});
                    }
                }
            }
            auto [tail, irs_1] = def_list(self->children[1], insert_now);
            head.insert(head.end(), tail.begin(), tail.end());
            irs = extend(irs, irs_1);
            return {head, irs};
        }
        return {{}, {}};
    }

    static std::tuple<std::vector<std::pair<Field*, std::string>>, IRList> def(
        NODE* self) {
        Type* type = specifier(self->children[0]);
        Type* derived = _type_exist(type, self->lineno);
        if (derived == NULL)
            return dec_list(self->children[1], type);
        else
            return dec_list(self->children[1], derived);
    }

    static std::tuple<std::vector<std::pair<Field*, std::string>>, IRList>
    dec_list(NODE* self, Type* type) {
        auto [field, irs, t] = dec(self->children[0], type);
        auto head = std::vector<std::pair<Field*, std::string>>{{field, t}};
        if (self->rule == 2) {
            auto [tail, irs_1] = dec_list(self->children[2], type);
            head.insert(head.end(), tail.begin(), tail.end());
            irs = extend(irs, irs_1);
        }
        return {head, irs};
    }

    static std::tuple<Field*, IRList, std::string> dec(NODE* self, Type* type) {
        IRList irs;
        Field* field = var_dec(self->children[0], type);
        if (self->rule == 2) {
            auto [e, irs_1, t] = exp(self->children[2]);
            if (!_is_equivalent(e->type, type)) {
                add_err(ErrorType::UNMATCH_ASS, self->lineno,
                        "Two sides of assignment have inconsistent "
                        "type",
                        "");
            }
            Entry* entry = new Entry(field);
            insert(entry);
            irs = extend(irs, irs_1);
            return {field, irs, t};
        }
        return {field, irs, ""};
    }

    static Field* var_dec(NODE* self, Type* type) {
        if (self->rule == 1) {
            return new Field{self->children[0]->node_val, type, self->lineno};
        } else if (self->rule == 2) {
            return var_dec(self->children[0],
                           new Type(new Array{type, _int(self->children[2])}));
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