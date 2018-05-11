#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, k;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin.close();
	}

//verific daca deja apare
	bool check(vector<int> v,int k){
		for(int i=0;i<k;i++)
			if(v[k] == v[i])
				return false;
			return true;
	}

	void backtracking(int pozitie_curenta,vector<int> v,vector<vector<int> > *all){
		if(pozitie_curenta == k) { //am k elemente
			all->push_back(v);
			cout<<all->size()<<" ";
		}
		else{ //nu am ajuns la k el
			for(int i=1;i<=n;i++){
				v.push_back(i); 
				if(check(v,pozitie_curenta) == true){ //veirfic v[k] bun, nu e deja pus
					backtracking(pozitie_curenta+1,v,all);
					cout<<"pozitie_curenta"<<pozitie_curenta;
				}	
				v.pop_back();

			}
		}
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate aranjamentele de N luate cate K ale
		multimii {1, ..., N}.

		Pentru a adauga un nou aranjament:
			vector<int> aranjament;
			all.push_back(aranjament);
		*/

		vector<int> x;
		backtracking(0,x,&all);
		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
