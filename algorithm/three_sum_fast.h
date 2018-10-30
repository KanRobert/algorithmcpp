#pragma once
#include"stopwatch.h"
#include<vector>
#include<algorithm>
#include<stdexcept>
#include<iostream>
#include<fstream>

namespace algorithmcpp {
	class ThreeSumFast {
	public:
		ThreeSumFast(const ThreeSumFast &) = delete;
		ThreeSumFast &operator=(const ThreeSumFast &) = delete;
		~ThreeSumFast() = delete;

	private:
		static bool ContainDuplicates(const std::vector<int> &a) {
			for (size_t i = 1; i < a.size(); ++i) {
				if (a[i] == a[i - 1]) return true;
			}
			return false;
		}

		template<typename Iter,typename T> 
		static Iter BinaryFind(Iter beg, Iter end, const T &val) {
			Iter it = std::lower_bound(beg, end, val);
			if (it != end && !(val < *it))
				return it;
			else
				return end;
		}

	public:
		static void PrintAll(std::vector<int> &a) {
			std::sort(a.begin(), a.end());
			if (ContainDuplicates(a)) throw std::invalid_argument("array Contains duplicate integers");
			for (auto it = a.cbegin(); it != a.cend();++it) {
				for (auto it2 = it + 1; it2 != a.cend();++it2) {
					auto it3 = BinaryFind(a.cbegin(), a.cend(), -(*it + *it2));
					if ((it3!=a.cend()) && (it2<it3)) std::cout << *it << " " << *it2 << " " << *it3 << std::endl;
				}
			}
		}

		static size_t Count(std::vector<int> &a) {
			std::sort(a.begin(), a.end());
			if (ContainDuplicates(a)) throw std::invalid_argument("array Contains duplicate integers");
			size_t cnt = 0;
			for (auto it = a.cbegin(); it != a.cend(); ++it) {
				for (auto it2 = it + 1; it2 != a.cend(); ++it2) {
					auto it3 = BinaryFind(a.cbegin(), a.cend(), -(*it + *it2));
					if ((it3 != a.cend()) && (it2<it3)) ++cnt;
				}
			}
			return cnt;
		}

		static void MainTest(int argc = 0, char* argv[] = nullptr) {
			std::ifstream in("../file/1Kints.txt");
			std::vector<int> a;
			int x;
			while (in >> x) {
				a.push_back(x);
			}
			Stopwatch timer;
			size_t cnt = Count(a);
			std::cout << "elapsed time = " << timer.ElapsedTime() << std::endl;
			std::cout << cnt << std::endl;
		}
	};
}