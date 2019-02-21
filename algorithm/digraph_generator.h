#pragma once
#include"digraph.h"
#include"set.h"
#include"stdrandom.h"
#include<stdexcept>
#include<vector>
#include<cstdio>

namespace algorithmcpp {
	class DigraphGenerator {
		struct Edge;
		friend bool operator<(const Edge &, const Edge &);
		friend bool operator>(const Edge &, const Edge &);
		friend bool operator==(const Edge &, const Edge &);
		friend bool operator!=(const Edge &, const Edge &);
		friend bool operator<=(const Edge &, const Edge &);
		friend bool operator>=(const Edge &, const Edge &);
		friend int Compare(const Edge &, const Edge &);

	private:
		struct Edge {
			size_t v;
			size_t w;
		};

	public:
		DigraphGenerator(const DigraphGenerator &) = delete;
		DigraphGenerator &operator=(const DigraphGenerator &) = delete;
		~DigraphGenerator() = delete;

		static Digraph Simple(size_t n_vertices, size_t n_edges) {
			if (n_edges > n_vertices*(n_vertices - 1)) throw std::invalid_argument("Too many edges");
			Digraph G(n_vertices);
			Set<Edge> set;
			while (G.E() < n_edges) {
				size_t v = StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices);
				Edge e{ v,w };
				if ((v != w) && !set.Contains(e)) {
					set.Add(e);
					G.AddEdge(v, w);
				}
			}
			return G;
		}

		static Digraph Simple(size_t n_vertices, double p) {
			if (p<0.0 || p>1.0) {
				throw std::invalid_argument("Probability must be between 0 and 1");
			}
			Digraph G(n_vertices);
			for (size_t v = 0; v < n_vertices; ++v) {
				for (size_t w = v + 1; w < n_vertices; ++w) {
					if (StdRandom::Bernoulli(p)) {
						G.AddEdge(v, w);
					}
				}
			}
			return G;
		}

		static Digraph Complete(size_t n_vertices) {
			return Simple(n_vertices, n_vertices*(n_vertices - 1));
		}

