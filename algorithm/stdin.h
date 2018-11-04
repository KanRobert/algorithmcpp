#pragma once
#include<string>
#include<fstream>
#include<sstream>

namespace algorithmcpp {
	class StdIn {
	public:
		StdIn(const StdIn &) = delete;
		StdIn &operator=(const StdIn &) = delete;
		~StdIn() = delete;

		static std::string ReadAll(std::ifstream &in) {
			std::stringstream sstr;
			sstr << in.rdbuf();
			return sstr.str();
		}
	};
}

