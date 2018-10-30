#include"directed_edge.h"

namespace algorithmcpp {

	int Compare(const DirectedEdge &lhs, const DirectedEdge &rhs) {
		if (lhs.edge_weight_ < rhs.edge_weight_) return -1;
		if (lhs.edge_weight_ > rhs.edge_weight_) return +1;
		return 0;
	}

	bool operator<(const DirectedEdge &lhs, const DirectedEdge &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const DirectedEdge &lhs, const DirectedEdge &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const DirectedEdge &lhs, const DirectedEdge &rhs) {
		if (lhs.edge_weight_ != rhs.edge_weight_) return false;
		return true;
	}

	bool operator<=(const DirectedEdge &lhs, const DirectedEdge &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const DirectedEdge &lhs, const DirectedEdge &rhs) {
		return Compare(lhs, rhs) >= 0;
	}

}
