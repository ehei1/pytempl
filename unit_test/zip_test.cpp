#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
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
			std::vector<int> f{ 1,2,3,4,5,11,12 };
			std::vector<int> i{ 6,7,8,9,10 };
			std::vector<float> ff{ 0,1,2 };

			size_t count{};

			for (auto v : pytempl::zip(f, i, ff)) {
				auto v0 = std::get<0>(v);
				auto v1 = std::get<1>(v);
				auto v2 = std::get<2>(v);

				std::cout << v0 << "," << v1 << "," << v2 << std::endl;

				++count;
			}

			Assert::IsTrue(count == std::min({ f.size(), i.size(), ff.size() }));
		}

		TEST_METHOD(TestSingleIteartion)
		{
			std::vector<int> f{ 1,2,3,4,5,11,12 };

			for (auto v : pytempl::zip(f)) {
				std::cout << v << std::endl;
			}
		}
		
		TEST_METHOD( TestSetValue )
		{
			struct Test {
				int i;
				int j;
			};
			std::vector<Test> t{ { 1, 0 },{ 2,0 } };

			auto r{ pytempl::zip( t ) };

			for ( auto& v : r ) {
				v.i = 100;
			}

			auto check = []( const Test& t ) { return t.i == 100; };
			Assert::IsTrue( std::all_of(std::cbegin(t), std::cend(t), check ) );
		}

		TEST_METHOD( TestConstContainer )
		{
			const std::vector<int> i{ 0,1,2,3,4 };
			auto r{ pytempl::zip( i ) };

			for ( auto v : r ) {
				std::cout << v << std::endl;
			}

			Assert::IsTrue( true );
		}

		TEST_METHOD(TestConstContainers)
		{
			const std::vector<int> i0{ 0,1,2,3,4 };
			const std::vector<int> i1{ 0,1,2,3,4 };
			
			for (auto v : pytempl::zip(i0, i1)) {
				std::cout << std::get<0>(v) << std::get<1>(v) << std::endl;
			}

			Assert::IsTrue(true);
		}

		TEST_METHOD(TestMixedContainers)
		{
			const std::vector<int> i0{ 0,1,2,3,4,5,6 };
			std::vector<int> i1{ 0,1,2,3 };
			std::list<std::string> s{ "h", "e", "l", "l", "o" };
			auto& rs = s;

			for (auto v : pytempl::zip(i0, i1, rs)) {
				auto v0 = std::get<0>(v);
				auto v1 = std::get<1>(v);
				auto v2 = std::get<2>(v);
			}

			Assert::IsTrue(true);
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
			Int_container i(5);
			std::iota( std::begin( i ), std::end( i ), 0 );

			auto zip = pytempl::zip( i );

			Int_container ii;
			auto insert = []( auto vv ) {
				int v{};

				std::tie( v ) = vv;

				return v;
			};
			std::transform( std::begin( zip ), std::end( zip ), std::back_inserter( ii ), insert );

			Assert::IsTrue( ii == Int_container{ 0,1,2,3,4 });
		}
	};
}