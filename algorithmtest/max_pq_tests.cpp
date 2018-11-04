#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\max_pq.h"
#include<vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::MaxPQ;
using std::vector;

namespace algorithmtest
{
	TEST_CLASS(MaxPQTests)
	{
	public:

		TEST_METHOD(MaxPQTest1)
		{
			MaxPQ<size_t> pq{ 0,1,2,3,4,5,6,7,8,9 };
			MaxPQ<size_t> pq2(vector<size_t>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
			Assert::IsTrue(pq.Size() == pq2.Size(), L"", LINE_INFO());
			Assert::IsTrue(pq.Keys() == pq2.Keys(), L"", LINE_INFO());

			for (size_t i = 0; i != pq2.Size(); ++i) {
				size_t max = pq.Max();
				Assert::IsTrue(max == pq.DelMax(), L"", LINE_INFO());
				Assert::IsTrue(pq.Size()==9-i, L"", LINE_INFO());
			}

			Assert::IsTrue(pq.IsEmpty(), L"", LINE_INFO());

			for (size_t i = 0; i != pq2.Size(); ++i) {
				pq.Insert(i);
				Assert::IsTrue(pq.Max() == i, L"", LINE_INFO());
			}

			Assert::IsTrue(pq2.Keys() == vector<size_t>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, L"", LINE_INFO());
		}

	};
}
