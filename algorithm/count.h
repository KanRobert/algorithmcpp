#pragma once
#include<fstream>
#include<set>
#include<map>
#include<iostream>

namespace algorithmcpp {
	class Count {
	public:
		Count(const Count &) = delete;
		Count &operator=(const Count &) = delete;
		~Count() = delete;

		static void MainTest(int argc = 0, char* argv[] = nullptr) {
			std::ifstream in("../file/pi.txt");
			std::ifstream whitelist("../file/input.txt");
			char c;
			std::set<char> alphabet;
			while (whitelist >> c) {
				alphabet.insert(c);
			}
			
			std::map<char, size_t> count;
			while (in >> c) {
				if (alphabet.find(c) != alphabet.end()) {
					++count[c];
				}
			}
			for (auto it = count.cbegin(); it != count.cend(); ++it) {
				std::cout << it->first << " " << it->second << std::endl;
			}
			
		}

	};
}