#pragma once
#include"queue.h"
#include<string>
#include<vector>
#include<iostream>
#include<optional>

namespace algorithmcpp {
	template<typename, typename> class SequentialSearchST;
	template<typename Key, typename Value> void swap(SequentialSearchST<Key, Value> &, SequentialSearchST<Key, Value> &);

	template<typename Key, typename Value> class SequentialSearchST {
		friend void swap<Key, Value>(SequentialSearchST<Key, Value> &, SequentialSearchST<Key, Value> &);
	public:
		SequentialSearchST() = default;
		SequentialSearchST(const SequentialSearchST &rhs) {
			for (const Node *p = rhs.first_; p != nullptr; p = p->next_) {
				Put(p->key_,p->val_);
			}
		}
		SequentialSearchST &operator=(SequentialSearchST rhs) {
			swap(*this, rhs);
			return *this;
		}
		SequentialSearchST(SequentialSearchST &&rhs) noexcept {
			first_ = rhs.first_;
			n_ = rhs.n_;
			rhs.first_ = nullptr;
			rhs.n_ = 0;
		}
		~SequentialSearchST() {
			while (first_) {
				Node *oldfirst = first_;
				first_ = oldfirst->next_;
				delete oldfirst;
			}
		}

	private:
		class Node {
		public:
			Key key_;
			Value val_;
			Node *next_;
		public:
			Node(const Key &key, const Value &val, Node *next)
				:key_(key),val_(val),next_(next){}
			Node(const Key &key, const Value &val, size_t size) :key_(key), val_(val), size(size) {}
			Node(const Node &) = delete;
			Node &operator=(const Node &) = delete;
			~Node() = default;
		};

		size_t n_ = 0;
		Node *first_ = nullptr;

		Node *Delete(Node *x, const Key &key) {
			if (!x) return nullptr;
			if (key == x->key_) {
				Node *tmp = x->next_;
				x->next_ = nullptr;
				delete x;
				--n_;
				return tmp;
			}
			x->next_ = Delete(x->next_, key);
			return x;
		}

	public:
		size_t Size() const {
			return n_;
		}

		bool IsEmpty() const {
			return n_ == 0;
		}

		bool Contains(const Key &key) const {
			return Get(key).has_value();
		}

		std::optional<Value> Get(const Key &key) const {
			for (Node *x = first_; x != nullptr; x = x->next_) {
				if (key == x->key_)	return std::optional<Value>(x->val_);
			}
			return std::optional<Value>();
		}

		void Put(const Key &key, const Value &val) {
			for (Node *x = first_; x != nullptr; x = x->next_) {
				if (key == x->key_) {
					x->val_ = val;
					return;
				}
			}
			first_ = new Node(key, val, first_);
			++n_;
		}

		void Delete(const Key &key) {
			first_ = Delete(first_, key);
		}

		Queue<Key> Keys() const {
			Queue<Key> queue;
			for (Node *x = first_; x != nullptr; x = x->next_)
				queue.Enqueue(x->key_);
			return queue;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			SequentialSearchST<std::string, int> st;
			std::vector<std::string> vec{ "c","e","a","f","b","d","h","g" };
			for (size_t i = 0; i != vec.size(); ++i) {
				std::string key_ = vec[i];
				st.Put(key_, i);
			}


			for (const auto &s : st.Keys())
				std::cout << s << " " << *st.Get(s) << std::endl;
			std::cout << std::endl;

			SequentialSearchST<std::string, int> st2(st);
			st = st2;
		}
	};

	template<typename Key, typename Value> void swap(SequentialSearchST<Key, Value> &lhs, SequentialSearchST<Key, Value> &rhs) {
		using std::swap;
		swap(lhs.first_, rhs.first_);
		swap(lhs.n_, rhs.n_);
	}
}