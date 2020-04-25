#include <iostream>
#include <string>
#include "info.h"
#include "cmdline.h"
using std::cout;
using std::string;

// ---[ unit function for main ]-----------------------------------------------
cmdline::parser parse_cmdline(int argc, char **argv);

// ---[ interaction mode's main loop ]-----------------------------------------
bool main_meun() {
    cout << info::meun;
    return false;
}

// ---[ the main part: main function ]-----------------------------------------
int main(int argc, char **argv) {
    // parse the command line
    cmdline::parser argparser = parse_cmdline(argc, argv);

    // ---[ output the version info ]---
    if( argparser.exist("version") ) {
        cout << info::version;

        return 0;
    }

    // ---[ going into the main loop ]---
    if( argc == 1 || argparser.exist("interaction") ) {
        while(main_meun())
            ;

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

    argparser.parse_check(argc, argv);
    return argparser;
}
