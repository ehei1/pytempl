#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#include "CppUnitTest.h"
#include "pytempl\zip.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS( UnitTest1 )
	{
	public:
		TEST_METHOD( TestIterationByShortestContainer )
		{
			std::vector<float> f{ 1,2,3,4,5,11,12 };
			std::vector<int> i{ 6,7,8,9,10 };
			std::vector<std::string> s{ "ax", "bbbb", "c", "d" };

			auto r{ pytempl::Zip<decltype( f ), decltype( i ), decltype( s )>( f, i, s ) };
			int count{};

			for ( auto v : r ) {
				float ff;
				int ii;
				std::string ss;

				std::tie( ff, ii, ss ) = v;
				std::cout << ff << "\t" << ii << "\t" << ss << std::endl;

				++count;
			}

			Assert::IsTrue( count == std::min( { f.size(), i.size(), s.size() } ) );
		}

		TEST_METHOD( TestConstIteration )
		{
			//using Int_container = std::vector<int>;
			//Int_container i(10);
			//std::iota( std::begin( i ), std::end( i ), 0 );

			//using Zip_type = pytempl::Zip<decltype( i )>;
			//auto zip{ Zip_type( i ) };

			//Int_container ii;
			//auto insert = []( auto vv ) {
			//	int v;

			//	//std::tie( v ) = *iterator;

			//	return v;
			//};
			//std::transform( std::begin( zip ), std::end( zip ), std::back_inserter( ii ), insert );
		}
	};
}