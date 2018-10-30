#pragma once
#include"static_set_of_ints.h"
#include<fstream>

namespace algorithmcpp {
	class Whitelist {
	public:
		Whitelist(const Whitelist &) = delete;
		Whitelist &operator=(const Whitelist &) = delete;
		~Whitelist() = delete;

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream input1("../file/tinyW.txt");
			std::ifstream input2("../file/tinyT.txt");
			std::vector<int> keys;
			int key;
			while (input1 >> key) {
				keys.push_back(key);
			}
			StaticSETofInts set(keys);
			while (input2 >> key) {
				if (!set.Contains(key)) std::cout << key << std::endl;
			}
		}
	};
}