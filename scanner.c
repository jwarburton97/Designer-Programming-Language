#include <stdio.h>
#include <stdlib.h>  /* for exit, malloc, realloc */
#include <ctype.h>   /* for isspace */
#include <string.h>  /* for strdup */
#include <assert.h>
#include "scanner.h"


typedef struct lexeme 
{
	const char type;
	char *string;
	int integer;
	double real;
}lexeme;

char pushbackChar;
Boolean CharacterPushed = FALSE;

void skipWhiteSpace(FILE *fp)
{
	
}
lexeme *lexNumber(FILE *fp)
{
	
}
lexeme *lexString(FILE *fp)
{
	
}
lexeme *lexVariableOrKeyword(FILE *fp)
{
	
}

lexeme *lex(FILE *fp) 
{ 
	char ch; 
	skipWhiteSpace(fp);
	ch = readChar(fp);
	switch(ch) 
	{ 
	// single character tokens 
		case '#':
			lexical->type = "HASHTAG";
			return lexical;
		case '(':
			lexical->type ="OPAREN";
			return lexical;
		case ')': 
			lexical->type = "CPAREN";
			return lexical;
		case '{':
			lexical->type = "OPEN_BRACE";
			return lexical;
		case '}':
			lexical->type = "CLOSE_BRACE";
			return lexical;
		case ',':
			lexical->type ="COMMA";
			return lexical;
		case '+': 
			lexical->type = "PLUS";
			return lexical;
		case '*':
			lexical->type ="TIMES";
			return lexical;
		case '-': 
			lexical->type = "MINUS";
			return lexical;
		case '/':
			lexical->type = "DIVIDE";
			return lexical;
		case '%':
			lexical->type = "MOD";
			return lexical;
		case '<': 
			lexical->type = "LESSTHAN";
			return lexical;
		case '>':
			lexical->type = "GREATERTHAN";
			return lexical;
		case '=': 
			lexical->type = "ASSIGN";
			return lexical;
		case ';': 
			lexical->type = "SEMICOLON";
			return lexical;
		default: 
		// multi-character tokens (only numbers, 
        // variables/keywords, and strings) 
			if (isAlpha(ch)) 
            { 
				ungetc(ch, fp); 
				return lexVariableOrKeyword();
            } 
			else if (ch == '\"') 
            {
				ungetc(ch, fp);
				return lexString(); 
            } 
			else
				return lex; 
	}
}
void scanner()
{
	
}
char readChar(FILE *fp)
    {
    int result;
    char x;
    result = fscanf(fp," %c",&x);
    if (result == EOF)
        {
        return EOF;
        }
    if (result == 0)
        {
        fprintf(stderr,"SCAN ERROR: attempt to read a non-whitespace character failed\n");
        fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
        exit(2);
        }
    return x;
    }
int main(int argc, char argv[])
{
	printf("LEXICAL ANALYZING BEGIN!\n");
	scanner(argv[1]);
	return 0;
}