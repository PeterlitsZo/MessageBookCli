%{

#include <string>
#include <memory>
#include <exception>

#include "interface.h"
#include "idmap.h"
#include "../units.h"

#include "../val/val.h"

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

%token LEFT_TRI_BRA RIGHT_TRI_BRA LEFT_BRA RIGHT_BRA DOT

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
        book.sort(dynamic_pointer_cast<Str>($2) -> raw());
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
    | subcommand NEWLINE {
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
    : LEFT_BRA subcommand RIGHT_BRA {
        $$ = $2;
    }
    | STRING {
        $$ = $1;
    }
    | VECSTR {
        $$ = $1;
    }
    | LEFT_TRI_BRA expr RIGHT_TRI_BRA {
        if ($2 -> type() != Type::STR) {
            yyerror("wanna a str type object");
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
    ;


subcommand
    : SREACH expr TOKEN {
        // assert that expr is LIST
        if ($2 -> type() != Type::STR) {
            yyerror("wanna a string after `sreach\'");
        }
        try {
            auto handle = book.sreach(dynamic_pointer_cast<Str>($2) -> raw(),
                                      dynamic_pointer_cast<Str>($3) -> raw());
            shared_ptr<ValBase> ptr = make_shared<PersonHandle>(handle);
            $$ = ptr;
        } catch(const char* msg) {
            yyerror(msg);
        }
    }
    | INIT expr {
        yyerror("init");
        if ($2 -> type() != Type::PERSONHANDLE) {
            yyerror("wanna a PersonHandle after `init\'");
        }
        try {
            dynamic_pointer_cast<PersonHandle>($2) -> init();
            $$ = $2;
        } catch (...) {
            yyerror( "the value is not in right syntax" );
        }
    }
    ;

%%
