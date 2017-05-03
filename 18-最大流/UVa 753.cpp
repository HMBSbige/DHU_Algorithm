#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 5000;
const int INF = 0x3f3f3f3f;

struct Edge {
	int u, v, c, next;
	explicit Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
		u = u0; v = v0; c = c0; next = next0;
	}
} edge[MAXN * 10];
int head[MAXN * 2], cnt;
bool visited[MAXN * 2];
int path[MAXN * 2], from, to, maxflow, offflow, m, n, k;

struct node {
	string a, b;
	int no;
	node(string a0, string b0, int no0) {
		a = a0;  b = b0;  no = no0;
	}
};
vector <string> device;
map <string, vector <int> > plug;
vector <node> adapter;
void addEdge(int u, int v, int c) {
	edge[cnt] = Edge(u, v, c, head[u]);
	head[u] = cnt++;
}
bool bfs() {
	auto s = from;
	queue <int> q;
	q.push(s);
	memset(visited, false, sizeof(visited));
	while (!q.empty()) {
		s = q.front();
		q.pop();
		visited[s] = true;
		for (auto i = head[s]; i != -1; i = edge[i].next) {
			auto d = edge[i].v;
			if (!visited[d] && edge[i].c > 0) {
				path[d] = i;
				q.push(d);
				if (d == to) return true;
			}
		}
	}
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		memset(head, -1, sizeof(head));
		cnt = 0;
		maxflow = 0;
		device.clear();
		plug.clear();
		adapter.clear();
		//input
		//receptacle
		cin >> n;

		from = 0;
		to = MAXN + n;

		for (auto i = 0; i < n; ++i) {
			string name;
			cin >> name;
			plug[name].push_back(MAXN + i);
			// connect super sink with receptacle
			addEdge(MAXN + i, to, 1);
			addEdge(to, MAXN + i, 0);
		}

		// device
		cin >> m;
		for (auto i = 0; i < m; ++i) {
			string name, b;
			cin >> name >> b;
			device.push_back(b);
			// connext super source with device
			addEdge(0, i + 1, 1);
			addEdge(i + 1, 0, 0);
		}

		// adapter
		cin >> k;
		for (auto i = 0; i < k; ++i) {
			string a, b;
			cin >> a >> b;
			plug[a].push_back(m + i + 1);
			adapter.push_back(node(a, b, m + i + 1));
		}

		// connect device with adapter or receptacle
		for (auto i = 0; i < m; ++i) {
			for (auto j = 0; j < plug[device[i]].size(); ++j) {
				addEdge(i + 1, plug[device[i]][j], 1);
				addEdge(plug[device[i]][j], i + 1, 0);
			}
		}

		// connect adapter with adapter or receptacle
		for (auto i = 0; i < adapter.size(); ++i) {
			for (auto j = 0; j < plug[adapter[i].b].size(); ++j) {
				addEdge(adapter[i].no, plug[adapter[i].b][j], INF);
				addEdge(plug[adapter[i].b][j], adapter[i].no, 0);
			}
		}


		while (bfs()) {
			offflow = MAXN;
			for (auto i = to; i != from; i = edge[path[i]].u) {
				if (edge[path[i]].c < offflow)
					offflow = edge[path[i]].c;
			}
			for (auto i = to; i != from; i = edge[path[i]].u) {
				edge[path[i]].c -= offflow;
				edge[path[i] ^ 1].c += offflow;
			}
			maxflow += offflow;
		}
		cout << m - maxflow << endl;
		if (T) 
			cout << endl;
	}
	return 0;
}