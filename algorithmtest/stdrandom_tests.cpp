#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\stdrandom.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::StdRandom;

namespace algorithmtest
{
	TEST_CLASS(StdRandomTests)
	{
	public:

		TEST_METHOD(StdRandomTest1)
		{
			for (int i = 0; i != 1024; ++i) {
				int x = StdRandom::Uniform(1);
				Assert::IsTrue(x == 0, L"", LINE_INFO());
			}


			for (int i = 0,a=-1024,b=1024; i!=100; ++i) {
				int y = StdRandom::Uniform(a, b);
				Assert::IsTrue(y>=a && y<b,L"", LINE_INFO());
			}

			double a = -1024.0, b = 1024.0;
			for (int i = 0; i != 100; ++i) {
				double y = StdRandom::Uniform(a, b);
				Assert::IsTrue(y >= a && y<b,L"",LINE_INFO());
			}

		}

	};
}
