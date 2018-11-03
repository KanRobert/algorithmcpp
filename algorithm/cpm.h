#pragma once
#include"edge_weighted_digraph.h"
#include"acyclic_lp.h"
#include<fstream>
#include<iostream>
#include<iomanip>

namespace algorithmcpp {
	class CPM {
	public:
		CPM() = delete;
		CPM(const CPM&) = default;
		CPM(CPM &&) noexcept = default;
		CPM &operator=(const CPM &) = default;
		CPM &operator=(CPM &&) noexcept = default;
		~CPM() = default;

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::ifstream in("../file/jobsPC.txt");
			size_t n;
			in >> n;
			size_t source = 2 * n;
			size_t sink = 2 * n + 1;
			EdgeWeightedDigraph G(2 * n + 2);
			for (size_t i = 0; i < n; ++i) {
				double duration;
				in >> duration;
				G.AddEdge(DirectedEdge(source, i, 0.0));
				G.AddEdge(DirectedEdge(i + n, sink, 0.0));
				G.AddEdge(DirectedEdge(i, i + n, duration));

				size_t m;
				in >> m;
				for (size_t j = 0; j < m; ++j) {
					size_t precedent;
					in >> precedent;
					G.AddEdge(DirectedEdge(n + i, precedent, 0.0));
				}
			}

			AcyclicLP lp(G, source);
			std::cout << " job   start  finish" << "\n";
			std::cout << "--------------------" << "\n";
			for (size_t i = 0; i < n; ++i) {
				std::cout << std::setw(4) << i << " " << std::setw(7) << std::fixed << std::setprecision(1) << lp.DistTo(i) << " " << std::setw(7) << std::fixed << std::setprecision(1) << lp.DistTo(i + n) << std::endl;
			}
			std::cout << "Finish time: " << std::setw(7) << std::fixed << std::setprecision(1) << lp.DistTo(sink) << std::endl;
		}
	};
}