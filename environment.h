#ifndef uuEnv
#define uuEnv
#include <stdio.h>
#include "lexeme.h"

extern lexeme *createEnv();
extern lexeme *extendEnv(lexeme *env, lexeme *vars, lexeme *vals);
extern lexeme *makeTable(lexeme *vars, lexeme *vals);
extern lexeme *lookupEnv(lexeme *var, lexeme *env);
extern int sameVariable(lexeme *x, lexeme *y);
extern lexeme *insert(lexeme *var, lexeme *val, lexeme *env);


#endif
