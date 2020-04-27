%{

#include <string>

#include "interface.h"
#include "../messagebook.h"
#include "../person_ptr.h"
#include "../units.h"

MessageBook mb("MessageBook.json");

extern void yyerror(const char *s);

extern "C" {
    extern int yylex(void);
}

%}

%union {
    std::string* strp;
    PersonPtr*   pptr;
}

%token PER_L PER_R

%token HELP LIST ADD DELETE EXIT NEWLINE

%token TOKEN

%token <strp> HEX_ID;
%type  <strp> STRING;
%type  <pptr> PERSON;
%type  <strp> EXPR;

%%

commands
    : // empty
    | commands command NEWLINE {
        print_next_arraw();
    }
    | commands NEWLINE {
        // nothing input
        print_next_arraw();
    }
    | error NEWLINE {
        yyerrok;
        print_next_arraw();
    }
    ;

command
    : HELP {
        print_command(help(mb));
    }
    | LIST {
        print_command(list(mb));
    }
    | ADD {
        print_command(add(mb));
    }
    | EXIT {
        return 0;
    }
    | DELETE HEX_ID {
        print_command(*$2);
        delete $2;
    }
    | EXPR {
        print_command(*$1);
        delete $1;
    }
    ;

EXPR     
    : PERSON {
        $$ = new std::string($1->str());
        delete $1;
    }
    | STRING {
        $$ = $1;
    }
    ;

STRING
    : HEX_ID {
        $$ = $1;
    }
    ;

PERSON
    : PER_L HEX_ID PER_R {
        $$ = new PersonPtr(mb, *$2);
    }
    ;

%%
