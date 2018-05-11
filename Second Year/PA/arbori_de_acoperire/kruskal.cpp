#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <tuple>
using namespace std;

const int kNmax = 2e5 + 10;

int comparator(tuple<int, int, int> m1, tuple<int, int, int> m2) {
	return  get<0>(m1) < get<0>(m2);
}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<tuple<int, int, int> > edges;
	vector<int> parent, size;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			edges.push_back(make_tuple(w, x, y));
		}
		parent.resize(n + 1);
		size.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			parent[i] = i;
			size[i] = 1;
		}
		fin.close();
	}

	int find_root(int node) {
		if (node == parent[node]) {
			return node;
		}
		return parent[node] = find_root(parent[node]);
	}

	void merge_forests(int root1, int root2) {
		if (size[root1] <= size[root2]) {
			size[root2] += size[root1];
			parent[root1] = root2;
		} else {
			size[root1] += size[root2];
			parent[root2] = root1;
		}
	}

	int get_result() {
		
		sort(edges.begin(), edges.end());

		int cost = 0;
		for(int i = 0; i < m; i++) {
			int first = find_root(get<1>(edges[i]));
			int second = find_root(get<2>(edges[i]));
			if(first != second) {
				cost += get<0>(edges[i]);
				merge_forests(first, second);
			}		
		}
		
		return cost;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
