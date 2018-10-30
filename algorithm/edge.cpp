#include"edge.h"

namespace algorithmcpp {

	int Compare(const Edge &lhs, const Edge &rhs) {
		if (lhs.edge_weight_ < rhs.edge_weight_) return -1;
		if (lhs.edge_weight_ > rhs.edge_weight_) return +1;
		return 0;
	}

	bool operator<(const Edge &lhs, const Edge &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const Edge &lhs, const Edge &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const Edge &lhs, const Edge &rhs) {
		if (lhs.edge_weight_ != rhs.edge_weight_) return false;
		return true;
	}

	bool operator<=(const Edge &lhs, const Edge &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const Edge &lhs, const Edge &rhs) {
		return Compare(lhs, rhs) >= 0;
	}

}
