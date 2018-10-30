#pragma once
#include"digraph.h"
#include"edge_weighted_digraph.h"
#include"directed_cycle.h"
#include"edge_weighted_directed_cycle.h"
#include"depth_first_order.h"
#include"stack.h"
#include"symbol_digraph.h"
#include<vector>

namespace algorithmcpp {
	class Topological {
	private:
		std::vector<size_t> rank_;
		Stack<size_t> order_;

	public:
		Topological() = delete;
		Topological(const Topological&) = default;
		Topological(Topological &&) noexcept = default;
		Topological &operator=(const Topological &) = default;
		Topological &operator=(Topological &&) noexcept = default;
		~Topological() = default;

		Topological(const Digraph &G) :rank_(std::vector<size_t>(G.V())){
			DirectedCycle finder(G);
			if (!finder.HasCycle()) {
				DepthFirstOrder dfs(G);
				order_ = dfs.ReversePost();
				size_t i = 0;
				for (size_t v : order_) {
					rank_[v] = i++;
				}
			}
		}

		Topological(const EdgeWeightedDigraph &G) :rank_(std::vector<size_t>(G.V())) {
			EdgeWeightedDirectedCycle finder(G);
			if (!finder.HasCycle()) {
				DepthFirstOrder dfs(G);
				order_ = dfs.ReversePost();
				size_t i = 0;
				for (size_t v : order_) {
					rank_[v] = i++;
				}
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t V = rank_.size();
			if (v >= V) throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(V - 1));
		}

	public:
		Stack<size_t> Order() const {
			return order_;
		}

		bool HasOrder() const {
			return !order_.IsEmpty();
		}

		int Rank(size_t v) const {
			ValidateVertex(v);
			if (HasOrder()) return static_cast<int>(rank_[v]);
			else return -1;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::string filename("../file/jobs.txt");
			SymbolDigraph sg(filename,'/');
			Topological topological(sg.InDigraph());
			for (size_t v : topological.Order()) {
				std::cout << sg.NameOf(v) << "\n";
			}
		}
	};
}