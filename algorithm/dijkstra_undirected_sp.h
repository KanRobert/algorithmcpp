#pragma once
#include"edge.h"
#include"index_min_pq.h"
#include"edge_weighted_graph.h"
#include"stack.h"
#include<limits>
#include<vector>
#include<stdexcept>
#include<fstream>
#include<iostream>
#include<iomanip>

namespace algorithmcpp {
	class DijkstraUndirectedSP {
	private:
		std::vector<double> dist_to_;
		std::vector<Edge> edge_to_;
		IndexMinPQ<double> pq_;

	public:
		DijkstraUndirectedSP() = delete;
		DijkstraUndirectedSP(const DijkstraUndirectedSP&) = default;
		DijkstraUndirectedSP(DijkstraUndirectedSP &&) noexcept = default;
		DijkstraUndirectedSP &operator=(const DijkstraUndirectedSP &) = default;
		DijkstraUndirectedSP &operator=(DijkstraUndirectedSP &&) noexcept = default;
		~DijkstraUndirectedSP() = default;

		DijkstraUndirectedSP(const EdgeWeightedGraph &G, size_t s) :
			dist_to_(std::vector<double>(G.V())),edge_to_(std::vector<Edge>(G.V())),pq_(IndexMinPQ<double>(G.V())){
			for (const Edge &e : G.Edges()) {
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
				for (const Edge &e : G.Adj(v)) {
					Relax(e, v);
				}
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t n_vertices = dist_to_.size();
			if (v >= n_vertices)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices - 1));
		}

		void Relax(const Edge &e, size_t v) {
			size_t w = e.Other(v);
			if (dist_to_[w] > dist_to_[v] + e.Weight()) {
				dist_to_[w] = dist_to_[v] + e.Weight();
				edge_to_[w] = e;
				if (pq_.Contains(w)) pq_.DecreaseKey(w,dist_to_[w]);
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

		Stack<Edge> PathTo(size_t v) const {
			ValidateVertex(v);
			if (!HasPathTo(v)) return Stack<Edge>();
			Stack<Edge> path;
			size_t x = v;
			for (Edge e = edge_to_[v]; e.IsValid(); e = edge_to_[x]) {
				path.Push(e);
				x = e.Other(x);
			}
			return path;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWG.txt");
			EdgeWeightedGraph G(in);
			size_t s = 6;
			DijkstraUndirectedSP sp(G, s);
			for (size_t t = 0; t < G.V(); ++t) {
				if (sp.HasPathTo(t)) {
					std::cout << s << " to " << t << " (" <<sp.DistTo(t) << ")  ";
					for (const Edge &e : sp.PathTo(t)) {
						std::cout << e.ToString()<< "  ";
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
