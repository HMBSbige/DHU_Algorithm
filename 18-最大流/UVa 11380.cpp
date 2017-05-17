#include <iostream>
#include <cstring>
#include <string>
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
} edge[MAXN * 10];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, maxflow, offflow, nCase, X, Y, P;

void addEdge(int u, int v, int c) {
	edge[cnt] = Edge(u, v, c, head[u]);
	head[u] = cnt++;
	edge[cnt] = Edge(v, u, 0, head[v]);
	head[v] = cnt++;
}

int in(int x, int y) {return (x - 1)*Y + y;}
int out(int x, int y) {return (x - 1)*Y + y + X*Y;}
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
	while (cin >> X >> Y >> P) {
		memset(head, -1, sizeof(head));
		cnt = 0;
		maxflow = 0;
		string graph[40], line;
		cin.ignore();
		for (auto i = 1; i <= X; ++i) {
			graph[i].push_back(' ');
			getline(cin, line);
			graph[i] += line;
			graph[i].push_back(' ');
		}
		from = 0;  to = 2 * X*Y + 1;

		for (auto i = 1; i <= X; ++i) {
			for (auto j = 1; j <= Y; ++j) {
				if (graph[i][j] == '*') {
					addEdge(from, in(i, j), 1);
				}
				if (graph[i][j] == '#') {
					addEdge(out(i, j), to, P);
				}
				if (graph[i][j] != '.' && graph[i][j] != '*') {
					addEdge(in(i, j), out(i, j), INF);
				}
				else if (graph[i][j] == '~') {
					addEdge(in(i, j), out(i, j), 0);
				}
				else {
					addEdge(in(i, j), out(i, j), 1);
				}
				for (auto k = 0; k < 4; ++k) {
					auto x = i + dx[k], y = j + dy[k];
					if (x >= 1 && x <= X && y >= 1 && y <= Y) {
						if (graph[x][y] != '~') {
							addEdge(out(i, j), in(x, y), INF);
						}
					}
				}
			}
		}
		auto min = INF;
		while (bfs(min)) {
			offflow = MAXN;
			offflow = min;
			for (auto i = to; i != from; i = edge[path[i]].u) {
				edge[path[i]].c -= offflow;
				edge[path[i] ^ 1].c += offflow;
			}
			maxflow += offflow;
			min = INF;
		}
		cout << maxflow << endl;
	}
	return 0;
}