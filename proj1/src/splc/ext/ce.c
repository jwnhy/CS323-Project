#include "ce.h"
int err_cnt = 0;
ERROR err_arr[MAX_ERR];
void add_err(ERROR_TYPE type, int lineno, const char* msg, const char* token) {
    char* token_buf = (char*)malloc(sizeof(char)*strlen(token));
    strcpy(token_buf, token);
    ERROR *err = &err_arr[err_cnt++];
    err->type = type;
    err->lineno = lineno;
    err->msg = msg;
    err->token = token_buf;
}

void print_err(const ERROR *err) {
    char c;
    if (err->type == LEX) {
        c = 'A';
    } else if (err->type == SYNTAX) {
        c = 'B';
    } else if (err->type == SEMANTIC) {
        c = 'C';
    }
    if (strlen(err->token))
        printf("Error type %c at Line %d: %s, %s\n", c, err->lineno, err->msg, err->token);
    else
        printf("Error type %c at Line %d: %s.\n", c, err->lineno, err->msg);

    
}

bool is_err() {
    return err_cnt > 0;
}