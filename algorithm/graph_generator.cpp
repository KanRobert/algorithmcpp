#include"graph_generator.h"

namespace algorithmcpp {
	int Compare(const GraphGenerator::Edge &lhs, const GraphGenerator::Edge &rhs) {
		if (lhs.v < rhs.v) return -1;
		if (lhs.v > rhs.v) return +1;
		if (lhs.w < rhs.w) return -1;
		if (lhs.w > rhs.w) return +1;
		return 0;
	}

	bool operator<(const GraphGenerator::Edge &lhs, const GraphGenerator::Edge &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const GraphGenerator::Edge &lhs, const GraphGenerator::Edge &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const GraphGenerator::Edge &lhs, const GraphGenerator::Edge &rhs) {
		return Compare(lhs, rhs) == 0;
	}

	bool operator!=(const GraphGenerator::Edge &lhs, const GraphGenerator::Edge &rhs) {
		return !(lhs == rhs);
	}

	bool operator<=(const GraphGenerator::Edge &lhs, const GraphGenerator::Edge &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const GraphGenerator::Edge &lhs, const GraphGenerator::Edge &rhs) {
		return Compare(lhs, rhs) >= 0;
	}
}