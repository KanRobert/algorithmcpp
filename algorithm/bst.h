#pragma once
#include"queue.h"
#include<cassert>
#include<stdexcept>
#include<string>
#include<algorithm>
#include<iostream>
#include<vector>
#include<optional>

namespace algorithmcpp {
	template<typename, typename> class BST;
	template<typename Key, typename Value> void swap(BST<Key, Value> &, BST<Key, Value> &);

	template<typename Key, typename Value> class BST {
		friend void swap<Key, Value>(BST<Key, Value> &, BST<Key, Value> &);
	public:
		BST() = default;
		BST(const BST &rhs) {
			for (const auto &key_ : rhs.Keys()) {
				Put(key_, *rhs.Get(key_));
			}
		}
		BST &operator=(BST rhs) {
			swap(*this, rhs);
			return *this;
		}
		BST(BST &&rhs) noexcept {
			root_ = rhs.root_;
			rhs.root_ = nullptr;
		}

		~BST() {
			delete root_;
			root_ = nullptr;
		}

	private:
		class Node {
		public:
			Key key_;
			Value val_;
			Node *left_ = nullptr;
			Node *right_ = nullptr;
			size_t size_;
		public:
			Node(const Key &_key, const Value &_val, size_t _size) :key_(_key), val_(_val), size_(_size) {}
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
			if (lhs == rhs) return 0;
			if (lhs < rhs) return -1;
			else return 1;
		}


		size_t Size(Node *x) const {
			if (!x) return 0;
			else return x->size_;
		}

		Node *Get(Node *x, const Key &key_) const {
			if (!x) return nullptr;
			if (key_ < (x->key_)) return Get(x->left_, key_);
			else if(key_>(x->key_)) return Get(x->right_, key_);
			else return x;
		}

		Node *Put(Node *x, const Key &key_, const Value &val_) {
			if (!x) return new Node(key_, val_, 1);
			if (key_ < x->key_) x->left_ = Put(x->left_, key_, val_);
			else if (key_ > x->key_) x->right_ = Put(x->right_, key_, val_);
			else x->val_ = val_;
			x->size_ = 1 + Size(x->left_) + Size(x->right_);
			return x;
		}

		Node *DeleteMin(Node *x) {
			if (!(x->left_)) {
				Node *ret = x->right_;
				x->right_ = nullptr;
				delete x;
				x = nullptr;
				return ret;
			}

			x->left_ = DeleteMin(x->left_);
			x->size_ = Size(x->left_) + Size(x->right_) + 1;
			return x;
		}

		Node *DeleteMax(Node *x) {
			if (!(x->right_)) {
				Node *ret = x->left_;
				x->left_ = nullptr;
				delete x;
				x = nullptr;
				return ret;
			}
			x->right_ = DeleteMax(x->right_);
			x->size_ = Size(x->left_) + Size(x->right_) + 1;
			return x;
		}

		Node *Delete(Node *x, const Key &key) {
			if (!x) return nullptr;

			int cmp = Compare(key, x->key_);
			if (cmp<0) x->left_ = Delete(x->left_, key);
			else if (cmp>0) x->right_ = Delete(x->right_, key);
			else {
				if (!(x->right_)) {
					Node *ret = x->left_;
					x->left_ = nullptr;
					delete x;
					x = nullptr;
					return ret;
				}
				if (!(x->left_)) {
					Node *ret = x->right_;
					x->right_ = nullptr;
					delete x;
					x = nullptr;
					return ret;
				}
				Node *t = x;
				x = Min(t->right_);
				x = new Node(x->key_, x->val_, x->size_);
				
				x->right_ = DeleteMin(t->right_);
				x->left_ = t->left_;
				t->left_ = nullptr;
				t->right_ = nullptr;
				delete t;
				t = nullptr;
			}
			x->size_ = Size(x->left_) + Size(x->right_) + 1;
			return x;
		}

		 Node *Min(Node *x) const {
			if (!(x->left_)) return x;
			else return Min(x->left_);
		}

		 Node *Max(Node *x) const {
			if (!(x->right_)) return x;
			else return Max(x->right_);
		}

		 Node *Floor(Node *x, const Key &key) const {
			if (!x) return nullptr;
			if (key == x->key_) return x;
			if (key < x->key_) return Floor(x->left_, key);
			Node *t = Floor(x->right_, key);
			if (!t) return t;
			else return x;
		}

		Node *Ceiling(Node *x, const Key &key) const {
			if (!x) return nullptr;
			if (key == x->key_) return x;
			if (key < x->key_) {
				Node *t = Ceiling(x->left_, key);
				if (!t) return t;
				else return x;
			}
			return Ceiling(x->right_, key);
		}

		 Node *Select(Node *x, size_t k) const {
			if (!x) return nullptr;
			size_t t= Size(x->left_);
			if (t > k) return Select(x->left_, k);
			else if (t < k) return Select(x->right_, k - t - 1);
			else return x;
		}

		size_t Rank(Node *x, const Key &key) const {
			if (!x) return 0;
			int cmp = Compare(key, x->key_);
			if (cmp<0) return Rank(x->left_, key);
			else if (cmp>0) return 1 + Size(x->left_) + Rank(x->right_, key);
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

		int Height(Node *x) const {
			if (!x) return -1;
			return 1 + std::Max(Height(x->left_), Height(x->right_));
		}

	public:
		bool IsEmpty() const {
			return Size() == 0;
		}

		size_t Size() const {
			return Size(root_);
		}


		bool Contains(const Key &key) const {
			return Get(key).has_value();
		}

		std::optional<Value> Get(const Key &key) const {
			Node *p = Get(root_, key);
			if (!p) return std::optional<Value>();
			else return std::optional<Value>(p->val_);
		}

		void Put(const Key &key, const Value &val) {
			root_ = Put(root_, key, val);
			assert(Check());
		}



		void DeleteMin() {
			if (IsEmpty()) throw std::underflow_error("Symbol table underflow");
			root_ = DeleteMin(root_);
			assert(Check());
		}


		void DeleteMax() {
			if (IsEmpty()) throw std::underflow_error("Symbol table underflow");
			root_ = DeleteMax(root_);
			assert(Check());
		}

		void Delete(const Key &key_) {
			root_ = Delete(root_, key_);
			assert(Check());
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
			Node *x = Ceiling(root_, key);
			if (!x) return std::optional<Key>();
			else return std::optional<Key>(x->key_);
		}

	    Key Select(size_t k) const {
			if (k >= Size())
				throw std::invalid_argument("argument to Select() is invalid: " + std::to_string(k));
			Node *x = Select(root_, k);
			return x->key_;
		}

		size_t Rank(const Key & key) const {
			return Rank(root_, key);
		}

		Queue<Key> Keys() const {
			if (IsEmpty()) return Queue<Key>();
			return Keys(Min(), Max());
		}

		Queue<Key> Keys(const Key &lo, const Key &hi) const {
			if(!(lo<=hi)) throw std::invalid_argument("invalid input range");
			Queue<Key> queue;
			Keys(root_, queue, lo, hi);
			return queue;
		}

		size_t Size(const Key &lo, const Key &hi) const {
			if (!(lo <= hi)) throw std::invalid_argument("invalid input range");
			if (Contains(hi)) return Rank(hi) - Rank(lo) + 1;
			else return  Rank(hi) - Rank(lo);
		}

		int Height() const {
			return Height(root_);
		}

		Queue<Key> LevelOrder() const{
			Queue<Key> keys;
			Queue<Node *> queue;
			queue.Enqueue(root_);
			while (!queue.IsEmpty()) {
				Node *x = queue.Dequeue();
				if (!x) continue;
				keys.Enqueue(x->key_);
				queue.Enqueue(x->left_);
				queue.Enqueue(x->right_);
			}
			return keys;
		}

	private:
		bool Check() const {
			if (!IsBST()) std::cout << "Not in symmetric order" << std::endl;
			if (!IsSizeConsistent()) std::cout << "Subtree counts not consistent" << std::endl;
			if (!IsRankConsistent()) std::cout << "Ranks not consistent" << std::endl;
			return IsBST() & IsSizeConsistent() & IsRankConsistent();
		}

		bool IsBST() const {
			return IsBST(root_,nullptr, nullptr);
		}

		bool IsBST(Node *x, const Key *minP, const Key *maxP) const {
			if (!x) return true;
			if (minP && (Compare(x->key_, *minP) <= 0)) return false;
			if (maxP && (Compare(x->key_, *maxP) >= 0)) return false;
			return IsBST(x->left_, minP, &(x->key_)) && IsBST(x->right_, &(x->key_), maxP);
		}

		bool IsSizeConsistent() const {
			return IsSizeConsistent(root_);
		}

		bool IsSizeConsistent(Node *x) const {
			if (!x) return true;
			if (x->size_ != Size(x->left_) + Size(x->right_) + 1) return false;
			return IsSizeConsistent(x->left_) && IsSizeConsistent(x->right_);
		}

		bool IsRankConsistent() const {
			for (size_t i = 0; i < Size(); ++i) 
				if (i != Rank(Select(i))) return false;
			for (const Key &key : Keys()) 
				if (Compare(key, Select(Rank(key))) != 0) return false;
			return true;
			
		}

	public:
		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			BST<std::string, int> st;
			std::vector<std::string> vec{ "c","e","a","f","b","d","h","g" };
			for (size_t i = 0; i != vec.size(); ++i) {
				std::string key = vec[i];
				st.Put(key, i);
			}

			assert(st.Contains("e"));

			for (const auto &s : st.LevelOrder())
				std::cout << s << " " << *st.Get(s) << std::endl;
			std::cout << std::endl;

			for (const auto &s : st.Keys())
				std::cout << s << " " << *st.Get(s) << std::endl;
			std::cout << std::endl;

			st.DeleteMax();
			st.DeleteMin();
			st.Delete("e");
			assert(!st.Contains("e"));

			for (const auto &s : st.LevelOrder())
				std::cout << s << " " << *st.Get(s) << std::endl;
			std::cout << std::endl;

			for (const auto &s : st.Keys())
				std::cout << s << " " << *st.Get(s) << std::endl;
			std::cout << std::endl;

			BST<std::string, int> st2(st);
			st = st2;
		}

	};

	template<typename Key, typename Value> void swap(BST<Key, Value> &lhs, BST<Key, Value> &rhs) {
		using std::swap;
		swap(lhs.root_, rhs.root_);
	}
}