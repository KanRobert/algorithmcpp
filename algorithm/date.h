#pragma once
#include<array>
#include<stdexcept>
#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include<cassert>

namespace algorithmcpp {
	class Date {
		friend bool operator<(const Date &, const Date &);
		friend bool operator>(const Date &, const Date &);
		friend bool operator==(const Date &, const Date &);
		friend bool operator!=(const Date &, const Date &);
		friend bool operator<=(const Date &, const Date &);
		friend bool operator>=(const Date &, const Date &);
		friend int Compare(const Date &, const Date &);

	public:
		Date(const Date &) = default;
		Date &operator=(const Date &) = default;
		Date(Date &&) noexcept = default;
		Date &operator=(Date &&) noexcept = default;
		~Date() = default;

		Date(size_t Month, size_t day, size_t year): month_(Month),day_(day),year_(year){
			if (!IsValid(Month, day, year)) throw std::invalid_argument("invalid date");
		}

		Date(const std::string &date) {
			std::vector<std::string> fields = Split(date, '/');
			if (fields.size() != 3) {
				throw std::invalid_argument("Invalid date");
			}
		    month_ = std::stoi(fields[0]);
			day_ = std::stoi(fields[1]);
			year_ = std::stoi(fields[2]);
			if (!IsValid(month_, day_, year_)) throw std::invalid_argument("invalid date");
		}

	private:
		static constexpr std::array<size_t, 13> kDays = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
		size_t month_=0;
		size_t day_=0;
		size_t year_=0;

		static std::vector<std::string> Split(const std::string &s, char delim) {
			std::vector<std::string> elems;
			std::string item_;
			std::istringstream ss(s);
			while (std::getline(ss, item_, delim)) {
				elems.push_back(item_);
			}
			return elems;
		}

		static bool IsValid(size_t m, size_t d, size_t y) {
			if (m < 1 || m > 12)      return false;
			if (d < 1 || d > kDays[m]) return false;
			if (m == 2 && d == 29 && !IsLeapYear(y)) return false;
			return true;
		}

		static bool IsLeapYear(size_t y) {
			if (y % 400 == 0) return true;
			if (y % 100 == 0) return false;
			return y % 4 == 0;
		}

	public:
		size_t Month() const {
			return month_;
		}

		size_t Day() const {
			return day_;
		}

		size_t Year() const {
			return year_;
		}

		Date Next() const {
			if (IsValid(month_, day_ + 1, year_)) return Date(month_, day_ + 1, year_);
			else if (IsValid(month_ + 1, 1, year_)) return  Date(month_ + 1, 1, year_);
			else return Date(1, 1, year_ + 1);
		}

		std::string ToString() const {
			return std::to_string(month_) + "/" + std::to_string(day_) + "/" + std::to_string(year_);
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			Date today(1, 18, 2018);
			std::cout << today.ToString() << std::endl;
			for (size_t i = 0; i < 20; ++i) {
				today = today.Next();
				std::cout << today.ToString() << std::endl;
			}

			assert(!(today > today.Next()));
			assert(!(today > today));
			assert(today.Next() > today);
		}

	};
	bool operator<(const Date &, const Date &);
	bool operator>(const Date &, const Date &);
	bool operator==(const Date &, const Date &);
	bool operator!=(const Date &, const Date &);
	bool operator<=(const Date &, const Date &);
	bool operator>=(const Date &, const Date &);
	int Compare(const Date &, const Date &);
}