#pragma once
#include<stdexcept>
#include<cassert>
#include<utility>

namespace algorithmcpp {
	template<typename> class Queue;
	template<typename Item> void swap(Queue<Item> &, Queue<Item> &);

	template<typename Item> class Queue {
		friend void swap<Item>(Queue<Item> &, Queue<Item> &);
	private:
		struct Node {
			Item item;
			Node *next;
		};

		Node* first_ = nullptr;
		Node* last_ = nullptr;
		size_t n_ = 0;

	public:
		Queue() = default;
		Queue(const Queue & rhs) {
			for (const Node *p = rhs.first_; p != nullptr; p = p->next) {
				Enqueue(p->item);
			}
		}
		Queue &operator=(Queue rhs) {
			swap(*this, rhs);
			return *this;
		}
		Queue(Queue &&rhs) noexcept {
			first_ = rhs.first_;
			last_ = rhs.last_;
			n_ = rhs.n_;
			rhs.first_ = nullptr;
			rhs.last_ = nullptr;
			rhs.n_ = 0;
		}

		~Queue() {
			while (first_) {
				Node *oldfirst = first_;
				first_ = oldfirst->next;
				delete oldfirst;
			}
		}

		bool IsEmpty() const {
			return first_ == nullptr;
		}

		size_t Size() const {
			return n_;
		}

		Item Peek() const {
			Check();
			return first_.item;
		}

		void Enqueue(const Item &item) {
			Node* oldlast = last_;
			last_ = new Node{item,nullptr};
			if (IsEmpty()) first_ = last_;
			else oldlast->next = last_;
			++n_;
		}

		Item Dequeue() {
			Check();
			Item item = first_->item;
			Node *oldfirst = first_;
			first_ = oldfirst->next;
			delete oldfirst;
			--n_;
			if (IsEmpty()) last_ = nullptr;
			return item;
		}

		class iterator {
		private:
			Node *pos_;
		public:
			iterator(Node *p) :pos_(p) {
			}

			iterator &operator++() {
				pos_ = pos_->next;
				return *this;
			}

			bool operator!=(const iterator &other) const {
				return pos_ != other.pos_;
			}

			Item &operator*() const {
				return pos_->item;
			}
		};

		class const_iterator {
		private:
			Node *pos_;
		public:
			const_iterator(Node *p) :pos_(p) {
			}

			const_iterator &operator++() {
				pos_ = pos_->next;
				return *this;
			}

			bool operator!=(const const_iterator &other) const {
				return pos_ != other.pos_;
			}

			const Item &operator*() const {
				return pos_->item;
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

		bool operator==(const Queue &that) const {
			if (Size() != that.Size()) return false;
			for (auto it1 = begin(), it2 = that.begin(); it1 != end() && it2 != that.end(); ++it1, ++it2) {
				if (*it1 != *it2) return false;
			}
			return true;
		}

		bool operator!=(const Queue &that) const {
			return !(*this == that);
		}


	private:
		void Check() const {
			if (IsEmpty()) throw std::underflow_error("Queue underflow");
		}

	public:
		static void MainTest(int argc=0, char *argv[]=nullptr) {
			Queue<int> queue;

			for (size_t i = 0; i != 5; ++i) {
				queue.Enqueue(i);
			}
			Queue<int> queue2(queue);
			assert(queue == queue2);
			Queue<int> queue3;
			while (!queue2.IsEmpty()) {
				queue3.Enqueue(queue2.Dequeue());
			}
			assert(queue == queue3);

		}
	};

	template<typename Item>void swap(Queue<Item> &lhs, Queue<Item> &rhs) {
		using std::swap;
		swap(lhs.first_, rhs.first_);
		swap(lhs.n_, rhs.n_);
	}
}