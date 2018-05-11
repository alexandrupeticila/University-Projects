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

	void dfsCV(int nod, int &step, vector<int> &idx, vector<int> &low, vector<int> &sol, bool rad) {
		idx[nod] = step;
		low[nod] = step;
		step++;	

		vector<int> copii;
		for (int i = 0; i < adj[nod].size(); ++i) {
			if (idx[adj[nod][i]] == -1) {
				copii.push_back(adj[nod][i]);
				dfsCV(adj[nod][i], step, idx, low, sol, false);
				low[nod] = min(low[adj[nod][i]], low[nod]);
			} else {
				low[nod] = min(idx[adj[nod][i]], low[nod]);
			}
		}

		if (rad) { //primul pas->nodul root
			if (copii.size() >= 2) { 
				sol.push_back(nod);
			}
		} else {
			for (int i = 0; i < copii.size(); ++i) {
				if (low[copii[i]] >= idx[nod]) {
					sol.push_back(nod);
					break;
				}
			}
		}
	}

	vector<int> get_result() {
		vector<int> sol;

		vector<int> idx(n + 1);
		vector<int> low(n + 1);

		for (int i = 1; i <= n; ++i) {
			idx[i] = low[i] = -1;
		}

		int step = 0;
		bool rad = true;
		for (int i = 1; i <= n; ++i) {
			if (idx[i] == -1) {
				dfsCV(i, step, idx, low, sol, true);
			}
		} 

		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
