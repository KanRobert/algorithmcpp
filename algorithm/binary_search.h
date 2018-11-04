#pragma once
#include<vector>
#include<algorithm>
#include<cassert>
#include<optional>

namespace algorithmcpp {


	template<typename Item>class BinarySearch {
	public:
		BinarySearch(const BinarySearch &) = delete;
		BinarySearch &operator=(const BinarySearch &) = delete;
		~BinarySearch() = delete;

		static std::optional<size_t> IndexOf(const std::vector<Item> &a, const Item &key) {
			size_t lo = 0;
			size_t hi = a.size() - 1;
			while (lo <= hi && hi<a.size()) {
				size_t mid = lo + (hi - lo) / 2;
				if (key < a[mid]) hi = mid - 1;
				else if (key > a[mid]) lo = mid + 1;
				else return std::optional<size_t>(mid);
			}
			return std::optional<size_t>();
		}

		static int Rank(const Item &key, const std::vector<Item> &a) {
			return IndexOf(a, key);
		}

		static void MainTest(int argc=0, char *argv[]=nullptr) {
			std::vector<int> whitelist{1,3,5,7,9};
			std::sort(whitelist.begin(), whitelist.end());
			
			int key=6;
			assert(!IndexOf(whitelist, key).has_value());
			assert(IndexOf(whitelist, 3).value() == 1);

			std::vector<int> whitelist2{ 1 };
			assert(!IndexOf(whitelist2, 0).has_value());
		}
	};


}