%{

#include <string>
#include "../messagebook.h"
#include "../person_ptr.h"

#include "interface.h"
#include "parser.h"

extern "C" {
    int yywrap(void);
    int yylex(void);
}

// ---[ defines ]--------------------------------------------------------------

// better YY_INPUT
#define YY_INPUT(buf, result, max_size) {      \
    result = ln.getNextChar(buf, max_size);    \
    /* means failed, false: */                 \
    if (result == 0 )                          \
        result = YY_NULL;                      \
}

%}

%x COMMENT

%option nounput

%%

    /* ---[ key words ]------------------------------------------------------ */

(help) {
    ln.update(yytext);
    return HELP;
}

(list) {
    ln.update(yytext);
    return LIST;
}

(new) {
    ln.update(yytext);
    return NEW;
}

(delete) {
    ln.update(yytext);
    return DELETE;
}

(exit) {
    ln.update(yytext);
    return EXIT;
}

(let) {
    ln.update(yytext);
    return LET;
}


    /* ---[ comments ]------------------------------------------------------- */
(;) {
    ln.update(yytext);
    BEGIN COMMENT;
}

<COMMENT>\n {
    ln.update(yytext);
    BEGIN INITIAL;
    return NEWLINE;
}

<COMMENT>. {
    ln.update(yytext);
    // ignore all character but newline
}


    /* ---[ others ]--------------------------------------------------------- */
(\"([^\"]*(\\\")*)*\"|\'([^\']*(\\\')*)*\') {
    // means: string
    ln.update(yytext);

    std::string temp_string(yytext);
    yylval.strp = new std::string(
        temp_string.substr(1, temp_string.size() - 2)
    );
    return STRING;
}

([a-zA-Z_][a-zA-Z0-9_]*) {
    ln.update(yytext);
    yylval.strp = new std::string(yytext);
    return TOKEN;
}

(\n) {
    ln.update(yytext);
    return NEWLINE;
}

("[") {
    ln.update(yytext);
    return PER_L;
}

("]") {
    ln.update(yytext);
    return PER_R;
}

[ \t\r]+ {
    ln.update(yytext);
    // skip when meet white space (but not newline)
}

. {
    // error
    return UNKNOWED;
}


%%

int yywrap(void) {
    return 1;
}

