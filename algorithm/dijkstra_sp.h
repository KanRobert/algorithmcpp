#pragma once
#include"directed_edge.h"
#include"index_min_pq.h"
#include"edge_weighted_digraph.h"
#include"stack.h"
#include<limits>
#include<vector>
#include<stdexcept>
#include<fstream>
#include<iostream>
#include<iomanip>

namespace algorithmcpp {
	class DijkstraSP {
	private:
		std::vector<double> dist_to_;
		std::vector<DirectedEdge> edge_to_;
		IndexMinPQ<double> pq_;

	public:
		DijkstraSP() = delete;
		DijkstraSP(const DijkstraSP&) = default;
		DijkstraSP(DijkstraSP &&) noexcept = default;
		DijkstraSP &operator=(const DijkstraSP &) = default;
		DijkstraSP &operator=(DijkstraSP &&) noexcept = default;
		~DijkstraSP() = default;

		DijkstraSP(const EdgeWeightedDigraph &G, size_t s) :
			dist_to_(std::vector<double>(G.V())), edge_to_(std::vector<DirectedEdge>(G.V())), pq_(IndexMinPQ<double>(G.V())) {
			for (const DirectedEdge &e : G.Edges()) {
				if (e.Weight() < 0) throw std::invalid_argument("edge " + e.ToString() + "has negative weight");
			}
			ValidateVertex(s);
			for (size_t v = 0; v < G.V(); ++v) {
				dist_to_[v] = std::numeric_limits<double>::max();
			}
			dist_to_[s] = 0.0;
			pq_.Insert(s, dist_to_[s]);
			while (!pq_.IsEmpty()) {
				size_t v = pq_.DelMin();
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
			if (dist_to_[w] > dist_to_[v] + e.Weight()) {
				dist_to_[w] = dist_to_[v] + e.Weight();
				edge_to_[w] = e;
				if (pq_.Contains(w)) pq_.DecreaseKey(w, dist_to_[w]);
				else pq_.Insert(w, dist_to_[w]);
			}
		}

	public:
		double DistTo(size_t v) const {
			ValidateVertex(v);
			return dist_to_[v];
		}

		bool HasPathTo(size_t v) const {
			ValidateVertex(v);
			return dist_to_[v] != std::numeric_limits<double>::max();
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
			std::ifstream in("../file/tinyEWD.txt");
			EdgeWeightedDigraph G(in);
			size_t s = 0;
			DijkstraSP sp(G, s);
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
