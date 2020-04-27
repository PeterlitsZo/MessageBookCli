%{

#include <string>
#include "../messagebook.h"
#include "../person_ptr.h"

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

(exit) {
    return EXIT;
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
(\"[0-9a-fA-F]{4,}\"|\'[0-9a-fA-F]{4,}\') {
    std::string temp_string(yytext);
    yylval.strp = new std::string(
        temp_string.substr(1, temp_string.size() - 2)
    );
    return HEX_ID;
}

([a-zA-Z_][a-zA-Z0-9_]*) {
    return TOKEN;
}

(\n) {
    return NEWLINE;
}

("[") {
    return PER_L;
}

("]") {
    return PER_R;
}

[ \t\r]+ {
    // skip when meet white space (but not newline)
}


%%

int yywrap(void) {
    return 1;
}

