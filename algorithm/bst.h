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
			for (const auto &key : rhs.Keys()) {
				Put(key, *rhs.Get(key));
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
		struct Node {
			Key key;
			Value val;
			size_t size;
			Node *left = nullptr;
			Node *right = nullptr;

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
			if (lhs == rhs) return 0;
			if (lhs < rhs) return -1;
			else return 1;
		}


		size_t Size(Node *x) const {
			if (!x) return 0;
			else return x->size;
		}

		Node *Get(Node *x, const Key &key) const {
			if (!x) return nullptr;
			if (key < (x->key)) return Get(x->left, key);
			else if(key>(x->key)) return Get(x->right, key);
			else return x;
		}

		Node *Put(Node *x, const Key &key, const Value &val) {
			if (!x) return new Node{ key, val, 1 };
			if (key < x->key) x->left = Put(x->left, key, val);
			else if (key > x->key) x->right = Put(x->right, key, val);
			else x->val = val;
			x->size = 1 + Size(x->left) + Size(x->right);
			return x;
		}

		Node *DeleteMin(Node *x) {
			if (!(x->left)) {
				Node *ret = x->right;
				x->right = nullptr;
				delete x;
				x = nullptr;
				return ret;
			}

			x->left = DeleteMin(x->left);
			x->size = Size(x->left) + Size(x->right) + 1;
			return x;
		}

		Node *DeleteMax(Node *x) {
			if (!(x->right)) {
				Node *ret = x->left;
				x->left = nullptr;
				delete x;
				x = nullptr;
				return ret;
			}
			x->right = DeleteMax(x->right);
			x->size = Size(x->left) + Size(x->right) + 1;
			return x;
		}

		Node *Delete(Node *x, const Key &key) {
			if (!x) return nullptr;

			int cmp = Compare(key, x->key);
			if (cmp<0) x->left = Delete(x->left, key);
			else if (cmp>0) x->right = Delete(x->right, key);
			else {
				if (!(x->right)) {
					Node *ret = x->left;
					x->left = nullptr;
					delete x;
					x = nullptr;
					return ret;
				}
				if (!(x->left)) {
					Node *ret = x->right;
					x->right = nullptr;
					delete x;
					x = nullptr;
					return ret;
				}
				Node *t = x;
				x = Min(t->right);
				x = new Node{ x->key, x->val, x->size };
				
				x->right = DeleteMin(t->right);
				x->left = t->left;
				t->left = nullptr;
				t->right = nullptr;
				delete t;
				t = nullptr;
			}
			x->size = Size(x->left) + Size(x->right) + 1;
			return x;
		}

		 Node *Min(Node *x) const {
			if (!(x->left)) return x;
			else return Min(x->left);
		}

		 Node *Max(Node *x) const {
			if (!(x->right)) return x;
			else return Max(x->right);
		}

		 Node *Floor(Node *x, const Key &key) const {
			if (!x) return nullptr;
			if (key == x->key) return x;
			if (key < x->key) return Floor(x->left, key);
			Node *t = Floor(x->right, key);
			if (!t) return t;
			else return x;
		}

		Node *Ceiling(Node *x, const Key &key) const {
			if (!x) return nullptr;
			if (key == x->key) return x;
			if (key < x->key) {
				Node *t = Ceiling(x->left, key);
				if (!t) return t;
				else return x;
			}
			return Ceiling(x->right, key);
		}

		 Node *Select(Node *x, size_t k) const {
			if (!x) return nullptr;
			size_t t= Size(x->left);
			if (t > k) return Select(x->left, k);
			else if (t < k) return Select(x->right, k - t - 1);
			else return x;
		}

		size_t Rank(Node *x, const Key &key) const {
			if (!x) return 0;
			int cmp = Compare(key, x->key);
			if (cmp<0) return Rank(x->left, key);
			else if (cmp>0) return 1 + Size(x->left) + Rank(x->right, key);
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

		int Height(Node *x) const {
			if (!x) return -1;
			return 1 + std::Max(Height(x->left), Height(x->right));
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
			else return std::optional<Value>(p->val);
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

		void Delete(const Key &key) {
			root_ = Delete(root_, key);
			assert(Check());
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
			Node *x = Ceiling(root_, key);
			if (!x) return std::optional<Key>();
			else return std::optional<Key>(x->key);
		}

	    Key Select(size_t k) const {
			if (k >= Size())
				throw std::invalid_argument("argument to Select() is invalid: " + std::to_string(k));
			Node *x = Select(root_, k);
			return x->key;
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
				keys.Enqueue(x->key);
				queue.Enqueue(x->left);
				queue.Enqueue(x->right);
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
			if (minP && (Compare(x->key, *minP) <= 0)) return false;
			if (maxP && (Compare(x->key, *maxP) >= 0)) return false;
			return IsBST(x->left, minP, &(x->key)) && IsBST(x->right, &(x->key), maxP);
		}

		bool IsSizeConsistent() const {
			return IsSizeConsistent(root_);
		}

		bool IsSizeConsistent(Node *x) const {
			if (!x) return true;
			if (x->size != Size(x->left) + Size(x->right) + 1) return false;
			return IsSizeConsistent(x->left) && IsSizeConsistent(x->right);
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