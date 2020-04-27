%{

#include "parser.h"

extern "C" {
    int yywrap(void);
    int yylex(void);
}

%}

%x COMMENT

%%

    /* ---[ key words ]------------------------------------------------------ */

(help) {
    return HELP;
}

(list) {
    return LIST;
}

(add) {
    return ADD;
}

(delete) {
    return DELETE;
}


    /* ---[ comments ]------------------------------------------------------- */
(;) {
    BEGIN COMMENT;
}

<COMMENT>\n {
    BEGIN INITIAL;
    return NEWLINE;
}

<COMMENT>. {
    // ignore all character but newline
}


    /* ---[ others ]--------------------------------------------------------- */
([0-9a-fA-F]{6,}) {
    return HEX_STRING;
}

([a-zA-Z_][a-zA-Z0-9_]*) {
    return TOKEN;
}

(\n) {
    return NEWLINE;
}


%%

int yywrap(void) {
    return 1;
}

