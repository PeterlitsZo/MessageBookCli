%{

#include <string>
#include <iostream>

#include "interface.h"
#include "../units.h"
#include "../val/val.h"

// this macro should be at the below of ../val.h
#define YYSTYPE std::shared_ptr<mbc::Val::ValBase>
// and is higher than parser.h

#include "parser.h"

using std::make_shared;
using std::dynamic_pointer_cast;
using std::string;

using mbc::Val::Str;
using mbc::Val::VecStr;


extern "C" {
    int yywrap(void);
    int yylex(void);
}

// ---[ for unistd.h on Windows ]----------------------------------------------

#defend YY_NO_UNISTD_H

#ifndef PETERLITS_UNISTD_H__
#define PETERLITS_UNISTD_H__

/* This is intended as a drop-in replacement for unistd.h on Windows.
 * Please add functionality as neeeded.
 * https://stackoverflow.com/a/826027/1202830
 */

#include <stdlib.h>
#include <io.h>
// #include "getopt.h" /* getopt at: https://gist.github.com/ashelly/7776712 */
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h> /* for _getcwd() and _chdir() */

#define srandom srand
#define random rand

 /* Values for the second argument to access.
    These may be OR'd together.  */
#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
    //#define   X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK    0       /* Test for existence.  */

#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek
/* read, write, and close are NOT being #defined here, because while there are
   file handle specific versions for Windows, they probably don't work for
   sockets. You need to look at your app and consider whether to call e.g.
   closesocket(). */

#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t long
#endif

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif // !PETERLITS_UNISTD_H__

// ---[ defines ]--------------------------------------------------------------

// better YY_INPUT
#define YY_INPUT(buf, result, max_size) {      \
    result = ln.getNextChar(buf, max_size);    \
    /* means failed, false: */                 \
    if (result == 0 )                          \
        result = YY_NULL;                      \
}

%}

%x COMMENT

%option nounput

STRING_1 (\"([^\"\n]*(\\\")*)*\")
STRING_2 (\'([^\'\n]*(\\\')*)*\')
STRING ({STRING_1}|{STRING_2})
WHITE ([ \n\t\r\v\f])

STRING_LIST (({STRING}{WHITE}*,{WHITE}*)*{STRING})
LIST (\[{WHITE}*{STRING_LIST}{WHITE}*\]|\[{WHITE}*\])

%%

    /* ---[ key words ]------------------------------------------------------ */

(help) {
    ln.update(yytext);
    return HELP;
}

(list) {
    ln.update(yytext);
    return LIST;
}

(new) {
    ln.update(yytext);
    return NEW;
}

(delete) {
    ln.update(yytext);
    return DELETE;
}

(exit) {
    ln.update(yytext);
    return EXIT;
}

(let) {
    ln.update(yytext);
    return LET;
}

(init) {
    ln.update(yytext);
    return INIT;
}
(sort) {
    ln.update(yytext);
    return SORT;
}
(sreach) {
    ln.update(yytext);
    return SREACH;
}

    /* ---[ comments ]------------------------------------------------------- */

(;) {
    ln.update(yytext);
    BEGIN COMMENT;
}

<COMMENT>\n {
    ln.update(yytext);
    BEGIN INITIAL;
    return NEWLINE;
}

<COMMENT>. {
    ln.update(yytext);
    // ignore all character but newline
}

    /* ---[ others ]--------------------------------------------------------- */

{STRING} {
    // means: string
    ln.update(yytext);

    yylval = make_shared<Str>();
    dynamic_pointer_cast<Str>(yylval) -> reprset(yytext);
    return STRING;
}

{LIST} {
    // means: vecstr
    ln.update(yytext);

    yylval = make_shared<VecStr>();
    dynamic_pointer_cast<VecStr>(yylval) -> set(yytext);
    return VECSTR;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    ln.update(yytext);

    yylval = make_shared<Str>();
    dynamic_pointer_cast<Str>(yylval) -> set(yytext);
    return TOKEN;
}

(<) {
    return LEFT_TRI_BRA;
}

(>) {
    return RIGHT_TRI_BRA;
}

(\() {
    return LEFT_BRA;
}

(\)) {
    return RIGHT_BRA;
}

(\.) {
    return DOT;
}

(\n) {
    ln.update(yytext);
    return NEWLINE;
}

[ \t\r]+ {
    ln.update(yytext);
    // skip when meet white space (but not newline)
}

. {
    // error
    return UNKNOWED;
}

%%

int yywrap(void) {
    // means: only one file
    return 1;
}

