#include "stdafx.h"

#include <list>
#include <vector>

#include "pytempl/chain.h"
#include "pytempl/cycle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(CycleTest)
	{
	public:
		TEST_METHOD(TestSimpleCycle)
		{
			std::vector<int> v0{ 0,1,2,3 };
			std::vector<int> v1;

			for (auto v : pytempl::cycle(v0, 2))
			{
				v1.push_back(v);
			}

			auto chain{ pytempl::chain(v0, v0) };
			auto begin = std::begin(chain);
			auto end = std::end(chain);

			std::vector<int> expecting(begin, end);

			Assert::IsTrue(v1 == expecting);
		}

		TEST_METHOD(TestInfiniteCycle)
		{
			std::vector<int> v0{ 0,1,2,3 };
			constexpr size_t loop_times{ 10 };
			auto cycle_limit{ v0.size() * loop_times };
			std::vector<int> v1;

			for (auto v : pytempl::cycle(v0))
			{
				v1.push_back(v);

				if (cycle_limit == v1.size()) {
					break;
				}
			}

			auto cycle{ pytempl::cycle(v0, loop_times) };
			auto begin = std::begin(cycle);
			auto end = std::end(cycle);

			std::vector<int> expecting(begin, end);

			Assert::IsTrue(v1 == expecting);
		}
	};
}