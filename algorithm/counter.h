#pragma once
#include"stdrandom.h"
#include<string>
#include<vector>
#include<iostream>

namespace algorithmcpp {
	class Counter {
		friend bool operator<(const Counter &, const Counter &);
		friend bool operator>(const Counter &, const Counter &);
		friend bool operator==(const Counter &, const Counter &);
		friend bool operator!=(const Counter &, const Counter &);
		friend bool operator<=(const Counter &, const Counter &);
		friend bool operator>=(const Counter &, const Counter &);
		friend int Compare(const Counter &, const Counter &);
	private:
		const std::string name_;
		size_t count_ = 0;

	public:
		Counter(const Counter &) = default;
		Counter &operator=(const Counter &) = default;
		Counter(Counter &&) noexcept  = default;
		Counter &operator=(Counter &&) noexcept = default;
		Counter(std::string id):name_(id) {};
		~Counter() = default;

	public:
		void Increment() {
			++count_;
		}

		size_t Tally() const {
			return count_;
		}

		std::string ToString() const {
			return std::to_string(count_) + " " + name_;
		}

		static void MainTest(int argc = 0, char* argv[] = nullptr) {
			constexpr size_t n = 6;
			constexpr size_t trials = 600000;

			std::vector<Counter> hits;
			for (size_t i = 0; i < n; ++i) {
				hits.push_back(Counter("counter" + std::to_string(i)));
			}

			for (size_t t = 0; t < trials; ++t) {
				hits[StdRandom::Uniform(n)].Increment();
			}

			for (size_t i = 0; i < n; ++i) {
				std::cout << hits[i].ToString() << std::endl;
			}
		}
	};
	
	bool operator<(const Counter &, const Counter &);
	bool operator>(const Counter &, const Counter &);
	bool operator==(const Counter &, const Counter &);
	bool operator!=(const Counter &, const Counter &);
	bool operator<=(const Counter &, const Counter &);
	bool operator>=(const Counter &, const Counter &);
	int Compare(const Counter &, const Counter &);
}