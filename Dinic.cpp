const int N = 1e4 + 4;

struct edge {
	int a, b, cap, flow;
};

int n, s = 1, t, d[N], ptr[N], q[N];
vector<edge> e;
vi g[N];

void add_edge(int a, int b, int cap) {
	edge e1 = {a, b, cap, 0};
	edge e2 = {b, a, 0, 0};
	g[a].pb((int)e.size());
	e.pb(e1);
	g[b].pb((int)e.size());
	e.pb(e2);
}

bool bfs() {
	int qh = 0, qt = 0;
	q[qt++] = s;
	memset(d, -1, sizeof d);
	d[s] = 0;
	while (qh < qt and d[t] == -1) {
		int v = q[qh++];
		for (int i = 0; i < g[v].size(); i++) {
			int id = g[v][i];
			int to = e[id].b;
			if (d[to] == -1 and e[id].flow < e[id].cap) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
		}
	}
	return (d[t] != -1);
}

int dfs(int v, int flow) {
	if (!flow) return 0;
	if (v == t) return flow;
	for (; ptr[v] < (int)g[v].size(); ptr[v]++) {
		int id = g[v][ptr[v]];
		int to = e[id].b;
		if (d[to] != d[v] + 1) continue;
		int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
		if (pushed) {
			e[id].flow += pushed;
			e[id ^ 1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}

int dinic() {
	int flow = 0;
	for (;;) {
		if (!bfs()) break;
		memset(ptr, 0, sizeof ptr);
		while (int pushed = dfs(s, inf)) flow += pushed;
	}
	return flow;
}
