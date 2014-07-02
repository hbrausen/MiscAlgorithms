#include <vector>
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
};

vector<int> BellmanFord(const Graph& G, int source)
{
	vector<int> dist(G.edges.size(), numeric_limits<int>::max());
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

int main(int argc, char **argv)
{
	return 0;
}