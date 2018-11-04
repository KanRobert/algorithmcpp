#include"counter.h"
namespace algorithmcpp {
	int Compare(const Counter &lhs,const Counter &rhs) {
		if (lhs.count_ < rhs.count_) return -1;
		else if (lhs.count_ > rhs.count_) return +1;
		else return 0;
	}

	bool operator<(const Counter &lhs, const Counter &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const Counter &lhs, const Counter &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const Counter &lhs, const Counter &rhs){
		return Compare(lhs, rhs) == 0;
	}

	bool operator!=(const Counter &lhs, const Counter &rhs) {
		return !(lhs == rhs);
	}

	bool operator<=(const Counter &lhs, const Counter &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const Counter &lhs, const Counter &rhs) {
		return Compare(lhs, rhs) >= 0;
	}
}