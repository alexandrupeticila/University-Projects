#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <climits>
using namespace std;

const int kNmax = 50005;

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
		folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.
		*/
		vector<int> d(n + 1, INT_MAX);
		vector<bool> visited(n, false);
		set<pair<int, int>> s;
		int i, j;

		d[source] = 0; 
		
		s.insert(make_pair(0, source));
		
		while (!s.empty()){
			int nod = (*s.begin()).second;

			//scot primul nod din multime.
			s.erase(s.begin());
			if (visited[nod] == true)
				continue;
			visited[nod] = true;

			// pentru fiecare nod din vecinii lui 'nod'
			for (i = 0; i < adj[nod].size(); i++ ) {

				int aux = d[nod] + adj[nod][i].second;

				//daca distanta  de la sursa la nodul i prin 'nod' este mai mica
				// atunci actualiza distanta
				// introduc in multime nodul adiacent cu costul lui
				if (!visited[ adj[nod][i].first ] && d[ adj[nod][i].first ] > aux ) {

					d[ adj[nod][i].first ] = aux;
					s.insert(make_pair(d[ adj[nod][i].first ], adj[nod][i].first));
				}
			}
		}

		// nu se poate ajunge de la source la nodul i
		for (i = 1; i <= n; i++) {
			if (d[i] == INT_MAX)
				d[i] = -1;
		}
		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << " ";
		}
		fout << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
