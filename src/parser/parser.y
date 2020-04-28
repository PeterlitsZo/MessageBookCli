%{

#include <string>

#include "interface.h"
#include "../messagebook.h"
#include "../person_ptr.h"
#include "../units.h"

MessageBook mb("MessageBook.json");

#define YYERROR_VERBOSE

extern void yyerror(const char *s);

extern "C" {
    extern int yylex(void);
}

// ---[ better error msg ]-----------------------------------------------------

%}

%union {
    std::string* strp;
    PersonPtr*   pptr;
}

%token PER_L PER_R

%token HELP LIST ADD DELETE EXIT NEWLINE UNKNOWED

%token TOKEN

%token <strp> HEX_ID;
%type  <strp> STRING;
%type  <pptr> PERSON;
%type  <strp> EXPR;

%%

commands
    : // *empty*
    | commands command {
        print_next_arraw();
    }
    | commands error NEWLINE {
        yyerrok;
        print_next_arraw();
        // reflash
        // ln.getNextLine();
    }
    ;

command
    : HELP NEWLINE {
        print_command(help(mb));
    }
    | LIST NEWLINE {
        print_command(list(mb));
    }
    | ADD NEWLINE {
        print_command(add(mb));
    }
    | EXIT NEWLINE {
        return 0;
    }
    | DELETE HEX_ID NEWLINE {
        print_command(*$2);
        delete $2;
    }
    | EXPR NEWLINE {
        print_command(*$1);
        delete $1;
    }
    | NEWLINE {
        // nothing input
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
