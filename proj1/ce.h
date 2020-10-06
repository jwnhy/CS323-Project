#pragma once
#define MAX_ERR 1000
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
typedef enum {
    LEX, SYNTAX, SEMANTIC
}ERROR_TYPE;

typedef struct ERROR {
    ERROR_TYPE type;
    int lineno;
    const char* msg;
    char* token;
}ERROR;
void add_err(ERROR_TYPE type, int lineno, const char* msg, const char* token);
void print_err(const ERROR *err);
bool is_err();

