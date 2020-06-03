#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <tuple>
#include <vector>

#include "CppUnitTest.h"
#include "pytempl\range.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(RangeTest)
	{
	public:
		TEST_METHOD(TestRangeStopOnly)
		{
			int v{};

			for (auto i : pytempl::range(10))
			{
				Assert::IsTrue(i == v++);
			}
		}

		TEST_METHOD(TestRangeStartWithStop)
		{
			int v{};

			for (auto i : pytempl::range(0, 10))
			{
				Assert::IsTrue(i == v++);
			}
		}

		TEST_METHOD(TestRangeWithAllArguments)
		{
			int v{};
			int step = 2;

			for (auto i : pytempl::range(0, 11, step))
			{
				Assert::IsTrue(i == v);

				v += step;
			}
		}

		TEST_METHOD(TestReverseRange)
		{
			int count = 10;

			for (auto i : pytempl::range(count, 0, -1)) {
				--count;
			}

			Assert::IsTrue(0 == count);
		}

		TEST_METHOD(TestEmptyRange)
		{
			int count{};

			for (auto i : pytempl::range(0)) {
				++count;
			}

			for (auto i : pytempl::range(10, 0)) {
				++count;
			}

			Assert::IsTrue(0 == count);
		}

		TEST_METHOD(TestIteration)
		{
			auto r = pytempl::range(10);
			std::vector<int> v(std::cbegin(r), std::cend(r));

			std::vector<int> vv(10);
			std::iota(std::begin(vv), std::end(vv), 0);

			Assert::IsTrue(v == vv);
		}

		TEST_METHOD(TestReverseIteration)
		{
			auto r = pytempl::range(10);
			std::vector<int> v(std::crbegin(r), std::crend(r));

			std::vector<int> vv(10);
			std::iota(std::rbegin(vv), std::rend(vv), 1);

			Assert::IsTrue(v == vv);
		}
	};
}