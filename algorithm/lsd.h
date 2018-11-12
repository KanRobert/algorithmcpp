#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<iostream>

namespace algorithmcpp {
	class LSD {
	private:
		static constexpr unsigned char kBitsPerByte = 8;
		static constexpr unsigned char kBitsPerInt = sizeof(int) * 8;
		static constexpr unsigned kN_Ascii = 1U << kBitsPerByte;

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
				std::vector<size_t> count(kN_Ascii + 1);
				for (size_t i = 0; i < n; ++i) {
					++count[a[i][d] + 1];
				}		
				for (size_t r = 0; r < kN_Ascii; ++r) {
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
			constexpr unsigned char mask = kN_Ascii - 1;
			constexpr unsigned char w = kBitsPerInt / kBitsPerByte;

			size_t n = a.size();
			std::vector<int> aux(n);
			for (size_t d = 0; d < w; ++d) {
				std::vector<size_t> count(kN_Ascii + 1);
				for (size_t i = 0; i < n; ++i) {
					size_t c = static_cast<size_t>((a[i] >> kBitsPerByte * d)&mask);
					++count[c + 1];
				}
				for (size_t r = 0; r < kN_Ascii; ++r) {
					count[r + 1] += count[r];
				}
				if (d == w - 1) {
					size_t shift1 = count[kN_Ascii] - count[kN_Ascii / 2];
					size_t shift2 = count[kN_Ascii / 2];
					for (size_t r = 0; r < kN_Ascii / 2; ++r) {
						count[r] += shift1;
					}
					for (size_t r = kN_Ascii / 2; r < kN_Ascii; ++r) {
						count[r] -= shift2;
					}
				}

				for (size_t i = 0; i < n; ++i) {
					size_t c = static_cast<size_t>((a[i] >> kBitsPerByte * d)&mask);
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
