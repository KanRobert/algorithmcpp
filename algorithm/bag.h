#pragma once
#include<cassert>
#include<utility>

namespace algorithmcpp {
	template<typename> class Bag;
	template<typename Item> void swap(Bag<Item> &, Bag<Item> &);
		 
	template<typename Item> class Bag {
		friend void swap<Item>(Bag<Item> &, Bag<Item> &);
	private:
		class Node {
		public:
			Item item_;
			Node *next_=nullptr;
		public:
			Node() = default;
			Node(const Node &) = delete;
			Node &operator=(const Node &) = delete;
			~Node() = default;
		};

		Node* first_=nullptr;
		size_t n_=0;

	public:
		Bag() = default;
		Bag(const Bag & rhs) {
			for (const Node *p = rhs.first_; p!=nullptr;p=p->next_) {
				Add(p->item_);
			}
		}
		Bag &operator=(Bag rhs) {
			swap(*this, Bag(rhs));
			return *this;
		}
		Bag(Bag &&rhs) noexcept {
			first_ = rhs.first_;
			n_ = rhs.n_;
			rhs.first_ = nullptr;
			rhs.n_ = 0;
		}

		~Bag() {
			while (first_) {
				Node *oldfirst = first_;
				first_ = oldfirst->next_;
				delete oldfirst;
			}
		}

		bool IsEmpty() const{
			return first_ == nullptr;
		}

		size_t Size() const{
			return n_;
		}

		void Add(const Item &item) {
			Node *oldfirst = first_;
			first_ = new Node;
			first_->item_ = item;
			first_->next_ = oldfirst;
			++n_;
		}

		bool Contains(const Item &item) const {
			for (const Node *p = first_; p != nullptr; p = p->next_) {
				if (p->item_ == item) return true;
			}
			return false;
		}

		class iterator {
		private:
			Node *pos_;
		public:
			iterator(Node *p):pos_(p) {
			}

			iterator &operator++() {
				pos_ = pos_->next_;
				return *this;
			}

			bool operator!=(const iterator &other) const {
				return pos_ != other.pos_;
			}

			Item &operator*() const {
				return pos_->item_;
			}
		};

		class const_iterator {
		private:
			Node *pos_;
		public:
			const_iterator(Node *p) :pos_(p) {
			}

			const_iterator &operator++() {
				pos_ = pos_->next_;
				return *this;
			}

			bool operator!=(const const_iterator &other) const {
				return pos_ != other.pos_;
			}

			const Item &operator*() const {
				return pos_->item_;
			}
		};

		const_iterator begin() const {
			return const_iterator(first_);
		}

		const_iterator end() const {
			return const_iterator(nullptr);
		}

		iterator begin() {
			return iterator(first_);
		}

		iterator end() {
			return iterator(nullptr);
		}

		bool operator==(const Bag &that) const {
			if (Size() != that.Size()) return false;
			for (auto it = that.begin(); it != that.end(); ++it) {
				if (!Contains(*it)) return false;
			}
			return true;
		}

		bool operator!=(const Bag &that) const {
			return !(*this == that);
		}

	public:
		static void MainTest(int argc=0, char *argv[]=nullptr) {
			Bag<size_t> bag;
			for (size_t i = 0; i != 5; ++i) {
				bag.Add(i);
			}
			for (const auto &x : bag) {
				std::cout << x << " ";
			}
			std::cout << std::endl;


			Bag<size_t> bag2(bag);
			for (const auto &x:bag2) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
			*bag2.begin() = 6;
			const Bag<size_t> &bag3 = bag2;
			std::cout << *bag3.begin()<<std::endl;

			Bag<size_t> bag4;
			for (size_t i = 5; i != 0; --i) {
				bag4.Add(i-1);
			}
			for (const auto &x:bag4) {
				std::cout << x << " ";
			}
			std::cout << std::endl;

			assert(bag.Contains(0));
			assert(!bag.Contains(6));
			assert(bag == bag4);
		}
	};

	template<typename Item>void swap(Bag<Item> &lhs, Bag<Item> &rhs) {
		using std::swap;
		swap(lhs.first_, rhs.first_);
		swap(lhs.n_, rhs.n_);
	}
}