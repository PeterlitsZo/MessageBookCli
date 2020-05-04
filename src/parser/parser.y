%{

#include <string>
#include <memory>

#include "interface.h"
#include "idmap.h"
#include "../units.h"

#include "../val.h"

#define YYERROR_VERBOSE

extern void yyerror(const char *s);

using std::make_shared;
using std::shared_ptr;
using std::dynamic_pointer_cast;

using mbc::Val::Type;
using mbc::Val::ValBase;
using mbc::Val::Str;
using mbc::Val::VecStr;
using mbc::Val::PersonHandle;
using mbc::Val::MessageBook;

// using units::mbc_exce;

// shared_ptr<ValBase> book = 
//     make_shared<mbc::Val::MessageBook>(std::string("MessageBook.json"));

mbc::Val::MessageBook book("MessageBook.json");
Idmap im;

extern "C" {
    extern int yylex(void);
}

// ---[ type ]-----------------------------------------------------------------
#define YYSTYPE std::shared_ptr<mbc::Val::ValBase>

// ---[ better error msg ]-----------------------------------------------------

%}

%token HELP LIST NEW DELETE EXIT LET INIT SORT SREACH

%token LEFT_TRI_BRA RIGHT_TRI_BRA DOT

%token NEWLINE 
%token UNKNOWED
%token STRING
%token VECSTR

%token TOKEN

%%

commands
    : // *empty*
    | commands command {
        print_next_arraw();
    }
    | commands error NEWLINE {
        yyerrok;
        print_next_arraw();
    }
    ;

command
    : HELP NEWLINE {
    }
    | EXIT NEWLINE {
        return 0;
    }
    | SORT TOKEN NEWLINE {
        // assrt that expr$1 is LIST and the expr$2 is STRING
    }
    | DELETE expr NEWLINE {
        // assert that expr is PERSONHANDLE
        if ($2 -> type() != Type::PERSONHANDLE) {
            yyerror("wanna a PersonHandle after `delete\'");
        }
        dynamic_pointer_cast<PersonHandle>($2) -> remove();
    }

    | expr NEWLINE {
        print_command($1 -> str());
    }

    | LET TOKEN expr NEWLINE {
        im.update(dynamic_pointer_cast<Str>($2) -> raw(), $3);
    }
    | LET expr DOT TOKEN expr NEWLINE {
        // assert that the expr$1 is PERSONHANDLE and the $2 is a STRING, or VECSTR
        if ($2 -> type() != Type::PERSONHANDLE) {
            yyerror("wanna a PersonHandle after `let\'");
        }

        if ($4 -> type() == Type::STR) {
            dynamic_pointer_cast<PersonHandle>($2)
                -> changeAttr(dynamic_pointer_cast<Str>($4) -> raw(),
                              dynamic_pointer_cast<Str>($5) -> raw());
        } else if ($4 -> type() == Type::VECSTR) {
            dynamic_pointer_cast<PersonHandle>($2)
                -> changeAttr(dynamic_pointer_cast<Str>($4) -> raw(),
                              dynamic_pointer_cast<VecStr>($5) -> raw());
        } else {
            yyerror("wanna a Str or VecStr after dot - `.\'");
        }
    }

    | NEWLINE {
        // do nothing
    }
    ;

expr
    : STRING {
        $$ = $1;
    }
    | VECSTR {
        $$ = $1;
    }
    | LEFT_TRI_BRA expr RIGHT_TRI_BRA {
        if ($2 -> type() != Type::STR) {
            // throw mbc_exce("wanna a str type object");
            throw "wanna a str type object";
        }

        auto handle = book.getPerson(dynamic_pointer_cast<Str>($2) -> raw());
        shared_ptr<ValBase> ptr(new PersonHandle(handle));
        $$ = ptr;
    }
    | LIST {
        $$ = make_shared<MessageBook>(book);
    }
    | NEW {
        $$ = make_shared<PersonHandle>(book.newPerson());
    }
    | TOKEN {
        try {
            $$ = im.get(dynamic_pointer_cast<Str>($1) -> raw());
        } catch (const char* msg) {
            yyerror(msg);
        }
    }
    | SREACH expr TOKEN {
        // assert that expr is LIST
        if ($2 -> type() != Type::STR) {
            yyerror("wanna a string after `sreach\'");
        }
        auto handle = book.sreach(dynamic_pointer_cast<Str>($1) -> raw(),
                                  dynamic_pointer_cast<Str>($3) -> raw());
        shared_ptr<ValBase> ptr(new PersonHandle(handle));
        $$ = ptr;
    }
    ;

%%
