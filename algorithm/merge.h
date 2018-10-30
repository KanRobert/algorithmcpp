#pragma once
#include<vector>
#include<cassert>
#include<string>

namespace algorithmcpp {
	template<typename Item>class Merge {
	public:
		Merge(const Merge &) = delete;
		Merge &operator=(const Merge &) = delete;
		~Merge() = delete;

	private:
		static void Combine(std::vector<Item> &a, std::vector<Item> &aux, size_t lo, size_t mid, size_t hi) {
			assert(IsSorted(a, lo, mid));
			assert(IsSorted(a, mid + 1, hi));

			for (size_t k = lo; k <= hi; ++k) {
				aux[k] = a[k];
			}

			size_t i = lo, j = mid + 1;
			for (size_t k = lo; k <= hi; ++k) {
				if (i > mid) a[k] = aux[j++];
				else if (j > hi) a[k] = aux[i++];
				else if (aux[j] < aux[i]) a[k] = aux[j++];
				else a[k] = aux[i++];
			}

			assert(IsSorted(a, lo, hi));
		}

		static void Sort(std::vector<Item>& a, std::vector<Item>& aux, size_t lo, size_t hi) {
			if (hi <= lo) return;
			size_t mid = lo + (hi - lo) / 2;
			Sort(a, aux, lo, mid);
			Sort(a, aux, mid + 1, hi);
			Combine(a, aux, lo, mid, hi);
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

		static void Combine(const std::vector<Item> &a, std::vector<size_t> &index, std::vector<size_t> &aux, size_t lo, size_t mid, size_t hi) {
			for (size_t k = lo; k <= hi; ++k) {
				aux[k] = index[k];
			}

			size_t i = lo, j = mid + 1;
			for (size_t k = lo; k <= hi; ++k) {
				if (i > mid) index[k] = aux[j++];
				else if (j > hi) index[k] = aux[i++];
				else if (a[aux[j]] < a[aux[i]]) index[k] = aux[j++];
				else index[k] = aux[i++];
			}
		}

		static void Sort(const std::vector<Item>& a, std::vector<size_t>& index, std::vector<size_t>& aux, size_t lo, size_t hi) {

			if (hi <= lo) return;
			size_t mid = lo + (hi - lo) / 2;
			Sort(a, index, aux, lo, mid);
			Sort(a, index, aux, mid + 1, hi);
			Combine(a, index, aux, lo, mid, hi);
		}

	public:
		static void Sort(std::vector<Item>& a) {
			if (a.size() == 0) return;
			std::vector<Item> aux(a.size());
			Sort(a, aux, 0, a.size()-1);  
			assert(IsSorted(a));
		}

		static std::vector<size_t> IndexSort(const std::vector<Item>& a) {
			std::vector<size_t>::size_type n = a.size();
			std::vector<size_t> index(n);
			for (size_t i = 0; i < n; ++i) {
				index[i] = i;
			}
			if (a.size() == 0) return index;
			std::vector<size_t> aux(n);
			Sort(a, index, aux, 0, n - 1);
			return index;
		}

	public:
		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::vector<std::string> svec;
			std::vector<std::string> cvec1(svec);
			std::vector<std::string> cvec2(svec);
			Merge<std::string>::Sort(svec);


			std::vector<size_t> index1 = Merge<std::string>::IndexSort(cvec2);
		}

	};
}