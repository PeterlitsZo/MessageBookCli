#include <iostream>
#include <string>

#include "../include/cmdline/cmdline.h"
#include "../include/logging/easylogging++.h"

#include "units.h"
#include "info.h"

#include "./parser/parser.h"

using std::cout;
using std::cin;
using std::string;

// ---[ unit function for main ]-----------------------------------------------
cmdline::parser parse_cmdline(int argc, char **argv);

// ---[ interaction mode's main loop ]-----------------------------------------
void interaction() {
    cout << "MessageBookCli " << info::version << std::endl;
    cout << "Enter command `help' for help\n" << std::endl;
    cout << ">>> ";
    yyparse();
}

// ---[ the main part: main function ]-----------------------------------------

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
    // parse the command line
    cmdline::parser argparser = parse_cmdline(argc, argv);

    // ---[ output the version info ]---
    if( argparser.exist("version") ) {
        cout << info::version << std::endl;
        return 0;
    }

    // ---[ going into the main loop ]---
    if( argc == 1 || argparser.exist("interaction") ) {
        interaction();
        return 0;
    }
}

// ---[ unit function for main ]-----------------------------------------------
cmdline::parser parse_cmdline(int argc, char **argv) {
    cmdline::parser argparser;

    // argparser: use '-i' or '--interaction' to get into interaction mode
    argparser.add("interaction", 'i', "in interaction mode (default)");
    // argparser: use '-v' or '--version' to show the version info
    argparser.add("version",     'v', "show the info of version");
    // argparser: use '-h' or '--help' to show the version info
    // [...](define by deafault)

    argparser.parse_check(argc, argv);
    return argparser;
}
