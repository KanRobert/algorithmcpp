#pragma once
#include<vector>
#include<string>
#include<stdexcept>
#include<iostream>

namespace algorithmcpp {
	class QuickUnionUF {
	private:
		std::vector<size_t> parent_;
		size_t count_;

	public:
		QuickUnionUF(size_t n):count_(n) {
			parent_.reserve(n);
			for (size_t i = 0; i < n; ++n) {
				parent_.push_back(i);
			}
		}

		QuickUnionUF(const QuickUnionUF &) = default;
		QuickUnionUF &operator=(const QuickUnionUF &p) = default;
		QuickUnionUF(QuickUnionUF &&) noexcept = default;
		QuickUnionUF &operator=(QuickUnionUF &&) noexcept = default;
		~QuickUnionUF() = default;

		size_t SiteCount() const {
			return count_;
		}

		size_t Find(size_t p) const {
			Validate(p);
			while (p != parent_[p]) {
				p = parent_[p];
			}
		}

	private:
		void Validate(size_t p) const {
			std::vector<size_t>::size_type N = parent_.size();
			if (p >= N) {
				throw std::out_of_range("index" + std::to_string(p) + "is not between 0 and " + std::to_string(N - 1));
			}
		}

		bool Connected(size_t p, size_t q) const {
			return Find(p) == Find(q);
		}

		void UnionSite(size_t p, size_t q) {
			size_t rootP = Find(p);
			size_t rootQ = Find(q);
			if (rootP == rootQ) return;
			parent_[rootP] = rootQ;
			--count_;
		}

	public:
		static void MainTest(int argc, char *argv[]) {
			size_t n;
			std::cin >> n;
			QuickUnionUF uf(n);
			size_t p, q;
			while (std::cin >> p >> q) {
				if (uf.Connected(p, q)) continue;
				uf.UnionSite(p, q);
				std::cout << p << " " << q << std::endl;
			}
			std::cout << uf.SiteCount() << " components";
		}
	};
}