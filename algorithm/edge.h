#pragma once
#include<stdexcept>
#include<string>
#include<iostream>

namespace algorithmcpp {
	class Edge {
		friend bool operator<(const Edge &, const Edge &);
		friend bool operator>(const Edge &, const Edge &);
		friend bool operator==(const Edge &, const Edge &);
		friend bool operator<=(const Edge &, const Edge &);
		friend bool operator>=(const Edge &, const Edge &);
		friend int Compare(const Edge &, const Edge &);

	private:
		size_t v_=0;
		size_t w_=0;
		double edge_weight_=0.0;

	public:
		Edge() = default;
		Edge(const Edge &) = default;
		Edge(Edge &&) noexcept = default;
		Edge &operator=(const Edge &) = default;
		Edge &operator=(Edge &&) noexcept = default;
		~Edge() = default;

		Edge(size_t v,size_t w,double edge_weight):
			v_(v),w_(w),edge_weight_(edge_weight){}

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
			std::string s;
			s += std::to_string(v_) + "-" + std::to_string(w_) + " " + std::to_string(edge_weight_);
			return s;
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
	int Compare(const Edge &, const Edge &);
}