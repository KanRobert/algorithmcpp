#pragma once
#include"dijkstra_sp.h"
#include"edge_weighted_digraph.h"
#include<vector>

namespace algorithmcpp {
	class DijkstraAllPairsSP {
	private:
		std::vector<DijkstraSP> all_;

	public:
		DijkstraAllPairsSP() = delete;
		DijkstraAllPairsSP(const DijkstraAllPairsSP&) = default;
		DijkstraAllPairsSP(DijkstraAllPairsSP &&) noexcept = default;
		DijkstraAllPairsSP &operator=(const DijkstraAllPairsSP &) = default;
		DijkstraAllPairsSP &operator=(DijkstraAllPairsSP &&) noexcept = default;
		~DijkstraAllPairsSP() = default;

		DijkstraAllPairsSP(const EdgeWeightedDigraph &G) {
			for (size_t v = 0; v < G.V(); ++v) {
				all_.push_back(DijkstraSP(G, v));
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t n_vertices = all_.size();
			if (v >= n_vertices)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices - 1));
		}

	public:
		Stack<DirectedEdge> Path(size_t s, size_t t) const {
			ValidateVertex(s);
			ValidateVertex(t);
			return all_[s].PathTo(t);
		}

		bool HasPath(size_t s, size_t t) const {
			ValidateVertex(s);
			ValidateVertex(t);
			return Dist(s, t) != std::numeric_limits<double>::max();
		}

		double Dist(size_t s, size_t t) const {
			ValidateVertex(s);
			ValidateVertex(t);
			return all_[s].DistTo(t);
		}
	};
}