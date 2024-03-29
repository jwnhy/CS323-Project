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

struct Type {
    Category category;
    union {
        Primitive primitive;
        Array* array;
        Struct* structure;
    };
    Type(Primitive primitive) {
        this->category = Category::PRIMITIVE;
        this->primitive = primitive;
    };
    Type(Array* array) {
        this->category = Category::ARRAY;
        this->array = array;
    };
    Type(Struct* structure) {
        this->category = Category::STRUCT;
        this->structure = structure;
    };
};

struct Array {
    struct Type* base;
    int size;
};

struct Struct {
    std::string name;
    std::vector<Field*> fields;
};

struct Field {
    std::string name;
    struct Type* type;
    int lineno;
};

struct Func {
    std::string name;
    std::vector<Field*> params;
    Type* ret;
};