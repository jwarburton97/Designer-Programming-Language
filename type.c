#include "type.h"

// env types
char *ENV = "ENV";
char *TABLE = "TABLE";
char *CLOSURE = "CLOSURE";
char *BUILTIN = "BUILTIN";

// higher level types
char *EXPRESSIONLIST = "EXPRESSIONLIST";
char *GLUE = "GLUE";
char *EXPR = "EXPR";
char *EXPRESSION = "EXPRESSION";
char *OPTPARAMLIST = "OPTPARAMLIST";
char *PARAMLIST = "PARAMLIST";
char *PRIMARY = "PRIMARY";
char *OPERATOR = "OPERATOR";
char *LITERAL = "LITERAL";
char *FUNCDEF = "FUNCDEF";
char *FUNCCALL = "FUNCCALL";
char *ARRAY = "ARRAY";
char *ARRAYACCESS = "ARRAYACCESS";
char *BLOCK = "BLOCK";
char *OPTIDLIST = "OPTIDLIST";
char *IDLIST = "IDLIST";

// lower level types
char *ID = "ID";
char *FUNC = "FUNC";
char *LAMBDA = "LAMBDA";
char *WHILE = "WHILE";
char *FOR = "FOR";
char *IF = "IF";
char *ELSE = "ELSE";
char *OPTELSE = "OPTELSE";
char *BREAK = "BREAK";

char *BAD = "BAD";
char *NIL = "NIL";

char *STRING = "STRING";
char *INT = "INT";

char *DOT = "DOT";
char *THIS = "THIS";

char *MINUS = "MINUS";
char *PLUS = "PLUS";
char *DIVIDE = "DIVIDE";
char *MULTIPLY = "MULTIPLY";
char *EXPONENT = "EXPONENT";
char *NOT = "NOT";
char *NE = "NE";
char *GT = "GT";
char *LT = "LT";
char *GTE = "GTE";
char *LTE = "LTE";
char *ISEQUAL = "ISEQUAL";
char *AND = "AND";
char *OR = "OR";
char *EQUALS = "EQUALS";

char *OPAREN = "OPAREN";
char *CPAREN = "CPAREN";
char *OSB = "OSB";
char *CSB = "CSB";
char *OBRACE = "OBRACE";
char *CBRACE = "CBRACE";
char *SEMI = "SEMI";
char *COMMA = "COMMA";
char *ENDOFFILE = "ENDOFFILE";
