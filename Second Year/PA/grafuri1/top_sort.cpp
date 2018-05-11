#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include<stack>
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
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Faceti sortarea topologica a grafului stocat cu liste de
		adiacenta in adj.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
		vector<int> topsort;
		vector<int> muchii(n+1,0);

		stack<int> S;

		for (int i = 1; i <=n; i++) {
			for (int j = 0; j < adj[i].size();j++)
				muchii[adj[i][j]]++; 
		}

		for (int i = 1; i <=n; i++) {
			if (muchii[i] == 0)
				S.push(i);
		}

	    while (!S.empty()) { // cat timp mai am noduri de prelucrat
	        int u = S.top();
	        S.pop(); // scot un nod din multimea S
	        topsort.push_back(u);
	        for (int i = 0; i < adj[u].size(); i++) {
	        	if (--muchii[adj[u][i]] == 0)
	        		S.push(adj[u][i]);
	        }
	    }

	    return topsort;
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
