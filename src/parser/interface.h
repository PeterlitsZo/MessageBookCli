#ifndef PETERLITS_INTERFACE_H__
#define PETERLITS_INTERFACE_H__

#include <string>

#include "lineno.h"
#include "../info.h"

extern Lineno ln;

void print_command(std::string str);
void print_next_arraw(void);

std::string parse_str(std::string str);

void yyerror(const char *s);

#endif // for ifndef PETERLITS_INTERFACE_H__
