# pytempl
C++ template implementation of python module

[zip](https://docs.python.org/3/library/functions.html#zip)
```
#include "pytempl/zip.h"

std::vector<int> iv{ 1, 2, 3, 4 ,5 };
std::vector<float> fv{ 1, 2, 3, 4, 5 };
auto z = pytempl::zip(iv, fv);

for(auto v : z ) {
  int i{};
  float f{};

  std::tie( i, f ) = v;
  auto& v = std::get<0>; // int&
}
```

[enumerate](https://docs.python.org/3/library/functions.html#enumerate)
```
#include "pytempl/enumerate.h"

std::vector<int> iv{ 1, 2, 3, 4 ,5 };

for( auto e : pytempl::enumerate(iv) ) {
	auto idx = std::get<0>(e); // index
	auto i = std::get<1>(e); // value of container
}
```

TODO
* doxygen apply