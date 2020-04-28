#ifndef PETERLITS_LINENO_H__
#define PETERLITS_LINENO_H__

#include <string>
#include <istream>

class Lineno {
public:
    Lineno(std::istream& file);

    int  getNextChar(char* buffer, int maxBuffer);
    void update(std::string token);
    bool getNextLine(void);

    int start();
    int next();
    int lineno();

private:
    // ---[ data ]-------------------------------------------------------------
    size_t        lineno_;       // the index of line;
    size_t        start_;        // this word's start index
    size_t        next_;         // the next word's start index

    size_t        pos_;          // the postion of scanner (in line)
    std::string   line_;         // the line string
    std::istream& file_;         // the file object
};

#endif // for ifndef PETERLITS_LINENO_H__
