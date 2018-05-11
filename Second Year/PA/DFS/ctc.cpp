#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
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
	vector<int> adjt[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

// in stiva pun ordinea de la sortarea topologica, din DFS N
//graf  transpus => sensul muchiilor este inversat -> din nodurile obtinute pot ajunge in nodul sursa
// ma voi duce pe muchiile care intra in nod, nu pe cele car ies(mod normal)
//pe istiva la dfs le punem in ordinea terminarii ca la sortarea topologica

// inn radacina ultimului arbore DFS N nu intra compoenenta din alt arbore dfs!!
// => componenta tare conexa
// urmatoarea componenta din stiva sigur este radacina unui arbore DFS (nu neaparat intreg), altfel ar fi fost
// gasita mai devreme sau deloc. 	
	void dfs(int nod, stack<int> &s, vector<int> &visited) {
		visited[nod] = 1;  // gri
		for (int i = 0; i < adj[nod].size(); ++i) {
			if (visited[adj[nod][i]] == 0) {
				dfs(adj[nod][i], s, visited);  //vizitez toate nodurile adiacente
			}
		}
		s.push(nod);	// pun pe stiva nodurile
		visited[nod] = 2;  //negru
	}

	void dfsT(int nod, vector<int> &visited, vector< vector<int> > &sol) {
		visited[nod] = 1;
		for (int i = 0; i < adjt[nod].size(); ++i) {
			if (visited[adjt[nod][i]] == 0) {
				dfsT(adjt[nod][i], visited, sol);
			}
		}
		sol.back().push_back(nod); //pun in vector, nu mai folosec stiva
		visited[nod] = 2;
	}

	vector< vector<int> > get_result() {
		vector< vector<int> > sol;

		stack<int> s;
		vector<int> visited(n + 1);

		for (int i = 1; i <= n; ++ i) {
			if (visited[i] == 0) {
				dfs(i, s, visited);
			}
		}

		for (int i = 1; i <= n; ++i) {
			printf("se termina in i = %d pasi\n",i );
			visited[i] = 0;
		}

		while(!s.empty()) {  //avem elemente in stiva
			if (visited[s.top()] == 0) {
				sol.push_back(vector<int>());
				dfsT(s.top(), visited, sol);
				s.pop();
			} else {
				s.pop();
			}
		}

		return sol;
	}

	void print_output(vector< vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
			}
			fout << '\n';
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
