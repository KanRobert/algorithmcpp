#pragma once
#include"suffix_array.h"
#include"stdin.h"
#include<string>
#include<regex>

namespace algorithmcpp {
	class LongestRepeatedSubstring {
	public:
		LongestRepeatedSubstring(const LongestRepeatedSubstring &) = delete;
		LongestRepeatedSubstring &operator=(const LongestRepeatedSubstring &) = delete;
		~LongestRepeatedSubstring() = delete;

		static std::string Lrs(const std::string &text) {
			size_t n = text.size();
			SuffixArray sa(text);
			std::string lrs;
			for (size_t i = 1; i < n; ++i) {
				size_t length = sa.Lcp(i);
				if (length > lrs.size()) {
					lrs = text.substr(sa.Index(i), length);
				}
			}
			return lrs;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyTale.txt");
			std::string s=StdIn::ReadAll(in);
			s=std::regex_replace(s, std::regex("\\s+"), " ");
			Trimmer::Trim(s);
			std::string text= Lrs(s);
			std::cout << "'" << text << "'" << std::endl;
		}
	};
}