#pragma once
#include"queue.h"
#include"digraph.h"
#include"edge_weighted_digraph.h"
#include"directed_edge.h"
#include"symbol_digraph.h"
#include<vector>

namespace algorithmcpp {
	class TopologicalX {
	private:
		std::vector<size_t> rank_;
		Queue<size_t> order_;

	public:
		TopologicalX() = delete;
		TopologicalX(const TopologicalX&) = default;
		TopologicalX(TopologicalX &&) noexcept = default;
		TopologicalX &operator=(const TopologicalX &) = default;
		TopologicalX &operator=(TopologicalX &&) noexcept = default;
		~TopologicalX() = default;

		TopologicalX(const Digraph &G) :rank_(std::vector<size_t>(G.V())) {
			std::vector<size_t> indegree(G.V());
			for (size_t v = 0; v < G.V(); ++v) {
				indegree[v] = G.Indegree(v);
			}
			size_t count = 0;
			Queue<size_t> queue;
			for (size_t v = 0; v < G.V(); ++v) {
				if (indegree[v] == 0) {
					queue.Enqueue(v);
				}
			}
			while(!queue.IsEmpty()){
				size_t v = queue.Dequeue();
				order_.Enqueue(v);
				rank_[v] = count++;
				for (size_t w : G.Adj(v)) {
					--indegree[w];
					if (indegree[w] == 0) {
						queue.Enqueue(w);
					}
				}
			}

			if (count != G.V()) {
				order_ = Queue<size_t>();
			}
		}

		TopologicalX(const EdgeWeightedDigraph &G) :rank_(std::vector<size_t>(G.V())) {
			std::vector<size_t> indegree(G.V());
			for (size_t v = 0; v < G.V(); ++v) {
				indegree[v] = G.Indegree(v);
			}
			size_t count = 0;
			Queue<size_t> queue;
			for (size_t v = 0; v < G.V(); ++v) {
				if (indegree[v] == 0) {
					queue.Enqueue(v);
				}
			}
			while (!queue.IsEmpty()) {
				size_t v = queue.Dequeue();
				order_.Enqueue(v);
				rank_[v] = count++;
				for (const DirectedEdge &e : G.Adj(v)) {
					size_t w = e.To();
					--indegree[w];
					if (indegree[w] == 0) {
						queue.Enqueue(w);
					}
				}
			}

			if (count != G.V()) {
				order_ = Queue<size_t>();
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t V = rank_.size();
			if (v >= V) throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(V - 1));
		}

	public:

		Queue<size_t> Order() const {
			return order_;
		}

		bool HasOrder() const {
			return !order_.IsEmpty();
		}

		int Rank(size_t v) const {
			ValidateVertex(v);
			if (HasOrder()) return static_cast<int>(rank_[v]);
			else return -1;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::string filename("../file/jobs.txt");
			SymbolDigraph sg(filename, '/');
			TopologicalX topologicalx(sg.InDigraph());
			for (size_t v : topologicalx.Order()) {
				std::cout << sg.NameOf(v) << "\n";
			}
		}
	};
}