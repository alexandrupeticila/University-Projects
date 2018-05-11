#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

const int kNmax = 105;

class Task {
 public:
	void solve() {
		read_input();
		compute();
		print_output();
	}

 private:
	int n;
	int d[kNmax][kNmax];
	int a[kNmax][kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fin >> a[i][j];
			}
		}
		fin.close();
	}

	void compute() {
		/*
		TODO: Gasiti distantele minime intre oricare doua noduri, folosind RoyFloyd
		pe graful orientat cu n noduri, m arce stocat in matricea ponderilor a
		(declarata mai sus).

		Atentie:
		O muchie (x, y, w) este reprezentata astfel in matricea ponderilor:
			a[x][y] = w;
		Daca nu exista o muchie intre doua noduri x si y, in matricea ponderilor
		se va afla valoarea 0:
			a[x][y] = 0;

		Trebuie sa populati matricea d[][] (declarata mai sus):
			d[x][y] = distanta minima intre nodurile x si y, daca exista drum.
			d[x][y] = 0 daca nu exista drum intre x si y.
			d[x][x] = 0.
		*/

			// facem initializarile in matrice
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (a[i][j] == 0) {  // nu exista muchie directa intre noduri
					d[i][j] = INT_MAX / 10;
				}
				else {		// exista muchie
					d[i][j] = a[i][j];
				}
			}
		}

		// facem relaxari folosindu ne de cele gasite pana la la pasul k-1
		// dupa pasul k, si nodul corespunzator poate fi folosit pentru a face
		// relaxari
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					int aux = d[i][k] + d[k][j];
					if (d[i][j] > aux) {
						d[i][j] = aux;
					}
				}
			}
		}

		// daca nu a fost actualizata distanta intre doua noduri inseamna ca nu exista
		// drum intre ele asa ca pe acele pozitii punem 0.
		// de asemenea, punem 0 si pe diagonala principala, deoarece nu exista drum de la
		// un nod la acelasi nod
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (d[i][j] == INT_MAX / 10 || i == j) {
					d[i][j] = 0;
				}
			}
		}
	}

	void print_output() {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fout << d[i][j] << ' ';
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
