#include <iostream>
#include <sstream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 5000;
struct Edge {
	int u, v, c, next;
	explicit Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
		u = u0; v = v0; c = c0; next = next0;
	}
} edge[MAXN * 10];
int head[MAXN * 2], cnt; // 前向星存储结构

bool visited[MAXN * 2];
int path[MAXN * 2], from, to, maxflow, offflow, n, nApp, sum;
char ans[11];
vector <char> app;

void addEdge(int u, int v, int c) {
	edge[cnt] = Edge(u, v, c, head[u]);
	head[u] = cnt++;
	edge[cnt] = Edge(v, u, 0, head[v]);
	head[v] = cnt++;
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
				visited[d] = true;
				path[d] = i;
				q.push(d);
				if (d == to) return true;
			}
		}
	}
	return false;
}
int main() {
	string line;
	while (getline(cin, line)) {
		memset(head, -1, sizeof(head));
		cnt = 0;
		maxflow = 0;
		nApp = 1;
		sum = 0;
		app.clear();
		char ch;
		int n;
		string computer;

		stringstream ss(line);
		ss >> ch >> n >> computer;
		sum += n;
		app.push_back(ch);  // 记录App的名称
		addEdge(0, 10 + nApp, n);
		for (auto j = 0; j < computer.length() - 1; ++j) {
			addEdge(10 + nApp, computer[j] - '0' + 1, 1);
		}

		while (getline(cin, line) && line != "") {
			nApp++;
			stringstream sss(line);
			sss >> ch >> n >> computer;
			sum += n;
			app.push_back(ch);
			addEdge(0, 10 + nApp, n);
			for (auto j = 0; j < computer.length() - 1; ++j) {
				addEdge(10 + nApp, computer[j] - '0' + 1, 1);
			}
		}

		from = 0;  to = 10 + nApp + 1;

		for (auto i = 1; i <= 10; ++i) {
			addEdge(i, to, 1);
		}

		for (auto i = 1; i <= 10; ++i) {
			ans[i] = '_';
		}

		while (bfs()) {
			offflow = MAXN;
			for (auto i = to; i != from; i = edge[path[i]].u) {
				if (edge[path[i]].c < offflow)
					offflow = edge[path[i]].c;
			}
			for (auto i = to; i != from; i = edge[path[i]].u) {
				if (i >= 1 && i <= 10) if (path[i] != -1) {
					ans[i] = app[edge[path[i]].u - 11];
				}
				edge[path[i]].c -= offflow;
				edge[path[i] ^ 1].c += offflow;
			}
			maxflow += offflow;
		}
		if (maxflow >= sum) {
			for (auto i = 1; i <= 10; ++i) {
				cout << ans[i];
			}
			cout << endl;
		}
		else
			cout << "!" << endl;

	}
	return 0;
}