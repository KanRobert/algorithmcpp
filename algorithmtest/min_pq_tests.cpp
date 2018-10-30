#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\min_pq.h"
#include<vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::MinPQ;
using std::vector;

namespace algorithmtest
{
	TEST_CLASS(MinPQTests)
	{
	public:

		TEST_METHOD(MinPQTest1)
		{
			MinPQ<int> pq{ 0,1,2,3,4,5,6,7,8,9 };
			MinPQ<int> pq2(vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
			Assert::IsTrue(pq.Size() == pq2.Size(), L"", LINE_INFO());
		    Assert::IsTrue(pq.Keys() == pq2.Keys(), L"", LINE_INFO());

			for (size_t i = 0; i != pq2.Size(); ++i) {
				int min = pq.min();
				Assert::IsTrue(min == pq.DelMin(), L"", LINE_INFO());
				Assert::IsTrue(pq.Size() == 9 - i, L"", LINE_INFO());
			}

			Assert::IsTrue(pq.IsEmpty(), L"", LINE_INFO());

			for (size_t i = 0; i != pq2.Size(); ++i) {
				pq.Insert(i);
				Assert::IsTrue(pq.min() == 0, L"", LINE_INFO());
			}

			Assert::IsTrue(pq2.Keys() == vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, L"", LINE_INFO());
		}

	};
}
