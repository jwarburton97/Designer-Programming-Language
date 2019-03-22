#include <stdio.h>
#include <stdlib.h>
#include "evaluator.h"
#include "lexeme.h"
#include "type.h"
#include "environment.h"
#include "lexer.h"
#include "parser.h"
#include "pp.h"


void error(char *e) {
    printf("%s\n", e);
}

lexeme *eval(lexeme *tree, lexeme *env) {
    if (tree != NULL) {
        if (!strcmp(tree->type, STRING)) {
            return tree;
        } else if (!strcmp(tree->type, INT)) {
            return tree;
        } else if (!strcmp(tree->type, ARRAY)) {
            return tree;
        } else if (!strcmp(tree->type, CLOSURE)) {
            return tree;
        } else if (!strcmp(tree->type, NIL)) {
            return tree;
        } else if (!strcmp(tree->type, BREAK)) {
            return tree;
        } else if (!strcmp(tree->type, DOT)) {
            return evalDot(tree, env);
        } else if (!strcmp(tree->type, ID) || !strcmp(tree->type, FUNC)) {
            if (!strcmp(tree->sval, "this")) {
                return env;
            }
            return lookupEnv(tree, env);
        } else if (!strcmp(tree->type, FUNCDEF)) {
            return evalFuncDef(tree, env);
        } else if (!strcmp(tree->type, FUNCCALL)) {
            return evalFuncCall(tree, env);
        } else if (!strcmp(tree->type, EXPRESSIONLIST)) {
            return evalExpressionList(tree, env);
        } else if (!strcmp(tree->type, EXPR)) {
            return evalExpr(tree, env);
        } else if (!strcmp(tree->type, LAMBDA)) {
            return evalLambda(tree, env);
        } else if (!strcmp(tree->type, WHILE)) {
            return evalWhile(tree, env);
        } else if (!strcmp(tree->type, IF)) {
            return evalIf(tree, env);
        } else if (!strcmp(tree->type, BLOCK)) {
            return evalBlock(tree, env);
        } else if (!strcmp(tree->type, OPTELSE)) {
            return evalOptElse(tree, env);
        } else if (!strcmp(tree->type, FOR)) {
            return evalFor(tree, env);
        } else if (!strcmp(tree->type, MINUS)) {
            return evalMinus(tree, env);
        } else if (!strcmp(tree->type, PLUS)) {
            return evalPlus(tree, env);
        } else if (!strcmp(tree->type, DIVIDE)) {
            return evalDivide(tree, env);
        } else if (!strcmp(tree->type, MULTIPLY)) {
            return evalMultiply(tree, env);
        } else if (!strcmp(tree->type, EXPONENT)) {
            return evalExponent(tree, env);
        } else if (!strcmp(tree->type, NOT)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, NE)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, GT)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, LT)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, GTE)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, LTE)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, ISEQUAL)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, AND)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, OR)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, EQUALS)) {
            return evalAssign(tree, env);
        } else if (!strcmp(tree->type, ARRAYACCESS)) {
            return evalArrayAccess(tree, env);
        } else {
            printf("Type: %s not evaluated.\n", tree->type);
        } 
    }
    return NULL;
}


lexeme *evalFuncDef(lexeme *t, lexeme *env) {
    lexeme *closure = newlexeme(CLOSURE);
    setCar(closure, env);
    setCdr(closure, t);
    return insert(getFuncDefName(t), closure, env);
}

lexeme *evalFuncCall(lexeme *t, lexeme *env) {
    lexeme *closure = eval(getFuncCallName(t), env);
    lexeme *args = getFuncCallArgs(t);
    lexeme *eargs = evalArgs(args, env);
    if (!strcmp(closure->type, BUILTIN)) {
        return closure->fp(eargs);
    }

    lexeme *params = getClosureParams(closure);
    lexeme *body = getClosureBody(closure);
    lexeme *senv = getClosureEnvironment(closure);
    lexeme *xenv = extendEnv(senv, params, eargs);
    return eval(body, xenv);
}

lexeme *evalArgs(lexeme *t, lexeme *env) {
    if (t == NULL) {
        return NULL;
    }
    return cons(GLUE, eval(car(t), env), evalArgs(cdr(t), env));
}

lexeme *evalBlock(lexeme *t, lexeme *env) {
    lexeme *result;
    while (t != NULL) {
        result = eval(car(t), env);
        if (result != NULL && !strcmp(result->type, BREAK)) {
            return result;
        }
        t = cdr(t);
    }
    return result;
}

