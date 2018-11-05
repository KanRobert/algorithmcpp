#pragma once
#include<string>
#include<algorithm>
#include<stdexcept>
#pragma push_macro("min")
#undef min

namespace algorithmcpp {
	class Substring {
		friend bool operator<(const Substring &, const Substring &);
		friend bool operator>(const Substring &, const Substring &);
		friend bool operator==(const Substring &, const Substring &);
		friend bool operator!=(const Substring &, const Substring &);
		friend bool operator<=(const Substring &, const Substring &);
		friend bool operator>=(const Substring &, const Substring &);
		friend int Compare(const Substring &, const Substring &);
		friend int Compare(const std::string &, const Substring &);
		friend int Compare(const Substring &,const std::string &);
	private:
		const std::string *  p_text_=nullptr;
		size_t lo_=0;
		size_t sz_ = 0;
	public:
		Substring() = default;
		Substring(const Substring &) = default;
		Substring &operator=(const Substring &) = default;
		Substring(Substring &&) noexcept = default;
		Substring &operator=(Substring &&) noexcept = default;
		~Substring() = default;

		Substring(const std::string &text, size_t lo,size_t sz) :
			p_text_(&text), lo_(lo),sz_(sz) {
			if (lo + sz > text.size()) throw std::invalid_argument("");
		}

		size_t Size() const {
			return sz_;
		}

		char operator[](size_t i) const {
			if (i >=sz_) throw std::invalid_argument("");
			return (*p_text_)[lo_ + i];
		}

		std::string ToString() const {
			return p_text_->substr(lo_, sz_);
		}
	};
}

#pragma pop_macro("min")
