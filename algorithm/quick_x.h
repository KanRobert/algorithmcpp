#pragma once
#include<vector>
#include<cassert>
#include<algorithm>

namespace algorithmcpp {
	template<typename Item> class QuickX {
	public:
		QuickX(const QuickX &) = delete;
		QuickX &operator=(const QuickX &) = delete;
		~QuickX() = delete;

	private:
		static constexpr size_t kInsertionSortCutoff = 8;
		static constexpr size_t kMedianOf_3_Cutoff = 40;

		static void InsertionSort(std::vector<Item> &a, size_t lo, size_t hi) {
			using std::swap;
			for (size_t i = lo; i <= hi; ++i)
				for (size_t j = i; j > lo && a[j] < a[j - 1]; --j)
					swap(a[j], a[j - 1]);
		}

		static size_t Median3(std::vector<Item> a, size_t i, size_t j, size_t k) {
			return (a[i] < a[j]) ?
				((a[j] < a[k]) ? j : ((a[i] < a[k]) ? k : i)) :
				((a[k] < a[j]) ? j : ((a[k] < a[i]) ? k : i));
		}

		static bool IsSorted(const std::vector<Item> &a) {
			return IsSorted(a, 0, a.size() - 1);
		}

		static bool IsSorted(const std::vector<Item> &a, size_t lo, size_t hi) {
			for (size_t i = lo + 1; i <= hi; ++i) {
				if (a[i] < a[i - 1]) return false;
			}
			return true;
		}

	public:
		static void Sort(std::vector<Item> &a) {
			Sort(a, 0, a.size() - 1);
			assert(IsSorted(a));
		}

		static void Sort(std::vector<Item> &a, size_t lo, size_t hi) {
			using std::swap;
			size_t n = hi - lo + 1;

			if (n <= kInsertionSortCutoff) {
				InsertionSort(a, lo, hi);
				return;
			}
			else if(n<=kMedianOf_3_Cutoff){
				size_t m = Median3(a, lo, lo + n / 2, hi);
				swap(a[m], a[lo]);
			}
			else {
				size_t eps = n / 8;
				size_t mid = lo + n / 2;
				size_t m1 = Median3(a, lo, lo + eps, lo + eps + eps);
				size_t m2 = Median3(a, mid - eps, mid, mid + eps);
				size_t m3 = Median3(a, hi - eps - eps, hi - eps, hi);
				size_t ninther = Median3(a, m1, m2, m3);
				swap(a[ninther], a[lo]);
			}

			size_t i = lo, j = hi + 1;
			size_t p = lo, q = hi + 1;
			Item v = a[lo];
			while (true) {
				while (a[++i] < v)
					if (i == hi) break;
				while (v < a[--j])
					if (j == lo) break;

				if (i == j && a[i] == v)
					swap(a[++p], a[i]);
				if (i >= j) break;

				swap(a[i], a[j]);
				if (a[i] == v) swap(a[++p], a[i]);
				if (a[j] == v) swap(a[--q], a[j]);
			}

			i = j + 1;
			for (size_t k = lo; k <= p; ++k) 
				swap(a[k], a[j--]);
			for (size_t k = hi; k >= q; --k)
				swap(a[k], a[i++]);

			Sort(a, lo, j);
			Sort(a, i, hi);
			assert(IsSorted(a, lo, hi));
		}

		static void MainTest(int argc = 0, char* argv[] = nullptr) {
			std::vector<int> a{ 5,4,3,2,1,6,7,8,9 };
			QuickX<int>::Sort(a);
		}
	};
}
