#pragma once
#include"stopwatch.h"
#include"stopwatch_win32.h"
#include<vector>
#include<iostream>
#include<fstream>

namespace algorithmcpp {
	class ThreeSum {
	public:
		ThreeSum(const ThreeSum &) = delete;
		ThreeSum &operator=(const ThreeSum &) = delete;
		~ThreeSum() = delete;

		static void PrintAll(const std::vector<int> &a) {
			size_t n = a.size();
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = i + 1; j < n; ++j) {
					for (size_t k = j + 1; k < n; ++k) {
						if (a[i] + a[j] + a[k] == 0) {
							std::cout << a[i] << " " << a[j] << " " << a[k] << std::endl;
						}
					}
				}
			}
		}

		static size_t Count(const std::vector<int> &a) {
			size_t n = a.size();
			size_t total = 0;
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = i + 1; j < n; ++j) {
					for (size_t k = j + 1; k < n; ++k) {
						if (a[i] + a[j] + a[k] == 0) {
							++total;
						}
					}
				}
			}
			return total;
		}

		static void MainTest(int argc = 0, char* argv[] = nullptr) {
			std::ifstream in("../file/1Kints.txt");
			std::vector<int> a;
			int x;
			while (in >> x) {
				a.push_back(x);
			}
			Stopwatch timer;
			StopwatchWin32 timer2;
			size_t cnt = Count(a);
			std::cout << "elapsed time = " << timer.ElapsedTime() << std::endl;
			std::cout << "elapsed time = " << timer2.ElapsedTime() << std::endl;
			std::cout << cnt << std::endl;

		}
	};
}