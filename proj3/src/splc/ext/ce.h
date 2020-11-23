#pragma once
#define MAX_ERR 1000
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum class ErrorType {
    VAR_NO_DEF = 1,
    FUNC_NO_DEF = 2,
    VAR_REDEF = 3,
    FUNC_REDEF = 4,
    UNMATCH_ASS = 5,
    RVAL_ON_LEFT = 6,
    UNMATCH_OP = 7,
    UNMATCH_RET = 8,
    UNMATCH_PARAM = 9,
    NON_ARR = 10,
    NON_FUNC = 11,
    NON_IDX = 12,
    NON_STRUCT = 13,
    MEM_NO_DEF = 14,
    STRUCT_REDEF = 15,
    MEM_REDEF = 16,
    STRUCT_NO_DEF = 17,

    LEX = 'A',
    SYNTAX = 'B',
};

typedef struct ERROR {
    ErrorType type;
    int lineno;
    const char* msg;
    char* token;
} ERROR;

void add_err(ErrorType type, int lineno, const char* msg, const char* token);
void print_err(const ERROR* err);
bool is_err();
