#pragma once
#include <string>
#include <vector>
#include "../../splc/gen/spl.tab.h"
enum class Category { PRIMITIVE, ARRAY, STRUCT };
enum class Primitive { FLOAT = FLOAT, INT = INT, CHAR = CHAR, NEXP = -1 };
struct Struct;
struct Field;
struct Array;
struct Type;
struct Func;
int _array_offset(Type* base, int idx);
int _struct_offset(Struct* s, int idx);
int _type_size(Type* type);
int _type_size(Primitive primitive);
int _type_size(Array* array);
int _type_size(Struct* structure);
struct Type {
    Category category;
    int size;
    union {
        Primitive primitive;
        Array* array;
        Struct* structure;
    };
    Type(Primitive primitive) {
        this->category = Category::PRIMITIVE;
        this->primitive = primitive;
        this->size = _type_size(primitive);
    };
    Type(Array* array) {
        this->category = Category::ARRAY;
        this->array = array;
        this->size = _type_size(array);
    };
    Type(Struct* structure) {
        this->category = Category::STRUCT;
        this->structure = structure;
        this->size = _type_size(structure);
    };
};

struct Array {
    Type* base;
    int size;
};

struct Struct {
    std::string name;
    std::vector<Field*> fields;
};

struct Field {
    std::string name;
    Type* type;
    int lineno;
};

struct Func {
    std::string name;
    std::vector<Field*> params;
    Type* ret;
};
