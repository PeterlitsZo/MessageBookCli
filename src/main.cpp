#include <iostream>
#include <string>

#include "info.h"
#include "cmdline.h"
#include "person.h"
#include "messagebook.h"
#include "units.h"

using std::cout;
using std::cin;
using std::string;

// ---[ unit function for main ]-----------------------------------------------
cmdline::parser parse_cmdline(int argc, char **argv);

// ---[ interaction mode's main loop ]-----------------------------------------
bool main_meun(MessageBook& mb) {
    int choose;
    cout << info::meun;
    cin >> choose;

    string name, sex, telephone, location, mail_number, email, qq_number, temp;
    Classes classes;
    switch (choose) {
    case 1:
        units::input("please enter name") >> name;
        units::input("please enter sex [M/F]") >> sex;
        units::input("please enter telephone [only include digit]") >> telephone;
        units::input("please enter location") >> location;
        units::input("please enter postal number [6-length number]") >> mail_number;
        units::input("please enter email") >> email;
        units::input("please enter qq number") >> qq_number;
        units::input("please enter classes") >> temp;

        mb.addPerson(name, sex, telephone, location, mail_number, email,
                     qq_number, {temp});
        break;
    case 2:
        // searchInfo();
        break;
    case 3:
        cout << mb;
        break;
    case 4:
        // changeInfo();
        break;
    case 5:
        // DeleteInfo();
        break;
    case 6:
        // Break the loop;
        return false;
    default:
        return true;
    }
    mb.save("MessageBook.json");
    return true;
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
        MessageBook mb("MessageBook.json");
        while(main_meun(mb))
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
