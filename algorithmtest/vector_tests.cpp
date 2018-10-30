#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Vector;
using std::initializer_list;
using std::sqrt;

namespace algorithmtest
{
	TEST_CLASS(VectorTests)
	{
	private:
		double SumOfSquare(initializer_list<double> lst)
		{
			double sum = 0;
			for (double x : lst)
			{
				sum += x*x;
			}
			return sum;
		}

	public:

		TEST_METHOD(VectorTest1)
		{
			Vector x({ 1.0,2.0,3.0,4.0 });
			Vector y({ 5.0,2.0,4.0,1.0 });

			Vector z = x + y;
			Assert::IsTrue(z==Vector({ 6.0,4.0,7.0,5.0 }), L"", LINE_INFO());

			z = x - y;
			Assert::IsTrue(z == Vector({ -4.0,0.0,-1.0,3.0 }), L"", LINE_INFO());

			z = x.Scale(2);
			Assert::IsTrue(z == Vector({ 2.0,4.0,6.0,8.0 }), L"", LINE_INFO());
			
			Assert::IsTrue(x.Dot(y) == (5.0+4.0+12.0+4.0), L"", LINE_INFO());

			Assert::IsTrue(x.Magnitude() == sqrt(SumOfSquare({ 1.0,2.0,3.0,4.0 })), L"", LINE_INFO());
			Assert::IsTrue(x.Direction() == x.Scale(1 / x.Magnitude()), L"", LINE_INFO());
			Assert::IsTrue(x.DistanceTo(y) == sqrt(SumOfSquare({ -4.0,0.0,-1.0,3.0 })), L"", LINE_INFO());
		}

	};
}
