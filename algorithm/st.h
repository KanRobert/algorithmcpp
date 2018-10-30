#pragma once
#include"queue.h"
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<stdexcept>
#include<cassert>
#include<optional>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

namespace algorithmcpp {
	template<typename Key, typename Value> class ST {
	private:
		std::map<Key, Value> st_;

	public:
		ST() = default;
		ST(const ST &) = default;
		ST &operator=(const ST &) = default;
		ST(ST &&) noexcept = default;
		ST &operator=(ST &&) noexcept = default;
		~ST() = default;

		std::optional<Value> Get(const Key &key) const {
			auto it = st_.find(key);
			if (it != st_.end()) return std::optional<Value>(it->second);
			else return std::optional<Value>();
		}

		void Put(const Key &key, const Value &val) {
			st_.insert({ key, val });
		}

		void Delete(const Key &key) {
			st_.erase(key);
		}

		bool Contains(const Key &key) const {
			return st_.find(key) != st_.end();
		}

		size_t Size() const {
			return st_.size();
		}

		bool IsEmpty() const {
			return st_.empty();
		}

		Queue<Key> Keys() const {
			Queue<Key> queue;
			for (auto it = st_.begin(); it != st_.end(); ++it) {
				queue.Enqueue(it->first);
			}
			return queue;
		}

		Key Min() const {
			if (IsEmpty()) throw std::underflow_error("calls Min() with empty symbol table");
			return st_.begin()->first;
		}

		Key Max() const {
			if (IsEmpty()) throw std::underflow_error("calls Max() with empty symbol table");
			return (--st_.end())->first;
		}

		std::optional<Key> Ceiling(const Key &key) const {
			auto it = st_.lower_bound(key);
			if (it != st_.end()) return std::optional<Key>(it->first);
			else return std::optional<Key>();
		}

		std::optional<Key> Floor(const Key &key) const {
			auto it = st_.upper_bound(key);
			if (it != st_.end()) return std::optional<Key>(it->first);
			else return std::optional<Key>();
		}

		void DeleteMin() {
			if (IsEmpty()) throw std::underflow_error("Symbol table underflow");
			st_.erase(st_.begin());
		}


		void DeleteMax() {
			if (IsEmpty()) throw std::underflow_error("Symbol table underflow");
			st_.erase(--st_.end());
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			ST<std::string, int> st;
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

			ST<std::string, int> st2(st);
			st = st2;
		}
	};
}

#pragma pop_macro("max")
#pragma pop_macro("min")