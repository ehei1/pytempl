#include "stdafx.h"

#include <algorithm>
#include <vector>

#include "pytempl/dropwhile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS( DropWhileTest )
	{
	public:
		TEST_METHOD( TestSingleChain )
		{
			auto prediction = []( int x ) { return x < 5; };
			auto container = { 1, 4, 6, 4, 1 };
			auto dropwhile = pytempl::dropwhile( prediction, std::move(container) );
			std::vector<int> result( std::begin( dropwhile ), std::end( dropwhile ) );

			if (!result.empty()) {
				Assert::IsTrue( result[0] >= 5 );
			}
		}
	};
}