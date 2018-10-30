#pragma once
#include<vector>
#include<stdexcept>
#include<string>
#include<iostream>
#include<memory>



namespace algorithmcpp {
	class WeightedQuickUnionUF {
	private:
		std::vector<size_t> parent_;
		std::vector<size_t> size_;
		size_t count_;

	public:
		WeightedQuickUnionUF(const WeightedQuickUnionUF &) = default;
		WeightedQuickUnionUF &operator=(const WeightedQuickUnionUF &) = default;
		WeightedQuickUnionUF(WeightedQuickUnionUF &&) noexcept = default;
		WeightedQuickUnionUF &operator=(WeightedQuickUnionUF &&) noexcept = default;
		~WeightedQuickUnionUF() = default;

		WeightedQuickUnionUF(size_t N) :count_(N){
			parent_.reserve(N);
			size_.reserve(N);
			for (size_t i = 0; i != N; ++i) {
				parent_.push_back(i);
				size_.push_back(1);
			}
		}

		size_t Find(size_t p) {
			Validate(p);
			while (p != parent_[p]) {
				p = parent_[p];
			}
			return p;
		}

		size_t SiteCount() const {
			return count_;
		}

		bool Connected(size_t p, size_t q) {
			return Find(p) == Find(q);
		}

		void UnionSite(size_t p, size_t q) {
			size_t rootP = Find(p);
			size_t rootQ = Find(q);
			if (rootP == rootQ) return;

			if (size_[rootP] < size_[rootQ]) {
				parent_[rootP] = rootQ;
				size_[rootQ] += size_[rootP];
			}
			else {
				parent_[rootQ] = rootP;
				size_[rootP] += size_[rootQ];
			}
			--count_;
		}

	private:
		void Validate(size_t p) const {
			std::vector<size_t>::size_type N = parent_.size();
			if (p >= N) {
				throw std::out_of_range("index" + std::to_string(p) + "is not between 0 and " + std::to_string(N - 1));
			}
		}

	public:
		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream input("../file/tinyUF.txt");
			size_t n;
			input >> n;
			WeightedQuickUnionUF uf(n);
			size_t p, q;
			while (input >> p >> q) {
				if (uf.Connected(p, q)) continue;
				uf.UnionSite(p, q);
				std::cout << p << " " << q << std::endl;
			}
			std::cout << uf.SiteCount() << " components" << std::endl;
			WeightedQuickUnionUF uf2(uf);
			uf = uf2;
		}

	};
}
