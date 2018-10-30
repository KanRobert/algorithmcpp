#pragma warning (disable : 4996)
#include"queue.h"
#include"edge.h"
#include"edge_weighted_graph.h"
#include"min_pq.h"
#include<fstream>
#include<iostream>
#include<vector>

namespace algorithmcpp {
	class LazyPrimMST {
	private:
		double total_weight_ = 0;
		Queue<Edge> mst_;
		std::vector<bool> marked_;
		MinPQ<Edge> pq_;

	public:
		LazyPrimMST() = delete;
		LazyPrimMST(const LazyPrimMST&) = default;
		LazyPrimMST(LazyPrimMST &&) noexcept = default;
		LazyPrimMST &operator=(const LazyPrimMST &) = default;
		LazyPrimMST &operator=(LazyPrimMST &&) noexcept = default;
		~LazyPrimMST() = default;

		LazyPrimMST(const EdgeWeightedGraph &G) :
			marked_(std::vector<bool>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (!marked_[v]) {
					Prim(G, v);
				}
			}
		}

	private:
		void Prim(const EdgeWeightedGraph &G, size_t s) {
			Scan(G, s);
			while (!pq_.IsEmpty()) {
				Edge e = pq_.DelMin();
				size_t v = e.Either();
				size_t w = e.Other(v);
				if (marked_[v] && marked_[w]) continue;
				mst_.Enqueue(e);
				total_weight_ += e.Weight();
				if (!marked_[v]) Scan(G, v);
				if (!marked_[w]) Scan(G, w);
			}
		}

		void Scan(const EdgeWeightedGraph &G, size_t v) {
			marked_[v] = true;
			for (const Edge &e : G.Adj(v)) {
				if (!marked_[e.Other(v)]) {
					pq_.Insert(e);
				}
			}
		}

	public:
		Queue<Edge> Edges() {
			return mst_;
		}

		double Weight() {
			return total_weight_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWG.txt");
			EdgeWeightedGraph G(in);
			LazyPrimMST mst_(G);
			for (const Edge &e : mst_.Edges()) {
				std::cout << e.ToString() << "\n";
			}
			std::cout << mst_.Weight() << "\n";
		}
	};
}