#include "interface.h"

#include <sstream>
#include <string>
#include <typeinfo>

#include "lineno.h"
#include "../info.h"
#include "../messagebook.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

Lineno ln(cin);

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
static string errormsg(string s) {
    // cout << ln.start() << " " << ln.next() << '\n';
    string temp;
    std::stringstream ss(temp);
    ss << "  | ";
    for (int i = 0; i < ln.start() - 1 ; i++ ) {
        ss << ' ';
    }
    for (int i = ln.start(); i < ln.next(); i++ ) {
        ss << '^';
    }
    ss << "\n" << "  | " << "line " << ln.lineno() << "," 
       << ln.start() << ": " << s;
    return ss.str();
}

void yyerror(const char* s) {
    cerr << errormsg(s) << endl;
}


