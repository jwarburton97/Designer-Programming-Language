#ifndef uuType
#define uuType

// env types
extern char *ENV;
extern char *TABLE;
extern char *CLOSURE;
extern char *BUILTIN;

// higher level types
extern char *EXPRESSIONLIST;
extern char *GLUE;
extern char *EXPR;
extern char *EXPRESSION;
extern char *OPTPARAMLIST;
extern char *PARAMLIST;
extern char *PRIMARY;
extern char *OPERATOR;
extern char *LITERAL;
extern char *FUNCDEF;
extern char *FUNCCALL;
extern char *ARRAY;
extern char *ARRAYACCESS;
extern char *BLOCK;
extern char *OPTIDLIST;
extern char *IDLIST;

// lower level types
extern char *ID;
extern char *FUNC;
extern char *LAMBDA;
extern char *WHILE;
extern char *FOR;
extern char *IF;
extern char *OPTELSE;
extern char *ELSE;
extern char *BREAK;

extern char *BAD;
extern char *NIL;

extern char *STRING;
extern char *INT;

extern char *DOT;
extern char *THIS;

extern char *MINUS;
extern char *PLUS;
extern char *DIVIDE;
extern char *MULTIPLY;
extern char *EXPONENT;
extern char *NOT;
extern char *NE;
extern char *GT;
extern char *LT;
extern char *GTE;
extern char *LTE;
extern char *ISEQUAL;
extern char *AND;
extern char *OR;
extern char *EQUALS;

extern char *OPAREN;
extern char *CPAREN;
extern char *OSB;
extern char *CSB;
extern char *OBRACE;
extern char *CBRACE;
extern char *SEMI;
extern char *COMMA;
extern char *ENDOFFILE;

#endif
