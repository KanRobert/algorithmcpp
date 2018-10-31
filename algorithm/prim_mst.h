#pragma once
#include"edge.h"
#include"index_min_pq.h"
#include"edge_weighted_graph.h"
#include"queue.h"
#include<vector>
#include<limits>

#pragma push_macro("max")
#undef max

namespace algorithmcpp {
	class PrimMST {
	private:
		std::vector<Edge> edge_to_;
		std::vector<double> dist_to_;
		std::vector<bool> marked_;
		IndexMinPQ<double> pq_;

	public:
		PrimMST() = delete;
		PrimMST(const PrimMST&) = default;
		PrimMST(PrimMST &&) noexcept = default;
		PrimMST &operator=(const PrimMST &) = default;
		PrimMST &operator=(PrimMST &&) noexcept = default;
		~PrimMST() = default;

		PrimMST(const EdgeWeightedGraph &G) :
			edge_to_(std::vector<Edge>(G.V())),dist_to_(std::vector<double>(G.V(),std::numeric_limits<double>::max())),marked_(std::vector<bool>(G.V())),pq_(IndexMinPQ<double>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (!marked_[v]) {
					Prim(G, v);
				}
			}
		}

	private:
		void Prim(const EdgeWeightedGraph &G, size_t s) {
			dist_to_[s] = 0.0;
			pq_.Insert(s, dist_to_[s]);
			while (!pq_.IsEmpty()) {
				size_t v = pq_.DelMin();
				Scan(G, v);
			}
		}

		void Scan(const EdgeWeightedGraph &G, size_t v) {
			marked_[v] = true;
			for (const Edge &e : G.Adj(v)) {
				size_t w = e.Other(v);
				if (marked_[w]) continue;
				if (e.Weight() < dist_to_[w]) {
					dist_to_[w] = e.Weight();
					edge_to_[w] = e;
					if (pq_.Contains(w)) pq_.DecreaseKey(w, dist_to_[w]);
					else pq_.Insert(w, dist_to_[w]);
				}
			}
		}

	public:

		Queue<Edge> Edges() {
			Queue<Edge> mst_;
			for (size_t v = 0; v < edge_to_.size(); ++v) {
				Edge e = edge_to_[v];
				if (e.Other(v) != v) {
					mst_.Enqueue(e);
				}
			}
			return mst_;
		}

		double Weight() {
			double total_weight_ = 0.0;
			for (const Edge &e : Edges()) {
				total_weight_ += e.Weight();
			}
			return total_weight_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWG.txt");
			EdgeWeightedGraph G(in);
			PrimMST mst_(G);
			for (const Edge &e : mst_.Edges()) {
				std::cout << e.ToString() << "\n";
			}
			std::cout << mst_.Weight() << "\n";
		}
	};
}

#pragma pop_macro("max")