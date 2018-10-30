#pragma once
#include<iostream>

namespace algorithmcpp {
	class Average {
	public:
		Average(const Average &) = delete;
		Average &operator=(const Average &) = delete;
		~Average() = delete;

		static void MainTest(int argc = 0, char* argv[] = nullptr) {
			size_t count = 0;
			double sum = 0.0;

			double a[] = { 1,2,3,4,5,6,7,8,9 };
			constexpr size_t sz = sizeof(a) / sizeof(*a);
			for (size_t i = 0; i != sz; ++i) {
				sum += a[i];
				++count;
			}
			double average = sum / count;
			std::cout << "The count of number is " << count << std::endl;
			std::cout << "Average is " << average << std::endl;
		}
	};
}