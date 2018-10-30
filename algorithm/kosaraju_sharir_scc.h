#pragma once
#include"digraph.h"
#include<vector>
#include"depth_first_order.h"

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

	public:
		size_t count() const {

		}
	};
}
