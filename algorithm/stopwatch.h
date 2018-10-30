#pragma once
#include<chrono>
#include<cmath>
#include<iostream>

namespace algorithmcpp {

	class Stopwatch {
	private:
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		TimePoint start_ = std::chrono::high_resolution_clock::now();

	public:
		Stopwatch() = default;
		Stopwatch(const Stopwatch &) = default;
		Stopwatch &operator=(const Stopwatch &) = default;
		Stopwatch(Stopwatch &&) = default;
		Stopwatch &operator=(Stopwatch &&) = default;
		~Stopwatch() = default;

		double ElapsedTime() {
			TimePoint finish= std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start_;
			return elapsed.count();
		}

		static void MainTest(int argc = 0, char* argv[] = nullptr) {
			const int n = 100;

			Stopwatch timer1;
			double sum1 = 0.0;
			for (size_t i = 1; i <= n; ++i) {
				sum1 += std::sqrt(i);
			}
			double time1 = timer1.ElapsedTime();
			std::cout << time1 << " " << "seconds" << std::endl;

			Stopwatch timer2;
			double sum2 = 0.0;
			for (size_t i = 1; i <= n; ++i) {
				sum2 += std::pow(i,0.5);
			}
			double time2 = timer2.ElapsedTime();
			std::cout << time2 << " " << "seconds" << std::endl;
		}
	};
}