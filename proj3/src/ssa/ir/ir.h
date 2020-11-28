#pragma once
#include <string>
#include <vector>
struct IR;
enum class IRType;
typedef std::vector<IR> IRList;
enum class IRType {
    LABEL,
    FUNCTION,
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    REF,
    RDEREF,
    LDEREF,
    GOTO,
    IF,
    RET,
    ALLOC,
    PARAM,
    ARG,
    CALL,
    READ,
    WRITE,
};
struct IR {
    IRType type;
    std::vector<std::string> args;
    std::string str() {
        switch (type) {
            case IRType::LABEL:
                return "LABEL " + args[0] + " :";
            case IRType::FUNCTION:
                return "FUNCTION " + args[0] + " :";
            case IRType::ASSIGN:
                return args[0] + " := " + args[1];
            case IRType::ADD:
                return args[0] + " := " + args[1] + " + " + args[2];
            case IRType::SUB:
                return args[0] + " := " + args[1] + " - " + args[2];
            case IRType::MUL:
                return args[0] + " := " + args[1] + " * " + args[2];
            case IRType::DIV:
                return args[0] + " := " + args[1] + " / " + args[2];
            case IRType::REF:
                return args[0] + " := &" + args[1];
            case IRType::RDEREF:
                return args[0] + " := *" + args[1];
            case IRType::LDEREF:
                return "*" + args[0] + " := " + args[1];
            case IRType::GOTO:
                return "GOTO " + args[0];
            case IRType::IF:
                return "IF " + args[0] + " " + args[1] + " " + args[2] +
                       " GOTO " + args[3];
            case IRType::RET:
                return "RETURN " + args[0];
            case IRType::ALLOC:
                return "DEC " + args[0] + " " + args[1];
            case IRType::PARAM:
                return "PARAM " + args[0];
            case IRType::ARG:
                return "ARG " + args[0];
            case IRType::CALL:
                return args[0] + " := " + "CALL " + args[1];
            case IRType::READ:
                return "READ " + args[0];
            case IRType::WRITE:
                return "WRITE " + args[0];
        }
        return "";
    }
};
