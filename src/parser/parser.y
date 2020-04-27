%{

#include <iostream>
#include <string>

// for C function
#include <stdio.h>
#include "../messagebook.h"
#include "../info.h"

using std::cout;
using std::cerr;
using std::string;

MessageBook mb("MessageBook.json");

void end_command(void);
void print_command(string str);
void print_command(void);

string help(void);
string add(void);

extern "C" {
    void yyerror(const char *s);
    extern int yylex(void);
}

%}


%token HELP LIST ADD DELETE EXIT NEWLINE
%token HEX_STRING TOKEN

%%

commands : // empty
         | commands command NEWLINE {
            end_command();
         }
         | error NEWLINE {
            yyerrok;
            end_command();
         }
         ;

command  : HELP {
            print_command(help());
         }
         | LIST
         | ADD {
            print_command(add());
         }
         | EXIT {
            return 0;
         }
         | DELETE HEX_STRING
         ;

%%

void yyerror(const char *s) {
    cerr << "^^^ [syntax error]: " << s << std::endl;
}

// ----------------------------------------------------------------------------

void end_command(void) {
    cout << ">>> ";
}

void print_command(string str) {
    cout << "||| ";
    for(auto it = str.begin(); it != str.end(); ++it) {
        if(*it == '\n') {
            cout << "\n||| ";
        } else {
            cout << *it;
        }
    }
    cout << '\n';
}

void print_command(void) {
    cout << "||| ";
}

// ----------------------------------------------------------------------------

string help(void) {
    return info::help_doc;
}

string add(void) {
    return "New empty person object's hash: " + mb.addPerson();
}
