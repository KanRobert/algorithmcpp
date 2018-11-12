#pragma once
#include<set>
#include<stdexcept>
#include<optional>
#include<string>
#include<cassert>
#include<iostream>

namespace algorithmcpp {
	template<typename Key> class Set {

	private:
		std::set<Key> tree_set_;

	public:
		Set() = default;
		Set(const Set &) = default;
		Set(Set &&) noexcept = default;
		Set &operator=(const Set &) = default;
		Set &operator=(Set &&) noexcept = default;
		~Set() = default;

		void Add(const Key &key) {
			tree_set_.insert(key);
		}

		bool Contains(const Key &key) const{
			return tree_set_.find(key) != tree_set_.end();
		}

		void Delete(const Key &key) {
			tree_set_.erase(key);
		}

		size_t Size() const {
			return tree_set_.size();
		}

		bool IsEmpty() const {
			return tree_set_.empty();
		}

		Key Max() const {
			if (IsEmpty()) throw std::invalid_argument("called max() with empty set");
			return *tree_set_.rbegin();
		}

		Key Min() const {
			if (IsEmpty()) throw std::invalid_argument("called min() with empty set");
			return *tree_set_.begin();
		}

		std::optional<Key> Ceiling(const Key &key) const {
			auto it = tree_set_.lower_bound(key);
			if (it == tree_set_.end()) return std::optional<Key>();
			return std::optional<Key>(*it);
		}

		std::optional<Key> Floor(const Key &key) const {
			auto it = tree_set_.upper_bound(key);
			if (it == tree_set_.begin()) return std::optional<Key>();
			return std::optional<Key>(*(--it));
		}

		Set<Key> Union(const Set<Key> &that) const {
			Set<Key> c;
			for (const Key &x : *this) {
				c.Add(x);
			}
			for (const Key &x : that) {
				c.Add(x);
			}
			return c;
		}

		Set<Key> Intersects(const Set<Key> &that) const {
			Set<Key> c;
			if (Size() < that.Size()) {
				for (const Key &x : *this) {
					if (that.Contains(x)) c.Add(x);
				}
			}
			else {
				for (const Key &x : that) {
					if ((*this).Contains(x)) c.Add(x);
				}
			}
			return c;
		}

		bool operator==(const Set<Key> &other) const {
			return tree_set_ == other.tree_set_ ;
		}

		bool operator!=(const Set<Key> &other) const {
			return tree_set_ != other.tree_set_;
		}

		typename std::set<Key>::const_iterator begin() const {
			return tree_set_.cbegin();
		}

		typename std::set<Key>::const_iterator end() const {
			return tree_set_.cend();
		}

		typename std::set<Key>::iterator begin() {
			return tree_set_.begin();
		}

		typename std::set<Key>::iterator end() {
			return tree_set_.end();
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			Set<std::string> sset;
			sset.Add("www.cs.princeton.edu");
			sset.Add("www.cs.princeton.edu");    // overwrite old value
			sset.Add("www.princeton.edu");
			sset.Add("www.math.princeton.edu");
			sset.Add("www.yale.edu");
			sset.Add("www.amazon.com");
			sset.Add("www.simpsons.com");
			sset.Add("www.stanford.edu");
			sset.Add("www.google.com");
			sset.Add("www.ibm.com");
			sset.Add("www.apple.com");
			sset.Add("www.slashdot.com");
			sset.Add("www.whitehouse.gov");
			sset.Add("www.espn.com");
			sset.Add("www.snopes.com");
			sset.Add("www.movies.com");
			sset.Add("www.cnn.com");
			sset.Add("www.iitb.ac.in");

			assert(sset.Contains("www.cs.princeton.edu"));
			assert(!sset.Contains("www.harvardsucks.com"));
			assert(sset.Contains("www.simpsons.com"));

			for (const std::string &s : sset) {
				std::cout << s << std::endl;
			}
		}
	};
}