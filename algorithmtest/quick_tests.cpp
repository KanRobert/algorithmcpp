#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\quick.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Quick;
using std::vector;
using std::string;
using std::exception;

namespace algorithmtest
{
	TEST_CLASS(QuickTests)
	{
	public:

		TEST_METHOD(QuickTest1)
		{
			vector<string> a{ "aba" };
			string s= Quick<string>::Select(a,0);

			Quick<string>::Sort(a);
			Assert::IsTrue(s == a[0], L"", LINE_INFO());

			a = vector<string>{ "zoo","able","after","cury","aba","bed","bug","boy","bing"," " };
			s = Quick<string>::Select(a, a.size() - 1);
			Assert::IsTrue(s=="zoo", L"", LINE_INFO());

			Quick<string>::Sort(a);
			Assert::IsTrue(a[1] == "aba", L"", LINE_INFO());



			auto funcPtr = [&]() {Quick<string>::Select(a, a.size()); };
			Assert::ExpectException<std::invalid_argument>(funcPtr, L"", LINE_INFO());

		}

	};
}
