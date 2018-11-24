#pragma once
#include"graph.h"
#include"queue.h"
#include"stdrandom.h"
#include"graph_generator.h"
#include"stack.h"
#include<vector>

namespace algorithmcpp {
	class BipartiteX {
	private:
		constexpr static bool kWhite = false;
		constexpr static bool kBlack = true;

		bool is_bipartite_ = true;
		std::vector<bool> color_;
		std::vector<bool> marked_;
		std::vector<size_t> edge_to_;
		Queue<size_t> cycle_;

	public:
		BipartiteX() = delete;
		BipartiteX(const BipartiteX &) = default;
		BipartiteX(BipartiteX &&) noexcept = default;
		BipartiteX &operator=(const BipartiteX &) = default;
		BipartiteX &operator=(BipartiteX &&) noexcept = default;
		~BipartiteX() = default;

		BipartiteX(const Graph &G) :
			color_(std::vector<bool>(G.V())), marked_(std::vector<bool>(G.V())), edge_to_(std::vector<size_t>(G.V())) {
			for (size_t v = 0; v < G.V() && is_bipartite_; ++v) {
				if (!marked_[v]) {
					Bfs(G, v);
				}
			}
		}

	private:
		void Bfs(const Graph &G, size_t s) {
			Queue<size_t> q;
			color_[s] = kWhite;
			marked_[s] = true;
			q.Enqueue(s);
			while (!q.IsEmpty()) {
				size_t v = q.Dequeue();
				for (size_t w : G.Adj(v)) {
					if (!marked_[w]) {
						marked_[w] = true;
						edge_to_[w] = v;
						color_[w] = !color_[v];
						q.Enqueue(w);
					}
					else if (color_[w] == color_[v]) {
						is_bipartite_ = false;
						Stack<size_t> stack;
						size_t x = v, y = w;
						while (x != y) {
							stack.Push(x);
							cycle_.Enqueue(y);
							x = edge_to_[x];
							y = edge_to_[y];
						}
						cycle_.Enqueue(x);
						while (!stack.IsEmpty()) {
							cycle_.Enqueue(stack.Pop());
						}
						cycle_.Enqueue(w);
						return;
					}
				}
			}

		}

		void ValidateVertex(size_t v) const {
			if (v >= marked_.size())
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(marked_.size() - 1));
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

		Queue<size_t> OddCycle() const {
			return cycle_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			size_t v1 = 10;
			size_t v2 = 10;
			size_t e = 20;
			size_t f = 15;

			Graph G = GraphGenerator::Bipartite(v1, v2, e);
			for (size_t i = 0; i < f; ++i) {
				size_t v = StdRandom::Uniform(v1 + v2);
				size_t w = StdRandom::Uniform(v1 + v2);
				G.AddEdge(v, w);
			}
			std::printf("%s\n", G.ToString().c_str());

			BipartiteX b(G);
			if (b.IsBipartite()) {
				std::printf("Graph is bipartite\n");
				for (size_t v = 0; v < G.V(); ++v) {
					std::printf("%zd: %d\n", v, b.Color(v));
				}
			}
			else {
				std::printf("Graph has an odd - length cycle : ");
				for (size_t x : b.OddCycle()) {
					std::printf("%zd ", x);
				}
				std::printf("\n");
			}
		}
	};
}