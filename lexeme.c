#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexeme.h"
#include "type.h"

lexeme *newlexeme(char *type) {
    lexeme *x = malloc(sizeof(lexeme));
    x->type = type;
    x->sval = NULL;
    x->ival = 0;
    x->left = NULL;
    x->right = NULL;
    x->array = NULL;
    return x;
}

lexeme *cons(char *t, lexeme *l, lexeme *r) {
    lexeme *x = malloc(sizeof(lexeme));
    x->type = t;
    x->left = l;
    x->right = r;
    return x;
}

lexeme *car(lexeme *x) {
    return x->left;
}

lexeme *cdr(lexeme *x) {
    return x->right;
}

void setCar(lexeme *x, lexeme *l) {
    x->left = l;
}

void setCdr(lexeme *x, lexeme *r) {
    x->right = r;
}

char *getType(lexeme *x) {
    return x->type;
}

char *displaylexeme(lexeme *x) {
    char *display = malloc(sizeof(char) * 128);
    if(x->type == STRING || x->type == ID) {
        sprintf(display, "%s %s", x->type, x->sval);
    } else if (x->type == INT) {
        strcpy(display, x->type);
        char buf[10];
        sprintf(buf, "%d", x->ival);
        strcat(display, " ");
        strcat(display, buf);
    } else {
        strcpy(display, x->type);
    }
    return display;
}
