#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\binary_search.h"
#include<vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;
using algorithmcpp::BinarySearch;

namespace algorithmtest
{
	TEST_CLASS(BinarySearchTests)
	{
	public:

		TEST_METHOD(BinarySearchTest1)
		{
			vector<int> a{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 22 };
			Assert::IsTrue(BinarySearch<int>::IndexOf(a, 1)==-1, L"", LINE_INFO());
			Assert::IsTrue(BinarySearch<int>::IndexOf(a, 20)==-1, L"", LINE_INFO());
			Assert::IsTrue(BinarySearch<int>::IndexOf(a, 25)==-1, L"", LINE_INFO());
			Assert::IsTrue(BinarySearch<int>::IndexOf(a, 4)==1, L"", LINE_INFO());
			Assert::IsTrue(BinarySearch<int>::IndexOf(a, 12)==5, L"", LINE_INFO());
			Assert::IsTrue(BinarySearch<int>::IndexOf(a, 22)==9, L"", LINE_INFO());
		}

	};
}
