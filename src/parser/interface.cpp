#include "interface.h"

#include <string>
#include <typeinfo>

#include "../info.h"
#include "../messagebook.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;

// ---[ command ]--------------------------------------------------------------

string help(MessageBook& mb) {
    return info::help_doc;
}

string add (MessageBook& mb) {
    return "New empty person object's hash: " + mb.addPerson();
}

string list(MessageBook& mb) {
    return mb.str();
}

// ---[ save ]-----------------------------------------------------------------

void save(MessageBook& mb) {
    mb.save();
}

// ---[ input/output ]---------------------------------------------------------

void print_command(string str) {
    cout << "  | ";
    for(auto it = str.begin(); it != str.end(); ++it) {
        if(*it == '\n' ) {
            if( it + 1 != str.end() ) {
                cout << "\n  | ";
            }
        } else {
            cout << *it;
        }
    }
    cout << '\n';
}

void print_next_arraw() {
    cout << ">>> ";
}

// ---[ print error ]----------------------------------------------------------
void yyerror(const char* s) {
    cerr << "^^^ [syntzx error]: " << s << std::endl;
}
