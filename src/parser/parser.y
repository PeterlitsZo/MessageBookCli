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
%token HELP LIST NEW DELETE EXIT LET NEWLINE UNKNOWED

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
        $2->remove();
        // [delete]: PERSON
        delete $2;
    }
    | EXPR_RESULT NEWLINE {
        print_command(*$1);
        // [delete]: EXPR
        delete $1;
    }
    | LET TOKEN STRING NEWLINE {
        IdmapValue temp;
        temp.type    = IdmapValue::TYPE::STRING;
        temp.value.s = $3;
        im[*($2)] = temp;
        // [delete]: TOKEN
        delete $2;
        // [do not delete]: STRING, because im handle it
    }
    | LET TOKEN PERSON NEWLINE {
        IdmapValue temp;
        temp.type    = IdmapValue::TYPE::PERSON;
        temp.value.p = $3;
        im[*($2)] = temp;
        // [delete]: TOKEN
        delete $2;
        // [do not delete]: PERSON, because im handle it
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
        $$ = new std::string(im[*($1)].str());
        // [delete]: TOKEN
        delete $1;
    }
    ;

/* need delete, type: personPtr* */
PERSON
    : PER_L STRING PER_R {
        $$ = new PersonPtr(mb, *$2);
    }
    | NEW {
        $$ = mb.addPerson();
    }
    ;

%%
