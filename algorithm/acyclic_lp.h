#pragma once
#include"directed_edge.h"
#include"edge_weighted_digraph.h"
#include"topological.h"
#include"stack.h"
#include<vector>
#include<limits>
#include<stdexcept>

namespace algorithmcpp {
	class AcyclicLP {
	private:
		std::vector<double> dist_to_;
		std::vector<DirectedEdge> edge_to_;

	public:
		AcyclicLP() = delete;
		AcyclicLP(const AcyclicLP&) = default;
		AcyclicLP(AcyclicLP &&) noexcept = default;
		AcyclicLP &operator=(const AcyclicLP &) = default;
		AcyclicLP &operator=(AcyclicLP &&) noexcept = default;
		~AcyclicLP() = default;

		AcyclicLP(const EdgeWeightedDigraph &G, size_t s) :
			dist_to_(std::vector<double>(G.V(), std::numeric_limits<double>::min())), edge_to_(std::vector<DirectedEdge>(G.V())) {
			ValidateVertex(s);
			dist_to_[s] = 0.0;
			Topological topological(G);
			if (!topological.HasOrder())
				throw std::invalid_argument("Digraph is not acyclic.");
			for (size_t v : topological.Order()) {
				for (const DirectedEdge &e : G.Adj(v)) {
					Relax(e);
				}
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t n_vertices = dist_to_.size();
			if (v >= n_vertices)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices - 1));
		}

		void Relax(const DirectedEdge &e) {
			size_t v = e.From();
			size_t w = e.To();
			if (dist_to_[w] < dist_to_[v] + e.Weight()) {
				dist_to_[w] = dist_to_[v] + e.Weight();
				edge_to_[w] = e;
			}
		}

	public:
		double DistTo(size_t v) const {
			ValidateVertex(v);
			return dist_to_[v];
		}

		bool HasPathTo(size_t v) const {
			ValidateVertex(v);
			return dist_to_[v] != std::numeric_limits<double>::min();
		}

		Stack<DirectedEdge> PathTo(size_t v) const {
			ValidateVertex(v);
			if (!HasPathTo(v)) return Stack<DirectedEdge>();
			Stack<DirectedEdge> path;
			for (DirectedEdge e = edge_to_[v]; e.IsValid(); e = edge_to_[e.From()]) {
				path.Push(e);
			}
			return path;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWDAG.txt");
			EdgeWeightedDigraph G(in);
			size_t s = 5;
			AcyclicLP sp(G, s);
			for (size_t t = 0; t < G.V(); ++t) {
				if (sp.HasPathTo(t)) {
					std::cout << s << " to " << t << " (" << std::fixed << std::setprecision(2) << sp.DistTo(t) << ")  ";
					for (const DirectedEdge &e : sp.PathTo(t)) {
						std::cout << e.ToString() << "  ";
					}
					std::cout << "\n";
				}
				else {
					std::cout << s << " to " << t << "  no path\n";
				}
			}
		}
	};
}