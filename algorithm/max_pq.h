#pragma once
#pragma warning (disable : 4996)
#include<memory>
#include<functional>
#include<vector>
#include<cassert>
#include<initializer_list>
#include<stdexcept>

#pragma push_macro("free")
#pragma push_macro("max")
#undef free
#undef max

namespace algorithmcpp {
	template<typename> class MaxPQ;
	template<typename Key> void swap(MaxPQ<Key> &, MaxPQ<Key> &);

	template<typename Key> class MaxPQ {
		friend void swap<Key>(MaxPQ<Key> &, MaxPQ<Key> &);
	private:
		static std::allocator<Key> alloc_;
		size_t nmemory_ = 2;
		Key *a_ = alloc_.allocate(nmemory_);
		Key *b_ = a_+1;
		size_t n_ = 0;
		std::function<bool(const Key &, const Key &)> less_;

	private:
		template<typename Iter>
		void ConstructHelper(Iter beg, Iter end) {
			Iter it = beg;
			while (it != end) {
				alloc_.construct(b_++, *it++);
			}
			for (size_t k = n_ / 2; k >= 1; --k)
				Sink(k);
		}

		void Free() {
			while (b_ != a_)
				if (b_ != a_ + 1) alloc_.destroy(--b_);
				else --b_;
				alloc_.deallocate(a_, nmemory_);
		}

		void Swim(size_t k) {
			using std::swap;
			while (k > 1 && less_(a_[k / 2], a_[k])) {
				swap(a_[k], a_[k / 2]);
				k /= 2;
			}
		}

		void Sink(size_t k) {
			using std::swap;
			while (2 * k <= n_) {
				size_t j = 2 * k;
				if (j < n_ && less_(a_[j], a_[j + 1])) j++;
				if (!less_(a_[k], a_[j])) break;
				swap(a_[k], a_[j]);
				k = j;
			}
		}

		bool IsMaxHeap() const {
			return IsMaxHeap(1);
		}

		bool IsMaxHeap(size_t k) const {
			if (k > n_) return true;
			size_t left = 2 * k;
			size_t right = 2 * k + 1;
			if (left <= n_ && less_(a_[k], a_[left])) return false;
			if (right <= n_ && less_(a_[k], a_[right])) return false;
			return IsMaxHeap(left) && IsMaxHeap(right);
		}

	public:
		MaxPQ(const std::function<bool(const Key &, const Key &)> func = std::less<Key>{})
			:less_(func){
		}
		MaxPQ(const MaxPQ &rhs):nmemory_(rhs.nmemory_),n_(rhs.n_),less_(rhs.less_) {
			std::uninitialized_copy_n(rhs.a_ + 1, n_, a_ + 1);
			b_ = a_ + 1 + n_;
		}
		MaxPQ &operator=(MaxPQ rhs) {
			swap(*this, rhs);
			return *this;
		}
		MaxPQ(MaxPQ &&rhs) noexcept:nmemory_(rhs.nmemory_),a_(rhs.a_),b_(rhs.b_),n_(rhs.n_), less_(rhs.less_) {
			rhs.nmemory_ = 0;
			rhs.a_ = nullptr;
			rhs.b_ = nullptr;
			rhs.n_ = 0;
		}

		~MaxPQ() {
			Free();
		}

		MaxPQ(size_t initCapacity, const std::function<bool(const Key &, const Key &)> func = std::less<Key>{})
			:nmemory_(initCapacity + 1), less_(func) {
		}

		MaxPQ(const std::vector<Key> &keys, const std::function<bool(const Key &, const Key &)> func = std::less<Key>{})
			:nmemory_(keys.size() + 1), n_(keys.size()), less_(func) {

			ConstructHelper(keys.begin(), keys.end());
			assert(IsMaxHeap());
		}

		MaxPQ(const std::initializer_list<Key> &keys, const std::function<bool(const Key &, const Key &)> func = std::less<Key>{})
			:nmemory_(keys.size() + 1), n_(keys.size()),less_(func) {

			ConstructHelper(keys.begin(), keys.end());
			assert(IsMaxHeap());
		}

		bool IsEmpty() const {
			return n_ == 0;
		}

		size_t Size() const {
			return n_;
		}

		Key Max() const {
			if (IsEmpty()) throw std::underflow_error("Priority queue underflow");
			return a_[1];
		}

		void Resize(size_t capacity) {
			assert(capacity > n_);
			Key * const temp = alloc_.allocate(capacity);
			std::uninitialized_copy_n(a_+1, n_, temp+1);
			Free();
			a_ = temp;
			b_ = a_ + 1 + n_;
			nmemory_ = capacity;
		}

		void Insert(const Key &x) {
			if (n_ == nmemory_ - 1) Resize(2 * nmemory_);
			alloc_.construct(b_++, x);
			++n_;
			Swim(n_);
			assert(IsMaxHeap());
		}

		Key DelMax() {
			using std::swap;
			if(IsEmpty()) throw std::underflow_error("Priority queue underflow");
			Key max = a_[1];
			swap(a_[1], a_[n_--]);
			Sink(1);
			alloc_.destroy(--b_);
			if ((n_ > 0) && (n_ == (nmemory_ - 1) / 4)) Resize(nmemory_ / 2);
			assert(IsMaxHeap());
			return max;
		}

		std::vector<Key> Keys() const{
			std::vector<Key> ret;
			ret.reserve(n_);
			MaxPQ<Key> tmp(*this);
			while(!tmp.IsEmpty())
				ret.push_back(tmp.DelMax());
			return ret;
		}


	public:
		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			MaxPQ<int> pq({ 1,2,3,4,5,6,7,8,9 });
			assert(pq.Size() == 9);

			int x = pq.DelMax();
			assert(x == 9);

			pq.Insert(10);
			assert(pq.Max() == 10);

			MaxPQ<int> pq2(pq);
			for (const auto &x : pq.Keys()) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
		}
	};

	template<typename Key>
	std::allocator<Key> MaxPQ<Key>::alloc_ = std::allocator<Key>();
	template<typename Key>void swap(MaxPQ<Key> &lhs, MaxPQ<Key> &rhs) {
		using std::swap;
		swap(lhs.nmemory_, rhs.nmemory_);
		swap(lhs.a_, rhs.a_);
		swap(lhs.b_, rhs.b_);
		swap(lhs.n_, rhs.n_);
		swap(lhs.less_, rhs.less_);
	}
}

#pragma pop_macro("max")
#pragma pop_macro("free")