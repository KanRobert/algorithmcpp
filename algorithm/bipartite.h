#pragma once
#include"graph.h"
#include"stack.h"
#include<vector>

namespace algorithmcpp {
	class Bipartite {
	private:
		bool is_bipartite_=true;
		std::vector<bool> color_;
		std::vector<bool> marked_;
		std::vector<size_t> edge_to_;
		Stack<size_t> cycle_;

	public:
		Bipartite() = delete;
		Bipartite(const Bipartite &) = default;
		Bipartite(Bipartite &&) noexcept = default;
		Bipartite &operator=(const Bipartite &) = default;
		Bipartite &operator=(Bipartite &&) noexcept = default;
		~Bipartite() = default;

		Bipartite(const Graph &G) :
			color_(std::vector<bool>(G.V())), marked_(std::vector<bool>(G.V())), edge_to_(std::vector<size_t>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (!marked_[v]) {
					Dfs(G, v);
				}
			}
		}

	private:
		void Dfs(const Graph &G, size_t v) {
			marked_[v] = true;
			for (size_t w : G.Adj(v)) {
				if (!cycle_.IsEmpty()) return;
				if (!marked_[w]) {
					edge_to_[w] = v;
					color_[w] = !color_[v];
					Dfs(G, w);
				}
				else if (color_[w] == color_[v]) {
					is_bipartite_ = false;
					cycle_.Push(w);
					for (size_t x = v; x != w; x = edge_to_[x]) {
						cycle_.Push(x);
					}
					cycle_.Push(w);
				}
			}
		}

		void ValidateVertex(size_t v) const {
			if (v >= marked_.size())
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices_ - 1));
		}

	public:
		bool IsBipartite() const {
			return is_bipartite_;
		}

		bool Color(size_t v) const {
			ValidateVertex(v);
			if (!is_bipartite_) {
				throw std::logic_error("graph is not bipartite");
			}
			return color_[v];
		}

		Stack<size_t> OddCycle() const {
			return cycle_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {

		}
	};
}