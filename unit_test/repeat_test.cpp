#include "stdafx.h"

#include <vector>

#include "CppUnitTest.h"
#include "pytempl/repeat.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(RepeatTest)
	{
	public:
		TEST_METHOD(TestSimpleRepeat)
		{
			auto r{ pytempl::repeat(4, 4) };
			auto b{ std::begin(r) };
			auto e{ std::end(r) };

			std::vector<int> v( b, e );

			Assert::IsTrue(v == std::vector<int>({ 4, 4, 4, 4 }));
		}

		TEST_METHOD(TestInfiniteRepeat)
		{
			auto r{ pytempl::repeat(42, 0) };
			std::vector<int> values;
			constexpr size_t max_count{ 100 };

			for (auto v : r) {
				values.push_back(v);

				if (values.size() == max_count) {
					break;
				}
			}

			Assert::IsTrue(values.size() == max_count);
		}
	};
}
