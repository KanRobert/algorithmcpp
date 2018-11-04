#pragma once
#include"suffix_array.h"
#include"stdin.h"
#include<string>
#include<algorithm>
#include<regex>

#pragma push_macro("min")
#undef min

namespace algorithmcpp {
	class LongestCommonSubstring {
	public:
		LongestCommonSubstring(const LongestCommonSubstring &) = delete;
		LongestCommonSubstring &operator=(const LongestCommonSubstring &) = delete;
		~LongestCommonSubstring() = delete;

	private:
		static std::string Lcp(const std::string &s, size_t p, const std::string &t, size_t q) {
			size_t n = std::min(s.size() - p, t.size() - q);
			for (size_t i = 0; i < n; ++i) {
				if (s[p + i] != t[q + i]) {
					return s.substr(p, i);
				}
			}
			return s.substr(p, n);
		}

		static int Compare(const std::string &s, size_t p, const std::string &t, size_t q) {
			size_t n = std::min(s.size() - p, t.size() - q);
			for (size_t i = 0; i < n; ++i) {
				if (s[p + i] < t[q + i]) return -1;
				if (s[p + i] > t[q + i]) return +1;
			}
			if (s.size() - p < t.size() - q) return -1;
			if (s.size() - p > t.size() - q) return +1;
			return 0;
		}

	public:
		static std::string Lcs(const std::string &s, const std::string &t) {
			SuffixArray suffix1(s);
			SuffixArray suffix2(t);

			std::string lcs;
			size_t i = 0, j = 0;
			while (i < s.size() && j < t.size()) {
				size_t p = suffix1.Index(i);
				size_t q = suffix2.Index(j);
				std::string x = Lcp(s, p, t, q);
				if (x.size() > lcs.size()) lcs = x;
				if (Compare(s, p, t, q) < 0) ++i;
				else ++j;
			}
			return lcs;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in1("../file/tale.txt");
			std::ifstream in2("../file/mobydick.txt");
			std::string s = StdIn::ReadAll(in1);
			std::string t = StdIn::ReadAll(in2);
			s = std::regex_replace(s, std::regex("\\s+"), " ");
			t = std::regex_replace(t, std::regex("\\s+"), " ");
			Trimmer::Trim(s);
			Trimmer::Trim(t);
			std::cout << "'" << Lcs(s, t) << "'" << std::endl;
		}
	};
}

#pragma pop_macro("min")