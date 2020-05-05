#include "units.h"

#include <cstdint>
#include <cstdio>
#include <istream>
#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include <vector>
#include <exception>

#include "../include/digestpp/digestpp.hpp"

using std::string;
using std::vector;
using std::regex;
using std::istream;
using std::ostream;
using std::stringstream;

namespace units {


// ----------------------------------------------------------------------------
// ---[ function for has ]-----------------------------------------------------
// ----------------------------------------------------------------------------

string md5(string str) {
    return digestpp::md5().absorb(str).hexdigest();
}

// ----------------------------------------------------------------------------
// ---[ function for check ]---------------------------------------------------
// ----------------------------------------------------------------------------

bool is_digit(char ch) {
    if(ch >= '0' && ch <= '9') {
        return true;
    } else {
        return false;
    }
}

bool is_digit(string str) {
    // if there is at least one char is not digit then the string is not digit
    for(auto ch_ptr = str.begin(); ch_ptr != str.end(); ++ch_ptr) {
        if(!is_digit(*ch_ptr)) {
            return false;
        }
    }
    // if all char is digit then the string is digit
    return true && str.size() != 0;
}

bool is_email(string str) {
    // if the format is like "abc@abc.abc"
    regex EmailPattern(R"(^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$)");
    std::match_results<string::const_iterator> Result;
    if(std::regex_match(str, Result, EmailPattern)) {
        return true;
    } else {
        return false;
    }
}

bool is_not_empty(string str) {
    return str.size() != 0;
}

// ----------------------------------------------------------------------------
// ---[ function for string repr-output ]--------------------------------------
// ----------------------------------------------------------------------------

string repr(string str) {
    string result;
    result += "\'";

    for (auto it = str.begin(); it != str.end(); ++it) {
        int temp_int;
        switch(*it) {
        case '\\':
            result += "\\\\";
            break;
        case '\'':
            result += "\\\'";
            break;
        case '\"':
            result += "\\\"";
            break;
        case '\n':
            result += "\\n";
            break;
        case '\r':
            result += "\\r";
        case '\t':
            temp_int = (4 - result.size())?(4 - result.size()):4;
            result += string(temp_int, ' ');
            break;
        default:
            result += *it;
            break;
        }
    }

    result += "\'";
    return result;
}

string repr(char* str) {
    return repr(string(str));
}

string repr(const char* str) {
    return repr(string(str));
}

// ----------------------------------------------------------------------------
// ---[ function for string ]--------------------------------------------------
// ----------------------------------------------------------------------------
vector<string> split(string str) {
    regex space_re(R"(\s+)");
    return vector<string>(
        std::sregex_token_iterator(str.begin(), str.end(), space_re, -1),
        std::sregex_token_iterator()
    );
}


string hard_warp(string str, int width) {
    string result;
    int pos = 0;
    for(auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
        ++ pos;
        if (*it == '\n') {
            pos = 0;            // if there is a soft here, then reset pos
        }
        if (pos == width && it + 1 != str.end()) {
            pos = 0;            // reset
            result += '\n';
        }
    }
    return result;
}


string add_head(string str, string head) {
    string result;
    result += head;
    for(auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
        // when meet newline-token then add head
        if(*it == '\n') {
            result += head;
        }
    }
    return result;
}

string parse_str_repr(string str) {
    stringstream ss;

    char edge_token = str[0];
    bool IN_ESCAPE  = false;
    for(auto it = str.begin() + 1; it != str.end(); ++it) {
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
                if (it + 1 != str.end() ) {
                    throw bad_parser(
                            "parse error. except meet useable edge token at end"
                            " (meet \'" + string() + *it + "\')"
                          );
                }
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


// sub units for the below function

bool is_space(char ch) {
    return std::regex_match(string() + ch, std::regex("\\s"));
}

// end of the sub units

vector<string> parse_vecstr_repr(string str) {
    vector<string> result;
    string atom;
    char edge_token;
    // status block
    struct S {
        enum t1 {in_list, out_list}              IN_LIST     ;
        enum t2 {ok_next, not_ok_next, ok_both}  OK_FOR_NEXT ;
        enum t3 {in_str, in_str_escape, out_str} IN_STRING   ;

        S(t1 in_list, t2 ok_for_next, t3 in_string)
            :IN_LIST(in_list), OK_FOR_NEXT(ok_for_next), IN_STRING(in_string)
            {}
        bool operator==(const S& value) const {
            return value.IN_STRING == IN_STRING
                && value.OK_FOR_NEXT == OK_FOR_NEXT
                && value.IN_LIST == IN_LIST;
        }
    } status(S::out_list, S::not_ok_next, S::out_str);

    // loop block
    for (auto it = str.cbegin(); it != str.cend(); ++it) {
        // ---[ going to be in list ]
        // at the outside of list
        if (status == S(S::out_list, S::not_ok_next, S::out_str)) {
            if(*it == '[') {
                status.IN_LIST = S::in_list;
                status.OK_FOR_NEXT = S::ok_both;
            } else {
                throw bad_parser("prase error. except the first token is \'[\'");
            }

        // ---[ going to be in string or get the end of string ]
        // at the inside of list and going to read a string
        } else if (status == S(S::in_list, S::ok_next, S::out_str)) {
            if (is_space(*it)) {
                ; // do nothing
            } else if (*it == '\'' or *it == '\"') {
                status.OK_FOR_NEXT = S::not_ok_next;
                status.IN_STRING = S::in_str;
                atom += *it;
                edge_token = *it;
            } else {
                throw bad_parser("parse error. except a string");
            }
        // at the inside of list and except a token ']' or ','
        } else if (status == S(S::in_list, S::not_ok_next, S::out_str)) {
            if (is_space(*it)) {
                ; // do nothing
            } else if (*it == ',') {
                status.OK_FOR_NEXT = S::ok_next;
            } else if (*it == ']') {
                // ------------------------------------------------------------
                // out to list
                // ------------------------------------------------------------
                status.IN_LIST = S::out_list;
            } else {
                throw bad_parser("parse error, except a token \',\' or \']\'");
            }
        // at the inside of list and except a token ']' or a string
        } else if (status == S(S::in_list, S::ok_both, S::out_str)) {
            if (is_space(*it)) {
                ; // do nothing
            } else if (*it == '\'' or *it == '\"') {
                status.OK_FOR_NEXT = S::not_ok_next;
                status.IN_STRING = S::in_str;
                atom += *it;
                edge_token = *it;
            } else  if (*it == ']') {
                // ------------------------------------------------------------
                // out to list
                // ------------------------------------------------------------
                status.IN_LIST = S::out_list;
            } else {
                throw bad_parser("parser error, except a token \']\' or a string");
            }

        // ---[ in string ]----------------------------------------------------
        } else if (status == S(S::in_list, S::not_ok_next, S::in_str)) {
            // add self to string
            atom += *it;

            if (*it == '\\') {
                status.IN_STRING = S::in_str_escape;
            } else if (*it == edge_token) {
                // ------------------------------------------------------------
                // append result
                // ------------------------------------------------------------
                result.push_back(parse_str_repr(atom));
                atom = "";
                status.IN_STRING = S::out_str;
            }
        } else if (status == S(S::in_list, S::not_ok_next, S::in_str_escape)) {
            // add self to string
            atom += *it;

            status.IN_STRING = S::in_str;

        // ---[ error ]--------------------------------------------------------
        } else {
            throw bad_parser("unexcept status");
        }
    }

    return result;
}

// ----------------------------------------------------------------------------
// ---[ function for input ]---------------------------------------------------
// ----------------------------------------------------------------------------
Input::Input(istream& in, ostream& out) :in_(in), out_(out) {}

istream& Input::operator() (string info) {
    out_ << ' ' << info << " > ";
    return in_;
}

istream& input(string info) {
    std::cout << ' ' << info << " > ";
    return std::cin;
}

istream& input(ostream& out, istream& in, string info) {
    out << ' ' << info << " > ";
    return in;
}

// ----------------------------------------------------------------------------
// ---[ string function ]------------------------------------------------------
// ----------------------------------------------------------------------------
bool start_with(string full, string sub) {
    return full.find(sub) == 0 ? true: false;
}

} // for namespace units


