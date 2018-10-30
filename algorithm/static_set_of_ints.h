#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>

namespace algorithmcpp {
	class StaticSETofInts {
	private:
		std::vector<int> a;
	public:
		StaticSETofInts() = delete;
		StaticSETofInts(const StaticSETofInts &) = default;
		StaticSETofInts &operator=(const StaticSETofInts &) = default;
		StaticSETofInts(StaticSETofInts &&) noexcept= default;
		StaticSETofInts &operator=(StaticSETofInts &&) noexcept= default;
		~StaticSETofInts() = default;

		StaticSETofInts(const std::vector<int> &keys):a(keys){
			std::sort(a.begin(),a.end());
			for (size_t i = 1; i != a.size(); ++i)
				if (a[i] == a[i - 1]) throw std::invalid_argument("Argument arrays Contains duplicate keys.");
		}

		bool Contains(int key) const {
			return Rank(key) != -1;
		}

		int Rank(int key) const {
			int lo = 0;
			int hi = static_cast<int>(a.size() - 1);
			while (lo <= hi) {
				int mid = lo + (hi - lo) / 2;
				if (key < a[mid]) hi = mid - 1;
				else if (key > a[mid]) lo = mid + 1;
				else return mid;
			}
			return -1;
		}

	};
}