#pragma once
#pragma warning(disable:4996)
#include"graph.h"
#include"set.h"
#include"stdrandom.h"
#include"min_pq.h"
#include<stdexcept>
#include<cstdio>

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

		static Graph Path(size_t n_vertices) {
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);
			for (size_t i = 0; i < n_vertices - 1; ++i) {
				G.AddEdge(vertices[i], vertices[i + 1]);
			}
			return G;
		}

		static Graph BinaryTree(size_t n_vertices) {
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);
			for (size_t i = 1; i < n_vertices; ++i) {
				G.AddEdge(vertices[i], vertices[(i - 1) / 2]);
			}
			return G;
		}

		static Graph Cycle(size_t n_vertices) {
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);
			for (size_t i = 0; i < n_vertices - 1; ++i) {
				G.AddEdge(vertices[i], vertices[i + 1]);
			}
			G.AddEdge(vertices[n_vertices - 1], vertices[0]);
			return G;
		}

		static Graph EulerianCycle(size_t n_vertices, size_t n_edges) {
			if (n_vertices == 0) {
				throw std::invalid_argument("An Eulerian cycle must have at least one vertex");
			}
			if (n_edges == 0) {
				throw std::invalid_argument("An Eulerian cycle must have at least one edge");
			}
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_edges);
			for (size_t i = 0; i < n_edges; ++i) {
				vertices[i] = StdRandom::Uniform(n_vertices);
			}
			for (size_t i = 0; i < n_edges - 1; ++i) {
				G.AddEdge(vertices[i], vertices[i + 1]);
			}
			G.AddEdge(vertices[n_edges - 1], vertices[0]);
			return G;
		}

		static Graph EulerianPath(size_t n_vertices, size_t n_edges) {
			if (n_vertices == 0) {
				throw std::invalid_argument("An Eulerian path must have at least one vertex");
			}
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_edges+1);
			for (size_t i = 0; i < n_edges + 1; ++i) {
				vertices[i] = StdRandom::Uniform(n_vertices);
			}
			for (size_t i = 0; i < n_edges; ++i) {
				G.AddEdge(vertices[i], vertices[i + 1]);
			}
			return G;
		}

		static Graph Wheel(size_t n_vertices) {
			if (n_vertices <= 1) throw std::invalid_argument("Number of vertices must be at least 2");
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);

			for (size_t i = 1; i < n_vertices - 1; ++i) {
				G.AddEdge(vertices[i], vertices[i + 1]);
			}
			G.AddEdge(vertices[n_vertices - 1], vertices[1]);

			for (size_t i = 1; i < n_vertices; ++i) {
				G.AddEdge(vertices[0], vertices[i]);
			}
			return G;
		}

		static Graph Star(size_t n_vertices) {
			if (n_vertices == 0) throw std::invalid_argument("Number of vertices must be at least 1");
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);
			for (size_t i = 1; i < n_vertices; ++i) {
				G.AddEdge(vertices[0], vertices[i]);
			}
			return G;
		}

		static Graph Regular(size_t n_vertices, size_t k) {
			if (n_vertices*k % 2 != 0) {
				throw std::invalid_argument("Number of vertices * k must be even");
			}
			Graph G(n_vertices);
			std::vector<size_t> vertices(n_vertices*k);
			for (size_t v = 0; v < n_vertices; ++v) {
				for (size_t j = 0; j < k; ++j) {
					vertices[v + n_vertices * j] = v;
				}
			}
			StdRandom::Shuffle(vertices);
			for (size_t i = 0; i < n_vertices*k / 2; ++i) {
				G.AddEdge(vertices[2 * i], vertices[2 * i + 1]);
			}
			return G;
		}

		static Graph Tree(size_t n_vertices) {
			Graph G(n_vertices);
			if (n_vertices == 1) return G;
			std::vector<size_t> prufer(n_vertices - 2);
			for (size_t i = 0; i < n_vertices - 2; ++i) {
				prufer[i] = StdRandom::Uniform(n_vertices);
			}
			std::vector<size_t> degree(n_vertices);
			for (size_t v = 0; v < n_vertices; ++v) {
				degree[v] = 1;
			}
			for (size_t i = 0; i < n_vertices - 2; ++i) {
				++degree[prufer[i]];
			}

			MinPQ<size_t> pq;
			for (size_t v = 0; v < n_vertices; ++v) {
				if (degree[v] == 1) pq.Insert(v);
			}

			for (size_t i = 0; i < n_vertices - 2; ++i) {
				size_t v = pq.DelMin();
				G.AddEdge(v, prufer[i]);
				--degree[v];
				--degree[prufer[i]];
				if (degree[prufer[i]] == 1) pq.Insert(prufer[i]);
			}
			G.AddEdge(pq.DelMin(), pq.DelMin());
			return G;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			size_t n_vertices = 10;
			size_t n_edges = 12;
			size_t n_vertices1 = n_vertices / 2;
			size_t n_vertices2 = n_vertices - n_vertices1;

			std::printf("complete graph\n");
			std::printf("%s\n", Complete(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("simple\n");
			std::printf("%s\n", Simple(n_vertices,n_edges).ToString().c_str());
			std::printf("\n");

			std::printf("Erdos-Renyi\n");
			double p = n_edges / (n_vertices*(n_vertices - 1) / 2.0);
			std::printf("%s\n", Simple(n_vertices, p).ToString().c_str());
			std::printf("\n");

			std::printf("complete bipartite\n");
			std::printf("%s\n", CompleteBipartite(n_vertices1, n_vertices2).ToString().c_str());
			std::printf("\n");

			std::printf("bipartite\n");
			std::printf("%s\n", Bipartite(n_vertices1, n_vertices2,n_edges).ToString().c_str());
			std::printf("\n");

			std::printf("Erdos Renyi bipartite\n");
			double q = static_cast<double>(n_edges) / (n_vertices1*n_vertices2);
			std::printf("%s\n", Bipartite(n_vertices1, n_vertices2, q).ToString().c_str());
			std::printf("\n");

			std::printf("path\n");
			std::printf("%s\n", Path(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("cycle\n");
			std::printf("%s\n", Cycle(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("binary tree\n");
			std::printf("%s\n", BinaryTree(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("tree\n");
			std::printf("%s\n", Tree(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("4-regular\n");
			std::printf("%s\n", Regular(n_vertices,4).ToString().c_str());
			std::printf("\n");

			std::printf("star\n");
			std::printf("%s\n", Star(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("wheel\n");
			std::printf("%s\n", Wheel(n_vertices).ToString().c_str());
			std::printf("\n");
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