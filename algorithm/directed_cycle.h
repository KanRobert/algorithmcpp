#pragma once
#include"digraph.h"
#include"stack.h"
#include<vector>
#include<stdexcept>
#include<string>
#include<iostream>
#include<fstream>

namespace algorithmcpp {
	class DirectedCycle {
	private:
		std::vector<bool> marked_;
		std::vector<size_t> edge_to_;
		std::vector<bool> on_stack_;
		Stack<size_t> cycle_;

	public:
		DirectedCycle() = delete;
		DirectedCycle(const DirectedCycle&) = default;
		DirectedCycle(DirectedCycle &&) noexcept = default;
		DirectedCycle &operator=(const DirectedCycle &) = default;
		DirectedCycle &operator=(DirectedCycle &&) noexcept = default;
		~DirectedCycle() = default;

		DirectedCycle(Digraph G) :
			marked_(std::vector<bool>(G.V())), edge_to_(std::vector<size_t>(G.V())), on_stack_(std::vector<bool>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if(!marked_[v] && cycle_.IsEmpty()) Dfs(G, v);
			}			
		}

	private:
		void Dfs(const Digraph &G, size_t v) {
			on_stack_[v] = true;
			marked_[v] = true;
			for (size_t w : G.Adj(v)) {
				if (!cycle_.IsEmpty()) return;
				else if (!marked_[w]) {
					edge_to_[w] = v;
					Dfs(G, w);
				}
				else if (on_stack_[w]) {
					for (size_t x = v; x != w; x = edge_to_[x]) {
						cycle_.Push(x);
					}
					cycle_.Push(w);
					cycle_.Push(v);
				}
			}
			on_stack_[v] = false;
		}

	public:
		bool HasCycle() const {
			return !cycle_.IsEmpty();
		}

		Stack<size_t> Cycle() const {
			return cycle_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyDG.txt");
			Digraph G(in);
			DirectedCycle finder(G);
			if (finder.HasCycle()) {
				std::cout << "Directed cycle: ";
				for (size_t v : finder.Cycle()) {
					std::cout << v << " ";
				}
				std::cout << "\n";
			}
			else {
				std::cout << "No directed cycle\n";
			}
		}
	};

}