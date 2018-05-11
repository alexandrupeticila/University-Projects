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
	int n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	bool check(vector<int> v,int k){
		if(k == 1) //am pus prima dama--oriunde
			return true;
		else{	//sunt puse cateva
			
			for(int i=1;i<k;i++){ //sa nu fie pe coloana, diagonala cu celelalre
				if(v[i] == v[k]) 
					return false;
				if(k+v[k] == i+v[i] || k+v[i] == i+v[k])
					return false;
			}
			return true;	
		}
	}

	void backtracking(int k,vector<int> *v,int *ok){
		if(k == n+1){ //am pus toate damele
			(*ok)=1;
			return;
		}
		for(int i=1;i<=n;i++){ //pana gasesc o pozitie ok	
			if(*ok == 0){
			(*v)[k]= i;
			if(check(*v,k) == true) 
				backtracking(k+1,v,ok);
			}
		}
	}

	vector<int> get_result() {
		vector<int> sol(n+1,0);

		/*
		TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
		n x n.

		Pentru a plasa o dama pe randul i, coloana j:
			sol[i] = j.
		Randurile si coloanele se indexeaza de la 1 la n.

		De exemplu, configuratia (n = 5)
		X----
		--X--
		----X
		-X---
		---X-
		se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.
		*/
		//sol.push_back(0);
		int ok=0;
		backtracking(1,&sol,&ok);
		//printf("da");


		//	printf("aaaaaaaaaaaa");
		//cout<<sol.size();
		for(int i=1;i<=n;i++)
			cout<<sol[i]<<" ";
	

		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i != n ? ' ' : '\n');
		}	
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
