#include "lexeme.h"
#include "lexer.h"
#include "parser.h"
#include "type.h"

lexeme *lex(Parser *p) {
    int ch;
    skipWhiteSpace(p);
    ch = getChar(p);
    if (ch == EOF) return newlexeme(ENDOFFILE);

    switch(ch) {
        // single character tokens
        case '.':
            return newlexeme(DOT);
        case '-':
            return newlexeme(MINUS);
        case '+':
            return newlexeme(PLUS);
        case '/':
            return newlexeme(DIVIDE);
        case '*':
            return newlexeme(MULTIPLY);
        case '^':
            return newlexeme(EXPONENT);
        case '!':
            ch = getChar(p);
            if (ch == '=') {
                return newlexeme(NE);
            }
            ungetc(ch, p->fIn);
            return newlexeme(NOT);
        case '>':
            ch = getChar(p);
            if (ch == '=') {
                return newlexeme(GTE);
            }
            ungetc(ch, p->fIn);
            return newlexeme(GT);
        case '<':
            ch = getChar(p);
            if (ch == '=') {
                return newlexeme(LTE);
            }
            ungetc(ch, p->fIn);
            return newlexeme(LT);
        case '&':
            return newlexeme(AND);
        case '|':
            return newlexeme(OR);
        case '=':
            ch = getChar(p);
            if (ch == '=') {
                return newlexeme(ISEQUAL);
            }
            ungetc(ch, p->fIn);
            return newlexeme(EQUALS);
        case '(':
            return newlexeme(OPAREN);
        case ')':
            return newlexeme(CPAREN);
        case '[':
            return newlexeme(OSB);
        case ']':
            return newlexeme(CSB);
        case '{':
            return newlexeme(OBRACE);
        case '}':
            return newlexeme(CBRACE);
        case ';':
            return newlexeme(SEMI);
        case ',':
            return newlexeme(COMMA);
        
        default:
            // multi-character tokens
            // (only numbers, variables/keywords, and strings)
            if (isdigit(ch)) {
                return lexNumber(p, ch);
            } else if (isalpha(ch)) {
                return lexID(p, ch);  //and keywords!
            } else if (ch == '\"') {
                return lexString(p, ch);
            }
    }
    return newlexeme(BAD);
}

lexeme *lexNumber(Parser *p, int i) {
    lexeme *l = newlexeme(INT);
    char n[64] = "";
    int size = 1;
    n[0] = i;
    i = getChar(p);

    while (!isWhiteSpace(i) && isdigit(i)) {
        n[size++] = i;
        i = getChar(p);
    }

    ungetc(i, p->fIn);
    n[size++] = '\0';
    l->ival = atoi(n);
    l->sval = n;

    return l;

}

lexeme *lexID(Parser *p, int i) {
    lexeme *l = newlexeme(ID);
    char s[32] = "";
    int size = 1;
    s[0] = i;
    i = getChar(p);

    while(!isWhiteSpace(i) && (isalpha(i) || isdigit(i))) {
        s[size++] = i;
        i = getChar(p);
    }

    ungetc(i, p->fIn);
    s[size++] = '\0';
   
    if (!strcmp(s, "func")) {
        l->type = FUNC;
    } else if (!strcmp(s, "lambda")) {
        l->type = LAMBDA;
    } else if (!strcmp(s, "while")) {
        l->type = WHILE;
    } else if (!strcmp(s, "for")) {
        l->type = FOR;
    } else if (!strcmp(s, "if")) {
        l->type = IF;
    } else if (!strcmp(s, "else")) {
        l->type = ELSE;
    } else if (!strcmp(s, "nil")) {
        l->type = NIL;
    } else if (!strcmp(s, "break")) {
        l->type = BREAK;
    } else {
        l->sval = malloc(strlen(s) + 1);
        strcpy(l->sval, s);
        //l->sval = s;
    }
    return l;
}

lexeme *lexString(Parser *p, int i) {
    lexeme *l = newlexeme(STRING);
    char s[128] = "";
    int size = 0;
    //s[0] = i;
    i = getChar(p);

    while(i != '\"') {
        s[size] = i;
        size++;
        i = getChar(p);
    }

    s[size++] = '\0';
    l->sval = malloc(strlen(s) + 1);
    strcpy(l->sval, s);
    l->ival = size;
    //printf("s: %s", s);
    //printf("l->sval: %s", l->sval);
    
    return l;
}

int isNewLine(int cur) {
    return cur == '\r' || cur == '\n' || cur == '\t';  
}

int isWhiteSpace(int cur) {
    return isNewLine(cur) || cur == ' ';
}

int getChar(Parser *p) {
    int cur = fgetc(p->fIn);
    if (cur == '/') {
        int curr = fgetc(p->fIn);
        if (curr == '/') {
            while (!isNewLine(cur) && !feof(p->fIn)) {
                cur = fgetc(p->fIn);
            }
        } else {
            ungetc(curr, p->fIn);
        }
    }
    return cur;
}

void skipWhiteSpace(Parser *p) {
    int cur = getChar(p);
    while (isWhiteSpace(cur) && !feof(p->fIn)) {
        if (isNewLine(cur)) {
            p->line++;
        }
        cur = getChar(p);
    }
    ungetc(cur, p->fIn);
}

