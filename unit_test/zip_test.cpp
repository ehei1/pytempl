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
	TEST_CLASS( ZipTest )
	{
	public:
		TEST_METHOD( TestIterationByShortestContainer )
		{
			std::vector<float> f{ 1,2,3,4,5,11,12 };
			std::vector<int> i{ 6,7,8,9,10 };
			std::vector<std::string> s{ "ax", "bbbb", "c", "d" };

			auto r{ pytempl::zip( f, i, s ) };
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

		TEST_METHOD( TestSetValue )
		{
			struct Test {
				int i;
				int j;
			};
			std::vector<Test> t{ { 1, 0 },{ 2,0 } };

			auto r{ pytempl::zip( t ) };

			for ( auto v : r ) {
				auto& vv = std::get<0>( v );
				vv.i = 100;
			}

			auto check = []( const Test& t ) { return t.i == 100; };
			Assert::IsTrue( std::all_of(std::cbegin(t), std::cend(t), check ) );
		}

		TEST_METHOD( TestConstContainer )
		{
			const std::vector<int> i{ 0,1,2,3,4 };
			auto r{ pytempl::zip( i ) };

			for ( auto v : r ) {
				int ii;

				std::tie( ii ) = v;

				std::cout << ii << std::endl;
			}

			Assert::IsTrue( true );
		}

		TEST_METHOD( TestRefContainer )
		{
			std::vector<int> i{ 0,1,2,3,4 };
			auto& ri{ i };
			auto r{ pytempl::zip( ri ) };

			for ( auto v : r ) {
				int ii;

				std::tie( ii ) = v;

				std::cout << ii << std::endl;
			}

			Assert::IsTrue( true );
		}

		TEST_METHOD( TestConstRefContainer )
		{
			const std::vector<int> i{ 0,1,2,3,4 };
			auto& ri{ i };
			auto r{ pytempl::zip( ri ) };

			for ( auto v : r ) {
				int ii;

				std::tie( ii ) = v;

				std::cout << ii << std::endl;
			}

			Assert::IsTrue( true );
		}

		TEST_METHOD( TestConstIteration )
		{
			using Int_container = std::vector<int>;
			Int_container i(10);
			std::iota( std::begin( i ), std::end( i ), 0 );

			//auto zip = pytempl::zip( i );

			//Int_container ii;
			//auto insert = []( auto vv ) {
			//	int v;

			//	//std::tie( v ) = *iterator;

			//	return v;
			//};
			//std::transform( std::begin( zip ), std::end( zip ), std::back_inserter( ii ), insert );

			Assert::IsTrue( true );
		}
	};
}