#pragma once
#include<cassert>
#include<stdexcept>

/*Stack is exactly same as LinkedStack, so there is not need to write twice*/
namespace algorithmcpp {
	template<typename> class Stack;
	template<typename Item> void swap(Stack<Item> &, Stack<Item> &);

	template<typename Item> class Stack {
		friend void swap<Item>(Stack<Item> &, Stack<Item> &);
	private:
		class Node {
		public:
			Item item_;
			Node *next_ = nullptr;
		public:
			Node() = default;
			Node(const Node &) = delete;
			Node &operator=(const Node &) = delete;
			~Node() = default;
		};

		Node* first_ = nullptr;
		size_t n_ = 0;

	public:
		Stack() {
			assert(Check());
		}
		Stack(const Stack &rhs) {
			Stack<Item> tmp;
			for (const Node *p = rhs.first_; p != nullptr; p = p->next_) {
				tmp.Push(p->item_);
			}
			for (const Node *p = tmp.first_; p != nullptr; p = p->next_) {
				Push(p->item_);
			}
		}
		Stack &operator=(Stack rhs) {
			swap(*this, rhs);
			return *this;
		}
		Stack(Stack &&rhs) noexcept {
			first_ = rhs.first_;
			n_ = rhs.n_;
			rhs.first_ = nullptr;
			rhs.n_ = 0;
		}

		~Stack() {
			while (first_) {
				Node *oldfirst = first_;
				first_ = oldfirst->next_;
				delete oldfirst;
			}
		}

		bool IsEmpty() const {
			return first_ == nullptr;
		}

		size_t Size() const {
			return n_;
		}

		void Push(const Item &item) {
			Node *oldfirst = first_;
			first_ = new Node;
			first_->item_ = item;
			first_->next_ = oldfirst;
			++n_;
			assert(Check());
		}

		Item Pop() {
			CheckEmpty();
			Item item = first_->item_;
			Node *oldfirst = first_;
			first_ = oldfirst->next_;
			delete oldfirst;
			--n_;
			assert(Check());
			return item;
		}

		Item Peek() {
			CheckEmpty();
			return first_->item_;
		}

		class iterator {
		private:
			Node *pos_;
		public:
			iterator(Node *p) :pos_(p) {
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

		bool operator==(const Stack &that) const {
			if (Size() != that.Size()) return false;
			for (auto it1 = begin(), it2 = that.begin(); it1 != end() && it2 != that.end(); ++it1, ++it2) {
				if (*it1 != *it2) return false;
			}
			return true;
		}

		bool operator!=(const Stack &that) const {
			return !(*this == that);
		}

	private:
		bool Check() {
			if (n_ == 0) {
				if (first_ != nullptr) return false;
			}
			else if (n_ == 1) {
				if (first_ == nullptr) return false;
				if (first_->next_ != nullptr) return false;
			}
			else {
				if (first_ == nullptr) return false;
				if (first_->next_ == nullptr) return false;
			}

			size_t numberOfNodes = 0;
			for (Node *x = first_; (x != nullptr) && (numberOfNodes <= n_); x = x->next_) {
				++numberOfNodes;
			}
			if (numberOfNodes != n_) return false;
			return true;

		}

		void CheckEmpty() const {
			if (IsEmpty()) throw std::underflow_error("Queue underflow");
		}

	public:
		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			Stack<int> stack;

			for (size_t i = 0; i != 5; ++i) {
				stack.Push(i);
			}
			Stack<int> stack2(stack);
			assert(stack == stack2);
			Stack<int> stack3;
			while (!stack2.IsEmpty()) {
				stack3.Push(stack2.Pop());
			}
			assert(stack != stack3);
		}

	};

	template<typename Item>void swap(Stack<Item> &lhs, Stack<Item> &rhs) {
		using std::swap;
		swap(lhs.first_, rhs.first_);
		swap(lhs.n_, rhs.n_);
	}
}