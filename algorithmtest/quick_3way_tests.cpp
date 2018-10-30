#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\quick_3way.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Quick3way;
using std::vector;
using std::string;

namespace algorithmtest
{
	TEST_CLASS(Quick3wayTests)
	{
	public:

		TEST_METHOD(Quick3wayTest1)
		{
			vector<string> a{ "aba" };
			string s = "aba";
			Quick3way<string>::Sort(a);
			Assert::IsTrue(s == a[0], L"", LINE_INFO());

			a = vector<string>{ "zoo","able","after","cury","aba","bed","bug","boy","bing"," " };


			Quick3way<string>::Sort(a);
			Assert::IsTrue(a[1] == "aba", L"", LINE_INFO());

		}

	};
}
