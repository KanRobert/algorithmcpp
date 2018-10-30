#pragma once
#include"digraph.h"
#include"bag.h"
#include"queue.h"
#include"stack.h"
#include<vector>
#include<stdexcept>
#include<string>
#include<iostream>
#include<fstream>
#include<limits>

namespace algorithmcpp {
	class BreadthFirstDirectedPaths {
	private:
		std::vector<bool> marked_;
		std::vector<size_t> edge_to_;
		std::vector<size_t> distance_;

	public:
		BreadthFirstDirectedPaths() = delete;
		BreadthFirstDirectedPaths(const BreadthFirstDirectedPaths&) = default;
		BreadthFirstDirectedPaths(BreadthFirstDirectedPaths &&) noexcept = default;
		BreadthFirstDirectedPaths &operator=(const BreadthFirstDirectedPaths &) = default;
		BreadthFirstDirectedPaths &operator=(BreadthFirstDirectedPaths &&) noexcept = default;
		~BreadthFirstDirectedPaths() = default;

		BreadthFirstDirectedPaths(const Digraph &G, size_t s) :
			marked_(std::vector<bool>(G.V())), edge_to_(std::vector<size_t>(G.V())), distance_(std::vector<size_t>(G.V(), std::numeric_limits<size_t>::max())) {
			ValidateVertex(s);
			Bfs(G, s);
		}

		BreadthFirstDirectedPaths(const Digraph &G, const std::vector<size_t> &sources) :
			marked_(std::vector<bool>(G.V())), edge_to_(std::vector<size_t>(G.V())), distance_(std::vector<size_t>(G.V(), std::numeric_limits<size_t>::max())) {
			ValidateVertices(sources);
			Bfs(G, sources);
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t n_vertices_ = marked_.size();
			if (v >= n_vertices_) throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices_ - 1));
		}

		void ValidateVertices(const std::vector<size_t> &vertices) {
			size_t n_vertices_ = marked_.size();
			for (size_t v : vertices) {
				if (v >= n_vertices_) throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices_ - 1));
			}
		}

		void Bfs(const Digraph &G, size_t s) {
			Queue<size_t> q;
			distance_[s] = 0;
			marked_[s] = true;
			q.Enqueue(s);

			while (!q.IsEmpty()) {
				size_t v = q.Dequeue();
				for (size_t w : G.Adj(v)) {
					if (!marked_[w]) {
						edge_to_[w] = v;
						distance_[w] = distance_[v] + 1;
						marked_[w] = true;
						q.Enqueue(w);
					}
				}
			}
		}

		void Bfs(const Digraph &G, std::vector<size_t> sources) {
			Queue<size_t> q;
			for (size_t s : sources) {
				marked_[s] = true;
				distance_[s] = 0;
				q.Enqueue(s);
			}

			while (!q.IsEmpty()) {
				size_t v = q.Dequeue();
				for (size_t w : G.Adj(v)) {
					if (!marked_[w]) {
						edge_to_[w] = v;
						distance_[w] = distance_[v] + 1;
						marked_[w] = true;
						q.Enqueue(w);
					}
				}
			}
		}

	public:
		bool HasPathTo(size_t v) {
			ValidateVertex(v);
			return marked_[v];
		}

		size_t DistTo(size_t v) {
			ValidateVertex(v);
			return distance_[v];
		}

		Stack<size_t> PathTo(size_t v) {
			ValidateVertex(v);
			if (!HasPathTo(v)) return Stack<size_t>();
			Stack<size_t> path;
			size_t x;
			for (x = v; distance_[x] != 0; x = edge_to_[x]) {
				path.Push(x);
			}
			path.Push(x);
			return path;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyDG.txt");
			Digraph G(in);

			size_t s = 3;
			BreadthFirstDirectedPaths Bfs(G, s);

			for (size_t v = 0; v < G.V(); ++v) {
				if (Bfs.HasPathTo(v)) {
					std::cout << s << " to " << v << " ("<<Bfs.DistTo(v)<<")"<<":  ";
					for (size_t x : Bfs.PathTo(v)) {
						if (x == s) std::cout << x;
						else std::cout << "-" << x;
					}
					std::cout << "\n";
				}
				else {
					std::cout << s << " to " << v << " (-)" << ":  " << "not connected\n";
				}
			}
		}
	};

}