lexeme *evalDot(lexeme *t, lexeme *env) {
    lexeme *l = eval(t->left, env);
    lexeme *r = lookupEnv(t->right, l);
    return r;
}

lexeme *evalPlus(lexeme *t, lexeme *env) {
	//eval the left and the right hand sides
    lexeme *left = eval(car(t),env);
    lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        lexeme *new = newlexeme(INT);
		new->ival = left->ival + right->ival;
		return new;
    } else if (left->type == INT && right->type == STRING) {
        lexeme *new = newlexeme(STRING);
		sprintf(new->sval, "%d%s", left->ival, right->sval);
		return new;
    } else if (left->type == STRING && right->type == INT) {
        lexeme *new = newlexeme(STRING);
		sprintf(new->sval, "%s%d", left->sval, right->ival);
		return new;
    } else if (left->type == STRING && right->type == STRING) {
        lexeme *new = newlexeme(STRING);
		sprintf(new->sval, "%s%s", left->sval, right->sval);
		return new;
    } else {
        error("Can only add ints or strings.");
        exit(1);
        return NULL;
    } 
}
lexeme *evalLamda(lexeme *t, lexeme *env)
{
	return cons(CLOSURE, env, t);
}
lexeme *evalMinus(lexeme *t, lexeme *env) {
	//eval the left and the right hand sides
    lexeme *left = eval(car(t),env);
    lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        lexeme *new = newlexeme(INT);
		new->ival = left->ival - right->ival;
		return new;
    } else {
        error("FATAL: Can only subtract ints.");
        exit(1);
        return NULL;
    } 
}

lexeme *evalDivide(lexeme *t, lexeme *env) {
	//eval the left and the right hand sides
    lexeme *left = eval(car(t),env);
    lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        lexeme *new = newlexeme(INT);
		new->ival = left->ival / right->ival;
		return new;
    } else {
        error("Can only divide ints.");
        exit(1);
        return NULL;
    } 
}

lexeme *evalMultiply(lexeme *t, lexeme *env) {
	//eval the left and the right hand sides
    lexeme *left = eval(car(t),env);
    lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        lexeme *new = newlexeme(INT);
		new->ival = left->ival * right->ival;
		return new;
    } else {
        error("Can only multiply ints.");
        exit(1);
        return NULL;
    } 
}

lexeme *evalExponent(lexeme *t, lexeme *env) {
	//eval the left and the right hand sides
    lexeme *left = eval(car(t),env);
    lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        lexeme *new = newlexeme(INT);
        int i, result = 1;
        for (i=0; i < right->ival; i++) {
            result *= left->ival;
        }
		new->ival = result;
		return new;
    } else {
        error("Can only multiply ints.");
        exit(1);
        return NULL;
    } 
}

lexeme *evalAssign(lexeme *t, lexeme *env) {
    lexeme *value = eval(cdr(t), env);
    if (!strcmp(t->left->type, ARRAYACCESS)) {
        lexeme *temp = evalArrayAccess(t->left, env);
        temp->type = value->type;
        temp->sval = value->sval;
        temp->ival = value->ival;
        temp->fp = value->fp;
        temp->left = value->left;
        temp->right = value->right;
        temp->array = value->array;
    } else {
        insert(car(t), value, env);
    }
    return value;
}

lexeme *evalWhile(lexeme *t, lexeme *env) {
    lexeme *result = NULL;
    while (isTrue(eval(car(t), env))) {
        result = eval(cdr(t), env);
        if (!strcmp(result->type, BREAK)) {
            return newlexeme(NIL);
        }
    }
    return result;
}

lexeme *evalIf(lexeme *t, lexeme *env) {
    lexeme *result = NULL;
    if (isTrue(eval(t->left, env))) {
           result =  eval(t->right->left, env);
    } else {
        result = eval(t->right->right, env);
    }
    return result;
}

lexeme *evalOptElse(lexeme *t, lexeme *env) {
    if (t == NULL) {
        return NULL;
    } else {
        return eval(t->left, env);
    }
}

lexeme *evalFor(lexeme *t, lexeme *env) {
    lexeme *result = NULL;
    eval(car(car(t)), env);
    while (isTrue(eval(cdr(car(t)), env))) {
        result = eval(t->right->right, env);
        eval(t->right->left, env);
    }
    return result;
}

