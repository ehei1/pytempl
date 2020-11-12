#include "stdafx.h"
#include <iostream>
#include <map>
#include <unordered_map>

#include "ChainMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS( ChainMapTest )
	{
	public:
		TEST_METHOD( TestSimple )
		{
			using cont_t = std::map<int, int>;
			cont_t a{ {1, 1}, {2, 2} };
			cont_t b{ {1, 1}, {2, 3} };

			auto c = pytempl::ChainMap( a, b );
			auto v = c[2];

			Assert::IsTrue( v == 3 );
		}
	};
}