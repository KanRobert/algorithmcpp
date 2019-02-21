#pragma once
#include"stack.h"
#include"digraph.h"
#include"bag.h"
#include"digraph_generator.h"
#include<vector>

namespace algorithmcpp {
	class DirectedEulerianCycle {
	private:
		Stack<size_t> cycle_;
	public:
		DirectedEulerianCycle() = delete;
		DirectedEulerianCycle(const DirectedEulerianCycle&) = default;
		DirectedEulerianCycle(DirectedEulerianCycle &&) noexcept = default;
		DirectedEulerianCycle &operator=(const DirectedEulerianCycle &) = default;
		DirectedEulerianCycle &operator=(DirectedEulerianCycle &&) noexcept = default;
		~DirectedEulerianCycle() = default;

	private:
		static int NonIsolatedVertex(const Digraph &G) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (G.Outdegree(v) > 0) {
					return v;
				}
			}
			return -1;
		}

		static void UnitTest(const Digraph &G, const std::string &description) {
			std::cout << description << "\n";
			std::cout << "-------------------------------------" << "\n";
			std::cout << G.ToString();

			DirectedEulerianCycle euler(G);
			std::cout << "Eulerian cycle:  ";
			if (euler.HasEulerianCycle()) {
				for (size_t v : euler.Cycle()) {
					std::cout << v << " ";
				}
				std::cout << "\n";
			}
			else {
				std::cout << "none" << "\n";
			}
			std::cout << "\n";
		}

	public:
		DirectedEulerianCycle(const Digraph &G) {
			if (G.E() == 0) return;

			for (size_t v = 0; v < G.V(); ++v) {
				if (G.Outdegree(v) != G.Indegree(v)) return;
			}

			std::vector<Bag<size_t>::iterator> begs(G.V(),nullptr);
			std::vector<Bag<size_t>::iterator> ends(G.V(),nullptr);
			std::vector<Bag<size_t>> bags(G.V());
			for (size_t v = 0; v < G.V(); ++v) {
				bags[v] = G.Adj(v);
				begs[v] = bags[v].begin();
			}

			int s = NonIsolatedVertex(G);
			Stack<size_t> stack;
			stack.Push(static_cast<size_t>(s));

			while (!stack.IsEmpty()) {
				size_t v = stack.Pop();
				while (begs[v] != ends[v]) {
					stack.Push(v);
					v = *begs[v]++;
				}
				cycle_.Push(v);
			}

			if (cycle_.Size() != G.E() + 1) {
				cycle_ = Stack<size_t>();
			}
		}

		Stack<size_t> Cycle() const {
			return cycle_;
		}

		bool HasEulerianCycle() {
			return !cycle_.IsEmpty();
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			size_t n_vertices = 5;
			size_t n_edges = 5;

			Digraph G1 = DigraphGenerator::EulerianCycle(n_vertices, n_edges);
			UnitTest(G1, "Eulerian cycle");

			Digraph G2 = DigraphGenerator::EulerianPath(n_vertices, n_edges);
			UnitTest(G2, "Eulerian path");

			Digraph G3(n_vertices);
			UnitTest(G3, "empty digraph");

			Digraph G4(n_vertices);
			size_t v4 = StdRandom::Uniform(n_vertices);
			G4.AddEdge(v4, v4);
			UnitTest(G4, "single self loop");

			Digraph H1 = DigraphGenerator::EulerianCycle(n_vertices / 2, n_edges / 2);
			Digraph H2 = DigraphGenerator::EulerianCycle(n_vertices-n_vertices / 2, n_edges-n_edges / 2);
			std::vector<size_t> perm(n_vertices);
			for (size_t i = 0; i < n_vertices; ++i) {
				perm[i] = i;
			}
			StdRandom::Shuffle(perm);
			Digraph G5(n_vertices);
			for (size_t v = 0; v < H1.V(); ++v) {
				for (size_t w : H1.Adj(v)) {
					G5.AddEdge(perm[v], perm[w]);
				}
			}
			for (size_t v = 0; v < H2.V(); ++v) {
				for (size_t w : H2.Adj(v)) {
					G5.AddEdge(perm[n_vertices / 2 + v], perm[n_vertices / 2 + w]);
				}
			}
			UnitTest(G5, "Union of two disjoint cycles");

			Digraph G6 = DigraphGenerator::Simple(n_vertices, n_edges);
			UnitTest(G6, "Simple graph");
		}

	};

}