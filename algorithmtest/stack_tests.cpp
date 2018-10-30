#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Stack;

namespace algorithmtest
{
	TEST_CLASS(StackTests)
	{
	public:

		TEST_METHOD(StackTest1)
		{
			Stack<int> stack;
			stack.Push(3);
			Assert::IsTrue(stack.Peek() == 3,L"",LINE_INFO());

			stack.Push(4);
			Assert::IsTrue(stack.Peek() == 4,L"",LINE_INFO());

			Assert::IsTrue(stack.Pop() == 4, L"", LINE_INFO());
			Assert::IsTrue(stack.Pop() == 3, L"", LINE_INFO());
			Assert::IsTrue(stack.Size() == 0, L"", LINE_INFO());

			for (int i = 0; i != 5; ++i) {
				stack.Push(i);
			}
			bool consistent = true;
			int i = 5;
			for (auto beg = stack.begin(),end = stack.end(); beg != end; ++beg) {
				if (*beg != --i) consistent = false;
			}
			Assert::IsTrue(consistent == true, L"", LINE_INFO());
		}

	};
}
