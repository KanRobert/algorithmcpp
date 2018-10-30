#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\bag.h"
#include<vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Bag;
using std::vector;

namespace algorithmtest
{
	TEST_CLASS(BagTests)
	{
	public:

		TEST_METHOD(BagTest1)
		{
			vector<int> expected;
			Bag<int> bag;
			vector<int> sb;
			for (int s : bag) {
				sb.push_back(s);
			}
			Assert::IsTrue(bag.IsEmpty(), L"", LINE_INFO());
			Assert::IsTrue(expected==sb, L"", LINE_INFO());

			bag.Add(3);
			expected.push_back(3);
			sb.clear();
			for (int s : bag) {
				sb.push_back(s);
			}
			Assert::IsTrue(expected == sb, L"", LINE_INFO());

			bag.Add(2);
			bag.Add(3);
			Assert::IsFalse(bag.IsEmpty(), L"", LINE_INFO());
			Assert::IsTrue(bag.Size()==3, L"", LINE_INFO());
			expected.push_back(2);
			expected.push_back(3);
			sb.clear();
			for (int s : bag) {
				sb.push_back(s);
			}
			Assert::IsTrue(expected == sb, L"", LINE_INFO());

		}

	};
}
