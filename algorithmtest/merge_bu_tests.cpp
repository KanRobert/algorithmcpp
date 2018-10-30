#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\merge_bu.h"
#include<fstream>
#include<string>
#include<algorithm>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::MergeBU;
using std::ifstream;
using std::string;
using std::vector;


namespace algorithmtest
{
	TEST_CLASS(MergeXTests)
	{
	public:

		TEST_METHOD(MergeBUTest1)
		{
			ifstream input("../file/tiny.txt");
			vector<string> svec;
			string s;
			while (input >> s) {
				svec.push_back(s);
			}
			vector<string> cvec1(svec);
			MergeBU<string>::Sort(svec);
			std::stable_sort(cvec1.begin(), cvec1.end());
			Assert::IsTrue(svec == cvec1, L"", LINE_INFO());

		}

	};
}
