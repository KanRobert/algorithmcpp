#pragma once
#include<fstream>
#include<set>
#include<string>
#include<iostream>

namespace algorithmcpp {
	class BlackFilter {
	public:
		BlackFilter(const BlackFilter &) = delete;
		BlackFilter &operator=(const BlackFilter &) = delete;
		~BlackFilter() = delete;

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream input1("../file/list.txt");
			std::ifstream input2("../file/tinyTale.txt");
			std::set<std::string> keys;
			std::string key;
			while (input1 >> key) {
				keys.insert(key);
			}

			int i = 0;
			while (input2 >> key) {
				if (keys.find(key) != keys.end()) {
					std::cout << key << " ";
					++i;
					if (i % 8 == 0) std::cout << std::endl;
				}
			}
		}
	};
}