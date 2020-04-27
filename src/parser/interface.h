#ifndef PETERLITS_INTERFACE_H__
#define PETERLITS_INTERFACE_H__

#include <string>

#include "../messagebook.h"
#include "../info.h"

std::string help(MessageBook& mb);
std::string add (MessageBook& mb);
std::string list(MessageBook& mb);

void save(MessageBook& mb);

void print_command(std::string str);
void print_next_arraw(void);

void yyerror(const char *s);

#endif // for ifndef PETERLITS_INTERFACE_H__
