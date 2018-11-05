#include"substring.h"
#undef min

namespace algorithmcpp {
	int Compare(const Substring &lhs, const Substring &rhs) {
		size_t n = std::min(lhs.Size(), rhs.Size());
		for (size_t i = 0; i < n; ++i) {
			if (lhs[i] < rhs[i]) return -1;
			if (lhs[i] > rhs[i]) return +1;
		}
		if (lhs.Size() < rhs.Size()) return -1;
		if (lhs.Size() > rhs.Size()) return +1;
		return 0;
	}

	bool operator<(const Substring &lhs, const Substring &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const Substring &lhs, const Substring &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const Substring &lhs, const Substring &rhs) {
		return Compare(lhs, rhs) == 0;
	}

	bool operator!=(const Substring &lhs, const Substring &rhs) {
		return !(lhs == rhs);
	}

	bool operator<=(const Substring &lhs, const Substring &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const Substring &lhs, const Substring &rhs) {
		return Compare(lhs, rhs) >= 0;
	}

	int Compare(const std::string &lhs, const Substring &rhs) {
		size_t n = std::min(lhs.size(), rhs.Size());
		for (size_t i = 0; i < n; ++i) {
			if (lhs[i] < rhs[i]) return -1;
			if (lhs[i] > rhs[i]) return +1;
		}
		if (lhs.size() < rhs.Size()) return -1;
		if (lhs.size() > rhs.Size()) return +1;
		return 0;
	}

	int Compare(const Substring &lhs, const std::string &rhs) {
		int cmp = Compare(rhs, lhs);
		if (cmp < 0) return +1;
		if (cmp > 0) return -1;
		return 0;
	}
}