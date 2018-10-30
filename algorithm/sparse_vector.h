#pragma once
#include"st.h"
#include<stdexcept>
#include<cmath>

namespace algorithmcpp {
	class SparseVector {
	private:
		size_t d_;
		ST<size_t, double> st_;

	public:
		SparseVector() = delete;
		SparseVector(const SparseVector &) = default;
		SparseVector &operator=(const SparseVector &) = default;
		SparseVector(SparseVector &&) noexcept= default;
		SparseVector &operator=(SparseVector &&) noexcept = default;
		~SparseVector() = default;

		SparseVector(size_t d) :d_(d) {}

		void Put(size_t i, double value) {
			if (i >= d_) throw std::invalid_argument("illegal index");
			if (value == 0.0) st_.Delete(i);
			else st_.Put(i, value);
		}

		double Get(size_t i) const {
			if (i >= d_) throw std::invalid_argument("illegal index");
			if (st_.Contains(i)) return st_.Get(i).value();
			else return 0.0;
		}

		size_t Nnz() const {
			return st_.Size();
		}

		size_t Dimension() const {
			return d_;
		}

		double dot(const SparseVector &that) const {
			if(d_!=(that.d_)) throw std::invalid_argument("vector lengths disagree");
			double sum = 0.0;
			if (st_.Size() <= that.st_.Size()) {
				Queue<size_t> keys = st_.Keys();
				for (const auto i : keys)
					if (that.st_.Contains(i)) sum += Get(i)*(that.Get(i));
			}
			else {
				Queue<size_t> keys = that.st_.Keys();
				for (const auto i : keys)
					if (st_.Contains(i)) sum += Get(i)*(that.Get(i));
			}
			return sum;
		}

		double dot(const std::vector<double> &that) const {
			if (d_ != (that.size())) throw std::invalid_argument("vector lengths disagree");
			double sum = 0.0;
			Queue<size_t> keys = st_.Keys();
			for (const auto i : keys) {
				sum += that[i] * Get(i);
			}
			return sum;
		}

		double magnitude() const {
			return std::sqrt(dot(*this));
		}

		SparseVector scale(double alpha) const {
			SparseVector ret(d_);
			for (const auto i : st_.Keys())
				ret.Put(i, alpha*Get(i));
			return ret;
		}

		SparseVector plus(const SparseVector &that) const {
			if(d_!=that.d_) throw std::invalid_argument("vector lengths disagree");
			SparseVector ret(d_);
			for (const auto i : st_.Keys()) ret.Put(i, Get(i));
			for (const auto i : that.st_.Keys()) ret.Put(i, that.Get(i)+ret.Get(i));
			return ret;
		}

		std::string ToString() const {
			std::string s;
			for (const auto i : st_.Keys()) {
				s += "(" + std::to_string(i) + ", " + std::to_string(st_.Get(i).value()) + ") ";
			}
			return s;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			SparseVector a(10);
			SparseVector b(10);
			a.Put(9, 0.75);
			a.Put(6, 0.11);
			a.Put(6, 0.00);
			b.Put(3, 0.60);
			b.Put(4, 0.90);
			std::cout << "a = " << a.ToString()<<std::endl;
			std::cout << "b = " << b.ToString() << std::endl;
			std::cout << "a dot b = " << a.dot(b) << std::endl;
			std::cout << "a + b = " << a.plus(b).ToString() << std::endl;
			SparseVector c(a);
			a = c;
			SparseVector d_(SparseVector(20));
		}
	};
}