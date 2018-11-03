#pragma once
#include"directed_edge.h"
#include"queue.h"
#include"stack.h"
#include"edge_weighted_digraph.h"
#include"edge_weighted_directed_cycle.h"
#include<vector>
#include<limits>
#include<stdexcept>
#include<iomanip>

namespace algorithmcpp {
	class BellmanFordSP {
	private:
		std::vector<double> dist_to_;
		std::vector<DirectedEdge> edge_to_;
		std::vector<bool> on_queue_;
		Queue<size_t> queue_;
		size_t cost_=0;
		Stack<DirectedEdge> cycle_;

	public:
		BellmanFordSP() = delete;
		BellmanFordSP(const BellmanFordSP&) = default;
		BellmanFordSP(BellmanFordSP &&) noexcept = default;
		BellmanFordSP &operator=(const BellmanFordSP &) = default;
		BellmanFordSP &operator=(BellmanFordSP &&) noexcept = default;
		~BellmanFordSP() = default;

		BellmanFordSP(const EdgeWeightedDigraph &G, size_t s) :
			dist_to_(std::vector<double>(G.V(), std::numeric_limits<double>::max())), edge_to_(std::vector<DirectedEdge>(G.V())), on_queue_(std::vector<bool>(G.V())) {
			dist_to_[s] = 0.0;
			queue_.Enqueue(s);
			on_queue_[s] = true;
			while (!queue_.IsEmpty() && !HasNegativeCycle()) {
				size_t v = queue_.Dequeue();
				on_queue_[v] = false;
				Relax(G, v);
			}
		}

	private:
		void Relax(const EdgeWeightedDigraph &G, size_t v) {
			for (const DirectedEdge &e : G.Adj(v)) {
				size_t w = e.To();
				if (dist_to_[w] > dist_to_[v] + e.Weight()) {
					dist_to_[w] = dist_to_[v] + e.Weight();
					edge_to_[w] = e;
					if (!on_queue_[w]) {
						queue_.Enqueue(w);
						on_queue_[w] = true;
					}
				}
				if (cost_++ %G.V() == 0) {
					FindNegativeCycle();
					if (HasNegativeCycle()) return;
				}
			}
		}

		void FindNegativeCycle() {
			size_t n_vertices = edge_to_.size();
			EdgeWeightedDigraph spt(n_vertices);
			for (size_t v = 0; v < n_vertices; ++v) {
				if (edge_to_[v].IsValid()) {
					spt.AddEdge(edge_to_[v]);
				}
			}
			EdgeWeightedDirectedCycle finder(spt);
			cycle_ = finder.Cycle();
		}

		void ValidateVertex(size_t v) const {
			size_t n_vertices = dist_to_.size();
			if (v >= n_vertices)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices - 1));
		}

	public:
		bool HasNegativeCycle() const {
			return !cycle_.IsEmpty();
		}

		Stack<DirectedEdge> NegativeCycle() const {
			return cycle_;
		}

		double DistTo(size_t v) const {
			ValidateVertex(v);
			if (HasNegativeCycle()) {
				throw std::logic_error("Negative cost cycle exists");
			}
			return dist_to_[v];
		}

		bool HasPathTo(size_t v) const {
			ValidateVertex(v);
			return dist_to_[v] != std::numeric_limits<double>::max();
		}

		Stack<DirectedEdge> PathTo(size_t v) const {
			ValidateVertex(v);
			if (HasNegativeCycle()) {
				throw std::logic_error("Negative cost cycle exists");
			}
			if (!HasPathTo(v)) return Stack<DirectedEdge>();
			Stack<DirectedEdge> path;
			for (DirectedEdge e = edge_to_[v]; e.IsValid(); e = edge_to_[e.From()]) {
				path.Push(e);
			}
			return path;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWDn.txt");
			EdgeWeightedDigraph G(in);
			size_t s = 0;
			BellmanFordSP sp(G, s);
			if (sp.HasNegativeCycle()) {
				for (DirectedEdge e : sp.NegativeCycle()) {
					std::cout << e.ToString() << "\n";
				}
			}
			else {
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
		}

	};
}