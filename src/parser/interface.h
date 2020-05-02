#ifndef PETERLITS_INTERFACE_H__
#define PETERLITS_INTERFACE_H__

#include <string>

#include "lineno.h"
// #include "../messagebook.h"
#include "../info.h"

extern Lineno ln;

// std::string help(MessageBook& mb);
// std::string add (MessageBook& mb);
// std::string list(MessageBook& mb);
// 
// void save(MessageBook& mb);

void print_command(std::string str);
void print_next_arraw(void);

std::string parse_str(std::string str);

void yyerror(const char *s);

#endif // for ifndef PETERLITS_INTERFACE_H__
