typedef vector<list<int> >::const_iterator ConstNodeIterator;
typedef list<int>::const_iterator ConstEdgeIterator;

struct Graph {
	Graph(int N) : graph(N, list<int>()) {}
	void addEdge(int src, int dst) { graph[src].push_back(dst); }
	void reverse() {
		vector<list<int> > rGraph(graph.size(), list<int>());
		for (int i = 0; i < graph.size(); ++i) {
			for (ConstEdgeIterator it = graph[i].begin(); it != graph[i].end(); ++it) {
				rGraph[*it] = i;
			}
		}
		graph = rGraph;
	}
	vector<list<int> > graph;
};

void DFS(const Graph& G, int node, vector<bool>& visited, stack<int>& order)
{
	visited[node] = true;
	for (ConstEdgeIterator it = G.graph.begin(); it != G.graph.end(); ++it)
		if (!visited[*it]) DFS(G, *it, visited);
	order.push(node);
}

list<list<int> > SCC(Graph& G)
{
	vector<bool> visited(G.graph.size(), false);
	stack<int> order;
	for (int i = 0; i < visited.size(); ++i)
		if (!visited[i]) DFS(G, i, visited, order);
	G.reverse();
	visited = vector<bool>(G.graph.size(), false);
	list<list<int> > components;
	while (!order.empty()) {
		while (visited[order.top()]) order.pop();
		
	}
}
