#pragma once
#include"digraph.h"
#include"depth_first_order.h"
#include"queue.h"
#include<vector>
#include<fstream>
#include<iostream>

namespace algorithmcpp {
	class KosarajuSharirSCC {
	private:
		std::vector<bool> marked_;
		std::vector<size_t> id_;
		size_t count_ = 0;

	public:
		KosarajuSharirSCC() = delete;
		KosarajuSharirSCC(const KosarajuSharirSCC &) = default;
		KosarajuSharirSCC(KosarajuSharirSCC &&) noexcept = default;
		KosarajuSharirSCC &operator=(const KosarajuSharirSCC &) = default;
		KosarajuSharirSCC &operator=(KosarajuSharirSCC &&) noexcept = default;
		~KosarajuSharirSCC() = default;

	public:
		KosarajuSharirSCC(const Digraph &G) :marked_(std::vector<bool>(G.V())), id_(std::vector<size_t>(G.V())){
			DepthFirstOrder dfs(G.Reverse());
			for (size_t v : dfs.ReversePost()) {
				if (!marked_[v]) {
					Dfs(G, v);
					++count_;
				}
			}
		}

	private:
		void Dfs(const Digraph &G, size_t v) {
			marked_[v] = true;
			id_[v] = count_;
			for (size_t w : G.Adj(v)) {
				if (!marked_[w]) Dfs(G, w);
			}
		}

		void ValidateVertex(size_t v) const {
			size_t n_vertices = marked_.size();
			if (v >= n_vertices)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices - 1));
		}

	public:
		size_t Count() const {
			return count_;
		}

		bool StronglyConnected(size_t v, size_t w) const {
			ValidateVertex(v);
			ValidateVertex(w);
			return id_[v] == id_[w];
		}

		size_t Id(size_t v) const {
			ValidateVertex(v);
			return id_[v];
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/mediumDG.txt");
			Digraph G(in);
			KosarajuSharirSCC scc(G);

			size_t m = scc.Count();
			std::cout << m << " strong components" << "\n";
			std::vector<Queue<size_t>> components(m);
			for (size_t v = 0; v < G.V(); ++v) {
				components[scc.Id(v)].Enqueue(v);
			}

			for (size_t i = 0; i < m; ++i) {
				for (size_t v : components[i]) {
					std::cout << v << " ";
				}
				std::cout << "\n";
			}
		}
	};
}
