#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];

	struct Edge {
		int x;
		int y;
	};

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	void dfsB(int nod, int parent, int &step, vector<int> &idx, vector<int> &low, vector<Edge> &sol) {
		idx[nod] = step;
		low[nod] = step;
		step++;

		for (int i = 0; i < adj[nod].size(); ++i) {
			if (adj[nod][i] != parent) {
				if (idx[adj[nod][i]] == -1) {
					dfsB(adj[nod][i], nod, step, idx, low, sol);
					low[nod] = min(low[nod], low[adj[nod][i]]);
					if (low[adj[nod][i]] > idx[nod]) {
						Edge curr;
						curr.x = nod;
						curr.y = adj[nod][i];
						sol.push_back(curr);
					}
				} else {
					low[nod] = min(low[nod], idx[adj[nod][i]]);
				}
			}
		}
	}

	vector<Edge> get_result() {
		vector<Edge> sol;

		vector<int> idx(n + 1);
		vector<int> low(n + 1);

		for (int i = 1; i <= n; ++i) {
			idx[i] = low[i] = -1;
		}

		int step = 0;
		for (int i = 1; i <= n; ++i) {
			if (idx[i] == -1) {
				dfsB(i, i, step, idx, low, sol);
			}
		} 

		return sol;
	}

	void print_output(vector<Edge> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i].x << ' ' << result[i].y << '\n';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
