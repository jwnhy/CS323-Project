#include "ce.h"
int err_cnt = 0;
ERROR err_arr[MAX_ERR];
void add_err(ErrorType type, int lineno, const char* msg, const char* token) {
    char* token_buf = (char*)malloc(sizeof(char) * strlen(token));
    strcpy(token_buf, token);
    ERROR* err = &err_arr[err_cnt++];
    err->type = type;
    err->lineno = lineno;
    err->msg = msg;
    err->token = token_buf;
    print_err(err);
}

void print_err(const ERROR* err) {
    if (err->type == ErrorType::SYNTAX || err->type == ErrorType::LEX) {
        if (strlen(err->token))
            printf("Error type %c at Line %d: %s, %s\n", err->type, err->lineno,
                   err->msg, err->token);
        else
            printf("Error type %c at Line %d: %s.\n", err->type, err->lineno,
                   err->msg);
    } else
        printf("Error type %d at Line %d: %s.\n", err->type, err->lineno,
               err->msg);
}

bool is_err() {
    return err_cnt > 0;
}