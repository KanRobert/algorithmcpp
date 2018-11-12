#pragma once
#include"graph.h"
#include"set.h"
#include"stdrandom.h"
#include<stdexcept>

namespace algorithmcpp {
	class GraphGenerator {
		struct Edge;
		friend bool operator<(const Edge &, const Edge &);
		friend bool operator>(const Edge &, const Edge &);
		friend bool operator==(const Edge &, const Edge &);
		friend bool operator!=(const Edge &, const Edge &);
		friend bool operator<=(const Edge &, const Edge &);
		friend bool operator>=(const Edge &, const Edge &);
		friend int Compare(const Edge &, const Edge &);
	private:
		struct Edge{
			size_t v;
			size_t w;
		};

	public:
		GraphGenerator(const GraphGenerator &) = delete;
		GraphGenerator &operator=(const GraphGenerator &) = delete;
		~GraphGenerator() = delete;

		static Graph Simple(size_t n_vertices, size_t n_edges) {
			if (n_edges > n_vertices*(n_vertices - 1) / 2) {
				throw std::invalid_argument("Too many edges");
			}
			Graph G(n_vertices);
			Set<Edge> set;
			while (G.E() < n_edges) {
				size_t v = StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices);
				if (v == w) continue;
				Edge e{ v, w };
				if (!set.Contains(e)) {
					set.Add(e);
					G.AddEdge(v, w);
				}
			}
			return G;
		}

		static Graph Simple(size_t n_vertices, double p) {
			if (p<0.0 || p>1.0) {
				throw std::invalid_argument("Probability must be between 0 and 1");
			}
			Graph G(n_vertices);
			for (size_t v = 0; v < n_vertices; ++v) {
				for (size_t w = v + 1; w < n_vertices; ++w) {
					if (StdRandom::Bernoulli(p)) {
						G.AddEdge(v, w);
					}
				}
			}
			return G;
		}

		static Graph Complete(size_t n_vertices) {
			return Simple(n_vertices, 1.0);
		}

		static Graph CompleteBipartite(size_t n_left_vertices, size_t n_right_vertices) {
			return Bipartite(n_left_vertices, n_right_vertices, n_left_vertices*n_right_vertices);
		}

		static Graph Bipartite(size_t n_left_vertices, size_t n_right_vertices, size_t n_edges) {
			if (n_edges > n_left_vertices*n_right_vertices) {
				throw std::invalid_argument("Too many edges");
			}
			Graph G(n_left_vertices + n_right_vertices);
			std::vector<size_t> vertices(n_left_vertices + n_right_vertices);
			for (size_t i = 0; i < n_left_vertices + n_right_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);
			Set<Edge> set;
			while (G.E() < n_edges) {
				size_t i = StdRandom::Uniform(n_left_vertices);
				size_t j = n_left_vertices + StdRandom::Uniform(n_right_vertices);
				Edge e{ vertices[i], vertices[j] };
				if (!set.Contains(e)) {
					set.Add(e);
					G.AddEdge(vertices[i], vertices[j]);
				}
			}
			return G;
		}

		static Graph Bipartite(size_t n_left_vertices, size_t n_right_vertices, double p) {
			if (p<0.0 || p>1.0) {
				throw std::invalid_argument("Probability must be between 0 and 1");
			}
			Graph G(n_left_vertices + n_right_vertices);
			std::vector<size_t> vertices(n_left_vertices + n_right_vertices);
			for (size_t i = 0; i < n_left_vertices + n_right_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);
			for (size_t v = 0; v < n_left_vertices; ++v) {
				for (size_t w = 0; w < n_right_vertices; ++w) {
					if (StdRandom::Bernoulli(p)) {
						G.AddEdge(vertices[v], vertices[n_left_vertices+w]);
					}
				}
			}
			return G;
		}
	};

	bool operator<(const GraphGenerator::Edge &, const GraphGenerator::Edge &);
	bool operator>(const GraphGenerator::Edge &, const GraphGenerator::Edge &);
	bool operator==(const GraphGenerator::Edge &, const GraphGenerator::Edge &);
	bool operator!=(const GraphGenerator::Edge &, const GraphGenerator::Edge &);
	bool operator<=(const GraphGenerator::Edge &, const GraphGenerator::Edge &);
	bool operator>=(const GraphGenerator::Edge &, const GraphGenerator::Edge &);
	int Compare(const GraphGenerator::Edge &, const GraphGenerator::Edge &);
}