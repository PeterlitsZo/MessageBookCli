#include "lineno.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <iomanip>
#include <type_traits>

using std::string;
using std::istream;
using std::getline;
using std::getc;

Lineno::Lineno(istream& file): file_(file) {
    lineno_ = 0;
    start_  = 0;
    next_   = 1;

    line_   = "";
    pos_    = 0;
}

int Lineno::start() {
    return start_;
}

int Lineno::next() {
    return next_;
}

int Lineno::lineno() {
    return lineno_;
}

bool Lineno::getNextLine(void) {
    // add lineno
    ++lineno_;

    // read line
    if ( ! getline(file_, line_) ) {
        // touch the EOF.
        return false;
    }
    line_ += '\n';

    // init those var: pos, the scanner pointer,
    //                 start, the first token's pos
    pos_   = 0;
    start_ = 0;
    next_  = 1;

    return true;
}

int  Lineno::getNextChar(char* buffer, int maxBuffer) {
    const int FAIL    = 0;
    const int SUCCESS = 1;

    // if at the line's end, then try to get the next line
    if ( pos_ >= line_.size() ) {
        if ( ! getNextLine() ) {
            return FAIL;
        }
    }

    // read the next character
    buffer[0] = line_[pos_];
    ++pos_;

    // assert that the character we get is not 0('\0');
    return (buffer[0] == 0) ? FAIL : SUCCESS;
}

void Lineno::update(string token) {
    // std::cout << start_ << ' ' << next_ << " -> " << next_ << ' '<< pos_ << '\n';
    start_ = next_;
    next_  = pos_;
}
