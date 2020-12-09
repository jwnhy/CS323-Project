#include "ir.h"
using namespace std;
IRList extend(IRList irs_a, IRList irs_b) {
    irs_a.insert(irs_a.end(), irs_b.begin(), irs_b.end());
    return irs_a;
}
string to_str(IRType type) {
    switch (type) {
        case IRType::LABEL:
            return "LABEL";
        case IRType::FUNCTION:
            return "FUNCTION";
        case IRType::ASSIGN:
            return "ASSIGN";
        case IRType::ADD:
            return "ADD";
        case IRType::SUB:
            return "SUB";
        case IRType::MUL:
            return "MUL";
        case IRType::DIV:
            return "DIV";
        case IRType::REF:
            return "REF";
        case IRType::RDEREF:
            return "RDEREF";
        case IRType::LDEREF:
            return "LDEREF";
        case IRType::GOTO:
            return "GOTO";
        case IRType::IF:
            return "IF";
        case IRType::RET:
            return "RET";
        case IRType::ALLOC:
            return "ALLOC";
        case IRType::PARAM:
            return "PARAM";
        case IRType::ARG:
            return "ARG";
        case IRType::CALL:
            return "CALL";
        case IRType::READ:
            return "READ";
        case IRType::WRITE:
            return "WRITE";
        default:
            return "NIR";
    }
}
