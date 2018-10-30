#pragma once
#include"st.h"
#include"digraph.h"
#include<string>
#include<vector>
#include<memory>
#include<fstream>
#include<iostream>
#include<sstream>
#include<stdexcept>

namespace algorithmcpp {
	class SymbolDigraph {
	private:
		ST<std::string, size_t> st_;
		std::vector<std::string> keys_;
		std::shared_ptr<Digraph> p_graph_;

	public:
		SymbolDigraph() = delete;
		SymbolDigraph(const SymbolDigraph&) = default;
		SymbolDigraph(SymbolDigraph &&) noexcept = default;
		SymbolDigraph &operator=(const SymbolDigraph &) = default;
		SymbolDigraph &operator=(SymbolDigraph &&) noexcept = default;
		~SymbolDigraph() = default;

		SymbolDigraph(const std::string &filename,char delimiter) {
			std::ifstream in(filename);
			std::string line;
			std::istringstream linestream;
			while (std::getline(in, line)) {
				std::istringstream linestream(line);
				std::string name;
				while (std::getline(linestream, name, delimiter)) {
					if (!st_.Contains(name)) {
						st_.Put(name, st_.Size());
					}
				}
			}
			std::cout << "Done reading " << filename << std::endl;

			keys_.resize(st_.Size());
			for (const std::string &name : st_.Keys()) {
				keys_[st_.Get(name).value()] = name;
			}

			p_graph_ = std::make_shared<Digraph>(st_.Size());
			in.clear();
			in.seekg(0, in.beg);
			while (std::getline(in, line)) {
				std::istringstream linestream(line);
				std::string name;
				std::getline(linestream, name, delimiter);
				size_t v = st_.Get(name).value();
				while (std::getline(linestream, name, delimiter)) {
					size_t w = st_.Get(name).value();
					p_graph_->AddEdge(v, w);
				}
			}
		}

	private:
		void ValidateVertex(size_t v) const {
			size_t n_vertices = p_graph_->V();
			if (v >= n_vertices)
				throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(n_vertices - 1));
		}

	public:

		bool Contains(const std::string &s) const {
			return st_.Contains(s);
		}

		size_t IndexOf(const std::string &s) const {
			return st_.Get(s).value();
		}

		std::string NameOf(size_t v) const {
			ValidateVertex(v);
			return keys_[v];
		}

		Digraph InDigraph() const {
			return *p_graph_;
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::string filename("../file/routes.txt");
			SymbolDigraph sg(filename,' ');
			Digraph digraph = sg.InDigraph();
			std::vector<std::string> routes{ "JFK","ORD","LAS" };
			for (const std::string &source : routes) {
				if (sg.Contains(source)) {
					size_t s = sg.IndexOf(source);
					std::cout << source << ": ";
					for (size_t v : digraph.Adj(s)) {
						std::cout << " " << sg.NameOf(v);
					}
					std::cout << "\n";
				}
				else {
					std::cout << "input not contain " << source << "\n";
				}
			}
		}
	};
}