#pragma once
#include"queue.h"
#include<string>
#include<iostream>
#include<memory>
#include<cassert>
#include<functional>
#include<vector>
#include<utility>
#include<optional>

#pragma push_macro("free")
#undef free

namespace algorithmcpp {
	template<typename, typename> class LinearProbingHashST;
	template<typename Key, typename Value> void swap(LinearProbingHashST<Key, Value> &, LinearProbingHashST<Key, Value> &);

	template<typename Key, typename Value> class LinearProbingHashST {
		friend void swap<Key, Value>(LinearProbingHashST<Key, Value> &, LinearProbingHashST<Key, Value> &);
	private:
		static constexpr size_t kInitCapacity = 4;
		static constexpr std::hash<Key> hasher_ = std::hash<Key>{};
		static std::allocator<Key> kalloc_;
		static std::allocator<Value> valloc_;
		size_t m_ = kInitCapacity;
		size_t n_ = 0;
		std::vector<bool> constructed_=std::vector<bool>(m_);
		Key *ka_ = kalloc_.allocate(m_);
		Value *va_ = valloc_.allocate(m_);
		

		size_t Hash(const Key &key) const{
			return hasher_(key) % m_;
		}

		void Free() {
			for (size_t i = 0; i != m_; ++i) {
				if (constructed_[i]) {
					kalloc_.destroy(ka_ + i);
					valloc_.destroy(va_ + i);
				}
			}
			kalloc_.deallocate(ka_, m_);
			valloc_.deallocate(va_, m_);
		}

		void Resize(size_t capacity) {
			LinearProbingHashST<Key, Value> temp(capacity);
			for (size_t i = 0; i < m_; ++i) {
				if (constructed_[i]) {
					temp.Put(ka_[i], va_[i]);
				}
			}
			Free();
			ka_ = temp.ka_;
			va_ = temp.va_;
			m_ = temp.m_;
			constructed_ = temp.constructed_;
			temp.ka_ = nullptr;
			temp.va_ = nullptr;
			temp.m_ = 0;
			temp.n_ = 0;
		}

	public:
		LinearProbingHashST() = default;
		LinearProbingHashST(const LinearProbingHashST &rhs) {
			for (const auto &key : rhs.Keys()) {
				Put(key, *rhs.Get(key));
			}
		}
		LinearProbingHashST &operator=(LinearProbingHashST rhs) {
			swap(*this, rhs);
			return *this;
		}
		LinearProbingHashST(LinearProbingHashST &&rhs) noexcept {
			m_ = rhs.m_;
			n_ = rhs.n_;
			constructed_ = rhs.constructed_;
			ka_ = rhs.ka_;
			va_ = rhs.va_;
			rhs.m_ = 0;
			rhs.n_ = 0;
			rhs.contructed.clear();
			rhs.ka_ = nullptr;
			rhs.va_ = nullptr;
		}

		~LinearProbingHashST() {
			Free();
		}

		LinearProbingHashST(size_t capacity) :m_(capacity){}

		size_t Size() const {
			return n_;
		}

		bool IsEmpty() const {
			return n_ == 0;
		}

		bool Contains(const Key &key) const {
			return Get(key).has_value();
		}

		void Put(const Key &key, const Value &val) {
			if (n_ >= m_ / 2) Resize(2 * m_);
			size_t i= Hash(key);
			for (; constructed_[i]; i = (i + 1) % m_) {
				if (ka_[i] == key) {
					va_[i] = val;
					return;
				}
			}
			kalloc_.construct(ka_ + i, key);
			valloc_.construct(va_ + i, val);
			constructed_[i] = true;
			++n_;
		}

		std::optional<Value> Get(const Key &key) const {
			for (size_t i = Hash(key); constructed_[i]; i = (i + 1) % m_) {
				if (ka_[i] == key)	return std::optional<Value>(va_[i]);
			}
			return std::optional<Value>();
		}

		void Delete(const Key &key) {
			if (!Contains(key)) return;
			size_t i = Hash(key);
			while (key != ka_[i]) i = (i + 1) % m_;
			kalloc_.destroy(ka_ + i);
			valloc_.destroy(va_ + i);
			constructed_[i] = false;
			--n_;

			i = (i + 1) % m_;
			while (constructed_[i]) {
				Key keyToRehash = std::move(ka_[i]);
				Value valToRehash = std::move(va_[i]);
				kalloc_.destroy(ka_ + i);
				valloc_.destroy(va_ + i);
				constructed_[i] = false;
				--n_;
				Put(keyToRehash, valToRehash);
				i = (i + 1) % m_;
			}
			if (n_ > 0 && n_ < m_ / 8) Resize(m_ / 2);
		}

		Queue<Key> Keys() const {
			Queue<Key> queue;
			for (size_t i = 0; i != m_; ++i) {
				if (constructed_[i]) queue.Enqueue(ka_[i]);
			}
			return queue;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			LinearProbingHashST<std::string, int> st;
			std::vector<std::string> vec{ "c","e","a","f","b","d","h","g" };
			for (size_t i = 0; i != vec.size(); ++i) {
				std::string key = vec[i];
				st.Put(key, i);
			}

			assert(st.Contains("e"));

			for (const auto &s : st.Keys())
				std::cout << s << " " << *st.Get(s) << std::endl;
			std::cout << std::endl;

			st.Delete("e");
			assert(!st.Contains("e"));

			LinearProbingHashST<std::string, int> st2(st);
			st = st2;
		}

	};

	template<typename Key,typename Value>
	std::allocator<Key> LinearProbingHashST<Key,Value>::kalloc_ = std::allocator<Key>();
	template<typename Key,typename Value>
	std::allocator<Value> LinearProbingHashST<Key, Value>::valloc_ = std::allocator<Value>();

	template<typename Key, typename Value> void swap(LinearProbingHashST<Key, Value> &lhs, LinearProbingHashST<Key, Value> &rhs) {
		using std::swap;
		swap(lhs.m_, rhs.m_);
		swap(lhs.n_, rhs.n_);
		swap(lhs.constructed_, rhs.constructed_);
		swap(lhs.ka_, rhs.ka_);
		swap(lhs.va_, rhs.va_);
	}
}

#pragma pop_macro("free")
