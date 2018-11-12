#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>

#pragma push_macro("min")
#undef min

namespace algorithmcpp {
	class MSD {
	private:
		static constexpr unsigned char kBitsPerByte = 8;
		static constexpr unsigned char kBitsPerInt = sizeof(int) * 8;
		static constexpr unsigned kN_Ascii = 1U << kBitsPerByte;
		static constexpr unsigned kCutOff = 15;

	public:
		MSD(const MSD &) = delete;
		MSD &operator=(const MSD &) = delete;
		~MSD() = delete;

	private:
		static int CharAt(const std::string &s, size_t d) {
			if (d >= s.size()) return -1;
			return static_cast<int>(s[d]);
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


		static void Sort(std::vector<std::string> &a, size_t lo, size_t hi, size_t d, std::vector<std::string> &aux) {
			if (hi <= lo + kCutOff) {
				Insertion(a, lo, hi, d);
				return;
			}

			std::vector<size_t> count(kN_Ascii + 2);
			for (size_t i = lo; i <= hi; ++i) {
				int c = CharAt(a[i], d);
				++count[c + 2];
			}
			for (size_t r = 0; r < kN_Ascii + 1; ++r) {
				count[r + 1] += count[r];
			}
			for (size_t i = lo; i <= hi; ++i) {
				int c = CharAt(a[i], d);
				aux[count[c + 1]++] = a[i];
			}
			for (size_t i = lo; i <= hi; ++i) {
				a[i] = aux[i - lo];
			}

			for (size_t r = 1; r < kN_Ascii+1; ++r) {
				Sort(a, lo + count[r], lo + count[r + 1], d + 1, aux);
			}

		}

	public:
		static void Sort(std::vector<std::string> &a) {
			size_t n = a.size();
			if (n == 0) return;
			std::vector<std::string> aux(n);
			Sort(a, 0, n - 1, 0, aux);
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