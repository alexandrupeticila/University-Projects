#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
#include <climits>
using namespace std;

const int kNmax = 50005;

// BellmanFord
class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source;
	vector<pair<int, int> > adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti distantele minime de la nodul source la celelalte noduri
		folosind BellmanFord pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.

		In cazul in care exista ciclu de cost negativ, returnati un vector gol:
			return vector<int>();
		*/
		vector<int> d(n + 1, 0);
		vector<bool> visited(n, false);
		int i, j, k;

		for (i = 1; i <= n; i++) {
			d[i] = INT_MAX/10;
		}
		
		d[source] = 0;

		//initializam toate pozitiile(nodurile) catre care avem muchii din sursa
		for (i = 0; i < adj[source].size(); i++ ) {
			d[ adj[source][i].first ] = d[source] + adj[source][i].second;
		}


		bool relaxari = true;

		//ma opresc cand nu mai sunt relaxari de facut
		for (i = 1; i < n - 1; i++) {
			if (relaxari == false)
				return d;
			relaxari = false;

			//parcurg toate muchiile si fac relaxarile necasare
			for (j = 1; j <= n; j++) {
				for (k = 0; k < adj[j].size(); k++){
					int aux = d[j] + adj[j][k].second;
					if (d[adj[j][k].first] > aux) {
						d[adj[j][k].first] = aux;
						relaxari = true;
					}
				}
			}
		}

		//daca se mai pot relaxa muchii
		//intoarcem  un vector gol
		for (j = 1; j <= n; j++) {
			for (k = 0; k < adj[j].size(); k++){
				if (d[adj[j][k].first] > d[j] + adj[j][k].second) {
					return vector<int>();
				}		
			}
		}

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		if (result.size() == 0) {
			fout << "Ciclu negativ!\n";
		} else {
			for (int i = 1; i <= n; i++) {
				fout << result[i] << ' ';
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
