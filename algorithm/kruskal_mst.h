#pragma once
#pragma warning (disable : 4996)
#include"queue.h"
#include"edge.h"
#include"edge_weighted_graph.h"
#include"min_pq.h"
#include"uf.h"
#include<fstream>
#include<iostream>


namespace algorithmcpp {
	class KruskalMST {
	private:
		double total_weight_=0;
		Queue<Edge> mst_;

	public:
		KruskalMST() = delete;
		KruskalMST(const KruskalMST&) = default;
		KruskalMST(KruskalMST &&) noexcept = default;
		KruskalMST &operator=(const KruskalMST &) = default;
		KruskalMST &operator=(KruskalMST &&) noexcept = default;
		~KruskalMST() = default;

		KruskalMST(const EdgeWeightedGraph &G) {
			MinPQ<Edge> pq;
			for (const Edge &e : G.Edges()) {
				pq.Insert(e);
			}

			UF uf(G.V());
			while (!pq.IsEmpty() && mst_.Size() < G.V() - 1) {
				Edge e = pq.DelMin();
				size_t v = e.Either();
				size_t w = e.Other(v);
				if (!uf.Connected(v, w)) {
					uf.UnionSite(v, w);
					mst_.Enqueue(e);
					total_weight_ += e.Weight();
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
			KruskalMST mst_(G);
			for (const Edge &e : mst_.Edges()) {
				std::cout << e.ToString() << "\n";
			}
			std::cout << mst_.Weight() << "\n";
		}
	};
}