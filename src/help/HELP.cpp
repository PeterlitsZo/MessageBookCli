namespace HELP_DOC {
const char* HELP =
   "Help Doc for *\n"
   "===============================================================================\n"
   "\n"
   "Basic Command\n"
   "-------------------------------------------------------------------------------\n"
   "\n"
   "### `help`\n"
   "\n"
   "Want to get a usage for this programme or some command, use like this:\n"
   "\n"
   "   >>> help; after the semicolon there is comment\n"
   "     | Help Doc for *\n"
   "     | ...(this doc)\n"
   "\n"
   "If want to get usage about other command, use `help <command>`.\n"
   "\n"
   "### `exit`\n"
   "\n"
   "Use command `exit` to exit this programme.\n"
   "\n"
   "### `delete`\n"
   "\n"
   "Use command like `delete <person>`, see more to `Basic type::Person`.\n"
   "\n"
   "For example, we know that `expr` new and `[<hash-id>]` has type of person, so\n"
   "we can do with:\n"
   "\n"
   "   >>> delete new; delete the person whose hash is \'b18d80...‘.\n"
   "   >>> delete <\'123456\'>; try to get a person and then to delete it.\n"
   "\n"
   "### `sort`\n"
   "\n"
   "Use command `sort` can sort a list, it need a info about attribution:\n"
   "\n"
   "   >>> sort list name\n"
   "   >>> list; now it well output the list that sorted by name\n"
   "     | ...\n"
   "\n"
   "### `let`\n"
   "\n"
   "The command `let` can use a token to hold a value, like this:\n"
   "\n"
   "   >>> let me new\n"
   "   >>> let my_name \'ba la la xiao mo xian\'\n"
   "   >>> let my_classes [\'ba\', \'la\', \'mo\']\n"
   "   >>> let me.name my_name; set the token `me`\'s name\n"
   "   >>> let me.classes my_classes; set the token `me`\'s classes\n"
   "\n"
   "It can also set a `persons`\'s attribute like before.\n"
   "\n"
   "### `init`\n"
   "\n"
   "The command `init` will init a person and then return the person, like this:\n"
   "\n"
   "   >>> let me (init new)\n"
   "     | please enter name > peter\n"
   "     | ...\n"
   "   >>> me\n"
   "     | +-----| id: ... |------\n"
   "     | | ...\n"
   "\n"
   "### `search`\n"
   "\n"
   "The command `sreach` will return the first result that it find, like this:\n"
   "\n"
   "   >>> let me (search \'peter\' name)\n"
   "\n"
   "Then the token `me` will hold a person that named \'peter\'.\n"
   "\n"
   "Basic type\n"
   "-------------------------------------------------------------------------------\n"
   "\n"
   "### `MessageBook`\n"
   "\n"
   "You can use a keyword `list` to get the current `MessageBook`, this programme\n"
   "will show its value as a list if `person`.\n"
   "\n"
   "### `Person`\n"
   "\n"
   "Use keyword `new` to get a empty person, or if you know his/her hash ID, use\n"
   "like `< hash-ID-string >` to get it. For example:\n"
   "\n"
   "   >>> new\n"
   "     |  ┌-----| id: \'b81d80d9a7822507301ead965c748cc0\' |-------\n"
   "     |  | name: [invaild], sex: [invaild], telephone: [invaild], mail-numbe ...\n"
   "     |  | email: [invaild], qq-number: [invaild], location: [invaild]\n"
   "     |  └ classes: []\n"
   "  >>> <\'b81\'>\n"
   "     |  ┌-----| id: \'b81d80d9a7822507301ead965c748cc0\' |-------\n"
   "     |  | name: [invaild], sex: [invaild], telephone: [invaild], mail-numbe ...\n"
   "     |  | email: [invaild], qq-number: [invaild], location: [invaild]\n"
   "     |  └ classes: []\n"
   "\n"
   "### `String`\n"
   "\n"
   "A string is include by two quotation marks, such as `\"this\"`, or like `\'this\'`\n"
   "\n"
   "### `Vector_String`\n"
   "\n"
   "A Vector_String will looks like this - `[\'this\', \'and\', \'that\']`.\n"
   "\n"
   "The classes of `Person` object has type of `Vector_String`, so you can do like\n"
   "this below:\n"
   "\n"
   "   >>> let new.classes [\'this\', \'and\', \'that\']\n"
   "\n"
   "\n"
;}