#pragma once
#pragma warning (disable : 4996)
#include<stdexcept>
#include<string>
#include<iostream>

namespace algorithmcpp {
	class DirectedEdge {
		friend bool operator<(const DirectedEdge &, const DirectedEdge &);
		friend bool operator>(const DirectedEdge &, const DirectedEdge &);
		friend bool operator==(const DirectedEdge &, const DirectedEdge &);
		friend bool operator!=(const DirectedEdge &, const DirectedEdge &);
		friend bool operator<=(const DirectedEdge &, const DirectedEdge &);
		friend bool operator>=(const DirectedEdge &, const DirectedEdge &);
		friend int Compare(const DirectedEdge &, const DirectedEdge &);

	private:
		size_t v_ = 0;
		size_t w_ = 0;
		double edge_weight_ = 0.0;
		bool valid_ = false;

	public:
		DirectedEdge() = default;
		DirectedEdge(const DirectedEdge &) = default;
		DirectedEdge(DirectedEdge &&) noexcept = default;
		DirectedEdge &operator=(const DirectedEdge &) = default;
		DirectedEdge &operator=(DirectedEdge &&) noexcept = default;
		~DirectedEdge() = default;

		DirectedEdge(size_t v, size_t w, double edge_weight) :
			v_(v), w_(w), edge_weight_(edge_weight),valid_(true) {}

		size_t From() const {
			return v_;
		}

		size_t To() const {
			return w_;
		}

		double Weight() const {
			return edge_weight_;
		}

		std::string ToString() const {
			char s[32];
			sprintf(s, "%u->%u %.2f", static_cast<unsigned>(v_), static_cast<unsigned>(w_), edge_weight_);
			return std::string(s);
		}

		bool IsValid() const {
			return valid_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			DirectedEdge edge(12, 34, 5.67);
			std::cout << edge.ToString() << std::endl;
		}
	};

	bool operator<(const DirectedEdge &, const DirectedEdge &);
	bool operator>(const DirectedEdge &, const DirectedEdge &);
	bool operator==(const DirectedEdge &, const DirectedEdge &);
	bool operator!=(const DirectedEdge &, const DirectedEdge &);
	bool operator<=(const DirectedEdge &, const DirectedEdge &);
	bool operator>=(const DirectedEdge &, const DirectedEdge &);
	int Compare(const DirectedEdge &, const DirectedEdge &);
}