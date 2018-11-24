#pragma once
#include"bipartite_x.h"
#include"graph_generator.h"
#include<vector>
#include<stdexcept>
#include<cstdio>

namespace algorithmcpp {
	class BipartiteMatching {
	private:
		static constexpr int kUnMatched = -1;
		size_t cardinality_ = 0;
		size_t n_vertices_;
		BipartiteX bipartition_;
		std::vector<int> mate_;
		std::vector<bool> in_min_vertex_cover_;
		std::vector<bool> marked_;
		std::vector<int> edge_to_;

	public:
		BipartiteMatching() = delete;
		BipartiteMatching(const BipartiteMatching &) = default;
		BipartiteMatching(BipartiteMatching &&) noexcept = default;
		BipartiteMatching &operator=(const BipartiteMatching &) = default;
		BipartiteMatching &operator=(BipartiteMatching &&) noexcept = default;
		~BipartiteMatching() = default;

		BipartiteMatching(const Graph &G) :
			n_vertices_(G.V()), bipartition_(G), mate_(std::vector<int>(n_vertices_, kUnMatched)), in_min_vertex_cover_(std::vector<bool>(n_vertices_)) {
			if (!bipartition_.IsBipartite()) {
				throw std::invalid_argument("graph is not bipartite");
			}

			while (HasAugmentingPath(G)) {
				int t = -1;
				for (int v = 0; v < static_cast<int>(G.V()); ++v) {
					if (!IsMatched(v) && edge_to_[v] != -1) {
						t = v;
						break;
					}
				}

				for (int v = t; v != -1; v = edge_to_[edge_to_[v]]) {
					int w = edge_to_[v];
					mate_[v] = w;
					mate_[w] = v;
				}
				++cardinality_;
			}

			for (int v = 0; v < static_cast<int>(n_vertices_); ++v) {
				if (bipartition_.Color(v) && !marked_[v]) in_min_vertex_cover_[v] = true;
				if (!bipartition_.Color(v) && marked_[v])  in_min_vertex_cover_[v] = true;
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			if (v >= n_vertices_)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices_ - 1));
		}

		bool IsResidualGraphEdge(size_t v, size_t w) const {
			if ((mate_[v] != w) && bipartition_.Color(v)) return true;
			if ((mate_[v] == w) && !bipartition_.Color(v)) return true;
			return false;
		}

		bool HasAugmentingPath(const Graph &G) {
			marked_ = std::vector<bool>(n_vertices_);
			edge_to_ = std::vector<int>(n_vertices_, -1);
			Queue<size_t> queue;
			for (size_t v = 0; v < n_vertices_; ++v) {
				if (bipartition_.Color(v) && !IsMatched(v)) {
					queue.Enqueue(v);
					marked_[v] = true;
				}
			}

			while (!queue.IsEmpty()) {
				size_t v = queue.Dequeue();
				for (size_t w : G.Adj(v)) {
					if (IsResidualGraphEdge(v, w) && !marked_[w]) {
						edge_to_[w] = v;
						marked_[w] = true;
						if (!IsMatched(w)) return true;
						queue.Enqueue(w);
					}
				}
			}
			return false;
		}

	public:
		bool IsMatched(size_t v) const {
			ValidateVertex(v);
			return mate_[v] != kUnMatched;
		}

		bool InMinVertexCover(size_t v) const {
			ValidateVertex(v);
			return in_min_vertex_cover_[v];
		}

		int Mate(size_t v) const {
			ValidateVertex(v);
			return mate_[v];
		}

		size_t Size() const {
			return cardinality_;
		}

		bool IsPerfect() const {
			return cardinality_ * 2 == n_vertices_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			size_t v1 = 10;
			size_t v2 = 10;
			size_t e = 20;
			Graph G = GraphGenerator::Bipartite(v1, v2,e);
			std::printf("%s\n", G.ToString().c_str());
			
			BipartiteMatching matching(G);
			std::printf("Number of edges in max matching        = %zd\n", matching.Size());
			std::printf("Graph has a perfect matching           = %d\n", matching.IsPerfect());
			std::printf("\n");

			std::printf("Max matching: ");
			for (int v = 0; v < static_cast<int>(G.V()); ++v) {
				int w = matching.Mate(v);
				if (matching.IsMatched(v) && static_cast<int>(v) < w) {
					std::printf("%zd-%d ", v, w);
				}
			}
			std::printf("\n");

			std::printf("Min vertex cover: ");
			for (int v = 0; v < static_cast<int>(G.V()); ++v) {
				if (matching.InMinVertexCover(v)) {
					std::printf("%d ", v);
				}
			}
			std::printf("\n");
		}
	};
}