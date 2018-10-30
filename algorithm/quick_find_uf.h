#pragma once
#include<vector>
#include<string>
#include<stdexcept>
#include<iostream>

namespace algorithmcpp {
	class QuickFindUF {
	private:
		std::vector<size_t> id_;
		size_t count_;

	public:
		QuickFindUF(size_t n):count_(n) {
			id_.reserve(n);
			for (size_t i = 0; i != n; ++i) {
				id_.push_back(i);
			}
		}

		QuickFindUF(const QuickFindUF &) = default;
		QuickFindUF &operator=(const QuickFindUF &p) = default;
		QuickFindUF(QuickFindUF &&) noexcept = default;
		QuickFindUF &operator=(QuickFindUF &&) noexcept = default;
		~QuickFindUF() = default;

		size_t SiteCount() const {
			return count_;
		}

		size_t Find(size_t p) const {
			Validate(p);
			return id_[p];
		}

		bool Connected(size_t p, size_t q) const {
			Validate(p);
			Validate(q);
			return id_[p] == id_[q];
		}

		void UnionSite(size_t p, size_t q) {
			Validate(p);
			Validate(q);
			size_t pID = id_[p];
			size_t qID = id_[q];

			if (pID == qID) return;

			for (size_t i = 0; i != id_.size(); ++i) {
				if (id_[i] == pID) id_[i] = qID;
				--count_;
			}
		}

	private:
		void Validate(size_t p) const {
			std::vector<size_t>::size_type N = id_.size();
			if (p >= N) {
				throw std::out_of_range("index" + std::to_string(p) + "is not between 0 and " + std::to_string(N - 1));
			}
		}

	public:
		static void MainTest(int argc, char *argv[]) {
			size_t n;
			std::cin >> n;
			QuickFindUF uf(n);
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
