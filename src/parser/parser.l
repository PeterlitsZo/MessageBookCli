%{

#include <string>
#include <iostream>

#include "interface.h"
#include "../units.h"
#include "../val/val.h"

// this macro should be at the below of ../val.h
#define YYSTYPE std::shared_ptr<mbc::Val::ValBase>
// and is higher than parser.h

#include "parser.h"

using std::make_shared;
using std::dynamic_pointer_cast;
using std::string;

using mbc::Val::Str;
using mbc::Val::VecStr;


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

STRING_1 (\"([^\"\n]*(\\\")*)*\")
STRING_2 (\'([^\'\n]*(\\\')*)*\')
STRING ({STRING_1}|{STRING_2})
WHITE ([ \n\t\r\v\f])

STRING_LIST (({STRING}{WHITE}*,{WHITE}*)*{STRING})
LIST (\[{WHITE}*{STRING_LIST}{WHITE}*\]|\[{WHITE}*\])

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

(init) {
    ln.update(yytext);
    return INIT;
}
(sort) {
    ln.update(yytext);
    return SORT;
}
(sreach) {
    ln.update(yytext);
    return SREACH;
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

{STRING} {
    // means: string
    ln.update(yytext);

    yylval = make_shared<Str>();
    dynamic_pointer_cast<Str>(yylval) -> reprset(yytext);
    return STRING;
}

{LIST} {
    // means: vecstr
    ln.update(yytext);

    yylval = make_shared<VecStr>();
    dynamic_pointer_cast<VecStr>(yylval) -> set(yytext);
    return VECSTR;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    ln.update(yytext);

    yylval = make_shared<Str>();
    dynamic_pointer_cast<Str>(yylval) -> set(yytext);
    return TOKEN;
}

(<) {
    return LEFT_TRI_BRA;
}

(>) {
    return RIGHT_TRI_BRA;
}

(\() {
    return LEFT_BRA;
}

(\)) {
    return RIGHT_BRA;
}

(\.) {
    return DOT;
}

(\n) {
    ln.update(yytext);
    return NEWLINE;
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
    // means: only one file
    return 1;
}

