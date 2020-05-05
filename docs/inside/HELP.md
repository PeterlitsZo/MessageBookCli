Help Doc for *
===============================================================================

Basic Command
-------------------------------------------------------------------------------

### `help`

Want to get a usage for this programme or some command, use like this:

   >>> help; after the semicolon there is comment
     | Help Doc for *
     | ...(this doc)

If want to get usage about other command, use `help <command>`.

### `exit`

Use command `exit` to exit this programme.

### `delete`

Use command like `delete <person>`, see more to `Basic type::Person`.

For example, we know that `expr` new and `[<hash-id>]` has type of person, so
we can do with:

   >>> delete new; delete the person whose hash is 'b18d80...‘.
   >>> delete <'123456'>; try to get a person and then to delete it.

### `sort`

Use command `sort` can sort a list, it need a info about attribution:

   >>> sort list name
   >>> list; now it well output the list that sorted by name
     | ...

### `let`

The command `let` can use a token to hold a value, like this:

   >>> let me new
   >>> let my_name 'ba la la xiao mo xian'
   >>> let my_classes ['ba', 'la', 'mo']
   >>> let me.name my_name; set the token `me`'s name
   >>> let me.classes my_classes; set the token `me`'s classes

It can also set a `persons`'s attribute like before.

### `init`

The command `init` will init a person and then return the person, like this:

   >>> let me (init new)
     | please enter name > peter
     | ...
   >>> me
     | +-----| id: ... |------
     | | ...

### `search`

The command `sreach` will return the first result that it find, like this:

   >>> let me (search 'peter' name)

Then the token `me` will hold a person that named 'peter'.

Basic type
-------------------------------------------------------------------------------

### `MessageBook`

You can use a keyword `list` to get the current `MessageBook`, this programme
will show its value as a list if `person`.

### `Person`

Use keyword `new` to get a empty person, or if you know his/her hash ID, use
like `< hash-ID-string >` to get it. For example:

   >>> new
     |  ┌-----| id: 'b81d80d9a7822507301ead965c748cc0' |-------
     |  | name: [invaild], sex: [invaild], telephone: [invaild], mail-numbe ...
     |  | email: [invaild], qq-number: [invaild], location: [invaild]
     |  └ classes: []
  >>> <'b81'>
     |  ┌-----| id: 'b81d80d9a7822507301ead965c748cc0' |-------
     |  | name: [invaild], sex: [invaild], telephone: [invaild], mail-numbe ...
     |  | email: [invaild], qq-number: [invaild], location: [invaild]
     |  └ classes: []

### `String`

A string is include by two quotation marks, such as `"this"`, or like `'this'`

### `Vector_String`

A Vector_String will looks like this - `['this', 'and', 'that']`.

The classes of `Person` object has type of `Vector_String`, so you can do like
this below:

   >>> let new.classes ['this', 'and', 'that']

