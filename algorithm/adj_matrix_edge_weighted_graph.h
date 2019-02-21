#pragma once
#include"directed_edge.h"
#include"stdrandom.h"
#include"bag.h"
#include<vector>
#include<stdexcept>
#include<string>
#include<iostream>

namespace algorithmcpp {
	class AdjMatrixEdgeWeightedDigraph {
	private:
		size_t n_vertices_;
		size_t n_edges_=0;
		std::vector<std::vector<DirectedEdge>> adj_;

	public:
		AdjMatrixEdgeWeightedDigraph() = delete;
		AdjMatrixEdgeWeightedDigraph(const AdjMatrixEdgeWeightedDigraph&) = default;
		AdjMatrixEdgeWeightedDigraph(AdjMatrixEdgeWeightedDigraph &&) noexcept = default;
		AdjMatrixEdgeWeightedDigraph &operator=(const AdjMatrixEdgeWeightedDigraph &) = default;
		AdjMatrixEdgeWeightedDigraph &operator=(AdjMatrixEdgeWeightedDigraph &&) noexcept = default;
		~AdjMatrixEdgeWeightedDigraph() = default;

		AdjMatrixEdgeWeightedDigraph(size_t n_vertices,size_t n_edges=0) :
			n_vertices_(n_vertices) {
			adj_.resize(n_vertices_);
			if (n_edges_ > n_vertices_*n_vertices_) throw std::invalid_argument("too many edges");
			for (size_t i = 0; i < n_vertices_; ++i) {
				adj_[i].resize(n_vertices_);
			}
			while(n_edges_< n_edges) {
				size_t v = StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices_);
				double weight = std::round(100 * StdRandom::Uniform()) / 100.0;
				AddEdge(DirectedEdge(v, w, weight));
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

		void AddEdge(DirectedEdge e) {
			size_t v = e.From();
			size_t w = e.To();
			ValidateVertex(v);
			ValidateVertex(w);
			if (!adj_[v][w].IsValid()) {
				++n_edges_;
				adj_[v][w] = e;
			}
		}

		Bag<DirectedEdge> Adj(size_t v) const {
			ValidateVertex(v);
			Bag<DirectedEdge> ret;
			for (size_t i = 0; i < adj_[v].size(); ++i) {
				if (adj_[v][i].IsValid()) {
					ret.Add(adj_[v][i]);
				}
			}
			return ret;
		}

		std::string ToString() const {
			std::string s;
			s += std::to_string(n_vertices_) + " " + std::to_string(n_edges_) + "\n";
			for (size_t v = 0; v < n_vertices_; ++v) {
				s += std::to_string(v) + ": ";
				for (DirectedEdge e : Adj(v)) {
					s += e.ToString() + " ";
				}
				s += "\n";
			}
			return s;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			size_t n_vetices = 5;
			size_t n_edges = 10;
			AdjMatrixEdgeWeightedDigraph G(n_vetices, n_edges);
			std::cout << G.ToString() << std::endl;
		}
	};
}
