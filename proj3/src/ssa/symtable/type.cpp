#include "type.h"
int _type_size(Type* type) {
    switch (type->category) {
        case Category::ARRAY:
            return _type_size(type->array);
        case Category::PRIMITIVE:
            return _type_size(type->primitive);
        case Category::STRUCT:
            return _type_size(type->structure);
    }
    return 0;
}
int _type_size(Primitive primitive) {
    if (primitive == Primitive::CHAR)
        return 2;
    else
        return 4;
}
int _type_size(Array* array) {
    return _type_size(array->base) * array->size;
}
int _type_size(Struct* structure) {
    int sum = 0;
    for (auto member : structure->fields)
        sum += _type_size(member->type);
    return sum;
}