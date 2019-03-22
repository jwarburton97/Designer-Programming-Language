#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "evaluator.h"
#include "parser.h"
#include "lexeme.h"
#include "lexer.h"
#include "type.h"

lexeme *parse(FILE *xfile) 
{
    Parser *p = malloc(sizeof(Parser));

    p->fIn = xfile;
    p->line = 1;
    p->pending = lex(p);
    p->tree = program(p);

    return p->tree;
}
// pending functions
int expressionListPending(Parser *p) 
{
   return expressionPending(p);
} 
int expressionPending(Parser *p) 
{
    return exprPending(p) || loopPending(p) || iffPending(p) || funcDefPending(p);
}
int exprPending(Parser *p) 
{
    return unaryPending(p);
}
int optParamListPending(Parser *p) 
{
    return paramListPending(p) || 1;  // ?? do I even need this?
}
int paramListPending(Parser *p) 
{
    return exprPending(p);
}
int idListPending(Parser *p) 
{
    return check(p, ID);
}
int unaryPending(Parser *p) 
{
    return literalPending(p) || check(p, OPAREN) || check(p, BREAK) || \
           lambdaPending(p) || variablePending(p) || check(p, NIL) || operatorPending(p);
}
int operatorPending(Parser *p) 
{
    return check(p, MINUS) || check(p, PLUS) || check(p, DIVIDE) || check(p, MULTIPLY) || check(p, EXPONENT) || \
           check(p, NOT) || check(p, GT) || check(p, LT) || check(p, GTE) || check(p, LTE) || \
           check(p, ISEQUAL) || check(p, NE) || check(p, AND) || check(p, OR) || check(p, EQUALS);
}
int literalPending(Parser *p) 
{
    return check(p, INT) || check(p, STRING);
}
int funcDefPending(Parser *p) 
{
    return check(p, FUNC);
}
int lambdaPending(Parser *p) 
{
    return check(p, LAMBDA);
}

int loopPending(Parser *p) 
{
    return whileePending(p) || forrPending(p); 
}
int blockPending(Parser *p) 
{
    return check(p, OBRACE);
}
int whileePending(Parser *p) 
{
    return check(p, WHILE);
}
int forrPending(Parser *p) 
{
    return check(p, FOR);
}
int iffPending(Parser *p) 
{
    return check(p, IF);
}
int optElsePending(Parser *p) 
{
    return check(p, ELSE) || 1; // ?? Do I need this?
}
int variablePending(Parser *p) 
{
    return check(p, ID);
}
lexeme *program(Parser *p) 
{
    lexeme *x =  expressionList(p);
    check(p, ENDOFFILE);
    return x;
}
lexeme *expressionList(Parser *p) 
{
    lexeme *x, *y = NULL;
    x = expression(p);
    if (expressionListPending(p)) 
	{
        y = expressionList(p);
    }
    return cons(EXPRESSIONLIST, x, y);
}
lexeme *expression(Parser *p) 
{
    if (loopPending(p)) 
	{
        return loop(p);
    }
	else if (iffPending(p)) 
	{
        return iff(p);
    }
	else if (funcDefPending(p)) 
	{
        return funcDef(p);
    } 
	else if(exprPending(p)) 
	{
        lexeme *x = expr(p);
        match(p, SEMI);
        return x;
    }
	else 
	{
        error("Expression not found.");
        exit(1);
    }
    return NULL;
}
lexeme *expr(Parser *p) 
{
    lexeme *x = NULL, *y = NULL, *z = NULL;
    x = unary(p);
    if(operatorPending(p)) 
	{
        y = operator(p);
        z = expr(p);
        return cons(EXPR, x, cons(GLUE, y, z));
    }
    return cons(EXPR, x, NULL);
}
lexeme *optParamList(Parser *p) 
{
    lexeme *x = newlexeme(OPTPARAMLIST);
    if(paramListPending(p)) 
	{
        x->left = paramList(p);
    }
    return x;
}
lexeme *paramList(Parser *p) 
{
    lexeme *x, *y = NULL;
    x = expr(p);
    if(check(p, COMMA)) 
	{
        match(p, COMMA);
        y = paramList(p);
    }
    return cons(PARAMLIST, x, y);
}
lexeme *unary(Parser *p) 
{
    lexeme *x, *y = NULL;
    if(literalPending(p)) 
	{
        return literal(p);
    }
	else if (check(p, BREAK)) 
	{
        return match(p, BREAK);
    } 
	else if(check(p, OPAREN)) 
	{
        match(p, OPAREN);
        x = expr(p);
        match(p, CPAREN);
        return x;
    }
	else if(lambdaPending(p)) 
	{
        x = lambda(p);
        if (check(p, OPAREN)) 
		{
            match(p, OPAREN);
            y = optParamList(p);
            match(p, CPAREN);
            return cons(FUNCCALL, x, y);
        }
        return x;
    }
	else if (check(p, NIL)) 
	{
        return match(p, NIL);
    } 
	else if(check(p, ID)) 
	{
        x = match(p, ID);
        if(check(p, OSB)) 
		{
            match(p, OSB);
            y = expr(p);
            match(p, CSB);
            return cons(ARRAYACCESS, x, y);
        }
		else if(check(p, OPAREN)) 
		{
            match(p, OPAREN);
            y = optParamList(p);
            match(p, CPAREN);
            return cons(FUNCCALL, x, y);
        }
		else if (check(p, DOT)) 
		{
            y = match(p, DOT);
            y->left = x;
            y->right = unary(p);
            return y;
        }
        return x;
    } 
	else
	{
        error("unary not found.");
        exit(1);
    }
    return NULL;
}

