#include <stdio.h>
#include "environment.h"
#include "lexeme.h"
#include "type.h"

lexeme *createEnv() {
    return extendEnv(NULL, NULL, NULL);
}

lexeme *extendEnv(lexeme *env, lexeme *vars, lexeme *vals) {
    return cons(ENV, makeTable(vars, vals), env);
}

lexeme *makeTable(lexeme *vars, lexeme *vals) {
    return cons(TABLE, vars, vals);
}

lexeme *lookupEnv(lexeme *var, lexeme *env) {
    while (env != NULL) {
        lexeme *table = car(env);
        lexeme *vars = car(table);
        lexeme *vals = cdr(table);
        while (vars != NULL) {
            if (sameVariable(var, car(vars))) {
                return car(vals);
            }
            //walk the lists in parallel
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
    }
    fprintf(stderr, "FATAL: variable, %s, is undefined.", var->sval);
    return NULL;
}

int sameVariable(lexeme *x, lexeme *y) {
    return !strcmp(x->sval, y->sval);
}

lexeme *insert(lexeme *var, lexeme *val, lexeme *env) {
    lexeme *table = car(env);
    setCar(table, cons(GLUE, var, car(table)));
    setCdr(table, cons(GLUE, val, cdr(table)));
    return val;
}
