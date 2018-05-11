#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> dist;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 0, d; i < n; i++) {
			fin >> d;
			dist.push_back(d);
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati numarul minim de opriri necesare pentru a ajunge
		la destinatie.
		*/
		int drum_parcurs = 0;
		int i = 0; //parcurgem vectorul de distante
		int nr_benzinarii = 0;
		
		while(drum_parcurs < dist[n-1]){
			
			while( dist[i] - drum_parcurs <= m &&  i < n){
				i++;
			}
			i--;
			
			nr_benzinarii++;
			drum_parcurs = dist[i];
			
		}
		return nr_benzinarii -1;
	}

	void print_output(int result) {
		ofstream fout("out");
		cout << result<<endl;
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}