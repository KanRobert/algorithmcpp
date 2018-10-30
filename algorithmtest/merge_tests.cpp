#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\merge.h"
#include<fstream>
#include<string>
#include<algorithm>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Merge;
using std::ifstream;
using std::string;
using std::vector;


namespace algorithmtest
{
	TEST_CLASS(MergeTests)
	{
	public:

		TEST_METHOD(MergeTest1)
		{
			ifstream input("../file/tiny.txt");
			vector<string> svec;
			string s;
			while (input >> s) {
				svec.push_back(s);
			}

			vector<string> cvec1(svec);
			vector<string> cvec2(svec);
			Merge<string>::Sort(svec);
			std::stable_sort(cvec1.begin(), cvec1.end());
			Assert::IsTrue(svec == cvec1, L"", LINE_INFO());


			vector<size_t> index1 = Merge<string>::IndexSort(cvec2);
			vector<size_t> index2;
			index2.reserve(cvec2.size());
			for (size_t i = 0; i != cvec2.size(); ++i) {
				index2.push_back(i);
			}
			std::stable_sort(index2.begin(), index2.end(), [&cvec2](size_t a, size_t b) {return cvec2[a] < cvec2[b]; });
			Assert::IsTrue(index1 == index2, L"", LINE_INFO());
		}

	};
}