lexeme *evalExpressionList(lexeme *t, lexeme *env) {
    lexeme *result = newlexeme(NIL);
    while (t != NULL) {
        result = eval(t->left, env);
        if (result != NULL && !strcmp(result->type, BREAK)) {
            return result;
        }
        t = t->right;
    }
    return result;
}

lexeme *evalExpr(lexeme *t, lexeme *env) {
    if (t->right == NULL) {
        return eval(t->left, env);
    } else {
        return evalSimpleOp(cons(t->right->left->type, t->left, t->right->right), env); 
    }
}

lexeme *evalLambda(lexeme *t, lexeme *env) {
	return cons(CLOSURE, env, t);
}

lexeme *evalSimpleOp(lexeme *t, lexeme *env) {
    t->right = eval(t->right, env);
    if (!strcmp(t->type, EQUALS)) {
        return evalAssign(t, env);
    }
    t->left = eval(t->left, env);
    lexeme *result = newlexeme(INT);
    if (!strcmp(t->type, NOT)) {
    } else if (!strcmp(t->type, NE)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival == t->right->ival) {
                result->ival = 0;
            } else {
                result->ival = 1;
            }
        } else if ((!strcmp(t->left->type, STRING) || !strcmp(t->left->type, ID)) && (!strcmp(t->right->type, STRING) || !strcmp(t->left->type, ID))) {
            result->ival = !strcmp(t->left->sval, t->right->sval);
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, STRING)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, INT)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, INT)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, STRING)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, NIL) && strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else {
            printf("l->%s, r->%s\n", t->left->type, t->right->type);
            error("Invalid comparison.");
            exit(1);
            return NULL;
        }
        
    } else if (!strcmp(t->type, GT)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival > t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, LT)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival < t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, GTE)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival >= t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, LTE)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival <= t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, ISEQUAL)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival == t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else if ((!strcmp(t->left->type, STRING) || !strcmp(t->left->type, ID)) && (!strcmp(t->right->type, STRING) || !strcmp(t->left->type, ID))) {
            result->ival = !strcmp(t->left->sval, t->right->sval);
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, STRING)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, INT)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, INT)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, STRING)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, NIL) && strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else {
            printf("l->%s, r->%s\n", t->left->type, t->right->type);
            printf("Invalid comparison.");
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, AND)) {
        if (isTrue(t->left) && isTrue(t->right)) {
            result->ival = 1;
        } else {
            result->ival = 0;
        }
    } else if (!strcmp(t->type, OR)) {
        if (isTrue(t->left) || isTrue(t->right)) {
            result->ival = 1;
        } else {
            result->ival = 0;
        }
    } else if (!strcmp(t->type, PLUS)) {
        return evalPlus(t, env);
    } else if (!strcmp(t->type, MINUS)) {
        return evalMinus(t, env);
    } else if (!strcmp(t->type, DIVIDE)) {
        return evalDivide(t, env);
    } else if (!strcmp(t->type, MULTIPLY)) {
        return evalMultiply(t, env);
    } else if (!strcmp(t->type, EXPONENT)) {
        return evalExponent(t, env);
    } else {
        return NULL;
    }
    return result;
}

lexeme *evalArrayAccess(lexeme *t, lexeme *env) {
    lexeme *temp = lookupEnv(t->left, env);
    if (strcmp(temp->type, ARRAY)) {
        error("Invalid array.\n");
        printf("Type: %s\n", temp->type);
        exit(1);
    } 
    lexeme *index = eval(t->right, env);
    if (strcmp(index->type, INT)) {
        error("Must access array with INT.\n");
        exit(1);
    }
    return temp->array[index->ival];
}

// helpers
lexeme *getFuncDefName(lexeme *f) {
    return car(f);
}

lexeme *getFuncCallName(lexeme *t) {
    return car(t);
}

lexeme *getFuncCallArgs(lexeme *t) {
    // right is OPTPARAMLIST, then left is PARAMLIST
    return car(cdr(t));
}

lexeme *getClosureParams(lexeme *t) {
    return t->right->right->left->left;
}

lexeme *getClosureBody(lexeme *t) {
    return cdr(cdr(cdr(t)));
}

lexeme *getClosureEnvironment(lexeme *t) {
    return car(t);
}

