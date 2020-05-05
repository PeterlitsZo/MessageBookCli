#include "interface.h"

#include <sstream>
#include <string>
#include <typeinfo>
#include <iostream>

#include "lineno.h"
#include "../help/help.h"
#include "../info.h"

using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

Lineno ln(cin);

// ---[ input/output ]---------------------------------------------------------

void print_command(string str) {
    // if the string is not empty
    if (str != "") {
        cout << "  | ";
        for(auto it = str.begin(); it != str.end(); ++it) {
            if(*it == '\n' ) {
                // and the '\n' is not at the end
                if( it + 1 != str.end() ) {
                    cout << "\n  | ";
                }
            } else {
                cout << *it;
            }
        }
        cout << '\n';
    }
}

void print_next_arraw() {
    cout << ">>> ";
}


// ---[ print error ]----------------------------------------------------------
static string errormsg(string s) {
    // cout << ln.start() << " " << ln.next() << '\n';
    string temp;
    std::stringstream ss(temp);
    // if there is a syntax error
    if ( ln.start() < ln.next() ) {
        ss << "  | ";
        for (int i = 0; i < ln.start() - 1 ; i++ ) {
            ss << ' ';
        }
        for (int i = ln.start(); i < ln.next(); i++ ) {
            ss << '^';
        }
        ss << "\n" << "  | " << "line " << ln.lineno() << "," 
           << ln.start() << ": " << s;
    } else {
        ss <<  "  | " << "line " << ln.lineno() << ": " << s;
    }
    return ss.str();
}

void yyerror(const char* s) {
    cerr << errormsg(s) << endl;
}


