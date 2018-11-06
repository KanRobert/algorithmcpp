#pragma once
#include"bag.h"
#include<iostream>
#include<vector>
#include<stdexcept>
#include<string>
#include<fstream>

namespace algorithmcpp {
	class Graph {
	private:
		size_t n_vertices_=0;
		size_t n_edges_=0;
		std::vector<Bag<size_t>> adjacencies_=std::vector<Bag<size_t>>(n_vertices_);

	public:
		Graph() = delete;
		Graph(const Graph &) = default;
		Graph(Graph &&) noexcept = default;
		Graph &operator=(const Graph &) = default;
		Graph &operator=(Graph &&) noexcept = default;
		~Graph() = default;

		Graph(size_t v) :n_vertices_(v){}
		Graph(std::istream &in){
			in >> n_vertices_;
			adjacencies_= std::vector<Bag<size_t>>(n_vertices_);
			size_t n_edges;
			in >> n_edges;
			for (size_t i = 0; i !=n_edges_; ++i) {
				size_t v;
				size_t w;
				in >> v;
				in >> w;
				ValidateVertex(v);
				ValidateVertex(w);
				AddEdge(v, w);
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

		void AddEdge(size_t v, size_t w) {
			ValidateVertex(v);
			ValidateVertex(w);
			++n_edges_;
			adjacencies_[v].Add(w);
			adjacencies_[w].Add(v);
		}

		Bag<size_t> Adj(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v];
		}

		size_t Degree(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v].Size();
		}

		std::string ToString() const {
			std::string s;
			s += std::to_string(n_vertices_) + " vertices, " + std::to_string(n_edges_) + " edges \n";
			for (size_t v = 0; v < n_vertices_; ++v) {
				s += std::to_string(v) + ": ";
				for (size_t w : adjacencies_[v]) {
					s += std::to_string(w) + " ";
				}
				s += "\n";
			}
			return s;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyG.txt");
			Graph G(in);
			std::cout << G.ToString();
		}

	};
}