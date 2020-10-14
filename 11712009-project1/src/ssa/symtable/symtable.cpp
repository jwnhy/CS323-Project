#include "symtable.h"
using namespace std;
vector<SymTable*> scope_stack;
vector<SymTable*>::iterator stack_top;
void init() {
    scope_stack.clear();
    SymTable* global_table = new SymTable();
    scope_stack.push_back(global_table);

    stack_top = scope_stack.begin();
}

void enter() {
    scope_stack.push_back(new SymTable());
    stack_top++;
}

void exit() {
    stack_top--;
}

void insert(Entry* entry, int lineno) {
    SymTable* scope = *stack_top;
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
        else
            add_err(SEMANTIC, lineno, "Redefinition", "");
    }
}

Entry* lookup(string name, EntryType entry_type) {
    for (auto scope_iter = stack_top; scope_iter >= scope_stack.begin();
         scope_iter--) {
        SymTable* scope = *scope_iter;
        auto item = scope->find(name);
        if (item != scope->end())
            return item->second[(int)entry_type];
    }
    return nullptr;
}
string to_str(Type* type) {
    if (type->category == Category::PRIMITIVE) {
        if (type->primitive == Primitive::INT)
            return "INT";
        else if (type->primitive == Primitive::FLOAT)
            return "FLOAT";
        else
            return "CHAR";
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
    return string(indent, ' ') + to_str(type) + ": " + name;
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
        for (auto p : *t) {
            auto entry = p.second;
            print_entry(entry[0], indent);
            print_entry(entry[1], indent);
            print_entry(entry[2], indent);
        }
        indent += 2;
    }
}