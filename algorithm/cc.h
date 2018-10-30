#pragma once
#include"graph.h"
#include"edge_weighted_graph.h"
#include"edge.h"
#include"queue.h"
#include<vector>
#include<stdexcept>
#include<fstream>
#include<iostream>

namespace algorithmcpp {
	class CC {
	private:
		std::vector<bool> marked_;
		std::vector<size_t> id_;
		std::vector<size_t> size_;
		size_t nComponents_=0;

	public:
		CC() = delete;
		CC(const CC&) = default;
		CC(CC &&) noexcept = default;
		CC &operator=(const CC &) = default;
		CC &operator=(CC &&) noexcept = default;
		~CC() = default;

		CC(const Graph &G) :
			marked_(std::vector<bool>(G.V())), id_(std::vector<size_t>(G.V())), size_(std::vector<size_t>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (!marked_[v]) {
					Dfs(G, v);
					++nComponents_;
				}
			}
		}

		CC(const EdgeWeightedGraph &G) :
			marked_(std::vector<bool>(G.V())), id_(std::vector<size_t>(G.V())), size_(std::vector<size_t>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (!marked_[v]) {
					Dfs(G, v);
					++nComponents_;
				}
			}
		}

	private:
		void Dfs(const Graph &G, size_t v) {
			marked_[v] = true;
			id_[v] = nComponents_;
			++size_[nComponents_];
			for (size_t w : G.Adj(v)) {
				if (!marked_[w]) {
					Dfs(G, w);
				}
			}
		}

		void Dfs(const EdgeWeightedGraph &G, size_t v) {
			marked_[v] = true;
			id_[v] = nComponents_;
			++size_[nComponents_];
			for (const Edge &e : G.Adj(v)) {
				size_t w = e.Other(v);
				if (!marked_[w]) {
					Dfs(G, w);
				}
			}
		}

		void ValidateVertex(size_t v) const {
			size_t V = marked_.size();
			if (v >= V) {
				if (v >= V) throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(V - 1));
			}
		}

	public:

		size_t Id(size_t v) const {
			ValidateVertex(v);
			return id_[v];
		}

		size_t Size(size_t v) const {
			ValidateVertex(v);
			return size_[id_[v]];
		}

		size_t Count() const {
			return nComponents_;
		}

		bool Connected(size_t v, size_t w) const {
			ValidateVertex(v);
			ValidateVertex(w);
			return Id(v) == Id(w);
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyG.txt");
			Graph G(in);
			CC cc(G);

			size_t m = cc.Count();
			std::cout << m << " components\n";
			std::vector<Queue<size_t>> components(m);
			for (size_t v = 0; v < G.V(); ++v) {
				components[cc.Id(v)].Enqueue(v);
			}

			for (size_t i = 0; i < m; ++i) {
				for (size_t v: components[i]) {
					std::cout << v << " ";
				}
				std::cout << "\n";
			}
		}

	};
}