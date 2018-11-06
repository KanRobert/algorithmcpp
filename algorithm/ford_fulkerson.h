#pragma once
#include"flow_edge.h"
#include"flow_network.h"
#include"queue.h"
#include<vector>
#include<stdexcept>
#include<cstdlib>
#include<limits>
#include<algorithm>
#include<fstream>
#include<functional>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

namespace algorithmcpp {
	class FordFulkerson {
	private:
		static FlowEdge flow_edge_;
		static constexpr double kfloat_point_epsilon_ = 1e-10;

		size_t n_vertices_;
		double value_=0.0;
		std::vector<bool> marked_;
		std::vector<std::reference_wrapper<FlowEdge>> edge_to_;

	public:
		FordFulkerson() = delete;
		FordFulkerson(const FordFulkerson &) = default;
		FordFulkerson(FordFulkerson &&) noexcept = default;
		FordFulkerson &operator=(const FordFulkerson &) = default;
		FordFulkerson &operator=(FordFulkerson &&) noexcept = default;
		~FordFulkerson() = default;

		FordFulkerson(FlowNetwork &G, size_t s, size_t t) :
			n_vertices_(G.V()), edge_to_(std::vector<std::reference_wrapper<FlowEdge>>(G.V(),flow_edge_)) {
			ValidateVertex(s);
			ValidateVertex(t);
			if (s == t) throw std::invalid_argument("source equals sink");
			while (HasAugmentingPath(G, s, t)) {
				double bottle = std::numeric_limits<double>::max();
				for (size_t v = t; v != s; v = edge_to_[v].get().Other(v)) {
					bottle = std::min(bottle, edge_to_[v].get().ResidualCapacityTo(v));
				}
				for (size_t v = t; v != s; v = edge_to_[v].get().Other(v)) {
					edge_to_[v].get().AddResidualFlowTo(v, bottle);
				}
				value_ += bottle;
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			if (v >= n_vertices_)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices_ - 1));
		}

		bool HasAugmentingPath(FlowNetwork &G, size_t s, size_t t) {
			marked_ = std::vector<bool>(G.V());
			Queue<size_t> queue;
			queue.Enqueue(s);
			marked_[s] = true;
			while (!queue.IsEmpty() && !marked_[t]) {
				size_t v = queue.Dequeue();
				for (FlowEdge &e : G.Adj(v)) {
					size_t w = e.Other(v);
					if (e.ResidualCapacityTo(w) > 0.0 && !marked_[w]) {
						edge_to_[w] = e;
						marked_[w] = true;
						queue.Enqueue(w);
					}
				}
			}
			return marked_[t];

		}

	public:
		double Value() const {
			return value_;
		}

		bool InCut(size_t v) const {
			ValidateVertex(v);
			return marked_[v];
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWG.txt");
			FlowNetwork G(in);
			std::cout << G.ToString();
			size_t s = 0;
			size_t t = G.V()-1;
			FordFulkerson maxflow(G, s, t);
			std::cout << "Max flow from " << s << " to " << t<<"\n";
			for (size_t v = 0; v < G.V(); ++v) {
				for (FlowEdge e : G.Adj(v)) {
					if ((v == e.From()) && e.Flow() > 0) {
						std::cout << "  " << e.ToString()<<"\n";
					}
				}
			}

			std::cout << "Min Cut: ";
			for (size_t v = 0; v < G.V(); ++v) {
				if (maxflow.InCut(v)) {
					std::cout << v << " ";
				}
			}
			std::cout << "\n";
			std::cout << "Max flow value = Min cut capacity = " << maxflow.Value() << std::endl;
		}
	};
}

#pragma pop_macro("max")
#pragma pop_macro("min")