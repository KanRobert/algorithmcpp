#include "stdafx.h"
#include "CppUnitTest.h"
#include"..\algorithm\queue.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using algorithmcpp::Queue;
using std::string;

namespace algorithmtest
{
	TEST_CLASS(QueueTests)
	{
	public:

		TEST_METHOD(QueueTest1)
		{
			Queue<string> queue;
			Assert::IsTrue(queue.IsEmpty() == true, L"", LINE_INFO());
			Assert::IsTrue(queue.Size() == 0, L"", LINE_INFO());

			queue.Enqueue("Kevin Wayne");
			queue.Enqueue("Robert Sedgewick");
			queue.Enqueue("Einsten");
			Assert::IsTrue(queue.Size() == 3, L"", LINE_INFO());

			string item = queue.Dequeue();
			Assert::IsTrue(queue.Size() == 2, L"", LINE_INFO());
			Assert::IsTrue(item== "Kevin Wayne", L"", LINE_INFO());
		}

	};
}
