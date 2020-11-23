#include "symtable.h"
using namespace std;
vector<pair<Type*, SymTable*>> scope_stack;
int CNT = 0;

void init() {
    scope_stack.clear();
    SymTable* global_table = new SymTable();
    scope_stack.push_back({NULL, global_table});
}

void enter(Type* ret_type) {
    scope_stack.push_back({ret_type, new SymTable()});
}

void exit() {
    scope_stack.pop_back();
}

void insert(Entry* entry) {
    SymTable* scope = scope_stack.back().second;
    string name;
    auto iter = scope->find(entry->name());
    if (iter == scope->end()) {
        array<Entry*, 3> entry_arr{0, 0, 0};
        entry_arr[(int)entry->entry_type] = entry;
        scope->insert({entry->name(), entry_arr});
    } else {
        auto& entry_arr = (*iter).second;
        if (entry_arr[(int)entry->entry_type] == NULL)
            entry_arr[(int)entry->entry_type] = entry;
        else {
            switch (entry->entry_type) {
                case EntryType::FIELD:
                    add_err(ErrorType::VAR_REDEF, entry->lineno,
                            "Variable Redefinition", "");
                    break;
                case EntryType::FUNC:
                    add_err(ErrorType::FUNC_REDEF, entry->lineno,
                            "Function Redefinition", "");
                    break;
                case EntryType::TYPE:
                    add_err(ErrorType::STRUCT_REDEF, entry->lineno,
                            "Structure Redefinition", "");
                    break;
            }
        }
    }
}

Entry* lookup(string name, EntryType entry_type) {
    for (auto scope_iter = scope_stack.end() - 1;
         scope_iter >= scope_stack.begin(); scope_iter--) {
        SymTable* scope = (*scope_iter).second;
        auto item = scope->find(name);
        if (item != scope->end() && item->second[(int)entry_type])
            return item->second[(int)entry_type];
    }
    return NULL;
}
string to_str(Type* type) {
    if (type->category == Category::PRIMITIVE) {
        if (type->primitive == Primitive::INT)
            return "INT";
        else if (type->primitive == Primitive::FLOAT)
            return "FLOAT";
        else if (type->primitive == Primitive::INT)
            return "CHAR";
        else if (type->primitive == Primitive::NEXP)
            return "NON-EXP";
        else
            return to_string(static_cast<int>(type->primitive));
    } else if (type->category == Category::STRUCT) {
        return "struct " + type->structure->name;
    } else {
        return to_str(type->array->base) + "[" + to_string(type->array->size) +
               "]";
    }
}

string to_str(Field* field, int indent = 0) {
    Type* type = field->type;
    string name = field->name;
    return string(indent, ' ') + to_str(type) + ": " + name + " (" +
           to_string(field->lineno) + ")";
}

string to_str(Struct* structure, int indent = 0) {
    string s = string(indent, ' ') + "struct " + structure->name + " {\n";
    for (auto f : structure->fields) {
        s = s + string(indent, ' ') + to_str(f, 2) + "\n";
    }
    s = s + string(indent, ' ') + "}";
    return s;
}

string to_str(Func* func, int indent = 0) {
    string s = string(indent, ' ') + to_str(func->ret) + " " + func->name + "(";
    for (auto f : func->params) {
        s = s + string(indent, ' ') + to_str(f) + ", ";
    }
    s = s + string(indent, ' ') + ")";
    return s;
}

void print_entry(Entry* entry, int indent = 0) {
    if (!entry)
        return;
    if (entry->entry_type == EntryType::FIELD) {
        cout << to_str(entry->field, indent);
    } else if (entry->entry_type == EntryType::TYPE) {
        cout << to_str(entry->type->structure, indent);
    } else {
        cout << to_str(entry->func, indent);
    }
    cout << "\n";
}

void print_symtable() {
    int indent = 0;
    for (auto t : scope_stack) {
        for (auto p : *t.second) {
            auto entry = p.second;
            print_entry(entry[0], indent);
            print_entry(entry[1], indent);
            print_entry(entry[2], indent);
        }
        indent += 2;
    }
}