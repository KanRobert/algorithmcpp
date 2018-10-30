#pragma once
#include<stdexcept>
#include<string>
#include<iostream>

namespace algorithmcpp {
	class DirectedEdge {
		friend bool operator<(const DirectedEdge &, const DirectedEdge &);
		friend bool operator>(const DirectedEdge &, const DirectedEdge &);
		friend bool operator==(const DirectedEdge &, const DirectedEdge &);
		friend bool operator<=(const DirectedEdge &, const DirectedEdge &);
		friend bool operator>=(const DirectedEdge &, const DirectedEdge &);
		friend int Compare(const DirectedEdge &, const DirectedEdge &);

	private:
		size_t v_ = 0;
		size_t w_ = 0;
		double edge_weight_ = 0.0;

	public:
		DirectedEdge() = default;
		DirectedEdge(const DirectedEdge &) = default;
		DirectedEdge(DirectedEdge &&) noexcept = default;
		DirectedEdge &operator=(const DirectedEdge &) = default;
		DirectedEdge &operator=(DirectedEdge &&) noexcept = default;
		~DirectedEdge() = default;

		DirectedEdge(size_t v, size_t w, double edge_weight) :
			v_(v), w_(w), edge_weight_(edge_weight) {}

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
			std::string s;
			s += std::to_string(v_) + "->" + std::to_string(w_) + " " + std::to_string(edge_weight_);
			return s;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			DirectedEdge edge(12, 34, 5.67);
			std::cout << edge.ToString() << std::endl;
		}
	};

	bool operator<(const DirectedEdge &, const DirectedEdge &);
	bool operator>(const DirectedEdge &, const DirectedEdge &);
	bool operator==(const DirectedEdge &, const DirectedEdge &);
	bool operator<=(const DirectedEdge &, const DirectedEdge &);
	bool operator>=(const DirectedEdge &, const DirectedEdge &);
	int Compare(const DirectedEdge &, const DirectedEdge &);
}