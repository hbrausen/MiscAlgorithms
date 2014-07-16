#include <vector>
#include <list>
#include <limits>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

struct Edge {
	Edge() : dst(0), len(0) {}
	Edge(int dst, int len) : dst(dst), len(len) {}
	int dst, len;
};

struct Graph {
	Graph(int N) : graph(N, list<Edge>()) {}
	void addEdge(int src, int dst, int len) { graph[src].push_back(Edge(dst, len)); }
	vector<list<Edge> > graph;
};

vector<int> Dijkstra(const Graph& G, int src)
{
	vector<bool> visited(G.graph.size(), false);
	vector<int> distance(G.graph.size(), numeric_limits<int>::max());
	vector<int> prev(G.graph.size(), -1);
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	
	distance[src] = 0;
	q.push(make_pair(0, src));
	
	while (!q.empty()) {
		pair<int, int> entry = q.top(); q.pop();
		int cur = entry.second;
		if (visited[cur]) continue;
		for (list<Edge>::const_iterator it = G.graph[cur].begin(); it != G.graph[cur].end(); ++it) {
			if (visited[it->dst]) continue;
			if (distance[cur] + it->len < distance[it->dst]) {
				distance[it->dst] = distance[cur] + it->len;
				prev[it->dst] = cur;
				q.push(make_pair(distance[it->dst], it->dst));
			}
		}
		visited[cur] = true;
	}
	return prev;
}
