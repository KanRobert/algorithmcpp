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
			for (const auto &key_ : rhs.Keys()) {
				Put(key_, *rhs.Get(key_));
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

		class Node {
		public:
			Key key_;
			Value val_;
			Node *left_ = nullptr;
			Node *right_ = nullptr;
			bool color_;
			size_t size_;
		public:
			Node(const Key &key,const Value &val,bool color,size_t size):key_(key),val_(val),color_(color),size_(size){}
			Node(const Node &) = delete;
			Node &operator=(const Node &) = delete;
			~Node() {
				delete left_;
				left_ = nullptr;
				delete right_;
				right_ = nullptr;
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
			return x->color_ == kRed;
		}

		size_t Size(Node *x) const{
			if (!x) return 0;
			return x->size_;
		}

		Node *Get(Node *x, const Key &key_) const {
			while (x) {
				if (key_ < x->key_) x = x->left_;
				else if (key_ > x->key_) x = x->right_;
				else return x;
			}
			return nullptr;
		}

		Node *Put(Node *h, const Key &key, const Value &val) {
			if (!h) return new Node(key, val, kRed, 1);
			if (key < h->key_) h->left_ = Put(h->left_, key, val);
			else if (key > h->key_) h->right_ = Put(h->right_, key, val);
			else h->val_ = val;

			//better than if (IsRed(h->right_)) h = RotateLeft(h);
			if (IsRed(h->right_) && !IsRed(h->left_)) h = RotateLeft(h);
			if (IsRed(h->left_) && IsRed(h->left_->left_)) h = RotateRight(h);
			if (IsRed(h->left_) && IsRed(h->right_)) FlipColors(h);
			h->size_ = Size(h->left_) + Size(h->right_) + 1;
			return h;
		}

		Node *DeleteMin(Node *h) {
			if (!h->left_) {
				delete h;
				return nullptr;
			} 

			if (!IsRed(h->left_) && !IsRed(h->left_->left_)) {
				h = MoveRedLeft(h);
			}

			h->left_ = DeleteMin(h->left_);
			return Balance(h);
		}

		Node *DeleteMax(Node *h) {
			if (IsRed(h->left_)) {
				h = RotateRight(h);
			}

			if (!h->right_) {
				delete h;
				return nullptr;
			}

			if (!IsRed(h->right_) && !IsRed(h->right_->left_)) {
				h = MoveRedRight(h);
			}

			h->right_ = DeleteMax(h->right_);

			return Balance(h);
		}

		Node *Delete(Node *h, const Key &key) {
			if (key < h->key_) {
				if (!IsRed(h->left_) && !IsRed(h->left_->left_)) {
					h = MoveRedLeft(h);
				}
				h->left_ = Delete(h->left_, key);
			}
			else {
				if (IsRed(h->left_)) {
					h = RotateRight(h);
				}
				if (key == h->key_ && !h->right_) {
					delete h;
					return nullptr;
				}
				if (!IsRed(h->right_) && !IsRed(h->right_->left_)) {
					h = MoveRedRight(h);
				}
				if (key == h->key_) {
					Node *x = Min(h->right_);
					h->key_ = x->key_;
					h->val_ = x->val_;
					h->right_ = DeleteMin(h->right_);
				}
				else {
					h->right_ = Delete(h->right_, key);
				}
			}
			return Balance(h);
		}

		Node *RotateRight(Node *h) {
			Node *x = h->left_;
			h->left_ = x->right_;
			x->right_ = h;
			x->color_ = h->color_;
			h->color_ = kRed;
			x->size_ = h->size_;
			h->size_ = Size(h->left_) + Size(h->right_) + 1;
			return x;
		}

		Node *RotateLeft(Node *h) {
			Node *x = h->right_;
			h->right_ = x->left_;
			x->left_ = h;
			x->color_ = h->color_;
			h->color_ = kRed;
			x->size_ = h->size_;
			h->size_ = Size(h->left_) + Size(h->right_) + 1;
			return x;
		}

		void FlipColors(Node *h) {
			h->color_ = !h->color_;
			h->left_->color_ = !h->left_->color_;
			h->right_->color_ = !h->right_->color_;
		}

		Node *MoveRedLeft(Node *h) {
			FlipColors(h);
			if (IsRed(h->right_->left_)) {
				h->right_ = RotateRight(h->right_);
				h = RotateLeft(h);
				FlipColors(h);
			}
			return h;
		}

		Node *MoveRedRight(Node *h) {
			FlipColors(h);
			if (IsRed(h->left_->left_)) {
				h = RotateRight(h);
				FlipColors(h);
			}
			return h;
		}

		Node *Balance(Node *h) {
			if (IsRed(h->right_)) h = RotateLeft(h);
			if (IsRed(h->left_) && IsRed(h->left_->left_)) h = RotateRight(h);
			if (IsRed(h->left_) && IsRed(h->right_)) FlipColors(h);

			h->size_ = Size(h->left_) + Size(h->right_) + 1;
			return h;
		}

		int Height(Node *x) const {
			if (!x) return -1;
			return 1 + std::Max(Height(h->left_), Height(h->right_));
		}

		Node *Min(Node *x) const {
			if (!x->left_) return x;
			else return Min(x->left_);
		}

		Node *Max(Node *x) const {
			if (!x->right_) return x;
			else return Max(x->right_);
		}

		Node *Floor(Node *x, const Key &key_) const {
			if (!x) return nullptr;
			if (key_ == x->key_) return x;
			if (key_ < x->key_) return Floor(x->left_, key_);
			Node *t= Floor(x->right_, key_);
			if (!t) return t;
			else return x;
		}

		Node *Ceiling(Node *x, const Key &key_) const{
			if (!x) return nullptr;
			if (key_ == x->key_) return x;
			if (key_ > x->key_) return Ceiling(x->right_, key_);
			Node *t = Ceiling(x->left_, key_);
			if (!t) return t;
			else return x;
		}

		Node *Select(Node *x, size_t k) const {
			size_t t = Size(x->left_);
			if (t > k) return Select(x->left_, k);
			else if (t < k) return Select(x->right_, k - t - 1);
			else return x;
		}

		size_t Rank(const Key &key_, Node *x) const {
			if (!x) return 0;
			if (key_ < x->key_) return Rank(key_, x->left_);
			else if (key_ > x->key_) return 1 + Size(x->left_) + Rank(key_, x->right_);
			else return Size(x->left_);
		}

		void Keys(Node *x, Queue<Key> &queue, const Key &lo, const Key &hi) const {
			if (!x) return;
			int cmplo = Compare(lo, x->key_);
			int cmphi = Compare(hi, x->key_);
			if (cmplo<0) Keys(x->left_, queue, lo, hi);
			if (cmplo <= 0 && cmphi >= 0) queue.Enqueue(x->key_);
			if (cmphi >= 0) Keys(x->right_, queue, lo, hi);
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
			else return std::optional<Value>(p->val_);
		}

		bool Contains(const Key &key) const {
			return Get(key).has_value();
		}

		void Put(const Key &key, const Value &val) {
			root_ = Put(root_, key, val);
			root_->color_ = kBlack;
		}

		void DeleteMin() {
			if(IsEmpty()) throw std::underflow_error("BST underflow");

			if (!IsRed(root_->left_) && !IsRed(root_->right_)) {
				root_->color_ = kRed;
			}

			root_ = DeleteMin(root_);
			if (!IsEmpty()) root_->color_ = kBlack;
		}

		void DeleteMax() {
			if (IsEmpty()) throw std::underflow_error("BST underflow");

			if (!IsRed(root_->left_) && !IsRed(root_->right_)) {
				root_->color_ = kRed;
			}

			root_ = DeleteMax(root_);
			if (!IsEmpty()) root_->color_ = kBlack;
		}

		void Delete(const Key &key_) {
			if (!Contains(key_)) return;

			if (!IsRed(root_->left_) && !IsRed(root_->right_)) {
				root_->color_ = kRed;
			}

			root_ = Delete(root_, key_);
			if (!IsEmpty()) root_->color_ = kBlack;
		}

		int Height() const {
			return Height(root_);
		}

		Key Min() const {
			if(IsEmpty()) throw std::underflow_error("calls Min() with empty symbol table");
			return Min(root_)->key_;
		}

		Key Max() const {
			if(IsEmpty()) throw std::underflow_error("calls Max() with empty symbol table");
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
			Node x = Ceiling(root_, key);
			if (!x) return std::optional<Key>();
			else return std::optional<Key>(x->key_);
		}

		Key Select(size_t k) const {
			if (k >= Size()) throw std::invalid_argument("argument to Select() is invalid");
			Node *x = Select(root_, k);
			return x->key_;
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
				std::string key_ = vec[i];
				st.Put(key_, i);
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