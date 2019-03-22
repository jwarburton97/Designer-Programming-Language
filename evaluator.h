#ifndef uuEval
#define uuEval

#include <stdio.h>
#include "lexeme.h"
#include "environment.h"

extern lexeme *eval(lexeme *tree, lexeme *env);
extern lexeme *evalFuncDef(lexeme *t, lexeme *env);
extern lexeme *evalFuncCall(lexeme *t, lexeme *env);
extern lexeme *evalExpressionList(lexeme *t, lexeme *env);
extern lexeme *evalExpr(lexeme *t, lexeme *env);
extern lexeme *evalParamList(lexeme *t, lexeme *env);
extern lexeme *evalPrimary(lexeme *t, lexeme *env);
extern lexeme *evalLambda(lexeme *t, lexeme *env);
extern lexeme *evalWhile(lexeme *t, lexeme *env);
extern lexeme *evalIf(lexeme *t, lexeme *env);
extern lexeme *evalBlock(lexeme *t, lexeme *env);
extern lexeme *evalOptParamList(lexeme *t, lexeme *env);
extern lexeme *evalOptElse(lexeme *t, lexeme *env);
extern lexeme *evalFor(lexeme *t, lexeme *env);
extern lexeme *evalSimpleOp(lexeme *t, lexeme *env);
extern lexeme *evalArgs(lexeme *t, lexeme *env);
extern lexeme *evalPlus(lexeme *t, lexeme *env);
extern lexeme *evalMinus(lexeme *t, lexeme *env);
extern lexeme *evalDivide(lexeme *t, lexeme *env);
extern lexeme *evalMultiply(lexeme *t, lexeme *env);
extern lexeme *evalExponent(lexeme *t, lexeme *env);
extern lexeme *evalAssign(lexeme *t, lexeme *env);
extern lexeme *evalArrayAccess(lexeme *t, lexeme *env);
extern lexeme *evalDot(lexeme *t, lexeme *env);
extern void initEnv(lexeme *env);
extern void initStdlib(lexeme *global);
extern lexeme *printUU(lexeme *args);
extern void printlexeme(lexeme *x);
extern lexeme *printlnUU(lexeme *args);
extern lexeme *arrayUU(lexeme *args);
extern lexeme *arraySizeUU(lexeme *args);
extern void error(char* e);
// helpers
extern lexeme *getFuncDefName(lexeme *t);
extern lexeme *getFuncCallName(lexeme *t);
extern lexeme *getFuncCallArgs(lexeme *t);
extern lexeme *getClosureParams(lexeme *t);
extern lexeme *getClosureBody(lexeme *t);
extern lexeme *getClosureEnvironment(lexeme *t);
extern int isTrue(lexeme *t);


#endif
