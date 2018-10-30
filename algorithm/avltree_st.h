#pragma once
#include"queue.h"
#include<cassert>
#include<stdexcept>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<optional>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

namespace algorithmcpp {
	template<typename,typename> class AVLTreeST;
	template<typename Key,typename Value> void swap(AVLTreeST<Key,Value> &, AVLTreeST<Key, Value> &);

	template<typename Key, typename Value> class AVLTreeST {
		friend void swap<Key,Value>(AVLTreeST<Key, Value> &, AVLTreeST<Key, Value> &);
	public:
		AVLTreeST() = default;
		AVLTreeST(const AVLTreeST &rhs) {
			for (const auto &key_ : rhs.KeysLevelOrder()) {
				Put(key_, *rhs.Get(key_));
			}
		}
		AVLTreeST &operator=(AVLTreeST rhs) {
			swap(*this, rhs);
			return *this;
		}
		AVLTreeST(AVLTreeST &&rhs) noexcept{
			root_ = rhs.root_;
			rhs.root_ = nullptr;
		}

		~AVLTreeST() {
			delete root_;
			root_ = nullptr;
		}

	private:
		class Node {
		public:
			Key key_;
			Value val_;
			int height_;
			size_t size_;
			Node *left_ = nullptr;
			Node *right_ = nullptr;
		public:
			Node(const Key &key, const Value &val, int height, size_t size) :key_(key), val_(val), height_(height), size_(size) {}
			Node(const Node &) = delete;
			Node &operator=(const Node &) = delete;
			~Node() {
				delete left_;
				left_ = nullptr;
				delete right_;
				right_ = nullptr;
			}
		};

		Node *root_ = nullptr;

		int Compare(const Key &lhs, const Key &rhs) const {
			if (lhs < rhs) return -1;
			else if (lhs == rhs) return 0;
			else return +1;
		}

		size_t Size(Node *x) const {
			if (!x) return 0;
			return x->size_;
		}

		int Height(Node *x) const {
			if (!x) return -1;
			return x->height_;
		}

		Node *Get(Node *x, const Key &key) const {
			if (!x) return nullptr;
			int cmp = Compare(key, x->key_);
			if (cmp < 0) return Get(x->left_, key);
			else if (cmp > 0) return Get(x->right_, key);
			else return x;
		}

		Node *Put(Node *x, const Key &key, const Value &val) {
			if (!x) return new Node(key, val, 0, 1);
			int cmp = Compare(key, x->key_);
			if (cmp < 0) {
				x->left_ = Put(x->left_, key, val);
			}
			else if (cmp > 0) {
				x->right_ = Put(x->right_, key, val);
			}
			else {
				x->val_ = val;
				return x;
			}
			x->size_ = 1 + Size(x->left_) + Size(x->right_);
			return Balance(x);
		}

		Node* Balance(Node *x) {
			if (BalanceFactor(x) < -1) {
				if (BalanceFactor(x->right_) > 0) {
					x->right_ = RotateRight(x->right_);
				}
				x = RotateLeft(x);
			}
			else if (BalanceFactor(x) > 1) {
				if (BalanceFactor(x->left_) < 0) {
					x->left_ = RotateLeft(x->left_);
				}
				x = RotateRight(x);
			}
			return x;
		}

		int BalanceFactor(Node *x) const {
			return Height(x->left_) - Height(x->right_);
		}

		Node *RotateRight(Node *x) {
			Node *y = x->left_;
			x->left_ = y->right_;
			y->right_ = x;
			y->size_ = x->size_;
			x->size_ = 1 + Size(x->left_) + Size(x->right_);
			x->height_ = 1 + std::max(Height(x->left_), Height(x->right_));
			y->height_ = 1 + std::max(Height(y->left_), Height(y->right_));
			return y;
		}

		Node *RotateLeft(Node *x) {
			Node *y = x->right_;
			x->right_ = y->left_;
			y->left_ = x;
			y->size_ = x->size_;
			x->size_ = 1 + Size(x->left_) + Size(x->right_);
			x->height_ = 1 + std::max(Height(x->left_), Height(x->right_));
			y->height_ = 1 + std::max(Height(x->left_), Height(x->right_));
			return y;
		}

		Node *Delete(Node *x, const Key &key) {
			int cmp = Compare(key,x->key_);
			if (cmp < 0) {
				x->left_ = Delete(x->left_, key);
			}
			else if (cmp > 0) {
				x->right_ = Delete(x->right_, key);
			}
			else {
				if (x->left_ == nullptr) {
					Node *tmp = x->right_;
					x->right_ = nullptr;
					delete x;
					return tmp;
				}
				else if (x->right_ == nullptr) {
					Node *tmp = x->left_;
					x->left_ = nullptr;
					delete x;
					return tmp;
				}
				else {
					Node *y = x;
					x = Min(y->right_);
					Node *tmp = new Node(x->key_, x->val_, 0, 1);
					tmp->right_ = DeleteMin(y->right_);
					tmp->left_ = y->left_;;
					y->left_ = nullptr;
					y->right_ = nullptr;
					delete y;
					x = tmp;
				}
			}
			x->size_ = 1 + Size(x->left_) + Size(x->right_);
			x->height_ = 1 + std::max(Height(x->left_), Height(x->right_));
			return  Balance(x);
		}

		Node *DeleteMin(Node *x) {
			if (x->left_ == nullptr) {
				Node *tmp = x->right_;
				x->right_ = nullptr;
				delete x;
				return tmp;
			}
			x->left_ = DeleteMin(x->left_);
			x->size_ = 1 + Size(x->left_) + Size(x->right_);
			x->height_ = 1 + std::max(Height(x->left_), Height(x->right_));
			return Balance(x);
		}

		Node *DeleteMax(Node *x) {
			if (x->right_ == nullptr) {
				Node *tmp = x->left_;
				x->left_ = nullptr;
				delete x;
				return tmp;
			}
			x->right_ = DeleteMax(x->right_);
			x->size_ = 1 + Size(x->left_) + Size(x->right_);
			x->height_ = 1 + std::max(Height(x->left_), Height(x->right_));
			return Balance(x);
		}

		Node *Min(Node *x) const {
			if (x->left_ == nullptr) return x;
			return Min(x->left_);
		}

		Node *Max(Node *x) const {
			if (x->right_ == nullptr) return x;
			return Max(x->right_);
		}

		Node *Floor(Node *x, const Key &key) const {
			if (!x) return nullptr;
			int cmp = Compare(key, x->key_);
			if (cmp == 0) return x;
			if (cmp < 0) return Floor(x->left_, key);
			Node *y = Floor(x->right_, key);
			if (!y) return y;
			else return x;
		}

		Node *Ceiling(Node *x, const Key &key) const {
			if (!x) return nullptr;
			int cmp = Compare(key_, x->key_);
			if (cmp == 0) return x;
			if (cmp > 0) return Ceiling(x->right_, key);
			Node *y = Ceiling(x->left_, key);
			if (!y) return y;
			else return x;
		}

		Node *Select(Node *x, size_t k) const {
			if (!x) return nullptr;
			size_t t = Size(x->left_);
			if (t > k) return Select(x->left_, k);
			else if (t < k) return Select(x->right_, k - t - 1);
			else return x;
		}

		void KeysInOrder(Node *x, Queue<Key> &queue) const {
			if (!x) return;
			KeysInOrder(x->left_, queue);
			queue.Enqueue(x->key_);
			KeysInOrder(x->right_, queue);
		}

		void Keys(Node *x, Queue<Key> &queue, const Key &lo, const Key &hi) const {
			if (!x) return;
			int cmplo = Compare(lo, x->key_);
			int cmphi = Compare(hi, x->key_);
			if (cmplo < 0) Keys(x->left_, queue, lo, hi);
			if (cmplo <= 0 && cmphi >= 0) queue.Enqueue(x->key_);
			if (cmphi > 0) Keys(x->right_, queue, lo, hi);
		}

		size_t Rank(const Key &key, Node *x) {
			if (!x) return 0;
			int cmp = Compare(key, x->key_);
			if (cmp < 0) return Rank(key, x->key_);
			else if (cmp > 0) return 1 + Size(x->left_) + Rank(key, x->right_);
			else return Size(x->left_);
		}

	public:
		bool IsEmpty() const {
			return root_ == nullptr;
		}

		size_t Size() const {
			return Size(root_);
		}

		int Height() const {
			return Height(root_);
		}

		size_t Rank(const Key &key) const {
			return Rank(key, root_);
		}

		std::optional<Value> Get(const Key &key) const {
			Node *x = Get(root_, key);
			if (!x) return std::optional<Value>();
			return std::optional<Value>(x->val_);
		}

		bool Contains(const Key &key) const {
			return Get(key).has_value();
		}

		void Put(const Key &key, const Value &val) {
			root_ = Put(root_, key, val);
		}

		void Delete(const Key &key) {
			if (!Contains(key)) return;
			root_ = Delete(root_, key);
		}

		void DeleteMin() {
			if(IsEmpty()) std::underflow_error("calls DeleteMin() with empty symbol table");
			root_ = DeleteMin(root_);
		}

		void DeleteMax() {
			if (IsEmpty()) std::underflow_error("calls DeleteMax() with empty symbol table");
			root_ = DeleteMax(root_);
		}

		Key Min() const {
			if (IsEmpty()) throw std::underflow_error("calls Min() with empty symbol table");
			return Min(root_)->key_;
		}

		Key Max() const {
			if (IsEmpty()) throw std::underflow_error("calls Max() with empty symbol table");
			return Max(root_)->key_;
		}

		std::optional<Key> Floor(const Key &key) const {
			if (IsEmpty()) throw std::underflow_error("calls Floor() with empty symbol table");
			Node *x = Floor(root_, key);
			if (!x) return std::optional<Key>();
			else return std::optional<Key>(x->key_);
		}

		std::optional<Key> Ceiling(const Key &key) const {
			if (IsEmpty()) throw std::underflow_error("calls Ceiling() with empty symbol table");
			Node *x = Ceiling(root_, key);
			if (!x) std::optional<Key>();
			else return std::optional<Key>(x->key_);
		}

		Key Select(size_t k) const {
			if (k >= Size()) throw std::invalid_argument("k is not in range 0-" + std::to_string(Size() - 1));
			Node *x = Select(root_, k);
			return x->key_;
		}

		Queue<Key> KeysInOrder() const {
			Queue<Key> queue;
			KeysInOrder(root_, queue);
			return queue;
		}

		Queue<Key> KeysLevelOrder() const {
			Queue<Key> queue;
			if (!IsEmpty()) {
				Queue<Node *> queue2;
				queue2.Enqueue(root_);
				while (!queue2.IsEmpty()) {
					Node *x = queue2.Dequeue();
					queue.Enqueue(x->key_);
					if (x->left_ != nullptr) queue2.Enqueue(x->left_);
					if (x->right_ != nullptr) queue2.Enqueue(x->right_);
				}
			}
			return queue;
		}

		Queue<Key> Keys(const Key &lo, const Key &hi) const {
			Queue<Key> queue;
			Keys(root_, queue, lo, hi);
			return queue;
		}

		size_t Size(const Key &lo, const Key &hi) const {
			if (Compare(lo, hi) > 0) return 0;
			if (Contains(hi)) return Rank(hi) - Rank(lo) + 1;
			else return Rank(hi) - Rank(lo);
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			AVLTreeST<std::string, int> st;
			std::vector<std::string> vec{ "c","e","a","f","b","d","h","g" };
			for (size_t i = 0; i != vec.size(); ++i) {
				std::string key_ = vec[i];
				st.Put(key_, i);
			}

			assert(st.Contains("e"));

			for (const auto &s : st.KeysInOrder())
				std::cout << s << " " << st.Get(s).value() << std::endl;
			std::cout << std::endl;

			st.DeleteMax();
			st.DeleteMin();
			st.Delete("e");
			assert(!st.Contains("e"));

			for (const auto &s : st.KeysLevelOrder())
				std::cout << s << " " << st.Get(s).value() << std::endl;
			std::cout << std::endl;

			AVLTreeST<std::string, int> st2(st);
			st = st2;
		}

	};

	template<typename Key, typename Value> void swap(AVLTreeST<Key, Value> &lhs, AVLTreeST<Key, Value> &rhs) {
		using std::swap;
		swap(lhs.root_, rhs.root_);
	}
}

#pragma pop_macro("max")
#pragma pop_macro("min")