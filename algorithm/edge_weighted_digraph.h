#pragma once
#include"bag.h"
#include"directed_edge.h"
#include"stdrandom.h"
#include<vector>
#include<fstream>
#include<iostream>

namespace algorithmcpp {
	class EdgeWeightedDigraph {
	private:
		size_t n_vertices_ = 0;
		size_t n_edges_ = 0;
		std::vector<Bag<DirectedEdge>> adjacencies_ = std::vector<Bag<DirectedEdge>>(n_vertices_);
		std::vector<size_t> n_in_edges_=std::vector<size_t>(n_vertices_);
	public:
		EdgeWeightedDigraph() = delete;
		EdgeWeightedDigraph(const EdgeWeightedDigraph &) = default;
		EdgeWeightedDigraph(EdgeWeightedDigraph &&) noexcept = default;
		EdgeWeightedDigraph &operator=(const EdgeWeightedDigraph &) = default;
		EdgeWeightedDigraph &operator=(EdgeWeightedDigraph &&) noexcept = default;
		~EdgeWeightedDigraph() = default;

		EdgeWeightedDigraph(size_t n_vertices) :n_vertices_(n_vertices) {}

		EdgeWeightedDigraph(size_t n_vertices, size_t n_edges) :n_vertices_(n_vertices), n_edges_(n_edges) {
			for (size_t i = 0; i < n_edges_; ++i) {
				size_t v = StdRandom::Uniform(v);
				size_t w = StdRandom::Uniform(v);
				double edge_weight = std::round(100 * StdRandom::Uniform()) / 100;
				AddEdge(DirectedEdge(v, w, edge_weight));
			}
		}

		EdgeWeightedDigraph(std::istream &in) {
			in >> n_vertices_;
			adjacencies_ = std::vector<Bag<DirectedEdge>>(n_vertices_);
			n_in_edges_ = std::vector<size_t>(n_vertices_);
			size_t n_edges;
			in >> n_edges;
			for (size_t i = 0; i != n_edges; ++i) {
				size_t v;
				size_t w;
				in >> v;
				in >> w;
				ValidateVertex(v);
				ValidateVertex(w);
				double edgeWeight;
				in >> edgeWeight;
				AddEdge(DirectedEdge(v, w, edgeWeight));
			}
		}



	private:
		void ValidateVertex(size_t v) const {
			if (v >= n_vertices_)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices_ - 1));
		}

	public:
		size_t V() const {
			return n_vertices_;
		}

		size_t E() const {
			return n_edges_;
		}

		void AddEdge(const DirectedEdge &e) {
			size_t v = e.From();
			size_t w = e.To();
			ValidateVertex(v);
			ValidateVertex(w);
			++n_edges_;
			adjacencies_[v].Add(e);
			++n_in_edges_[w];
		}

		Bag<DirectedEdge> Adj(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v];
		}

		size_t Outdegree(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v].Size();
		}

		size_t Indegree(size_t v) const {
			ValidateVertex(v);
			return n_in_edges_[v];
		}

		Bag<DirectedEdge> Edges() const {
			Bag<DirectedEdge> list;
			for (size_t v = 0; v < n_vertices_; ++v) {
				for (const DirectedEdge &e : Adj(v)) {
					list.Add(e);
				}
			}
			return list;
		}

		std::string ToString() const {
			std::string s;
			s += std::to_string(n_vertices_) + " vertices, " + std::to_string(n_edges_) + " edges \n";
			for (size_t v = 0; v < n_vertices_; ++v) {
				s += std::to_string(v) + ": ";
				for (const DirectedEdge &e : adjacencies_[v]) {
					s += e.ToString() + " ";
				}
				s += "\n";
			}
			return s;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWG.txt");
			EdgeWeightedDigraph G(in);
			std::cout << G.ToString();
		}

	};

}