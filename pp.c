#include "error.h"
#include "parser.h"
#include "lexeme.h"
#include "lexer.h"
#include "type.h"
#include "pp.h"

void pretty(lexeme *l) {
    prettyPrinter(l, "");
}

void prettyPrinter(lexeme *l, char *s) {
    if (l != NULL) {
        if (!strcmp(l->type, STRING)) {
            printf("\"%s\"", l->sval);
        } else if (!strcmp(l->type, INT)) {
            printf("%d", l->ival);
        } else if (!strcmp(l->type, ID) || !strcmp(l->type, FUNC)) {
            printf("%s", l->sval);
        } else if (!strcmp(l->type, FUNCDEF)) {
            printf("func ");
            prettyPrinter(l->left, "");
            printf("(");
            prettyPrinter(l->right->left, "");
            printf(")");
            prettyPrinter(l->right->right, "");
        } else if (!strcmp(l->type, FUNCCALL)) {
            prettyPrinter(l->left, "");
            prettyPrinter(l->right, "");
        } else if (!strcmp(l->type, ARRAYACCESS)) {
            prettyPrinter(l->left, "");
            printf("[");
            prettyPrinter(l->right, "");
            printf("]\n");
        } else if (!strcmp(l->type, EXPRESSIONLIST)) {
            prettyPrinter(l->left, "");
            if (!strcmp(l->left->type, EXPR)) {

                printf("; \n");
            }
            prettyPrinter(l->right, "");
        } else if (!strcmp(l->type, EXPR)) {
            prettyPrinter(l->left, "");
            printf(" ");
            if (l->right != NULL) {
                prettyPrinter(l->right->left, "");
                prettyPrinter(l->right->right, "");
            }
        } else if (!strcmp(l->type, PARAMLIST)) {
            prettyPrinter(l->left, "");
            if (l->right) {
                printf(", ");
            }
            prettyPrinter(l->right, "");
        } else if (!strcmp(l->type, PRIMARY)) {
            prettyPrinter(l->left, "");
            prettyPrinter(l->right, "");
        } else if (!strcmp(l->type, LAMBDA)) {
            prettyPrinter(l->left, "");
            prettyPrinter(l->right, "");
        } else if (!strcmp(l->type, WHILE)) {
            printf("while (");
            prettyPrinter(l->left, "");
            printf(")\n");
            prettyPrinter(l->right, "");
        } else if (!strcmp(l->type, IF)) {
            printf("if (");
            prettyPrinter(l->left, "");
            printf(")\n");
            prettyPrinter(l->right->left, "");
            prettyPrinter(l->right->right, "");
        } else if (!strcmp(l->type, BLOCK)) {
            printf("{\n");
            prettyPrinter(l->left, "");
            printf("}\n");
        } else if (!strcmp(l->type, OPTPARAMLIST)) {
            printf("(");
            prettyPrinter(l->left, "");
            printf(") ");
        } else if (!strcmp(l->type, OPTELSE)) {
            if (l->left != NULL) {
                if (!strcmp(l->left->type, BLOCK)) {
                    printf(" else ");
                    prettyPrinter(l->left, "");
                } else if (!strcmp(l->left->type, IF)) {
                    printf(" else ");
                    prettyPrinter(l->left, "");
                }
            }
        } else if (!strcmp(l->type, FOR)) {
            printf("for (");
            prettyPrinter(l->left->left, "");
            printf("; ");
            prettyPrinter(l->left->right, "");
            printf("; ");
            prettyPrinter(l->right->left, "");
            printf(") ");
            prettyPrinter(l->right->right, "");
        } else if (!strcmp(l->type, MINUS)) {
            printf(" - ");
        } else if (!strcmp(l->type, PLUS)) {
            printf(" + ");
        } else if (!strcmp(l->type, DIVIDE)) {
            printf(" / ");
        } else if (!strcmp(l->type, MULTIPLY)) {
            printf(" * ");
        } else if (!strcmp(l->type, EXPONENT)) {
            printf(" ^ ");
        } else if (!strcmp(l->type, NOT)) {
            printf(" ! ");
        } else if (!strcmp(l->type, GT)) {
            printf(" > ");
        } else if (!strcmp(l->type, LT)) {
            printf(" < ");
        } else if (!strcmp(l->type, GTE)) {
            printf(" >= ");
        } else if (!strcmp(l->type, LTE)) {
            printf(" <= ");
        } else if (!strcmp(l->type, ISEQUAL)) {
            printf(" == ");
        } else if (!strcmp(l->type, AND)) {
            printf(" & ");
        } else if (!strcmp(l->type, OR)) {
            printf(" | ");
        } else if (!strcmp(l->type, EQUALS)) {
            printf(" = ");
        } //else {
            //printf("%s", l->sval);
       // }
    }
}