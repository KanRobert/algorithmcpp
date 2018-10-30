#pragma once
#include"queue.h"
#include<iostream>
#include<string>
#include<optional>

namespace algorithmcpp {
	template<typename, typename> class BTree;
	template<typename Key, typename Value> void swap(BTree<Key, Value> &, BTree<Key, Value> &);

	template<typename Key, typename Value> class BTree {
		friend void swap<Key, Value>(BTree<Key, Value> &, BTree<Key, Value> &);
	public:
		BTree() = default;
		BTree(const BTree &rhs) {
			for (const auto &key : rhs.Keys()) {
				Put(key, rhs.Get(key).value());
			}
		}
		BTree &operator=(BTree rhs) {
			swap(*this, rhs);
			return *this;
		}
		BTree(BTree &&rhs) noexcept {
			root_ = rhs.root_;
			altitude_ = rhs.altitude_;
			n_ = rhs.n_;
			rhs.root_ = nullptr;
			rhs.altitude_ = 0;
			rhs.n_ = 0;
		}
		~BTree() {
			delete root_;
			root_ = nullptr;
		}

	private:
		class Node;
		class Entry {
		public:
			Key key_;
			Value *val_;
			Node *next_;
		public:
			Entry(const Entry &) = delete;
			Entry &operator=(const Entry &) = delete;
			~Entry() {    
				delete val_;
				delete next_;
				val_ = nullptr;
				next_ = nullptr;
			}
			Entry(const Key &key, const Value *val, Node *next) :
				key_(key), next_(next) {
				if (!val) val_ = nullptr;
				else val_ = new Value(*val);
			}
		};

		class Node final {
		public:
			size_t m_;
			Entry **children_ = new Entry*[kM](); 

		public:
			Node(const Node &) = delete;
			Node &operator=(const Node &) = delete;
			~Node() {                        
				for (size_t i = 0; i < m_; ++i) {
					delete children_[i];
					children_[i] = nullptr;
				}
				delete children_;
				children_ = nullptr;
			}

			Node(int x):m_(x) {
			}
		};

		constexpr static size_t kM = 4;
		Node *root_ = new Node(0);
		int altitude_ = 0;
		size_t n_ = 0;

		int Compare(const Key &k1, const Key &k2) const {
			if (k1 < k2) return -1;
			if (k1 == k2) return 0;
			else return +1;
		}

		bool Less(const Key &k1, const Key &k2) const {
			return Compare(k1, k2) < 0;
		}

		bool Eq(const Key &k1, const Key &k2) const {
			return Compare(k1, k2) == 0;
		}

		const Value *Search(Node *x, const Key &key, int ht) const {
			Entry **children_ = x->children_;
			if (ht == 0) {
				for (size_t j = 0; j < x->m_; ++j) {
					if (Eq(key, children_[j]->key_)) return children_[j]->val_;
				}
			}
			else {
				for (size_t j = 0; j < x->m_; ++j) {
					if (j + 1 == x->m_ || Less(key, children_[j + 1]->key_))
						return Search(children_[j]->next_, key, ht - 1);
				}
			}
			return nullptr;
		}

		Node *Split(Node *h) {
			Node *t = new Node(kM / 2);
			h->m_ = kM / 2;
			for (size_t j = 0; j < kM / 2; ++j) {
				t->children_[j] = h->children_[kM / 2 + j];
			}
			for (size_t j = kM / 2; j < kM; ++j) {
				h->children_[j] = nullptr;
			}
			return t;
		}

		Node *Insert(Node *h, const Key &key, const Value &val, int ht) {
			size_t j;
			Entry *t=new Entry(key, &val, nullptr);

			if (ht == 0) {
				for (j = 0; j < h->m_; ++j) {
					if (Less(key, h->children_[j]->key_)) break;
				}
			}
			else {
				for (j = 0; j < h->m_; ++j) {
					if ((j + 1 == h->m_) || Less(key, h->children_[j + 1]->key_)) {
						Node *u = Insert(h->children_[j++]->next_, key, val, ht - 1);
						if (!u) {
							delete t;
							return nullptr;
						}
						t->key_ = u->children_[0]->key_;
						t->next_ = u;
						break;
					}
				}
			}
			if (j>0 && h->children_[j-1]->key_ == key) {
				*(h->children_[j-1]->val_) = val;
				delete t;
				return nullptr;
			}

			for (size_t i = h->m_; i > j; --i) {
				h->children_[i] = h->children_[i - 1];
			}
			h->children_[j] = t;
			++h->m_;
			if (h->m_ < kM) return nullptr;
			else return Split(h);
		}

		void Keys(Node *h, int ht, Queue<Key> &queue) const{
			Entry **children_ = h->children_;
			if (ht == 0) {
				for (size_t j = 0; j < h->m_; ++j) {
					queue.Enqueue(children_[j]->key_);
				}
			}
			else {
				for (size_t j = 0; j < h->m_; ++j) {
					Keys(children_[j]->next_, ht - 1, queue);
				}
			}
		}


	public:
		size_t Size() const {
			return n_;
		}

		bool IsEmpty() const {
			return n_ == 0;
		}

		int Height() const {
			return altitude_;
		}

		std::optional<Value> Get(const Key &key) const {
			const Value *tmp = Search(root_, key, altitude_);
			if (!tmp) return std::optional<Value>();
			return std::optional<Value>(*tmp);
		}

		bool Contains(const Key &key) const {
			return Get(key).has_value();
		}

		void Put(const Key &key, const Value &val) {
			bool iscontain = Contains(key);
			Node *u = Insert(root_, key, val, altitude_);
			if(!iscontain) ++n_;
			if (u == nullptr) return;

			Node *t = new Node(2);
			t->children_[0] = new Entry(root_->children_[0]->key_, nullptr, root_);
			t->children_[1] = new Entry(u->children_[0]->key_, nullptr, u);
			root_ = t;
			++altitude_;
		}

		Queue<Key> Keys() const {
			Queue<Key> queue;
			Keys(root_, altitude_, queue);
			return queue;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			BTree<std::string, std::string> st;
			st.Put("www.cs.princeton.edu", "128.112.136.12");
			st.Put("www.cs.princeton.edu", "128.112.136.11");
			st.Put("www.princeton.edu", "128.112.128.15");
			st.Put("www.yale.edu", "130.132.143.21");
			st.Put("www.simpsons.com", "209.052.165.60");
			st.Put("www.apple.com", "17.112.152.32");
			st.Put("www.amazon.com", "207.171.182.16");
			st.Put("www.ebay.com", "66.135.192.87");
			st.Put("www.cnn.com", "64.236.16.20");
			st.Put("www.google.com", "216.239.41.99");
			st.Put("www.nytimes.com", "199.239.136.200");
			st.Put("www.microsoft.com", "207.126.99.140");
			st.Put("www.dell.com", "143.166.224.230");
			st.Put("www.slashdot.org", "66.35.250.151");
			st.Put("www.espn.com", "199.181.135.201");
			st.Put("www.weather.com", "63.111.66.11");
			st.Put("www.yahoo.com", "216.109.118.65");

			std::cout << "cs.princeton.edu:  " << st.Get("www.cs.princeton.edu").value() << std::endl;
			assert(!st.Get("hardvardsucks.com").has_value());
			std::cout << "simpsons.com:  " << st.Get("www.simpsons.com").value() << std::endl;
			std::cout << "apple.com:  " << st.Get("www.apple.com").value() << std::endl;
			std::cout << "ebay.com:  " << st.Get("www.ebay.com").value() << std::endl;
			std::cout << std::endl;
			std::cout << "size " << st.Size() << std::endl;
			std::cout << "height " << st.Height() << std::endl;

			for (const auto &s : st.Keys())
				std::cout << s << " " << st.Get(s).value() << std::endl;
			std::cout << std::endl;

			BTree<std::string, std::string> st2(st);
			st = st2;
		}

	};

	template<typename Key, typename Value> void swap(BTree<Key, Value> &lhs, BTree<Key, Value> &rhs) {
		using std::swap;
		swap(lhs.root_, rhs.root_);
		swap(lhs.altitude_, rhs.altitude_);
		swap(lhs.n_, rhs.n_);
	}
}