#pragma once
#pragma warning (disable : 4996)
#include<memory>
#include<cassert>

namespace algorithmcpp {
	template<typename> class ResizingArrayBag;
	template<typename Item> void swap(ResizingArrayBag<Item> &, ResizingArrayBag<Item> &);

	template<typename Item> class ResizingArrayBag {
		friend void swap<Item>(ResizingArrayBag<Item> &, ResizingArrayBag<Item> &);
	private:
		static std::allocator<Item> alloc_;
		size_t nmemory_ = 2;
		Item *a_ = alloc_.allocate(nmemory_);
		Item *b_ = a_;
		size_t n_=0;

	public:
		ResizingArrayBag() = default;
		ResizingArrayBag(const ResizingArrayBag &rhs) :nmemory_(rhs.nmemory_), n_(rhs.n_) {
			std::uninitialized_copy_n(rhs.a_, n_, a_);
			b_ = a_ + n_;
		}
		ResizingArrayBag &operator=(const ResizingArrayBag &rhs) {
			swap(*this, ResizingArrayBag(rhs));
			return *this;
		}
		ResizingArrayBag(ResizingArrayBag &&rhs) noexcept :nmemory_(rhs.nmemory_), a_(rhs.a_), b_(rhs.b_), n_(rhs.n_){
			rhs.nmemory_ = 0;
			rhs.a_ = nullptr;
			rhs.b_ = nullptr;
			rhs.n_ = 0;
		}
		ResizingArrayBag &operator=(ResizingArrayBag &&rhs) noexcept {
			swap(*this, rhs);
			return *this;
		}
		~ResizingArrayBag(){
			while (b_ != a_)
				alloc_.destroy(--b_);
			alloc_.deallocate(a_, nmemory_);
		}

		bool IsEmpty() const {
			return n_ == 0;
		}

		int Size() const {
			return n_;
		}


		void Resize(size_t capacity) {
			assert(capacity >= n_);
			Item * const temp = alloc_.allocate(capacity);
			std::uninitialized_copy_n(a_, n_, temp);
			while (b_ != a_) alloc_.destroy(--b_);
			alloc_.deallocate(a_, nmemory_);
			a_ = temp;
			b_ = a_ + n_;
			nmemory_ = capacity;
		}

		void Add(const Item &item_) {
			if (n_ == nmemory_) Resize(2 * nmemory_);
			alloc_.construct(b_++, item_);
			++n_;
		}

		bool Contains(const Item &item_) const {
			for (const Item *p = a_; p != b_; ++p) {
				if (*p == item_) return true;
			}
			return false;
		}

		class iterator {
		private:
			Item *pos_;
		public:
			iterator(Item *p) :pos_(p) {

			}

			iterator &operator++() {
				++pos_;
				return *this;
			}

			bool operator!=(const iterator &other) const {
				return pos_ != other.pos_;
			}

			Item &operator*() const {
				return *pos_;
			}
		};

		class const_iterator {
		private:
			Item *pos_;
		public:
			const_iterator(Item *p) :pos_(p) {

			}

			const_iterator &operator++() {
				++pos_;
				return *this;
			}

			bool operator!=(const const_iterator &other) const {
				return pos_ != other.pos_;
			}

			const Item &operator*() const {
				return *pos_;
			}
		};

		iterator begin() {
			return iterator(a_);
		}

		iterator end() {
			return iterator(b_);
		}

		const_iterator begin() const {
			return const_iterator(a_);
		}

		const_iterator end() const {
			return const_iterator(b_);
		}

		bool operator==(const ResizingArrayBag &that) const {
			if (Size() != that.Size()) return false;
			for (auto it = that.begin(); it != that.end(); ++it) {
				if (!Contains(*it)) return false;
			}
			return true;
		}

		bool operator!=(const ResizingArrayBag &that) const {
			return !(*this == that);
		}

	public:
		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			ResizingArrayBag<size_t> bag;
			for (size_t i = 0; i != 5; ++i) {
				bag.Add(i);
			}
			for (const auto &x : bag) {
				std::cout << x << " ";
			}
			std::cout << std::endl;


			ResizingArrayBag<size_t> bag2(bag);
			for (const auto &x : bag2) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
			*bag2.begin() = 6;
			const ResizingArrayBag<size_t> &bag3 = bag2;
			std::cout << *bag3.begin() << std::endl;

			ResizingArrayBag<size_t> bag4;
			for (size_t i = 5; i != 0; --i) {
				bag4.Add(i - 1);
			}
			for (const auto &x : bag4) {
				std::cout << x << " ";
			}
			std::cout << std::endl;

			assert(bag.Contains(0));
			assert(!bag.Contains(6));
			assert(bag == bag4);
		}
	};

	template<typename Item>
    std::allocator<Item> ResizingArrayBag<Item>::alloc_ = std::allocator<Item>();
	template<typename Item>void swap(ResizingArrayBag<Item> &lhs, ResizingArrayBag<Item> &rhs) {
		using std::swap;
		swap(lhs.nmemory_, rhs.nmemory_);
		swap(lhs.a_, rhs.a_);
		swap(lhs.b_, rhs.b_);
		swap(lhs.n_, rhs.n_);
	}
}