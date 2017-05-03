#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 5010;
const int INF = 0x3f3f3f3f;
const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

struct Edge {
	int u, v, c, next;
	explicit Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
		u = u0; v = v0; c = c0; next = next0;
	}
}edge[MAXN * 10];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, maxflow, offflow, nCase, S, A, B;

void addEdge(int u, int v, int c) {
	edge[cnt] = Edge(u, v, c, head[u]);
	head[u] = cnt++;
	edge[cnt] = Edge(v, u, 0, head[v]);
	head[v] = cnt++;
}

bool bfs(int &min) {
	auto s = from;
	queue <int> q;
	q.push(s);
	memset(visited, false, sizeof(visited));
	while (!q.empty()) {
		s = q.front();
		q.pop();
		for (auto i = head[s]; i != -1; i = edge[i].next) {
			auto d = edge[i].v;
			if (!visited[d] && edge[i].c > 0) {
				visited[d] = true;
				if (edge[i].c < min) min = edge[i].c;
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
	cin >> nCase;
	while (nCase--) {
		memset(head, -1, sizeof(head));
		cnt = 0;
		maxflow = 0;
		cin >> S >> A >> B;
		from = 0;	to = S*A * 2 + 1;
		for (auto i = 1; i <= B; ++i) {
			int x, y;
			cin >> x >> y;
			addEdge(from, (x - 1)*A + y, 1);
		}
		for (auto i = 1; i <= A; ++i) {
			addEdge(i + S*A, to, 1);
			addEdge((S - 1)*A + i + S*A, to, 1);
		}
		for (auto i = 2; i < S; ++i) {
			addEdge((i - 1)*A + 1 + S*A, to, 1);
			addEdge((i - 1)*A + A + S*A, to, 1);
		}
		for (auto i = 1; i <= S; ++i) {
			for (auto j = 1; j <= A; ++j) {
				auto a = (i - 1)*A + j + S*A;
				addEdge(a - S*A, a, 1);
				for (auto k = 0; k < 4; ++k) {
					auto x = i + dx[k], y = j + dy[k];
					if (x >= 1 && x <= S && y >= 1 && y <= A) {
						auto b = (x - 1)*A + y;
						addEdge(a, b, 1);
					}
				}
			}
		}
		auto min = INF;
		while (bfs(min)) {
			offflow = min;
			for (auto i = to; i != from; i = edge[path[i]].u) {
				edge[path[i]].c -= offflow;
				edge[path[i] ^ 1].c += offflow;
			}
			maxflow += offflow;
			min = INF;
		}
		if (maxflow == B)
			cout << "possible" << endl;
		else
			cout << "not possible" << endl;
	}
	return 0;
}