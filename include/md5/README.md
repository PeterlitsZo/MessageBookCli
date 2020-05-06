MD5
===

`Forked from [md5](https://github.com/JieweiWei/md5)`

How to use?
-----------

``` C++
#include <string>
#include <iostream>

#include "path/to/MD5/md5.h"

std::string str("this is a string");
MD5::MD5 md5_obj(str);
std::cout << md5_obj.toStr() << std::endl;
```

