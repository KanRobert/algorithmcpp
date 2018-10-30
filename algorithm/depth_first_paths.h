#pragma once
#include"graph.h"
#include"stack.h"
#include<vector>
#include<stdexcept>
#include<string>
#include<iostream>
#include<fstream>

namespace algorithmcpp {
	class DepthFirstPaths {
	private:
		std::vector<bool> marked_;
		std::vector<size_t> edge_to_;
		size_t source_vertex_;

	public:
		DepthFirstPaths() = delete;
		DepthFirstPaths(const DepthFirstPaths&) = default;
		DepthFirstPaths(DepthFirstPaths &&) noexcept = default;
		DepthFirstPaths &operator=(const DepthFirstPaths &) = default;
		DepthFirstPaths &operator=(DepthFirstPaths &&) noexcept = default;
		~DepthFirstPaths() = default;

		DepthFirstPaths(Graph G, size_t s) :
			marked_(std::vector<bool>(G.V())), edge_to_(std::vector<size_t>(G.V())), source_vertex_(s) {
			ValidateVertex(s);
			Dfs(G, s);
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t V = marked_.size();
			if (v >= V) throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(V - 1));
		}

		void Dfs(const Graph &G, size_t v) {
			marked_[v] = true;
			for (size_t w : G.Adj(v)) {
				if (!marked_[w]) {
					edge_to_[w] = v;
					Dfs(G, w);
				}
			}
		}

	public:
		bool HasPathTo(size_t v) {
			ValidateVertex(v);
			return marked_[v];
		}

		Stack<size_t> PathTo(size_t v) {
			ValidateVertex(v);
			if (!HasPathTo(v)) return Stack<size_t>();
			Stack<size_t> path;
			for (size_t x = v; x != source_vertex_; x = edge_to_[x]) {
				path.Push(x);
			}
			path.Push(source_vertex_);
			return path;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyCG.txt");
			Graph G(in);

			size_t s = 0;
			DepthFirstPaths dfs(G, s);

			for (size_t v = 0; v < G.V(); ++v) {
				if (dfs.HasPathTo(v)) {
					std::cout << s << " To " << v << ":  ";
					for (size_t x : dfs.PathTo(v)) {
						if (x == s) std::cout << x;
						else std::cout << "-" << x;
					}
					std::cout << "\n";
				}
				else {
					std::cout << s << " To " << v << ":  " << "not connected\n";
				}
			}
		}
	};

}