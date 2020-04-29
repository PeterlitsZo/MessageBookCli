#include "interface.h"

#include <sstream>
#include <string>
#include <typeinfo>

#include "lineno.h"
#include "../help/help.h"
#include "../info.h"
#include "../messagebook.h"

using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

Lineno ln(cin);

// ---[ command ]--------------------------------------------------------------

string help(MessageBook& mb) {
    return HELP::HELP;
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

// ---[ parse ]----------------------------------------------------------------

string parse_str(string str) {
    assert(str.size() >= 2);
    stringstream ss;

    char edge_token = str[0];
    bool IN_ESCAPE  = false;
    for(auto it = str.begin(); it != str.end(); ++it) {
        if (IN_ESCAPE) {
            switch(*it) {
            case '\\': /* fail down */
            case '\"': /* fail down */
            case '\'': /* fail down */
            case '?':  ss << *it; break;

            case 't':  ss << '\t'; break;
            case 'n':  ss << '\n'; break;
            case 'r':  ss << '\r'; break;
            case 'a':  ss << '\a'; break;
            case 'b':  ss << '\b'; break;
            case 'f':  ss << '\f'; break;
            case 'v':  ss << '\v'; break;

            default:   ss << "\\" << *it;
            }
            IN_ESCAPE = false;
        } else {
            if (*it == edge_token) {
                // it must be at the last one index.
                // assert(it - str.begin() == str.size() - 1);
                return ss.str();
            } else if (*it == '\\') {
                IN_ESCAPE = true;
            } else {
                ss << *it;
            }
        }
    }
    return ss.str();
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


