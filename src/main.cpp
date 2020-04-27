#include <iostream>
#include <string>

#include "../include/cmdline/cmdline.h"

#include "units.h"
#include "info.h"
#include "person_ptr.h"
#include "messagebook.h"
#include "person.h"

#include "./parser/parser.h"

using std::cout;
using std::cin;
using std::string;

// ---[ unit function for main ]-----------------------------------------------
cmdline::parser parse_cmdline(int argc, char **argv);

// ---[ interaction mode's main loop ]-----------------------------------------
bool main_meun(MessageBook& mb) {
    units::Input input(cin, cout);
    int choose;
    cout << info::meun;
    cin >> choose;

    string name, sex, telephone, location, mail_number, email, qq_number, temp;
    // [WRANING] this is not a good name;
    string temp1, temp2;
    switch (choose) {
    case 1:
        mb.addPerson(cin, cout);
        break;
    case 2:
        // searchInfo();
        break;
    case 3:
        cout << mb;
        break;
    case 4:
        input("please enter info's ID") >> temp;
        input("please enter info's key") >> temp1;
        input("please enter info's value") >> temp2;
        mb.get(temp).change(temp1, temp2);
        break;
    case 5:
        input("please enter info's ID") >> temp;
        mb.get(temp).remove();
        break;
    case 6:
        // Break the loop;
        return false;
    default:
        return true;
    }
    mb.save();
    return true;
}

void interaction() {
    cout << "MessageBookCli " << info::version << std::endl;
    cout << "Enter command `help' for help\n" << std::endl;
    cout << ">>> ";
    yyparse();
}

// ---[ the main part: main function ]-----------------------------------------
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

    argparser.parse_check(argc, argv);
    return argparser;
}
