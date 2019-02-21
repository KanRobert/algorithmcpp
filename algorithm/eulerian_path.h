#pragma once
#include"stack.h"
#include"graph.h"
#include"queue.h"
#include"graph_generator.h"
#include<stdexcept>
#include<vector>
#include<memory>

namespace algorithmcpp {
	class EulerianPath {
	private:
		Stack<size_t> path_;

		class Edge {
		public:
			size_t v_;
			size_t w_;
			bool is_used_=false;

			Edge() = delete;
			Edge(const Edge &) = default;
			Edge(Edge &&) noexcept = default;
			Edge &operator=(const Edge &) = default;
			Edge &operator=(Edge &&) noexcept = default;
			~Edge() = default;
			Edge(size_t v, size_t w) :v_(v), w_(w) {}
			size_t Other(size_t vertex) const {
				if (vertex == v_) return w_;
				else if (vertex == w_) return v_;
				else throw std::invalid_argument("illegal endpoint");
			}
		};

	public:
		EulerianPath() = delete;
		EulerianPath(const EulerianPath&) = default;
		EulerianPath(EulerianPath &&) noexcept = default;
		EulerianPath &operator=(const EulerianPath &) = default;
		EulerianPath &operator=(EulerianPath &&) noexcept = default;
		~EulerianPath() = default;

	private:
		static int NonIsolatedVertex(const Graph &G) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (G.Degree(v) > 0) {
					return v;
				}
			}
			return -1;
		}

		static void UnitTest(const Graph &G, const std::string &description) {
			std::cout << description << "\n";
			std::cout << "-------------------------------------"<<"\n";
			std::cout << G.ToString();

			EulerianPath euler(G);
			std::cout << "Eulerian path:  ";
			if (euler.HasEulerianPath()) {
				for (size_t v : euler.Path()) {
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
		EulerianPath(const Graph &G) {
			size_t odd_degree_vertices = 0;
			int s = NonIsolatedVertex(G);
			for (size_t v = 0; v < G.V(); ++v) {
				if (G.Degree(v) % 2 != 0) {
					++odd_degree_vertices;
					s = v;
				}
			}

			if (odd_degree_vertices > 2) return;
			if (s == -1) s = 0;
			std::vector<Queue<std::shared_ptr<Edge>>> adj(G.V());
			for (size_t v = 0; v < G.V(); ++v) {
				size_t self_loops = 0;
				for (size_t w : G.Adj(v)) {
					if (v == w) {
						if (self_loops % 2 == 0) {
							auto e=std::make_shared<Edge>(v, w);
							adj[v].Enqueue(e);
							adj[w].Enqueue(e);
						}
						++self_loops;
					}
					else if (v < w) {
						auto e = std::make_shared<Edge>(v, w);
						adj[v].Enqueue(e);
						adj[w].Enqueue(e);
					}
				}
			}
			Stack<size_t> stack;
			stack.Push(s);

			while (!stack.IsEmpty()) {
				size_t v = stack.Pop();
				while (!adj[v].IsEmpty()) {
					auto edge = adj[v].Dequeue();
					if (edge->is_used_) continue;
					edge->is_used_ = true;
					stack.Push(v);
					v = edge->Other(v);
				}
				path_.Push(v);
			}
			if (path_.Size() != G.E() + 1) {
				path_ = Stack<size_t>();
			}
		}

		Stack<size_t> Path() const {
			return path_;
		}

		bool HasEulerianPath() const {
			return !path_.IsEmpty();
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			size_t n_vertices = 5;
			size_t n_edges = 5;
			
			Graph G1 = GraphGenerator::EulerianCycle(n_vertices, n_edges);
			UnitTest(G1, "Eulerian cycle");

			Graph G2 = GraphGenerator::EulerianPath(n_vertices, n_edges);
			UnitTest(G2, "Eulerian path");

			Graph G3 = GraphGenerator::Simple(n_vertices, n_edges);
			UnitTest(G3, "Simple graph");
		}
	};
}