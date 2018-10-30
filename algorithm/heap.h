#pragma once
#include<vector>
#include<cassert>
#include<string>
#include<algorithm>
#include<fstream>
#include<iostream>

namespace algorithmcpp {
	template<typename Item> class Heap {
	public:
		Heap(const Heap &) = delete;
		Heap &operator=(const Heap &) = delete;
		~Heap() = delete;

	private:
		static bool Less(const std::vector<Item> &pq, size_t i, size_t j) {
			return pq[i - 1] < pq[j - 1];
		}

		static void Exch(std::vector<Item> &pq, size_t i, size_t j) {
			using std::swap;
			swap(pq[i - 1], pq[j - 1]);
		}

		static void Sink(std::vector<Item> &pq, size_t k, size_t n) {
			while (2 * k <= n) {
				size_t j = 2 * k;
				if (j < n && Less(pq, j, j + 1)) ++j;
				if (!Less(pq, k, j)) break;
				Exch(pq, k, j);
				k = j;
			}
		}

	public:
		static void Sort(std::vector<Item> &pq) {
			size_t n = pq.size();
			for (size_t k = n / 2; k >= 1; --k)
				Sink(pq, k, n);
			while (n > 1) {
				Exch(pq, 1, n--);
				Sink(pq, 1, n);
			}
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream input("../file/tiny.txt");
			std::vector<std::string> svec;
			std::string s;
			while (input >> s) {
				svec.push_back(s);
			}
			Heap<std::string>::Sort(svec);
			for (const auto &x : svec) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
		}
	};
}