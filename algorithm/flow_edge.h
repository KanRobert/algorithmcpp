#pragma once
#pragma warning (disable : 4996)
#include<stdexcept>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<iostream>

namespace algorithmcpp {
	class FlowEdge {
	private:
		static constexpr double kfloat_point_epsilon_ = 1e-10;

		size_t v_=0;
		size_t w_=0;
		double capacity_ = 0.0;
		double flow_ = 0.0;
		bool valid_ = false;

	public:
		FlowEdge() = default;
		FlowEdge(const FlowEdge &) = default;
		FlowEdge(FlowEdge &&) noexcept = default;
		FlowEdge &operator=(const FlowEdge &) = default;
		FlowEdge &operator=(FlowEdge &&) noexcept = default;
		~FlowEdge() = default;

		FlowEdge(size_t v, size_t w, double capacity,double flow=0.0) :v_(v), w_(w), capacity_(capacity), flow_(flow), valid_(true) {
			if (capacity_ < 0.0) throw std::invalid_argument("edge capacity must be non-negative");
			if (flow_ < 0.0) throw std::invalid_argument("flow must be non-negative");
			if (flow_ > capacity_) throw std::invalid_argument("flow exceeds capacity");
		}

		bool IsValid() const {
			return valid_;
		}

		size_t From() const {
			return v_;
		}

		size_t To() const {
			return w_;
		}

		double Capacity() const {
			return capacity_;
		}

		double Flow() const {
			return flow_;
		}

		size_t Other(size_t vertex) const {
			if (vertex == v_) return w_;
			else if (vertex == w_) return v_;
			else throw std::invalid_argument("invalid endpoint");
		}

		double ResidualCapacityTo(size_t vertex) const {
			if (vertex == v_) return flow_;
			else if (vertex == w_) return capacity_-flow_;
			else throw std::invalid_argument("invalid endpoint");
		}

		void AddResidualFlowTo(size_t vertex, double delta) {
			if (delta < 0.0) throw std::invalid_argument("Delta must be nonnegative");
			if (vertex == v_) flow_ -= delta;
			else if (vertex == w_) flow_ += delta;
			else throw std::invalid_argument("invalid endpoint");

			if (std::abs(flow_) <= kfloat_point_epsilon_) flow_ = 0;
			if (std::abs(flow_ - capacity_) <= kfloat_point_epsilon_) flow_ = capacity_;

			if (flow_ < 0.0) throw std::invalid_argument("flow is negative");
			if (flow_ > capacity_) throw std::invalid_argument("flow exceeds capacity");
		}

		std::string ToString() const {
			char s[32];
			std::sprintf(s, "%u->%u %.2f/%.2f", static_cast<unsigned>(v_), static_cast<unsigned>(w_), flow_, capacity_);
			return std::string(s);
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			FlowEdge e(12, 23, 4.56);
			std::cout << e.ToString() << std::endl;
		}
	};
}