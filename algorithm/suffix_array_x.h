#pragma once
#include"trimmer.h"
#include<string>
#include<vector>
#include<cstdio>
#include<fstream>

namespace algorithmcpp {
	class SuffixArrayX {
	private:
		static constexpr size_t kCutOff = 5;
		std::string text_;
		std::vector<size_t> index_;

	public:
		SuffixArrayX() = delete;
		SuffixArrayX(const SuffixArrayX&) = default;
		SuffixArrayX(SuffixArrayX &&) noexcept = default;
		SuffixArrayX &operator=(const SuffixArrayX &) = default;
		SuffixArrayX &operator=(SuffixArrayX &&) noexcept = default;
		~SuffixArrayX() = default;

		SuffixArrayX(const std::string &text) :text_(text){
			for (size_t i = 0; i < text_.size(); ++i) {
				index_.push_back(i);
			}
			Sort(0, text_.size() - 1, 0);
		}

	private:
		static int CharAt(const std::string &s, size_t d) {
			if (d >= s.size()) return -1;
			return s[d];
		}

		bool Less(size_t i, size_t j, size_t d) const {
			if (i == j) return false;
			i += d;
			j += d;
			while (i < text_.size() && j < text_.size()) {
				if (text_[i] < text_[j]) return true;
				if (text_[i] > text_[j]) return false;
				++i;
				++j;
			}
			return i == text_.size();
		}

		void Insertion(size_t lo, size_t hi, size_t d) {
			using std::swap;
			for (size_t i = lo; i <= hi; ++i) {
				for (size_t j = i; j > lo && Less(index_[j], index_[j - 1], d); --j) {
					swap(index_[j], index_[j-1]);
				}
			}
		}

		void Sort(size_t lo, size_t hi, size_t d) {
			using std::swap;
			if (hi <= lo + kCutOff) {
				Insertion(lo, hi, d);
				return;
			}

			size_t lt = lo, gt = hi;
			int v = CharAt(text_, index_[lo] + d);
			size_t i = lo + 1;
			while (i <= gt) {
				int t = CharAt(text_, index_[i] + d);
				if (t < v) swap(index_[lt++], index_[i++]);
				else if (t > v) swap(index_[i], index_[gt--]);
				else ++i;
			}
			Sort(lo, lt - 1, d);
			if (v > 0) Sort(lt, gt, d + 1);
			Sort(gt + 1, hi, d);
		}

		size_t Lcp(size_t i, size_t j) const {
			size_t length = 0;
			while (i < text_.size() && j < text_.size()) {
				if (text_[i] != text_[j]) return length;
				++i;
				++j;
				++length;
			}
			return length;
		}

		int Compare(const std::string &query, size_t i) const {
			size_t m = query.size();
			size_t n = text_.size();
			size_t j = 0;
			while (i < n && j < m) {
				if (query[j] < text_[i]) return -1;
				if (query[j] > text_[i]) return +1;
				++i;
				++j;
			}
			if (i < n) return -1;
			if (j < m) return +1;
			return 0;
		}

	public:
		size_t Size() const {
			return text_.size();
		}

		size_t Lcp(size_t i) const {
			if (i<1 || i >= text_.size()) throw std::invalid_argument("");
			return Lcp(index_[i], index_[i - 1]);
		}

		std::string Select(size_t i) const {
			if (i >= text_.size()) throw std::invalid_argument("");
			return text_.substr(index_[i], text_.size() - index_[i]);
		}

		size_t Index(size_t i) const {
			if (i >= text_.size()) throw std::invalid_argument("");
			return index_[i];
		}

		size_t Rank(const std::string &query) const {
			size_t lo = 0, hi = text_.size() - 1;
			while (lo <= hi && hi < text_.size()) {
				size_t mid = lo + (hi - lo) / 2;
				int cmp = Compare(query, index_[mid]);
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
			SuffixArrayX suffix_array(s);
			std::printf("  i ind lcp rnk select\n");
			std::printf("---------------------------\n");
			for (size_t i = 0; i < s.size(); ++i) {
				size_t index = suffix_array.Index(i);
				std::string ith = "\"" + s.substr(index, s.size() - index) + "\"";
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
	
}