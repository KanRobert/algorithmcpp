#pragma once
#include"stdrandom.h"
#include"stopwatch.h"
#include"three_sum.h"
#include<vector>
#include<iostream>

namespace algorithmcpp {
	class DoublingRatio {
	public:
		DoublingRatio(const DoublingRatio &) = delete;
		DoublingRatio &operator=(const DoublingRatio &) = delete;
		~DoublingRatio() = delete;

	private:
		static constexpr int kMaximumInteger = 1000000;

	public:
		static double TimeTrial(size_t n) {
			std::vector<int> a;
			a.reserve(n);
			for (size_t i = 0; i < n; ++i) {
				a.push_back(StdRandom::Uniform(-kMaximumInteger, +kMaximumInteger));
			}
			Stopwatch timer;
			ThreeSum::Count(a);
			return timer.ElapsedTime();
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			double prev = TimeTrial(125);
			for (size_t n = 250; true; n += n) {
				double time = TimeTrial(n);
				std::cout << n << " " << time << " " << time / prev << std::endl;
				prev = time;
			}
		}
	};
}