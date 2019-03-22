#ifndef uulexeme
#define uulexeme

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct lexeme {
    char *type;

    char *sval;
    int ival;
    struct lexeme *(*fp)(struct lexeme *);

    struct lexeme *left;
    struct lexeme *right;

    struct lexeme **array;

} lexeme;

extern lexeme *newlexeme(char *type);

extern lexeme *cons(char *t, lexeme *l, lexeme *r);
extern lexeme *car(lexeme *x);
extern lexeme *cdr(lexeme *x);
extern void setCar(lexeme *x, lexeme *l);
extern void setCdr(lexeme *x, lexeme *l);
extern char *getType(lexeme *x);
extern char *displaylexeme(lexeme *x);

#endif