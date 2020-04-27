%{

#include "interface.h"

MessageBook mb("MessageBook.json");

extern void yyerror(const char *s);

extern "C" {
    extern int yylex(void);
}

%}


%token HELP LIST ADD DELETE EXIT NEWLINE
%token HEX_STRING TOKEN

%%

commands : // empty
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

command  : HELP {
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
         | DELETE HEX_STRING
         ;

%%
