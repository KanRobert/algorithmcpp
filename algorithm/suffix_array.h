#pragma once
#include"trimmer.h"
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<stdexcept>
#include<cstdio>

#pragma push_macro("min")
#undef min

namespace algorithmcpp {
	class SuffixArray {
		class Suffix;
		friend bool operator<(const Suffix &, const Suffix &);
		friend bool operator>(const Suffix &, const Suffix &);
		friend bool operator==(const Suffix &, const Suffix &);
		friend bool operator!=(const Suffix &, const Suffix &);
		friend bool operator<=(const Suffix &, const Suffix &);
		friend bool operator>=(const Suffix &, const Suffix &);
		friend int Compare(const Suffix &, const Suffix &);
		friend size_t LcpSuffix(const Suffix &, const Suffix &);
		friend int Compare(const std::string &, const Suffix &);
	private:
		class Suffix {
			friend bool operator<(const Suffix &, const Suffix &);
			friend bool operator>(const Suffix &, const Suffix &);
			friend bool operator==(const Suffix &, const Suffix &);
			friend bool operator!=(const Suffix &, const Suffix &);
			friend bool operator<=(const Suffix &, const Suffix &);
			friend bool operator>=(const Suffix &, const Suffix &);
			friend int Compare(const Suffix &, const Suffix &);
			friend size_t LcpSuffix(const Suffix &, const Suffix &);
			friend int Compare(const std::string &, const Suffix &);

		private:
			const std::string *  p_text_;
			size_t index_;
		public:
			Suffix(const Suffix &) = default;
			Suffix &operator=(const Suffix &) = default;
			Suffix(Suffix &&) noexcept = default;
			Suffix &operator=(Suffix &&) noexcept = default;
			~Suffix() = default;

			Suffix(const std::string &text, size_t index) :
				p_text_(&text), index_(index) {
			}

			size_t Size() const {
				return p_text_->size() - index_;
			}

			char operator[](size_t i) const {
				return (*p_text_)[index_ + i];
			}
			
			std::string ToString() const {
				return p_text_->substr(index_, p_text_->size() - index_);
			}

			size_t Index() const {
				return index_;
			}
		};
		
		std::vector<Suffix> suffixes_;
		std::string text_;


	public:
		SuffixArray() = delete;
		SuffixArray(const SuffixArray&) = default;
		SuffixArray(SuffixArray &&) noexcept = default;
		SuffixArray &operator=(const SuffixArray &) = default;
		SuffixArray &operator=(SuffixArray &&) noexcept = default;
		~SuffixArray() = default;

		SuffixArray(const std::string &text):text_(text) {
			size_t n = text_.size();
			for (size_t i = 0; i < n; ++i) {
				suffixes_.emplace_back(text_, i);
			}
			std::sort(suffixes_.begin(), suffixes_.end());
		}


		size_t Size() const {
			return suffixes_.size();
		}

		size_t Index(size_t i) const {
			if (i >= suffixes_.size()) throw std::invalid_argument("");
			return suffixes_[i].Index();
		}

		size_t Lcp(size_t i) const {
			if(i<1 || i>=suffixes_.size()) throw std::invalid_argument("");
			return LcpSuffix(suffixes_[i], suffixes_[i - 1]);
		}

		std::string Select(size_t i) const {
			if (i<0 || i >= suffixes_.size()) throw std::invalid_argument("");
			return suffixes_[i].ToString();
		}

		size_t Rank(const std::string &query) const {
			size_t lo = 0, hi = suffixes_.size() - 1;
			while (lo <= hi && hi < suffixes_.size()) {
				size_t mid = lo + (hi - lo) / 2;
				int cmp = Compare(query, suffixes_[mid]);
				if (cmp < 0) hi = mid - 1;
				else if (cmp > 0) lo = mid + 1;
				else return mid;
			}
			return lo;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/abra.txt");
			std::string s;
			std::getline(in, s);
			Trimmer::Trim(s);
			SuffixArray suffix_array(s);
			std::printf("  i ind lcp rnk select\n");
			std::printf("---------------------------\n");
			for (size_t i = 0; i < s.size(); ++i) {
				size_t index = suffix_array.Index(i);
				std::string ith="\""+s.substr(index,s.size()-index) + "\"";
				size_t rank = suffix_array.Rank(s.substr(index, s.size() - index));
				if (i == 0) {
					std::printf("%3zd %3zd %3s %3zd %s\n", i, index, "-", rank, ith.c_str());
				}
				else {
					size_t lcp = suffix_array.Lcp(i);
					std::printf("%3zd %3zd %3zd %3zd %s\n", i, index, lcp, rank, ith.c_str());
				}
			}
		}
	};
	
	bool operator<(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	bool operator>(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	bool operator==(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	bool operator!=(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	bool operator<=(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	bool operator>=(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	int Compare(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	size_t LcpSuffix(const SuffixArray::Suffix &, const SuffixArray::Suffix &);
	int Compare(const std::string &, const SuffixArray::Suffix &);
}

#pragma pop_macro("min")