int isTrue(lexeme *t) {
    if (t == NULL) {
        return 0;
    } else if (!strcmp(t->type, BAD)) {
        return 0;
    } else if (!strcmp(t->type, INT) && t->ival == 0) {
        return 0;
    } else {
        return 1;
    }
}
int main(int argc, char **argv, char **env) {
    int pp = 0;  //pretty printer variable
    char *fname = argv[1];
    if(argc < 2) {
        fprintf(stderr, "Usage: ./uu <uu source file>\n");
        exit(1);
    } else if (argc == 3) {
        if (!strcmp(argv[1], "-pp")) {
            pp = 1;
            fname = argv[2];
        }
    }
    
    lexeme *parseTree = parse(fopen(fname, "r"));
    if (pp) {
        pretty(parseTree);
        exit(0);
    }
    lexeme *global = createEnv();
    initEnv(global);
    initStdlib(global);
    eval(parseTree, global);
    parseTree = NULL;
}

void initEnv(lexeme *env) {
    lexeme *var = newlexeme(ID);
    var->sval = "print";
    lexeme *val = newlexeme(BUILTIN);
    val->fp = printUU;
    insert(var, val, env);

    var = newlexeme(ID);
    var->sval = "println";
    val = newlexeme(BUILTIN);
    val->fp = printlnUU;
    insert(var, val, env);

    var = newlexeme(ID);
    var->sval = "array";
    val = newlexeme(BUILTIN);
    val->fp = arrayUU;
    insert(var, val, env);
    
    var = newlexeme(ID);
    var->sval = "arraySize";
    val = newlexeme(BUILTIN);
    val->fp = arraySizeUU;
    insert(var, val, env);
}

void initStdlib(lexeme *global) {
    lexeme *parseTree = parse(fopen("ds.lusth", "r"));
    eval(parseTree, global);

    parseTree = parse(fopen("math.lusth", "r"));
    eval(parseTree, global);
}

lexeme *printUU(lexeme *args) {
    lexeme *result = NULL;
    while (args != NULL) {
        if (!strcmp(args->left->type, INT)) {
            printf("%d", args->left->ival);
        } else if (!strcmp(args->left->type, STRING)) {
            printf("%s", args->left->sval);
        } else if (!strcmp(args->left->type, ARRAY)) {
            int i;
            printf("[");
            for (i = 0; i < args->left->ival; i++) {
                if (i == (args->left->ival - 1)) {
                    printlexeme(args->left->array[i]);
                } else {
                    printlexeme(args->left->array[i]);
                    printf(",");
                }
            } 
            printf("]");
        } else if (!strcmp(args->left->type, CLOSURE)) {
            pretty(args->left->right);
        } else {
            printf("Can't print type: %s\n", args->left->type);
            exit(1);
        }
        result = args;
        args = args->right;
    }
    return result;
}

void printlexeme(lexeme *x) {
    if (!strcmp(x->type, INT)) {
        printf("%d", x->ival);
    } else if (!strcmp(x->type, STRING)) {
        printf("\"%s\"", x->sval);
    } else if (!strcmp(x->type, NIL)) {
        printf("nil");
    } else {
        printf("Can't print type: %s\n", x->type);
        exit(1);
    }
}

lexeme *printlnUU(lexeme *args) {
    lexeme *result = printUU(args);
    printf("\n");
    return result;
}

lexeme *arrayUU(lexeme *args) {
    if (args == NULL) {
        error("Not enough arguments for array\n");
        exit(1);
    } else if (args->right != NULL) {
        error("Too many arguments for array\n");
        exit(1);
    } else if (strcmp(args->left->type, INT)) {
        error("Argument to array must be an INT\n");
        exit(1);
    } else if (args->left->ival < 1) {
        error("Can't declare array with 0 or negative elements.\n");
        exit(1);
    } else {
        lexeme *arr = newlexeme(ARRAY);
        arr->array = malloc(args->left->ival * sizeof(lexeme *));
        arr->ival = args->left->ival;
        for (int i = 0; i < args->left->ival; i++) {
            arr->array[i] = newlexeme(NIL);
        }
        return arr;
    }
}

lexeme *arraySizeUU(lexeme *args) {
    if (args == NULL) {
        error("Not enough arguments for arraySize\n");
        exit(1);
    } else if (args->right != NULL) {
        error("Too many arguments for arraySize\n");
        exit(1);
    } else if (strcmp(args->left->type, ARRAY)) {
        error("Argument to arraySize must be an array\n");
        exit(1);
    } else {
        lexeme *temp = newlexeme(INT);
        temp->ival = args->left->ival;  
        return temp;
    }
}
