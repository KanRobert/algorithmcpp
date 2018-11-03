#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<iostream>

namespace algorithmcpp {
	class LSD {
	private:
		static constexpr unsigned char kbits_per_byte_ = 8;
		static constexpr unsigned char kbits_per_int = sizeof(int) * 8;
		static constexpr unsigned kn_ascii_ = 1U << kbits_per_byte_;

	public:
		LSD(const LSD &) = delete;
		LSD &operator=(const LSD &) = delete;
		~LSD() = delete;
	public:
		static void Sort(std::vector<std::string> &a, size_t w) {
			size_t n = a.size();
			std::vector<std::string> aux(n);
			for (size_t d = w; d > 0;) {
				--d;
				std::vector<size_t> count(kn_ascii_ + 1);
				for (size_t i = 0; i < n; ++i) {
					++count[a[i][d] + 1];
				}		
				for (size_t r = 0; r < kn_ascii_; ++r) {
					count[r + 1] += count[r];
				}
				for (size_t i = 0; i < n; ++i) {
					aux[count[a[i][d]]++] = a[i];
				}
				for (size_t i = 0; i < n; ++i) {
					a[i] = aux[i];
				}
			}
		}

		static void Sort(std::vector<int> &a) {
			constexpr unsigned char mask = kn_ascii_ - 1;
			constexpr unsigned char w = kbits_per_int / kbits_per_byte_;

			size_t n = a.size();
			std::vector<int> aux(n);
			for (size_t d = 0; d < w; ++d) {
				std::vector<size_t> count(kn_ascii_ + 1);
				for (size_t i = 0; i < n; ++i) {
					size_t c = static_cast<size_t>((a[i] >> kbits_per_byte_ * d)&mask);
					++count[c + 1];
				}
				for (size_t r = 0; r < kn_ascii_; ++r) {
					count[r + 1] += count[r];
				}
				if (d == w - 1) {
					size_t shift1 = count[kn_ascii_] - count[kn_ascii_ / 2];
					size_t shift2 = count[kn_ascii_ / 2];
					for (size_t r = 0; r < kn_ascii_ / 2; ++r) {
						count[r] += shift1;
					}
					for (size_t r = kn_ascii_ / 2; r < kn_ascii_; ++r) {
						count[r] -= shift2;
					}
				}

				for (size_t i = 0; i < n; ++i) {
					size_t c = static_cast<size_t>((a[i] >> kbits_per_byte_ * d)&mask);
					aux[count[c]++] = a[i];
				}
				for (size_t i = 0; i < n; ++i) {
					a[i] = aux[i];
				}
			}
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/words3.txt");
			std::vector<std::string> a;
			std::string word;
			size_t w = 0;
			while (in >> word) {
				if (word.size() > w) w = word.size();
				a.push_back(word);
			}
			
			Sort(a, w);
			for (const std::string &s : a) {
				std::cout << s << "\n";
			}
			std::cout << "\n";

			std::vector<int> ivec{ -9,-7,2,4,1,10,-3 };
			Sort(ivec);
			for (int x : ivec) {
				std::cout << x << "\n";
			}
		}

	};
}
