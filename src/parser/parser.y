%{

#include <string>

#include "interface.h"
#include "idmap.h"
#include "../messagebook.h"
#include "../person_ptr.h"
#include "../units.h"

Idmap       im;                       // use to hold all variable
MessageBook mb("MessageBook.json");   // use to handle date

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
%token HELP LIST NEW DELETE EXIT LET NEWLINE INIT UNKNOWED

%token <strp> TOKEN
%token <strp> STRING;

%type  <pptr> PERSON;
%type  <strp> EXPR_RESULT;

%%

commands
    : // *empty*
    | commands command {
        print_next_arraw();
        save(mb);
    }
    | commands error NEWLINE {
        yyerrok;
        print_next_arraw();
    }
    ;

command
    : HELP NEWLINE {
        print_command(help(mb));
    }
    | LIST NEWLINE {
        print_command(list(mb));
    }
    | EXIT NEWLINE {
        return 0;
    }
    | DELETE PERSON NEWLINE {
        if ($2) {
            if (not $2->remove()) {
                yyerror("runtime error: try to delete a [NULL person] person");
            }
        } else {
            yyerror("runtime error: try to delete a nil");
        }
        // [delete]: PERSON
        delete $2;
    }
    | INIT PERSON NEWLINE {
        if ($2) {
            if (not $2->init()) {
                yyerror("runtime error: try to delete a [NULL person] person");
            }
        } else {
            yyerror("runtime error: try to delete a nil");
        }
    }
    | EXPR_RESULT NEWLINE {
        print_command(*$1);
        // [delete]: EXPR
        delete $1;
    }
    | LET TOKEN STRING NEWLINE {
        im.update(*($2), new Val($3));
        // [delete]: TOKEN
        delete $2;
        // [do not delete]: STRING, because im handle it, im will delete auto
    }
    | LET TOKEN PERSON NEWLINE {
        im.update(*($2), new Val($3));
        // [delete]: TOKEN
        delete $2;
        // [do not delete]: PERSON, because im handle it, im will delete it auto
    }
    | NEWLINE {
        // nothing input
    }
    ;

/* need delete, type: string*: mean: return output */
EXPR_RESULT
    : PERSON {
        $$ = new std::string($1->str());
        // [delete]: PERSON
        delete $1;
    }
    | STRING {
        $$ = $1;
    }
    | TOKEN {
        $$ = new std::string(im.get(*($1))->str());
        // [delete]: TOKEN
        delete $1;
    }
    ;

/* need delete, type: personPtr* */
PERSON
    : PER_L STRING PER_R {
        $$ = new PersonPtr(mb.get(*$2));
    }
    | NEW {
        $$ = mb.addPerson();
    }
    | TOKEN {
        $$ = im.get(*($1))->getPersonPtr();
    }
    ;

%%
