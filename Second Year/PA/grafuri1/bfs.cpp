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
	int source;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result() {
		vector<int> d(n + 1);
		vector<bool> visited(n + 1);
		
		for (int i = 1; i < n + 1; i++)
			visited[i] = false;
		
		visited[source] = true;
		
		queue <int> queue;
		queue.push(source);
		d[source] = 0; // distanta pana la sursa este 0
		int node;
		int vecin;
		while (!queue.empty())	// coada are elemente
		{
			node = queue.front();	// scot primul element din coada
			queue.pop();
		 	for (int i = 0; i < adj[node].size(); i++)
		 	{

			  	vecin = adj[node][i];
				if (!visited[vecin])	// daca nodul vecin nu a fost vizitat
				{
					d[vecin] = d[node] + 1;	// lungimea drumului pana la vecinul lui node este lungimea pana la nod + 1
					visited[vecin] = true;	// a fost vizitat
					queue.push(vecin);		// pun vecinul in coada
				}
			}
		}
		
		for (int i = 1; i <= n; i++)
		  	if(!visited[i])
		  		d[i] = -1;
		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i == n ? '\n' : ' ');
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
