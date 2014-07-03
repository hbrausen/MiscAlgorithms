#include "bellmanford.cpp"

#include <iostream>

int main(int argc, char **argv)
{
	// Simple graph for testing purposes.
	Graph G;
	G.AddEdge(0, 1, 1);
	G.AddEdge(1, 2, 1);
	G.AddEdge(2, 3, 1);
	G.AddEdge(3, 0, -3);
	vector<int> dists = BellmanFord(G, 0);
	for (int i = 0;i < dists.size(); ++i)
		cout << i << '\t' << dists[i] << endl;
	cout << "Negative cycle:\t" << HasNegativeCycle(G, dists) << endl;
	return 0;
}
