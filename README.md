# pytempl
c++ template library by python inspired

### build
* Visual Studio 2015(v140) or later

### contents
* builtin
  * [enumerate](#enumerate)
  * [range](#range)
  * [zip](#zip)
* module
  * collections
    * ChainMap
  * itertools
    * accumulate
    * [chain](#chain)
	* [cycle](#cycle)
    * count
	* [dropwhile](#dropwhile)
	* filterfalse
    * islice
    * [repeat](#repeat)
    * random
    * choice
    * chocies



### [chain](https://docs.python.org/3/library/itertools.html#itertools.chain)
```cpp
#include "pytempl/chain.h"

std::list<int> a{ 0,1,2,3 };
std::array<int,3> b{ 4,5,6 };
std::vector<int> c{ 7, };
std::initializer_list<int> d{ 8,9 };

std::vector<int> result;

for (auto v : pytempl::chain(a, b, c, d)) {
    // v is from 0 to 9
}
```

### [cycle](https://docs.python.org/3/library/itertools.html#itertools.cycle)
```cpp
#include "pytempl/cycle.h"

std::list<int> a{ 0,1,2, };

for (auto v : pytempl::cycle(a, 2)) {
    // v is 0, 1, 2, 0, 1, 2
}
```

### [dropwhile](https://docs.python.org/3.8/library/itertools.html#itertools.dropwhile)
```cpp
#include "pytempl/dropwhile.h"

auto a{ 1, 4, 6, 4, 1 };
auto p = [](int x) { return x < 5; }; 

for(auto v : pytempl::dropwhile(p, a)) {
    // v = 6, 4, 1
}
```

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

### [repeat](https://docs.python.org/3.8/library/itertools.html#itertools.repeat)
```cpp
#include "pytempl/repeat.h"

for (auto v : pytempl::repeat(42, 4)) {
    // v = 42, 42, 42, 42
}
```

### [zip](https://docs.python.org/3/library/functions.html#zip)
```cpp
#include "pytempl/zip.h"

std::vector<int> a{ 1, 2, 3, 4 ,5 };
std::vector<float> b{ 6, 7, 8, 9, 10 };

for(auto v : pytempl::zip(a, b)) {
  auto i = std::get<0>(v); // 1, 2, 3, 4, 5
  auto f = std::get<1>(v); // 6, 7, 8, 9, 10
}
```

