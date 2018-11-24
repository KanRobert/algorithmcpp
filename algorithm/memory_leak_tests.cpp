#pragma warning (disable : 4996)

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include"acyclic_lp.h"
#include"acyclic_sp.h"
#include"average.h"
#include"avltree_st.h"
#include"bag.h"
#include"bellman_ford_sp.h"
#include"binary_search.h"
#include"bipartite.h"
#include"bipartite_matching.h"
#include"bipartite_x.h"
#include"breadth_first_directed_paths.h"
#include"breadth_first_paths.h"
#include"bst.h"
#include"btree.h"
#include"cc.h"
#include"count.h"
#include"counter.h"
#include"cpm.h"
#include"date.h"
#include"depth_first_directed_paths.h"
#include"depth_first_paths.h"
#include"depth_first_order.h"
#include"digraph.h"
#include"dijkstra_sp.h"
#include"dijkstra_undirected_sp.h"
#include"directed_cycle.h"
#include"directed_edge.h"
#include"doubling_ratio.h"
#include"edge.h"
#include"edge_weighted_digraph.h"
#include"edge_weighted_directed_cycle.h"
#include"edge_weighted_graph.h"
#include"flow_edge.h"
#include"flow_network.h"
#include"ford_fulkerson.h"
#include"graph.h"
#include"graph_generator.h"
#include"heap.h"
#include"index_max_pq.h"
#include"index_min_pq.h"
#include"kosaraju_sharir_scc.h"
#include"kruskal_mst.h"
#include"lazy_prim_mst.h"
#include"linear_probing_hashst.h"
#include"longest_common_substring.h"
#include"longest_repeated_substring.h"
#include"lsd.h"
#include"max_pq.h"
#include"merge.h"
#include"merge_bu.h"
#include"merge_x.h"
#include"min_pq.h"
#include"msd.h"
#include"point2d.h"
#include"prim_mst.h"
#include"queue.h"
#include"quick.h"
#include"quick_3way.h"
#include"quick_find_uf.h"
#include"quick_union_uf.h"
#include"quick_x.h"
#include"quick_3_string.h"
#include"redblack_bst.h"
#include"resizing_array_bag.h"
#include"separate_chaining_hashst.h"
#include"sequential_search_st.h"
#include"set.h"
#include"shell.h"
#include"sparse_vector.h"
#include"st.h"
#include"stack.h"
#include"stdrandom.h"
#include"stopwatch.h"
#include"stopwatch_win32.h"
#include"suffix_array.h"
#include"suffix_array_x.h"
#include"symbol_digraph.h"
#include"symbol_graph.h"
#include"three_sum.h"
#include"three_sum_fast.h"
#include"topological.h"
#include"topological_x.h"
#include"trimmer.h"
#include"uf.h"
#include"vector.h"
#include"weighted_quick_union_uf.h"
#include"white_filter.h"
#include"whitelist.h"


using namespace algorithmcpp;


int main(int argc, char *argv[]) {
	//Average::MainTest();
	//AVLTreeST<int, int>::MainTest();
	//Bag<int>::MainTest();
	//BinarySearch<int>::MainTest();
	//BreadthFirstDirectedPaths::MainTest();
	//BreadthFirstPaths::MainTest();
	//BST<int, int>::MainTest();
	//BTree<int, int>::MainTest();
	//Queue<int>::MainTest();
	//RedBlackBST<int, int>::MainTest();
	//Stack<int>::MainTest();
	//IndexMaxPQ<double>::MainTest();
	//IndexMinPQ<double>::MainTest();
	//MaxPQ<int>::MainTest();
	//MinPQ<int>::MainTest();
	//Whitelist::MainTest();
	//WhiteFilter::MainTest();
	//Merge<int>::MainTest();
	//MergeX<int>::MainTest();
	//MergeBU<int>::MainTest();
	//ResizingArrayBag<int>::MainTest();
	//Vector::MainTest();
	//UF::MainTest();
	//StdRandom::MainTest();
	//ST<int, int>::MainTest();
	//Stopwatch::MainTest();
	//StopwatchWin32::MainTest();
	//SparseVector::MainTest();
	//ThreeSum::MainTest();  //take about 70 seconds, no patience To wait
	//ThreeSumFast::MainTest();
	//Count::MainTest();
	//Counter::MainTest();
	//Quick<int>::MainTest();
	//QuickX<int>::MainTest();
	//Quick3way<int>::MainTest();
	//SequentialSearchST<int, int>::MainTest();
	//SeparateChainingHashST<int, int>::MainTest();
	//LinearProbingHashST<int, int>::MainTest();
	//Count::MainTest();
	//Counter::MainTest();
	//WeightedQuickUnionUF::MainTest();
	//Date::MainTest();
	//Point2D::MainTest();
	//DoublingRatio::MainTest();
	//Heap<int>::MainTest();
	//CC::MainTest();
	//Graph::MainTest();
	//Digraph::MainTest();
	//Edge::MainTest();
	//EdgeWeightedGraph::MainTest();
	//DirectedEdge::MainTest();
	//DepthFirstDirectedPaths::MainTest();
	//KruskalMST::MainTest();
	//LazyPrimMST::MainTest();
	//PrimMST::MainTest();
	//EdgeWeightedDigraph::MainTest();
	//DepthFirstPaths::MainTest();
	//BreadthFirstDirectedPaths::MainTest();
	//DirectedCycle::MainTest();
	//EdgeWeightedDirectedCycle::MainTest();
	//DepthFirstOrder::MainTest();	
	//SymbolGraph::MainTest();
	//SymbolDigraph::MainTest();
	//Topological::MainTest();
	//TopologicalX::MainTest();
	//KosarajuSharirSCC::MainTest();
	//DijkstraUndirectedSP::MainTest();
	//DijkstraSP::MainTest();
	//AcyclicSP::MainTest();
	//AcyclicLP::MainTest();
	//CPM::MainTest();
	//BellmanFordSP::MainTest();
	//LSD::MainTest();
	//MSD::MainTest();
	//Quick3String::MainTest();
	//SuffixArray::MainTest();
	//Trimmer::MainTest();
	//SuffixArrayX::MainTest();
	//LongestRepeatedSubstring::MainTest();
	//LongestCommonSubstring::MainTest();
	//FlowEdge::MainTest();
	//FlowNetwork::MainTest();
	//FordFulkerson::MainTest();
	//Set<int>::MainTest();
	//GraphGenerator::MainTest();
	//Bipartite::MainTest();
	//BipartiteX::MainTest();
	BipartiteMatching::MainTest();
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}