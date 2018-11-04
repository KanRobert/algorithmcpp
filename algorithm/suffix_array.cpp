#include"suffix_array.h"
#undef min

namespace algorithmcpp {
	int Compare(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		size_t n = std::min(lhs.Size(), rhs.Size());
		for (size_t i = 0; i < n; ++i) {
			if (lhs[i] < rhs[i]) return -1;
			if (lhs[i] > rhs[i]) return +1;
		}
		if (lhs.Size() < rhs.Size()) return -1;
		if (lhs.Size() > rhs.Size()) return +1;
		return 0;
	}

	bool operator<(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		return Compare(lhs, rhs) == 0;
	}

	bool operator!=(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		return !(lhs == rhs);
	}

	bool operator<=(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		return Compare(lhs, rhs) >= 0;
	}

	size_t LcpSuffix(const SuffixArray::Suffix &lhs, const SuffixArray::Suffix &rhs) {
		size_t n = std::min(lhs.Size(), rhs.Size());
		for (size_t i = 0; i < n; ++i) {
			if (lhs[i] != rhs[i]) return i;
		}
		return n;
	}

	int Compare(const std::string &lhs, const SuffixArray::Suffix &rhs) {
		size_t n = std::min(lhs.size(), rhs.Size());
		for (size_t i = 0; i < n; ++i) {
			if (lhs[i] < rhs[i]) return -1;
			if (lhs[i] > rhs[i]) return +1;
		}
		if (lhs.size() < rhs.Size()) return -1;
		if (lhs.size() > rhs.Size()) return +1;
		return 0;
	}
}