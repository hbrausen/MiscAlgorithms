#include <vector>
#include <set>
#include <utility>
#include <limits>

using namespace std;

struct Edge {
	Edge(int a, int b) : a(a), b(b) {}
	int a, b;
};

typedef pair<Edge, int> WeightedEdge;
typedef vector<WeightedEdge>::const_iterator WeightedGraphIterator;

struct Graph {
	vector<WeightedEdge> edges;
	set<int> nodes;
	void AddEdge(int a, int b, int w)
	{
		nodes.insert(a);
		nodes.insert(b);
		edges.push_back(make_pair(Edge(a,b), w));
	}
	void AddBiEdge(int a, int b, int w) { AddEdge(a,b,w); AddEdge(b,a,w); }
};

vector<int> BellmanFord(const Graph& G, int source)
{
	vector<int> dist(G.nodes.size(), numeric_limits<int>::max());
	dist[source] = 0;
	for (int i = 0; i < G.edges.size()-1; ++i)
		for (WeightedGraphIterator it = G.edges.begin(); it != G.edges.end(); ++it)
			dist[it->first.b] = min(dist[it->first.b], dist[it->first.a] + it->second);
	return dist;
}

bool HasNegativeCycle(const Graph& G, const vector<int>& dist)
{
	for (WeightedGraphIterator it = G.edges.begin(); it != G.edges.end(); ++it)
		if (dist[it->first.a] + it->second < dist[it->first.b]) return true;
	return false;
}
