Help Doc for *
===============================================================================

Command `help`
-------------------------------------------------------------------------------

Want to get a usage for this programme or some command, use like this:

   >>> help; after the semicolon there is comment
   ||| Help Doc for *
   ||| ...(this doc)

If want to get usage about other command, use `help <command>`.

Basic type
-------------------------------------------------------------------------------

### `MessageBook`

You can use a keyword `list` to get the current `MessageBook`, this programme
will show its value as a list if `person`.

### `Person`

Use keyword `new` to get a empty person, or if you know his/her hash ID, use
like `[<hash-ID-string>]` to get it. For example:

   >>> new
     |  ┌-----| id: 'b81d80d9a7822507301ead965c748cc0' |-------
     |  | name: [invaild], sex: [invaild], telephone: [invaild], mail-numbe ...
     |  | email: [invaild], qq-number: [invaild], location: [invaild]
     |  └ classes: []
  >>> ['b81']
     |  ┌-----| id: 'b81d80d9a7822507301ead965c748cc0' |-------
     |  | name: [invaild], sex: [invaild], telephone: [invaild], mail-numbe ...
     |  | email: [invaild], qq-number: [invaild], location: [invaild]
     |  └ classes: []

### `String`

A string is include by two quotation marks, such as `"this"`, or like `'this'`

Command `exit`
-------------------------------------------------------------------------------

Use command `exit` to exit this programme.






-------------------------------------------------------------------------------

Help is too long?

There are index of all help's table: (use `help <index>` to get help of some
topic)

``` table
type            exit            help            ...

[subindex for type]:
messagebook     person          string
```