lexeme *operator(Parser *p) 
{
    if (check(p, MINUS)) 
	{
        return match(p, MINUS);
    } 
	else if (check(p, PLUS)) 
	{
        return match(p, PLUS);
    } 
	else if (check(p, DIVIDE)) 
	{
        return match(p, DIVIDE);
    } 
	else if (check(p, MULTIPLY)) 
	{
        return match(p, MULTIPLY);
    } 
	else if (check(p, EXPONENT)) 
	{
        return match(p, EXPONENT);
    } 
	else if (check(p, NOT)) 
	{
        return match(p, NOT);
    }
	else if (check(p, NE)) 
	{
        return match(p, NE);
    } 
	else if (check(p, GT)) 
	{
        return match(p, GT);
    } 
	else if (check(p, LT)) 
	{
        return match(p, LT);
    } 
	else if (check(p, GTE)) 
	{
        return match(p, GTE);
    } 
	else if (check(p, LTE)) 
	{
        return match(p, LTE);
    } 
	else if (check(p, ISEQUAL)) 
	{
        return match(p, ISEQUAL);
    }
	else if (check(p, AND)) 
	{
        return match(p, AND);
    } 
	else if (check(p, OR)) 
	{
        return match(p, OR);
    } 
	else if (check(p, EQUALS)) 
	{
        return match(p, EQUALS);
    } 
	else if (check(p, DOT)) 
	{
        return match(p, DOT);
    }
	else 
	{
        error("Operator not found.");
        exit(1);
    }
    return NULL;
}
lexeme *literal(Parser *p) 
{
    if (check(p, INT)) 
	{
        return match(p, INT);
    } 
	else if (check(p, STRING))
	{
		return match(p, STRING);
    }
    return NULL;
}

