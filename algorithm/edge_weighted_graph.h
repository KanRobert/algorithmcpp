#pragma once
#include"bag.h"
#include"edge.h"
#include"stdrandom.h"
#include<iostream>
#include<vector>
#include<stdexcept>
#include<string>
#include<fstream>
#include<cmath>

namespace algorithmcpp {
	class EdgeWeightedGraph {
	private:
		size_t n_vertices_ = 0;
		size_t n_edges_ = 0;
		std::vector<Bag<Edge>> adjacencies_ = std::vector<Bag<Edge>>(n_vertices_);

	public:
		EdgeWeightedGraph() = delete;
		EdgeWeightedGraph(const EdgeWeightedGraph &) = default;
		EdgeWeightedGraph(EdgeWeightedGraph &&) noexcept = default;
		EdgeWeightedGraph &operator=(const EdgeWeightedGraph &) = default;
		EdgeWeightedGraph &operator=(EdgeWeightedGraph &&) noexcept = default;
		~EdgeWeightedGraph() = default;

		EdgeWeightedGraph(size_t v) :n_vertices_(v) {}

		EdgeWeightedGraph(size_t n_vertices, size_t n_edges):n_vertices_(n_vertices),n_edges_(n_edges) {
			for (size_t i = 0; i < n_edges_; ++i) {
				size_t v =StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices);
				double edgeWeight = std::round(100 * StdRandom::Uniform()) / 100;
				AddEdge(Edge(v, w, edgeWeight));
			}
		}

		EdgeWeightedGraph(std::istream &in) {
			in >> n_vertices_;
			adjacencies_ = std::vector<Bag<Edge>>(n_vertices_);
			size_t n_edges_;
			in >> n_edges_;
			for (size_t i = 0; i != n_edges_; ++i) {
				size_t v;
				size_t w;
				in >> v;
				in >> w;
				double edgeWeight;
				in >> edgeWeight;
				AddEdge(Edge(v,w,edgeWeight));
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

		void AddEdge(const Edge &e) {
			size_t v = e.Either();
			size_t w = e.Other(v);
			ValidateVertex(v);
			ValidateVertex(w);
			++n_edges_;
			adjacencies_[v].Add(e);
			adjacencies_[w].Add(e);
		}

		Bag<Edge> Adj(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v];
		}

		size_t Degree(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v].Size();
		}

		Bag<Edge> Edges() const {
			Bag<Edge> list;
			for (size_t v = 0; v < n_vertices_; ++v) {
				size_t selfLoops = 0;
				for (Edge e : Adj(v)) {
					if (e.Other(v) > v) {
						list.Add(e);
					}
					else if (e.Other(v) == v) {
						if (selfLoops % 2 == 0) list.Add(e);
						++selfLoops;
					}
				}
			}
			return list;
		}

		std::string ToString() const {
			std::string s;
			s += std::to_string(n_vertices_) + " vertices, " + std::to_string(n_edges_) + " edges \n";
			for (size_t v = 0; v < n_vertices_; ++v) {
				s += std::to_string(v) + ": ";
				for (Edge e : adjacencies_[v]) {
					s += e.ToString() + " ";
				}
				s += "\n";
			}
			return s;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWG.txt");
			EdgeWeightedGraph G(in);
			std::cout << G.ToString();
		}

	};
}