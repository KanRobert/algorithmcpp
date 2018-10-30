#pragma once
#include"bag.h"
#include<iostream>
#include<vector>
#include<stdexcept>
#include<string>
#include<fstream>

namespace algorithmcpp {
	class Digraph {
	private:
		size_t n_vertices_ = 0;
		size_t n_edges_ = 0;
		std::vector<Bag<size_t>> adjacencies_ = std::vector<Bag<size_t>>(n_vertices_);
		std::vector<size_t> indegrees_=std::vector<size_t>(n_vertices_);

	public:
		Digraph() = delete;
		Digraph(const Digraph &) = default;
		Digraph(Digraph &&) noexcept = default;
		Digraph &operator=(const Digraph &) = default;
		Digraph &operator=(Digraph &&) noexcept = default;
		~Digraph() = default;

		Digraph(size_t v) :n_vertices_(v) {}
		Digraph(std::istream &in) {
			in >> n_vertices_;
			adjacencies_ = std::vector<Bag<size_t>>(n_vertices_);
			indegrees_ = std::vector<size_t>(n_vertices_);
			size_t nEdges;
			in >> nEdges;
			for (size_t i = 0; i != nEdges; ++i) {
				size_t v;
				size_t w;
				in >> v;
				in >> w;
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
			++indegrees_[w];
		}

		Bag<size_t> Adj(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v];
		}

		size_t Outdegree(size_t v) const {
			ValidateVertex(v);
			return adjacencies_[v].Size();
		}

		size_t Indegree(size_t v) const {
			ValidateVertex(v);
			return indegrees_[v];
		}

		Digraph Reverse() const {
			Digraph ret(n_vertices_);
			for (size_t v = 0; v < n_vertices_; ++v) {
				for (size_t w : Adj(v)) {
					ret.AddEdge(w, v);
				}
			}
			return ret;
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
			std::ifstream in("../file/tinyDG.txt");
			Digraph G(in);
			std::cout << G.ToString();
		}

	};
}