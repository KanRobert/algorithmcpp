#pragma once
#include"queue.h"
#include"digraph.h"
#include"stack.h"
#include"edge_weighted_digraph.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<stdexcept>
#include<string>
#include<iomanip>

namespace algorithmcpp {
	class DepthFirstOrder {
	private:
		std::vector<bool> marked_;
		std::vector<size_t> pre_number_;
		std::vector<size_t> post_number_;
		size_t pre_counter_=0;
		size_t post_counter_=0;
		Queue<size_t> pre_order_;
		Queue<size_t> post_order_;

	public:
		DepthFirstOrder(const Digraph &G) :
			marked_(std::vector<bool>(G.V())), pre_number_(std::vector<size_t>(G.V())), post_number_(std::vector<size_t>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (!marked_[v]) {
					Dfs(G, v);
				}
			}
		}

		DepthFirstOrder(const EdgeWeightedDigraph &G):
			marked_(std::vector<bool>(G.V())), pre_number_(std::vector<size_t>(G.V())), post_number_(std::vector<size_t>(G.V())) {
			for (size_t v = 0; v < G.V(); ++v) {
				if (!marked_[v]) {
					Dfs(G, v);
				}
			}
		}

	private:
		void Dfs(const Digraph &G, size_t v) {
			marked_[v] = true;
			pre_number_[v] = pre_counter_++;
			pre_order_.Enqueue(v);
			for (size_t w : G.Adj(v)) {
				if (!marked_[w]) {
					Dfs(G, w);
				}
			}
			post_order_.Enqueue(v);
			post_number_[v] = post_counter_++;
		}

		void Dfs(const EdgeWeightedDigraph &G, size_t v) {
			marked_[v] = true;
			pre_number_[v] = pre_counter_++;
			pre_order_.Enqueue(v);
			for (const DirectedEdge &e : G.Adj(v)) {
				size_t w = e.To();
				if (!marked_[w]) {
					Dfs(G, w);
				}
			}
			post_order_.Enqueue(v);
			post_number_[v] = post_counter_++;
		}

		void ValidateVertex(size_t v) const {
			size_t V=marked_.size();
			if (v >= V) throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(V - 1));
		}

	public:
		size_t Pre(size_t v) const {
			ValidateVertex(v);
			return pre_number_[v];
		}

		size_t Post(size_t v) const {
			ValidateVertex(v);
			return post_number_[v];
		}

		Queue<size_t> Post() const {
			return post_order_;
		}

		Queue<size_t> Pre() const {
			return pre_order_;
		}

		Stack<size_t> ReversePost() const {
			Stack<size_t> reverse;
			for (size_t v : post_order_) {
				reverse.Push(v);
			}
			return reverse;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/tinyDAG.txt");
			Digraph G(in);
			DepthFirstOrder dfs(G);
			std::cout << "   v  pre post" << "\n";
			std::cout << "--------------" << "\n";
			for (size_t v = 0; v < G.V(); ++v) {
				std::cout<<std::setw(4)<<v<< std::setw(4) <<dfs.Pre(v)<< std::setw(4) <<dfs.Post(v)<<"\n";
			}

			std::cout << "Preorder:  ";
			for (size_t v : dfs.Pre()) {
				std::cout << v << " ";
			}
			std::cout << "\n";

			std::cout << "Postorder:  ";
			for (size_t v : dfs.Post()) {
				std::cout << v << " ";
			}
			std::cout << "\n";

			std::cout << "Reverse postorder:  ";
			for (size_t v : dfs.ReversePost()) {
				std::cout << v << " ";
			}
			std::cout << "\n";
		}

	};
}