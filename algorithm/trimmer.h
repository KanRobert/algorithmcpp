#pragma once
#include<string>
#include<cassert>

namespace algorithmcpp {
	class Trimmer {
	private:
		static  const char* const kwhitespace_;

	public:
		Trimmer(const Trimmer &) = delete;
		Trimmer &operator=(const Trimmer &) = delete;
		~Trimmer() = delete;

		static void TrimLeft(std::string& s, const char* t = kwhitespace_) {
			s.erase(0, s.find_first_not_of(t));
		}

		static void TrimRight(std::string& s, const char* t = kwhitespace_) {
			s.erase(s.find_last_not_of(t) + 1);
		}

		static void Trim(std::string& s, const char* t = kwhitespace_) {
			TrimRight(s, t);
			TrimLeft(s, t);
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::string s("  I love you      ");
			Trim(s);
			assert( s== "I love you");
		}
	};
}