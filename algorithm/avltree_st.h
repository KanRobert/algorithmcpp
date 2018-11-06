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
			for (const auto &key : rhs.KeysLevelOrder()) {
				Put(key, *rhs.Get(key));
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
		struct Node {
			Key key;
			Value val;
			int height;
			size_t size;
			Node *left;
			Node *right;

			Node(const Node &) = delete;
			Node &operator=(const Node &) = delete;
			~Node() {
				delete left;
				left = nullptr;
				delete right;
				right = nullptr;
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
			return x->size;
		}

		int Height(Node *x) const {
			if (!x) return -1;
			return x->height;
		}

		Node *Get(Node *x, const Key &key) const {
			if (!x) return nullptr;
			int cmp = Compare(key, x->key);
			if (cmp < 0) return Get(x->left, key);
			else if (cmp > 0) return Get(x->right, key);
			else return x;
		}

		Node *Put(Node *x, const Key &key, const Value &val) {
			if (!x) return new Node{ key, val, 0, 1 };
			int cmp = Compare(key, x->key);
			if (cmp < 0) {
				x->left = Put(x->left, key, val);
			}
			else if (cmp > 0) {
				x->right = Put(x->right, key, val);
			}
			else {
				x->val = val;
				return x;
			}
			x->size = 1 + Size(x->left) + Size(x->right);
			return Balance(x);
		}

		Node* Balance(Node *x) {
			if (BalanceFactor(x) < -1) {
				if (BalanceFactor(x->right) > 0) {
					x->right = RotateRight(x->right);
				}
				x = RotateLeft(x);
			}
			else if (BalanceFactor(x) > 1) {
				if (BalanceFactor(x->left) < 0) {
					x->left = RotateLeft(x->left);
				}
				x = RotateRight(x);
			}
			return x;
		}

		int BalanceFactor(Node *x) const {
			return Height(x->left) - Height(x->right);
		}

		Node *RotateRight(Node *x) {
			Node *y = x->left;
			x->left = y->right;
			y->right = x;
			y->size = x->size;
			x->size = 1 + Size(x->left) + Size(x->right);
			x->height = 1 + std::max(Height(x->left), Height(x->right));
			y->height = 1 + std::max(Height(y->left), Height(y->right));
			return y;
		}

		Node *RotateLeft(Node *x) {
			Node *y = x->right;
			x->right = y->left;
			y->left = x;
			y->size = x->size;
			x->size = 1 + Size(x->left) + Size(x->right);
			x->height = 1 + std::max(Height(x->left), Height(x->right));
			y->height = 1 + std::max(Height(x->left), Height(x->right));
			return y;
		}

		Node *Delete(Node *x, const Key &key) {
			int cmp = Compare(key,x->key);
			if (cmp < 0) {
				x->left = Delete(x->left, key);
			}
			else if (cmp > 0) {
				x->right = Delete(x->right, key);
			}
			else {
				if (x->left == nullptr) {
					Node *tmp = x->right;
					x->right = nullptr;
					delete x;
					return tmp;
				}
				else if (x->right == nullptr) {
					Node *tmp = x->left;
					x->left = nullptr;
					delete x;
					return tmp;
				}
				else {
					Node *y = x;
					x = Min(y->right);
					Node *tmp = new Node{ x->key, x->val, 0, 1 };
					tmp->right = DeleteMin(y->right);
					tmp->left = y->left;;
					y->left = nullptr;
					y->right = nullptr;
					delete y;
					x = tmp;
				}
			}
			x->size = 1 + Size(x->left) + Size(x->right);
			x->height = 1 + std::max(Height(x->left), Height(x->right));
			return  Balance(x);
		}

		Node *DeleteMin(Node *x) {
			if (x->left == nullptr) {
				Node *tmp = x->right;
				x->right = nullptr;
				delete x;
				return tmp;
			}
			x->left = DeleteMin(x->left);
			x->size = 1 + Size(x->left) + Size(x->right);
			x->height = 1 + std::max(Height(x->left), Height(x->right));
			return Balance(x);
		}

		Node *DeleteMax(Node *x) {
			if (x->right == nullptr) {
				Node *tmp = x->left;
				x->left = nullptr;
				delete x;
				return tmp;
			}
			x->right = DeleteMax(x->right);
			x->size = 1 + Size(x->left) + Size(x->right);
			x->height = 1 + std::max(Height(x->left), Height(x->right));
			return Balance(x);
		}

		Node *Min(Node *x) const {
			if (x->left == nullptr) return x;
			return Min(x->left);
		}

		Node *Max(Node *x) const {
			if (x->right == nullptr) return x;
			return Max(x->right);
		}

		Node *Floor(Node *x, const Key &key) const {
			if (!x) return nullptr;
			int cmp = Compare(key, x->key);
			if (cmp == 0) return x;
			if (cmp < 0) return Floor(x->left, key);
			Node *y = Floor(x->right, key);
			if (!y) return y;
			else return x;
		}

		Node *Ceiling(Node *x, const Key &key) const {
			if (!x) return nullptr;
			int cmp = Compare(key, x->key);
			if (cmp == 0) return x;
			if (cmp > 0) return Ceiling(x->right, key);
			Node *y = Ceiling(x->left, key);
			if (!y) return y;
			else return x;
		}

		Node *Select(Node *x, size_t k) const {
			if (!x) return nullptr;
			size_t t = Size(x->left);
			if (t > k) return Select(x->left, k);
			else if (t < k) return Select(x->right, k - t - 1);
			else return x;
		}

		void KeysInOrder(Node *x, Queue<Key> &queue) const {
			if (!x) return;
			KeysInOrder(x->left, queue);
			queue.Enqueue(x->key);
			KeysInOrder(x->right, queue);
		}

		void Keys(Node *x, Queue<Key> &queue, const Key &lo, const Key &hi) const {
			if (!x) return;
			int cmplo = Compare(lo, x->key);
			int cmphi = Compare(hi, x->key);
			if (cmplo < 0) Keys(x->left, queue, lo, hi);
			if (cmplo <= 0 && cmphi >= 0) queue.Enqueue(x->key);
			if (cmphi > 0) Keys(x->right, queue, lo, hi);
		}

		size_t Rank(const Key &key, Node *x) {
			if (!x) return 0;
			int cmp = Compare(key, x->key);
			if (cmp < 0) return Rank(key, x->key);
			else if (cmp > 0) return 1 + Size(x->left) + Rank(key, x->right);
			else return Size(x->left);
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
			return std::optional<Value>(x->val);
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
			return Min(root_)->key;
		}

		Key Max() const {
			if (IsEmpty()) throw std::underflow_error("calls Max() with empty symbol table");
			return Max(root_)->key;
		}

		std::optional<Key> Floor(const Key &key) const {
			if (IsEmpty()) throw std::underflow_error("calls Floor() with empty symbol table");
			Node *x = Floor(root_, key);
			if (!x) return std::optional<Key>();
			else return std::optional<Key>(x->key);
		}

		std::optional<Key> Ceiling(const Key &key) const {
			if (IsEmpty()) throw std::underflow_error("calls Ceiling() with empty symbol table");
			Node *x = Ceiling(root_, key);
			if (!x) std::optional<Key>();
			else return std::optional<Key>(x->key);
		}

		Key Select(size_t k) const {
			if (k >= Size()) throw std::invalid_argument("k is not in range 0-" + std::to_string(Size() - 1));
			Node *x = Select(root_, k);
			return x->key;
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
					queue.Enqueue(x->key);
					if (x->left != nullptr) queue2.Enqueue(x->left);
					if (x->right != nullptr) queue2.Enqueue(x->right);
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
				std::string key = vec[i];
				st.Put(key, i);
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