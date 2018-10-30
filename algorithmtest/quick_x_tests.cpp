#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\quick_x.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::QuickX;
using std::vector;
using std::string;

namespace algorithmtest
{
	TEST_CLASS(QuickXTests)
	{
	public:

		TEST_METHOD(QuickXTest1)
		{
			vector<string> a{ "aba" };
			string s = "aba";
			QuickX<string>::Sort(a);
			Assert::IsTrue(s == a[0], L"", LINE_INFO());

			a = vector<string>{ "zoo","able","after","cury","aba","bed","bug","boy","bing"," " };
			

			QuickX<string>::Sort(a);
			Assert::IsTrue(a[1] == "aba", L"", LINE_INFO());

		}

	};
}
