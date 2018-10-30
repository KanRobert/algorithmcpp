#pragma once
#include<vector>
#include<stdexcept>
#include<string>
#include<cassert>
#include<iostream>

#pragma push_macro("min")
#undef min

namespace algorithmcpp {
	template<typename Key> class IndexMaxPQ {
	private:
		size_t maxN_;
		size_t n_;
		std::vector<int> pq_;
		std::vector<int> qp_;
		std::vector<Key> keys_;

	public:
		IndexMaxPQ() = delete;
		IndexMaxPQ(const IndexMaxPQ &) = default;
		IndexMaxPQ(IndexMaxPQ &&) noexcept = default;
		IndexMaxPQ &operator=(const IndexMaxPQ &) = default;
		IndexMaxPQ &operator=(IndexMaxPQ &&) noexcept = default;
		~IndexMaxPQ() = default;

		IndexMaxPQ(size_t maxN) :
			maxN_(maxN), n_(0), pq_(std::vector<int>(maxN + 1, -1)), qp_(std::vector<int>(maxN + 1, -1)), keys_(std::vector<Key>(maxN)) {
		}

	private:
		void Check(size_t i) const {
			if (i >= maxN_) throw std::invalid_argument("index must be between " + std::to_string(0) + " and " + std::to_string(maxN_ - 1));
			if (!Contains(i)) throw std::invalid_argument("index is not in the priority queue");
		}

		void Exch(size_t i, size_t j) {
			using std::swap;
			swap(pq_[i], pq_[j]);
			qp_[pq_[i]] = i;
			qp_[pq_[j]] = j;
		}

		bool Less(size_t i, size_t j) const {
			return keys_[pq_[i]] > keys_[pq_[j]];
		}

		void Swim(size_t k) {
			while (k > 1 && Less(k / 2, k)) {
				Exch(k, k / 2);
				k = k / 2;
			}
		}

		void Sink(size_t k) {
			while (2 * k <= n_) {
				size_t j = 2 * k;
				if (j < n_ && Less(j, j + 1)) ++j;
				if (!Less(k, j)) break;
				Exch(k, j);
				k = j;
			}
		}

	public:

		bool IsEmpty() const {
			return n_ == 0;
		}

		bool Contains(size_t i) const {
			if (i >= maxN_) throw std::invalid_argument("index must be between " + std::to_string(0) + " and " + std::to_string(maxN_ - 1));
			return qp_[i] != -1;
		}

		size_t Size() const {
			return n_;
		}

		void Insert(size_t i, const Key &key) {
			if (i >= maxN_) throw std::invalid_argument("index must be between " + std::to_string(0) + " and " + std::to_string(maxN_ - 1));
			if (Contains(i)) throw std::invalid_argument("index is already in the priority queue");
			++n_;
			keys_[i] = key;
			qp_[i] = static_cast<int>(n_);
			pq_[n_] = static_cast<int>(i);
			Swim(n_);
		}

		size_t MaxIndex() const {
			if (n_ == 0) throw std::underflow_error("Priority queue underflow");
			return pq_[1];
		}

		Key MaxKey() const {
			if (n_ == 0) throw std::underflow_error("Priority queue underflow");
			return keys_[pq_[1]];
		}

		size_t DelMax() {
			if (n_ == 0) throw std::underflow_error("Priority queue underflow");
			size_t max = pq_[1];
			Exch(1, n_--);
			Sink(1);
			assert(max == pq_[n_ + 1]);
			qp_[max] = -1;
			pq_[n_ + 1] = -1;
			return max;
		}

		Key KeyOf(size_t i) const {
			Check(i);
			if (!Contains(i)) throw std::invalid_argument("index is not in the priority queue");
			return keys_[i];
		}

		void ChangeKey(size_t i, const Key &key) {
			Check(i);
			keys_[i] = key;
			Swim(qp_[i]);
			Sink(qp_[i]);
		}

		void DecreaseKey(size_t i, const Key &key) {
			Check(i);
			if (keys_[i] <= key) {
				throw std::invalid_argument("calling DecreaseKey() with given argument would not strictly decrease the key");
			}
			keys_[i] = key;
			Swim(qp_[i]);
		}

		void IncreaseKey(size_t i, const Key &key) {
			Check(i);
			if (keys_[i] >= key) {
				throw std::invalid_argument("calling IncreaseKey() with given argument would not strictly increase the key");
			}
			keys_[i] = key;
			Sink(qp_[i]);
		}

		void Delete(size_t i) {
			Check(i);
			size_t index = qp_[i];
			Exch(index, n_--);
			Swim(index);
			Sink(index);
			qp_[i] = -1;
		}

		std::vector<size_t> Vertices() const {
			std::vector<size_t> ret;
			ret.reserve(n_);
			IndexMaxPQ<Key> tmp(*this);
			while (!tmp.IsEmpty())
				ret.push_back(tmp.DelMax());
			return ret;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::vector<double> dvec{ 1.0,2.0,4.0,3.0,9.0,6.0,8.0,0.0 };
			IndexMaxPQ<double> pq(dvec.size());
			for (size_t i = 0; i < dvec.size(); ++i) {
				pq.Insert(i, dvec[i]);
			}

			while (!pq.IsEmpty()) {
				size_t i = pq.DelMax();
				std::cout << i << " " << dvec[i] << "\n";
			}
			std::cout << std::endl;
		}
	};
}

#pragma pop_macro("min")