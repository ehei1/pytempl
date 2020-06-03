# pytempl
reverse implementation of python functions by C++

* builtin
  * [enumerate](#enumerate)
  * max
  * min
  * [range](#range)
  * [zip](#zip)
* module
  * itertools
    * accumulate
    * chain
    * count
    * cycle
    * repeat
  * random
    * choice
    * chocies
 

### [enumerate](https://docs.python.org/3/library/functions.html#enumerate)
```cpp
#include "pytempl/enumerate.h"

std::vector<int> iv{ 1, 2, 3, 4 ,5 };

for( auto e : pytempl::enumerate(iv) ) {
	auto idx = std::get<0>(e); // index
	auto i = std::get<1>(e); // value of container
}
```

### [range](https://docs.python.org/3/library/functions.html#func-range)
```cpp
#include "pytempl/range.h"

for (auto i : pytempl::range(0, 5)) {
    // i = 0, 1, 2, 3, 4
}
```

### [zip](https://docs.python.org/3/library/functions.html#zip)
```cpp
#include "pytempl/zip.h"

std::vector<int> iv{ 1, 2, 3, 4 ,5 };
std::vector<float> fv{ 1, 2, 3, 4, 5 };
auto z = pytempl::zip(iv, fv);

for(auto v : z ) {
  int i{};
  float f{};

  std::tie( i, f ) = v;
}
```