		static Digraph Dag(size_t n_vertices, size_t n_edges) {
			if (n_edges > n_vertices*(n_vertices - 1) / 2) throw std::invalid_argument("Too mang edges");
			Digraph G(n_vertices);
			Set<Edge> set;
			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);
			while (G.E() < n_edges) {
				size_t v = StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices);
				Edge e{ v,w };
				if ((v < w) && !set.Contains(e)) {
					set.Add(e);
					G.AddEdge(vertices[v], vertices[w]);
				}
			}
			return G;
		}

		static Digraph Tournament(size_t n_vertices) {
			Digraph G(n_vertices);
			for (size_t v = 0; v < G.V(); ++v) {
				for (size_t w = v + 1; w < G.V(); ++w) {
					if (StdRandom::Bernoulli(0.5)) G.AddEdge(v, w);
					else G.AddEdge(w, v);
				}
			}
			return G;
		}

		static Digraph RootedInDAG(size_t n_vertices, size_t n_edges) {
			if(n_edges > n_vertices*(n_vertices-1)/2) throw std::invalid_argument("Too mang edges");
			if(n_edges< n_vertices-1) throw std::invalid_argument("Too few edges");
			Digraph G(n_vertices);
			Set<Edge> set;

			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);

			for (size_t v = 0; v < n_vertices - 1; ++v) {
				size_t w = StdRandom::Uniform(v + 1, n_vertices);
				Edge e{ v,w };
				set.Add(e);
				G.AddEdge(vertices[v], vertices[w]);
			}

			while (G.E() < n_edges) {
				size_t v = StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices);
				Edge e{ v,w };
				if ((v < w) && !set.Contains(e)) {
					set.Add(e);
					G.AddEdge(vertices[v], vertices[w]);
				}
			}
			return G;
		}

		static Digraph RootedOutDAG(size_t n_vertices, size_t n_edges) {
			if (n_edges > n_vertices*(n_vertices - 1) / 2) throw std::invalid_argument("Too mang edges");
			if (n_edges< n_vertices - 1) throw std::invalid_argument("Too few edges");
			Digraph G(n_vertices);
			Set<Edge> set;

			std::vector<size_t> vertices(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				vertices[i] = i;
			}
			StdRandom::Shuffle(vertices);

			for (size_t v = 0; v < n_vertices - 1; ++v) {
				size_t w = StdRandom::Uniform(v + 1, n_vertices);
				Edge e{ w,v };
				set.Add(e);
				G.AddEdge(vertices[w], vertices[v]);
			}

			while (G.E() < n_edges) {
				size_t v = StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices);
				Edge e{ w,v };
				if ((v < w) && !set.Contains(e)) {
					set.Add(e);
					G.AddEdge(vertices[w], vertices[v]);
				}
			}
			return G;
		}

		static Digraph RootedInTree(size_t n_vertices) {
			return RootedInDAG(n_vertices, n_vertices - 1);
		}

		static Digraph RootedOutTree(size_t n_vertices) {
			return RootedOutDAG(n_vertices, n_vertices - 1);
		}

		static Digraph Path(size_t n_vertices) {
			Digraph G(n_vertices);
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

		static Digraph BinaryTree(size_t n_vertices) {
			Digraph G(n_vertices);
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

		static Digraph Cycle(size_t n_vertices) {
			Digraph G(n_vertices);
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

		static Digraph EulerianCycle(size_t n_vertices, size_t n_edges) {
			Digraph G(n_vertices);
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

		static Digraph EulerianPath(size_t n_vertices, size_t n_edges) {
			if (n_vertices == 0) throw std::invalid_argument("An Eulerian path must have at least one vertex");
			Digraph G(n_vertices);
			std::vector<size_t> vertices(n_edges + 1);
			for (size_t i = 0; i < n_edges + 1; ++i) {
				vertices[i] = StdRandom::Uniform(n_vertices);
			}
			for (size_t i = 0; i < n_edges; ++i) {
				G.AddEdge(vertices[i], vertices[i + 1]);
			}
			return G;
		}

		static Digraph Strong(size_t n_vertices, size_t n_edges, size_t n_components) {
			if (n_components >= n_vertices) throw std::invalid_argument("Number of components must be less than that of vertices");
			if (n_edges <= 2 * (n_vertices - n_components)) throw std::invalid_argument("Number of edges must be more than 2*(n_vertices-n_components)");
			if (n_edges > n_vertices*(n_vertices - 1) / 2) throw std::invalid_argument("Too many edges");

			Digraph G(n_vertices);
			Set<Edge> set;

			std::vector<size_t> label(n_vertices);
			for (size_t v = 0; v < n_vertices; ++v) {
				label[v] = StdRandom::Uniform(n_components);
			}

			for (size_t i = 0; i < n_components; ++i) {
				size_t count = 0;
				for (size_t v = 0; v < G.V(); ++v) {
					if (label[v] == i) ++count;
				}

				std::vector<size_t> vertices(count);
				size_t j = 0;
				for (size_t v = 0; v < n_vertices; ++v) {
					if (label[v] == i) vertices[j++] = v;
				}
				StdRandom::Shuffle(vertices);

				for (size_t v = 0; v < count - 1; ++v) {
					size_t w = StdRandom::Uniform(v + 1, count);
					Edge e{ v,w };
					set.Add(e);
					G.AddEdge(vertices[v], vertices[w]);
				}

				for (size_t v = 0; v < count - 1; ++v) {
					size_t w = StdRandom::Uniform(v + 1, count);
					Edge e{ w,v };
					set.Add(e);
					G.AddEdge(vertices[w], vertices[v]);
				}
			}

			while (G.E() < n_edges) {
				size_t v = StdRandom::Uniform(n_vertices);
				size_t w = StdRandom::Uniform(n_vertices);
				Edge e{ v,w };
				if (!set.Contains(e) && v != w && label[v] <= label[w]) {
					set.Add(e);
					G.AddEdge(v, w);
				}
			}
			return G;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			size_t n_vertices = 10;
			size_t n_edges = 12;

			std::printf("complete graph\n");
			std::printf("%s\n", Complete(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("simple\n");
			std::printf("%s\n", Simple(n_vertices, n_edges).ToString().c_str());
			std::printf("\n");

			std::printf("path\n");
			std::printf("%s\n", Path(n_vertices).ToString().c_str());
			std::printf("\n");

			std::printf("cycle\n");
			std::printf("%s\n", Cycle(n_vertices).ToString().c_str());
			std::printf("\n");
		}
			
	};
}