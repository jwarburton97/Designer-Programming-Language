#ifndef uuParser
#define uuParser

#include <stdio.h>
#include "type.h"
#include "lexeme.h"

typedef struct parser {
    FILE *fIn;
    FILE *fOut;

    int line;
    lexeme *last;
    lexeme *pending;
    lexeme *tree;
} Parser;

extern lexeme *parse(FILE *fIn);

extern int check(Parser *p, char *x);
extern lexeme * match(Parser *p, char *x);
extern lexeme *advance(Parser *p);

// pending functions
extern int programPending(Parser *p);
extern int expressionListPending(Parser *p);
extern int expressionPending(Parser *p);
extern int exprPending(Parser *p);
extern int optParamListPending(Parser *p);
extern int paramListPending(Parser *p);
extern int unaryPending(Parser *p);
extern int operatorPending(Parser *p);
extern int literalPending(Parser *p);
extern int funcDefPending(Parser *p);
extern int lambdaPending(Parser *p);
extern int loopPending(Parser *p);
extern int blockPending(Parser *p);
extern int whileePending(Parser *p);
extern int forrPending(Parser *p);
extern int iffPending(Parser *p);
extern int optElsePending(Parser *p);
extern int idListPending(Parser *p);
extern int variablePending(Parser *p);

// lhs grammar functions
extern lexeme *program(Parser *p);
extern lexeme *expressionList(Parser *p);
extern lexeme *expression(Parser *p);
extern lexeme *expr(Parser *p);
extern lexeme *optParamList(Parser *p);
extern lexeme *paramList(Parser *p);
extern lexeme *unary(Parser *p);
extern lexeme *operator(Parser *p);
extern lexeme *literal(Parser *p);
extern lexeme *funcDef(Parser *p);
extern lexeme *lambda(Parser *p);
extern lexeme *loop(Parser *p);
extern lexeme *block(Parser *p);
extern lexeme *whilee(Parser *p);
extern lexeme *forr(Parser *p);
extern lexeme *iff(Parser *p);
extern lexeme *optElse(Parser *p);
extern lexeme *idList(Parser *p);
extern lexeme *optIdList(Parser *p);

extern void pretty(lexeme *l);
extern void prettyPrinter(lexeme *l, char *s);

#endif
