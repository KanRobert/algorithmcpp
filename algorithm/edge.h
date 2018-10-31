#pragma once
#pragma warning (disable : 4996)
#include<stdexcept>
#include<string>
#include<iostream>
#include<cstdio>

namespace algorithmcpp {
	class Edge {
		friend bool operator<(const Edge &, const Edge &);
		friend bool operator>(const Edge &, const Edge &);
		friend bool operator==(const Edge &, const Edge &);
		friend bool operator<=(const Edge &, const Edge &);
		friend bool operator>=(const Edge &, const Edge &);
		friend bool operator!=(const Edge &, const Edge &);
		friend int Compare(const Edge &, const Edge &);

	private:
		size_t v_=0;
		size_t w_=0;
		double edge_weight_=0.0;
		bool valid_ = false;

	public:
		Edge() = default;
		Edge(const Edge &) = default;
		Edge(Edge &&) noexcept = default;
		Edge &operator=(const Edge &) = default;
		Edge &operator=(Edge &&) noexcept = default;
		~Edge() = default;

		Edge(size_t v,size_t w,double edge_weight):
			v_(v),w_(w),edge_weight_(edge_weight),valid_(true){}

		double Weight() const {
			return edge_weight_;
		}

		size_t Either() const {
			return v_;
		}

		size_t Other(size_t vertex) const {
			if (vertex == v_) return w_;
			else if (vertex == w_) return v_;
			else throw std::invalid_argument("illegal endpoint");
		}

		std::string ToString() const {
			char s[32];
			sprintf(s,"%u-%u %.2f", static_cast<unsigned>(v_), static_cast<unsigned>(w_), edge_weight_);
			return std::string(s);
		}

		bool IsValid() const {
			return valid_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			Edge edge(12, 34, 5.67);
			std::cout << edge.ToString() << std::endl;
		}
	};

	bool operator<(const Edge &, const Edge &);
	bool operator>(const Edge &, const Edge &);
	bool operator==(const Edge &, const Edge &);
	bool operator<=(const Edge &, const Edge &);
	bool operator>=(const Edge &, const Edge &);
	bool operator!=(const Edge &, const Edge &);
	int Compare(const Edge &, const Edge &);
}