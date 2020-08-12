#include "stdafx.h"

#include <list>
#include <numeric>
#include <string>
#include <vector>

#include "pytempl/chain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(ChainTest)
	{
	public:
		TEST_METHOD(TestSingleChain)
		{
			std::vector<int> iv(5);
			std::iota(std::begin(iv), std::end(iv), 0);

			auto chain = pytempl::chain(iv);

			std::vector<int> result;

			for (auto v : chain) {
				result.push_back(v);
			}

			Assert::IsTrue(result == iv);
		}

		TEST_METHOD(TestMultiChain)
		{
			std::vector<int> iv0(5);
			std::iota(std::begin(iv0), std::end(iv0), 0);

			std::vector<int> iv1(5);
			std::iota(std::begin(iv1), std::end(iv1), 5);

			auto chain = pytempl::chain(iv0, iv1);

			std::vector<int> result;

			for (auto v : chain) {
				result.push_back(v);
			}

			std::vector<int> expected(iv0.size() + iv1.size());
			std::iota(std::begin(expected), std::end(expected), 0);

			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(TestHeterogenousChain)
		{
			std::list<int> a{ 0,1,2,3 };
			std::array<int,3> b{ 4,5,6 };
			std::vector<int> c{ 7, };
			std::initializer_list<int> d{ 8,9 };

			std::vector<int> result;

			for (auto v : pytempl::chain(a, b, c, d)) {
				result.push_back(v);
			}

			std::vector<int> expected(a.size() + b.size() + c.size() + d.size());
			std::iota(std::begin(expected), std::end(expected), 0);
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(TestEmptySingleChain)
		{
			std::list<float> a;
			std::vector<float> result;

			for (auto v : pytempl::chain(a)) {
				result.push_back(v);
			}

			Assert::IsTrue(result.empty());
		}

		TEST_METHOD(TestEmptyMultiChain)
		{
			std::list<float> a;
			std::vector<float> b;

			std::vector<float> result;

			for (auto v : pytempl::chain(a, b)) {
				result.push_back(v);
			}

			Assert::IsTrue(result.empty());
		}
	};
}