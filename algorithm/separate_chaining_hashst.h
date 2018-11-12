#pragma once
#include"queue.h"
#include"sequential_search_st.h"
#include<string>
#include<iostream>
#include<memory>
#include<cassert>
#include<functional>
#include<optional>


namespace algorithmcpp {
	template<typename, typename> class SeparateChainingHashST;
	template<typename Key, typename Value> void swap(SeparateChainingHashST<Key, Value> &, SeparateChainingHashST<Key, Value> &);

	template<typename Key, typename Value> class SeparateChainingHashST {
		friend void swap<Key, Value>(SeparateChainingHashST<Key, Value> &, SeparateChainingHashST<Key, Value> &);
	private:
		static constexpr size_t kInitCapacity = 4;
		static constexpr std::hash<Key> kHasher = std::hash<Key>{};
		size_t m_ = kInitCapacity;
		size_t n_ = 0;
		SequentialSearchST<Key,Value> *st_ = new SequentialSearchST<Key, Value>[m_];

		void Resize(size_t chains) {
			SeparateChainingHashST<Key, Value> temp(chains);
			for (size_t i = 0; i < m_; ++i) {
				for (const Key &key : st_[i].Keys()) {
					temp.Put(key, *st_[i].Get(key));
				}
			}
			m_ = temp.m_;
			n_ = temp.n_;
			st_ = temp.st_;
			temp.st_ = nullptr;
		}

		size_t Hash(const Key &key) {
			return kHasher(key) % m_;
		}

	public:
		SeparateChainingHashST() :SeparateChainingHashST(kInitCapacity) {};
		SeparateChainingHashST(const SeparateChainingHashST &rhs) :m_(rhs.m_), n_(rhs.n_) {
			for (size_t i = 0; i != m_; ++i) {
				st_[i] = rhs.st_[i];
			}
		}
		SeparateChainingHashST &operator=(SeparateChainingHashST rhs) {
			swap(*this, rhs);
			return *this;
		}
		SeparateChainingHashST(SeparateChainingHashST &&rhs) noexcept {
			m_ = rhs.m_;
			n_ = rhs.n_;
			st_ = rhs.st_;
			rhs.m_ = 0;
			rhs.n_ = 0;
			rhs.st_ = nullptr;
		}
		~SeparateChainingHashST() {
			delete[] st_;
		}
		SeparateChainingHashST(size_t m) :m_(m) {}


		size_t Size() {
			return n_;
		}

		bool IsEmpty() {
			return n_ == 0;
		}

		bool Contains(const Key &key) {
			return Get(key).has_value();
		}

		std::optional<Value> Get(const Key &key) {
			size_t i = Hash(key);
			return st_[i].Get(key);
		}

		void Put(const Key &key, const Value &val) {
			if (n_ >= 10 * m_) Resize(2 * m_);
			size_t i = Hash(key);
			if (!st_[i].Contains(key)) ++n_;
			st_[i].Put(key, val);
		}

		void Delete(const Key &key) {
			size_t i= Hash(key);
			if (st_[i].Contains(key))--n_;
			else return;

			st_[i].Delete(key);
			if (m_ > kInitCapacity && n_ <= 2 * m_) Resize(m_ / 2);
		}

		Queue<Key> Keys() {
			Queue<Key> queue;
			for (size_t i = 0; i != m_; ++i) {
				for (const Key &key : st_[i].Keys()) {
					queue.Enqueue(key);
				}
			}
			return queue;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			SeparateChainingHashST<std::string, int> st_;
			std::vector<std::string> vec{ "c","e","a","f","b","d","h","g" };
			for (size_t i = 0; i != vec.size(); ++i) {
				std::string key = vec[i];
				st_.Put(key, i);
			}

			assert(st_.Contains("e"));

			for (const auto &s : st_.Keys())
				std::cout << s << " " << *st_.Get(s) << std::endl;
			std::cout << std::endl;

			st_.Delete("e");
			assert(!st_.Contains("e"));
			SeparateChainingHashST<std::string, int> st2(st_);
			st_ = st2;
		}
	};
	template<typename Key, typename Value> void swap(SeparateChainingHashST<Key, Value> &lhs, SeparateChainingHashST<Key, Value> &rhs) {
		using std::swap;
		swap(lhs.m_, rhs.m_);
		swap(lhs.n_, rhs.n_);
		swap(lhs.st_, rhs.st_);
	}
}