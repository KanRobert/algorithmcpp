#include"date.h"

namespace algorithmcpp {

	int Compare(const Date &lhs, const Date &rhs) {
		if (lhs.year_ < rhs.year_) return -1;
		if (lhs.year_ > rhs.year_) return +1;
		if (lhs.month_ < rhs.month_) return -1;
		if (lhs.month_ > rhs.month_) return +1;
		if (lhs.day_ < rhs.day_) return -1;
		if (lhs.day_ > rhs.day_) return +1;
		return 0;
	}

	bool operator<(const Date &lhs, const Date &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const Date &lhs, const Date &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const Date &lhs, const Date &rhs) {
		if (lhs.year_ != rhs.year_) return false;
		if (lhs.month_ != rhs.month_) return false;
		if (lhs.day_ != rhs.day_) return false;
		return true;
	}

	bool operator!=(const Date &lhs, const Date &rhs) {
		return !(lhs == rhs);
	}

	bool operator<=(const Date &lhs, const Date &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const Date &lhs, const Date &rhs) {
		return Compare(lhs, rhs) >= 0;
	}

}
