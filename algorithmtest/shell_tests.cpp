#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\shell.h"
#include<fstream>
#include<string>
#include<algorithm>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Shell;
using std::ifstream;
using std::string;
using std::vector;


namespace algorithmtest
{
	TEST_CLASS(ShellTests)
	{
	public:

		TEST_METHOD(ShellTest1)
		{
			ifstream input("../file/tiny.txt");
			vector<string> svec;
			string s;
			while (input >> s) {
				svec.push_back(s);
			}
			Shell<string>::Sort(svec);
			Assert::IsTrue(std::is_sorted(svec.begin(),svec.end()), L"", LINE_INFO());

		}

	};
}
