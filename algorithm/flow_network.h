#pragma once
#include"flow_edge.h"
#include"bag.h"
#include"stdrandom.h"
#include<vector>
#include<iostream>
#include<fstream>

namespace algorithmcpp {
	class FlowNetwork {
	private:
		size_t n_vertices_;
		size_t n_edges_;
		std::vector<Bag<FlowEdge>> adjacencies_;

	public:
		FlowNetwork() = delete;
		FlowNetwork(const FlowNetwork &) = default;
		FlowNetwork(FlowNetwork &&) noexcept = default;
		FlowNetwork &operator=(const FlowNetwork &) = default;
		FlowNetwork &operator=(FlowNetwork &&) noexcept = default;
		~FlowNetwork() = default;

		FlowNetwork(size_t n_vertices, size_t n_edges = 0)
			:n_vertices_(n_vertices), n_edges_(n_edges), adjacencies_(std::vector<Bag<FlowEdge>>(n_vertices)) {
			for (size_t i = 0; i < n_edges; ++i) {
				size_t v = StdRandom::Uniform(v);
				size_t w = StdRandom::Uniform(v);
				double capacity = static_cast<double>(StdRandom::Uniform(100));
				AddEdge(FlowEdge(v, w, capacity));
			}
		}

		FlowNetwork(std::istream &in) {
			in >> n_vertices_;
			size_t n_edges;
			in >> n_edges;
			adjacencies_ = std::vector<Bag<FlowEdge>>(n_vertices_);
			for (size_t i = 0; i < n_edges; ++i) {
				size_t v;
				size_t w;
				in >> v;
				in >> w;
				ValidateVertex(v);
				ValidateVertex(w);
				double edge_weight;
				in >> edge_weight;
				AddEdge(FlowEdge(v, w, edge_weight));
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

		void AddEdge(const FlowEdge &e) {
			size_t v = e.From();
			size_t w = e.To();
			ValidateVertex(v);
			ValidateVertex(w);
			++n_edges_;
			adjacencies_[v].Add(e);
			adjacencies_[w].Add(e);
		}

		Bag<FlowEdge> Adj(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v];
		}

		Bag<FlowEdge> &Adj(size_t v) {
			ValidateVertex(v);
			return adjacencies_[v];
		}

		Bag<FlowEdge> Edges() const {
			Bag<FlowEdge> list;
			for (size_t v = 0; v < n_vertices_; ++v) {
				for (const FlowEdge &e : Adj(v)) {
					if (e.To() != v) {
						list.Add(e);
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
				for (const FlowEdge &e : adjacencies_[v]) {
					if (e.To() != v) {
						s += e.ToString() + " ";
					}				
				}
				s += "\n";
			}
			return s;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyEWG.txt");
			FlowNetwork G(in);
			std::cout << G.ToString();
		}
	};
}