#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#include "CppUnitTest.h"
#include "pytempl\enumerate.h"
#include "pytempl\zip.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS( EnumerateTest )
	{
	public:
		TEST_METHOD( TestMutable )
		{
			std::vector<int> v( 10 );
			std::iota( std::begin( v ), std::end( v ), 0 );

			for ( auto e : pytempl::enumerate( v ) ) {
				auto i = std::get<0>( e );
				auto ii = std::get<1>( e );

				Assert::IsTrue( i == ii );
			}
		}

		TEST_METHOD( TestConst )
		{
			std::vector<int> v( 10 );
			std::iota( std::begin( v ), std::end( v ), 0 );

			const decltype( v ) vv = std::move( v );

			for ( auto e : pytempl::enumerate( vv ) ) {
				auto i = std::get<0>( e );
				auto ii = std::get<1>( e );

				Assert::IsTrue( i == ii );
			}
		}

		TEST_METHOD( TestLvalue )
		{
			std::vector<int> v( 10 );
			std::iota( std::begin( v ), std::end( v ), 0 );

			auto& vv{ v };

			for ( auto e : pytempl::enumerate( vv ) ) {
				auto i = std::get<0>( e );
				auto ii = std::get<1>( e );

				Assert::IsTrue( i == ii );
			}
		}

		TEST_METHOD( TestZipIterator )
		{
			std::vector<int> iv( 10 );
			std::iota( std::begin( iv ), std::end( iv ), 0 );

			std::vector<float> fv( 10 );
			std::iota( std::begin( fv ), std::end( fv ), 0.f );

			auto z = pytempl::zip( iv, fv );

			for ( auto e : pytempl::enumerate( z ) ) {
				auto idx = std::get<0>( e );
				auto zz = std::get<1>( e );

				int i{};
				float f{};
				std::tie( i, f ) = zz;

				Assert::IsTrue( idx == i );
				Assert::IsTrue( idx == static_cast<int>( f ) );
			}
		}
	};
}