lexeme *funcDef(Parser *p) 
{
    lexeme *x, *y, *z = NULL;
    match(p, FUNC);
    x = match(p, ID);
    match(p, OPAREN);
    y = optIdList(p);
    match(p, CPAREN);
    z = block(p);
    return cons(FUNCDEF, x, cons(GLUE, y, z));
}
lexeme *optIdList(Parser *p) 
{
    lexeme *x = newlexeme(OPTIDLIST);
    if (idListPending(p)) 
	{
        x->left = idList(p);
    }
    return x;
}
lexeme *idList(Parser *p) 
{
    lexeme *x, *y = NULL;
    x = match(p, ID);
    if (check(p, COMMA)) 
	{
        match(p, COMMA);
        y = idList(p);
    }
    return cons(IDLIST, x, y);
}
lexeme *lambda(Parser *p) 
{
    lexeme *x, *y = NULL;
    match(p, LAMBDA);
    match(p, OPAREN);
    x = optIdList(p);
    match(p, CPAREN);
    y = block(p);
    return cons(LAMBDA, x, y);
}
lexeme *loop(Parser *p) 
{
    if (whileePending(p)) 
	{
        return whilee(p);
    } 
	else if (forrPending(p)) 
	{
        return forr(p);
    } 
	else 
	{
        error("Loop not found.");
        exit(1);
    }
    return NULL;
}
lexeme *block(Parser *p) 
{
    match(p, OBRACE);
    lexeme *l = cons(BLOCK, expressionList(p), NULL);
    match(p, CBRACE);
    return l;
}
lexeme *whilee(Parser *p) 
{
    lexeme *x, *y = NULL;
    match(p, WHILE);
    match(p, OPAREN);
    x = expr(p);
    match(p, CPAREN);
    y = block(p);
    return cons(WHILE, x, y);
}

lexeme *forr(Parser *p)
{
    lexeme *x, *y, *z, *a = NULL;
    match(p, FOR);
    match(p, OPAREN);
    x = expr(p);
    match(p, SEMI);
    y = expr(p);
    match(p, SEMI);
    z = expr(p);
    match(p, CPAREN);
    a = block(p);
    return cons(FOR, cons(GLUE, x, y), cons(GLUE, z, a));
}

lexeme *iff(Parser *p) 
{
    lexeme *x, *y, *z = NULL;
    match(p, IF);
    match(p, OPAREN);
    x = expr(p);
    match(p, CPAREN);
    y = block(p);
    z = optElse(p);
    return cons(IF, x, cons(GLUE, y, z));
}
lexeme *optElse(Parser *p) 
{
    lexeme *l = newlexeme(OPTELSE);
    if (check(p, ELSE)) 
	{
        match(p, ELSE);
        if (blockPending(p)) 
		{
            l->left = block(p);
            return l;
        } 
		else if (iffPending(p)) 
		{
            l->left = iff(p);
            return l;
        } 
		else 
		{
            error("optElse malformed.");
            exit(1);
        }
    }
    return NULL;
}
lexeme *lamda(Parser *p)
{
	lexeme *b, *o = NULL;
	match(p, LAMBDA);
	match(p, OPAREN);
	if(ID == NULL)
	{
		o = optParamList(p);
		match(p, CPAREN);
		b = block(p);
	}
	return cons(LAMBDA, o, b);
}
int check(Parser *p, char *x) 
{
    #ifdef uuDebug
    printf("Line: %d, PendingType: %s, TypeCheckedFor: %s\n", p->line, p->pending->type, x);
    #endif
    return strcmp(p->pending->type, x) == 0;
}
lexeme *match(Parser *p, char *x) 
{
    if (check(p, x)) 
	{
        return advance(p);
    } 
	else 
	{
        error("FATAL: Match Error");
        printf("\tLine: %d, PendingType: %s, TypeCheckedFor: %s\n", p->line, p->pending->type, x);
        if (!strcmp(x, SEMI)) 
		{
            printf("\tExpected ';' after expression.\n");
        }
		else if (!strcmp(x, CPAREN)) 
		{
            printf("\tExpected ')' after ID or Parameter list.\n");
        }
		else if (!strcmp(x, OBRACE))
		{
		printf("\tExpected '{' at the beginning of the block\n");
		}
		else if(!strcmp(x, OPAREN))
		{
			printf("\tExpected '(' Before ID or Parameter list.\n");
		}
        exit(1);
    }
}
lexeme *advance(Parser *p) 
{
    p->last = p->pending;
    p->pending = lex(p);
    return p->last;
}