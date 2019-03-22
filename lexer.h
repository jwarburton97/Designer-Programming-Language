#ifndef uuLexer
#define uuLexer
#include "parser.h"
#include "lexeme.h"

extern lexeme *lex(Parser *p);
extern lexeme *lexNumber(Parser *p, int i);
extern lexeme *lexID(Parser *p, int i);
extern lexeme *lexString(Parser *p, int i);
extern int isNewLine(int cur);
extern int isWhiteSpace(int cur);
extern int getChar(Parser *p);
extern void skipWhiteSpace(Parser *p);

#endif
