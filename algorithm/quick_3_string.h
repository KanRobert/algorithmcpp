#pragma once
#include"stdrandom.h"
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>

#pragma push_macro("min")
#undef min

namespace algorithmcpp {
	class Quick3String {
	private:
		static constexpr size_t kcut_off = 15;

	public:
		Quick3String(const Quick3String &) = delete;
		Quick3String &operator=(const Quick3String &) = delete;
		~Quick3String() = delete;

	private:
		static int CharAt(const std::string &s, size_t d) {
			if (d >= s.size()) return -1;
			return s[d];
		}

		static bool Less(const std::string &v, const std::string &w, size_t d) {
			for (size_t i = d; i < std::min(v.size(), w.size()); ++i) {
				if (v[i] < w[i]) return true;
				if (v[i] > w[i]) return false;
			}
			return v.size() < w.size();
		}

		static void Insertion(std::vector<std::string> &a, size_t lo, size_t hi, size_t d) {
			using std::swap;
			for (size_t i = lo; i <= hi; ++i) {
				for (size_t j = i; j > lo && Less(a[j], a[j - 1], d); --j) {
					swap(a[j], a[j - 1]);
				}
			}
		}

		static void Sort(std::vector<std::string> &a, size_t lo, size_t hi, size_t d) {
			using std::swap;
			if (hi <= lo + kcut_off) {
				Insertion(a, lo, hi, d);
				return;
			}
			size_t lt = lo, gt = hi;
			int v = CharAt(a[lo], d);
			size_t i = lo + 1;
			while (i <= gt) {
				int t = CharAt(a[i], d);
				if (t < v) swap(a[lt++], a[i++]);
				else if (t > v) swap(a[i], a[gt--]);
				else ++i;
			}
			Sort(a, lo, lt - 1, d);
			if (v >= 0) Sort(a, lt, gt, d + 1);
			Sort(a, gt + 1, hi, d);
		}

	public:
		static void Sort(std::vector<std::string> &a) {
			StdRandom::Shuffle(a);
			Sort(a, 0, a.size() - 1, 0);
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/shells.txt");
			std::vector<std::string> a;
			std::string word;
			while (in >> word) {
				a.push_back(word);
			}

			Sort(a);
			for (const std::string &s : a) {
				std::cout << s << "\n";
			}
		}
	};
}

#pragma pop_macro("min")