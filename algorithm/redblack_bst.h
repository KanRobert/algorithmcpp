#pragma once
#include"queue.h"
#include<cassert>
#include<stdexcept>
#include<algorithm>
#include<iostream>
#include<optional>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

namespace algorithmcpp {
	template<typename, typename> class RedBlackBST;
	template<typename Key, typename Value> void swap(RedBlackBST<Key, Value> &, RedBlackBST<Key, Value> &);

	template<typename Key, typename Value> class RedBlackBST {
		friend void swap<Key, Value>(RedBlackBST<Key, Value> &, RedBlackBST<Key, Value> &);
	public:
		RedBlackBST() = default;
		RedBlackBST(const RedBlackBST &rhs) {
			for (const auto &key : rhs.Keys()) {
				Put(key, *rhs.Get(key));
			}
		}
		RedBlackBST &operator=(RedBlackBST rhs) {
			swap(*this, rhs);
			return *this;
		}
		RedBlackBST(RedBlackBST &&rhs) noexcept {
			root_ = rhs.root_;
			rhs.root_ = nullptr;
		}

		~RedBlackBST() {
			delete root_;
			root_ = nullptr;
		}

	private:
		static const bool kRed = true;
		static const bool kBlack = false;

		struct Node {
			Key key;
			Value val;
			bool color;
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

		Node * root_ = nullptr;

		int Compare(const Key &lhs, const Key &rhs) const {
			if (lhs == rhs) return 0;
			if (lhs < rhs) return -1;
			else return 1;
		}

		bool IsRed(Node *x) const{
			if (!x) return false;
			return x->color == kRed;
		}

		size_t Size(Node *x) const{
			if (!x) return 0;
			return x->size;
		}

		Node *Get(Node *x, const Key &key) const {
			while (x) {
				if (key < x->key) x = x->left;
				else if (key > x->key) x = x->right;
				else return x;
			}
			return nullptr;
		}

		Node *Put(Node *h, const Key &key, const Value &val) {
			if (!h) return new Node{ key, val, kRed, 1 };
			if (key < h->key) h->left = Put(h->left, key, val);
			else if (key > h->key) h->right = Put(h->right, key, val);
			else h->val = val;

			//better than if (IsRed(h->right)) h = RotateLeft(h);
			if (IsRed(h->right) && !IsRed(h->left)) h = RotateLeft(h);
			if (IsRed(h->left) && IsRed(h->left->left)) h = RotateRight(h);
			if (IsRed(h->left) && IsRed(h->right)) FlipColors(h);
			h->size = Size(h->left) + Size(h->right) + 1;
			return h;
		}

		Node *DeleteMin(Node *h) {
			if (!h->left) {
				delete h;
				return nullptr;
			} 

			if (!IsRed(h->left) && !IsRed(h->left->left)) {
				h = MoveRedLeft(h);
			}

			h->left = DeleteMin(h->left);
			return Balance(h);
		}

		Node *DeleteMax(Node *h) {
			if (IsRed(h->left)) {
				h = RotateRight(h);
			}

			if (!h->right) {
				delete h;
				return nullptr;
			}

			if (!IsRed(h->right) && !IsRed(h->right->left)) {
				h = MoveRedRight(h);
			}

			h->right = DeleteMax(h->right);

			return Balance(h);
		}

		Node *Delete(Node *h, const Key &key) {
			if (key < h->key) {
				if (!IsRed(h->left) && !IsRed(h->left->left)) {
					h = MoveRedLeft(h);
				}
				h->left = Delete(h->left, key);
			}
			else {
				if (IsRed(h->left)) {
					h = RotateRight(h);
				}
				if (key == h->key && !h->right) {
					delete h;
					return nullptr;
				}
				if (!IsRed(h->right) && !IsRed(h->right->left)) {
					h = MoveRedRight(h);
				}
				if (key == h->key) {
					Node *x = Min(h->right);
					h->key = x->key;
					h->val = x->val;
					h->right = DeleteMin(h->right);
				}
				else {
					h->right = Delete(h->right, key);
				}
			}
			return Balance(h);
		}

		Node *RotateRight(Node *h) {
			Node *x = h->left;
			h->left = x->right;
			x->right = h;
			x->color = h->color;
			h->color = kRed;
			x->size = h->size;
			h->size = Size(h->left) + Size(h->right) + 1;
			return x;
		}

		Node *RotateLeft(Node *h) {
			Node *x = h->right;
			h->right = x->left;
			x->left = h;
			x->color = h->color;
			h->color = kRed;
			x->size = h->size;
			h->size = Size(h->left) + Size(h->right) + 1;
			return x;
		}

		void FlipColors(Node *h) {
			h->color = !h->color;
			h->left->color = !h->left->color;
			h->right->color = !h->right->color;
		}

		Node *MoveRedLeft(Node *h) {
			FlipColors(h);
			if (IsRed(h->right->left)) {
				h->right = RotateRight(h->right);
				h = RotateLeft(h);
				FlipColors(h);
			}
			return h;
		}

		Node *MoveRedRight(Node *h) {
			FlipColors(h);
			if (IsRed(h->left->left)) {
				h = RotateRight(h);
				FlipColors(h);
			}
			return h;
		}

		Node *Balance(Node *h) {
			if (IsRed(h->right)) h = RotateLeft(h);
			if (IsRed(h->left) && IsRed(h->left->left)) h = RotateRight(h);
			if (IsRed(h->left) && IsRed(h->right)) FlipColors(h);

			h->size = Size(h->left) + Size(h->right) + 1;
			return h;
		}

		int Height(Node *x) const {
			if (!x) return -1;
			return 1 + std::Max(Height(h->left), Height(h->right));
		}

		Node *Min(Node *x) const {
			if (!x->left) return x;
			else return Min(x->left);
		}

		Node *Max(Node *x) const {
			if (!x->right) return x;
			else return Max(x->right);
		}

		Node *Floor(Node *x, const Key &key) const {
			if (!x) return nullptr;
			if (key == x->key) return x;
			if (key < x->key) return Floor(x->left, key);
			Node *t= Floor(x->right, key);
			if (!t) return t;
			else return x;
		}

		Node *Ceiling(Node *x, const Key &key) const{
			if (!x) return nullptr;
			if (key == x->key) return x;
			if (key > x->key) return Ceiling(x->right, key);
			Node *t = Ceiling(x->left, key);
			if (!t) return t;
			else return x;
		}

		Node *Select(Node *x, size_t k) const {
			size_t t = Size(x->left);
			if (t > k) return Select(x->left, k);
			else if (t < k) return Select(x->right, k - t - 1);
			else return x;
		}

		size_t Rank(const Key &key, Node *x) const {
			if (!x) return 0;
			if (key < x->key) return Rank(key, x->left);
			else if (key > x->key) return 1 + Size(x->left) + Rank(key, x->right);
			else return Size(x->left);
		}

		void Keys(Node *x, Queue<Key> &queue, const Key &lo, const Key &hi) const {
			if (!x) return;
			int cmplo = Compare(lo, x->key);
			int cmphi = Compare(hi, x->key);
			if (cmplo<0) Keys(x->left, queue, lo, hi);
			if (cmplo <= 0 && cmphi >= 0) queue.Enqueue(x->key);
			if (cmphi >= 0) Keys(x->right, queue, lo, hi);
		}

	public:
		size_t Size() const {
			return Size(root_);
		}

		bool IsEmpty() const {
			return root_ == nullptr;
		}

		std::optional<Value> Get(const Key &key) const {
			Node *p = Get(root_, key);
			if (!p) return std::optional<Value>();
			else return std::optional<Value>(p->val);
		}

		bool Contains(const Key &key) const {
			return Get(key).has_value();
		}

		void Put(const Key &key, const Value &val) {
			root_ = Put(root_, key, val);
			root_->color = kBlack;
		}

		void DeleteMin() {
			if(IsEmpty()) throw std::underflow_error("BST underflow");

			if (!IsRed(root_->left) && !IsRed(root_->right)) {
				root_->color = kRed;
			}

			root_ = DeleteMin(root_);
			if (!IsEmpty()) root_->color = kBlack;
		}

		void DeleteMax() {
			if (IsEmpty()) throw std::underflow_error("BST underflow");

			if (!IsRed(root_->left) && !IsRed(root_->right)) {
				root_->color = kRed;
			}

			root_ = DeleteMax(root_);
			if (!IsEmpty()) root_->color = kBlack;
		}

		void Delete(const Key &key) {
			if (!Contains(key)) return;

			if (!IsRed(root_->left) && !IsRed(root_->right)) {
				root_->color = kRed;
			}

			root_ = Delete(root_, key);
			if (!IsEmpty()) root_->color = kBlack;
		}

		int Height() const {
			return Height(root_);
		}

		Key Min() const {
			if(IsEmpty()) throw std::underflow_error("calls Min() with empty symbol table");
			return Min(root_)->key;
		}

		Key Max() const {
			if(IsEmpty()) throw std::underflow_error("calls Max() with empty symbol table");
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
			Node x = Ceiling(root_, key);
			if (!x) return std::optional<Key>();
			else return std::optional<Key>(x->key);
		}

		Key Select(size_t k) const {
			if (k >= Size()) throw std::invalid_argument("argument to Select() is invalid");
			Node *x = Select(root_, k);
			return x->key;
		}

		size_t Rank(const Key &key) const {
			return Rank(key, root_);
		}

		size_t Size(const Key &lo, const Key &hi) const {
			if (lo > hi) return 0;
			if (Contains(hi)) return Rank(hi) - Rank(lo) + 1;
			else return Rank(hi) - Rank(lo);
		}

		Queue<Key> Keys() const {
			if (IsEmpty()) return Queue<Key>();
			return Keys(Min(), Max());
		}

		Queue<Key> Keys(const Key &lo, const Key &hi) const {
			if (!(lo <= hi)) throw std::invalid_argument("invalid input range");
			Queue<Key> queue;
			Keys(root_, queue, lo, hi);
			return queue;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			RedBlackBST<std::string, int> st;
			std::vector<std::string> vec{ "c","e","a","f","b","d","h","g" };
			for (size_t i = 0; i != vec.size(); ++i) {
				std::string key = vec[i];
				st.Put(key, i);
			}

			assert(st.Contains("e"));

			for (const auto &s : st.Keys())
				std::cout << s << " " << st.Get(s).value() << std::endl;
			std::cout << std::endl;

			st.DeleteMax();
			st.DeleteMin();
			st.Delete("e");
			assert(!st.Contains("e"));

			for (const auto &s : st.Keys())
				std::cout << s << " " << st.Get(s).value() << std::endl;
			std::cout << std::endl;

			RedBlackBST<std::string, int> st2;
			st = st2;
		}
	};

	template<typename Key, typename Value> void swap(RedBlackBST<Key, Value> &lhs, RedBlackBST<Key, Value> &rhs) {
		using std::swap;
		swap(lhs.root_, rhs.root_);
	}
}

#pragma pop_macro("max")
#pragma pop_macro("min")