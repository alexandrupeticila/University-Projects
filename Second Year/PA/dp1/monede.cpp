#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
#define INT_MAX  999999
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, S;
	vector<int> v;
	//n--nr de monede
	//S--suma de platit
	void read_input() {
		ifstream fin("in");
		fin >> n >> S;
		//v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 0, e; i < n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
		suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.
		*/
		
		//vectorul va contine nr minim de monede pt a plati suma i
		//folosim un vector pt ca, la pasul i+1 vom avea nevoie sa aprcurgem toate sumele
		//gasite pana atunci pentru a obtine un minim de monede cu care putem plati
		int dp[S+1];
		dp[0] = 0; //suma = 0 o platim cu 0
		for(int i = 1; i <= S; i++) dp[i] = INT_MAX;
		for(int i = 0; i <= S; i++) cout<<dp[i]<<" ";
		cout << endl;
			
		//pt a calcula nr minim de monede folosite pt a plati suma S, vom calcula nr minim pt
		//a plati sumele i =1,S. Apoi pentru suma S parcurgem vectorul de monede si atunci cand
		//gasim una mai mica decat S, vedem cate ne au trebuit sa platim suma S-V[i], incrementam
		//acel numar si alegem minimul dintre aceste rezultate.

		//parcurg de la suma = 1; pentru 0 nu folosim nici o moneda	
		for (int i = 1; i <= S; i++)
		{
			//parcurg tot vectorul de monede pt a gasi cea mai eficienta solutie pentru fiecare suma
			for (int j = 0; j < n; ++j)
			{
				if(v[j] <= i){ //verific daca moneda este mai mica decat suma si daca este continui operatiile
					int sub_res = dp[i-v[j]];	//vad cu cate monede pot plati suma curenta - moneda mea
              		if (sub_res != INT_MAX && sub_res + 1 < dp[i]){ //verific daca rezultatul este mai mic 
                		dp[i] = sub_res + 1;						//decat cel curent si actualizez
                		cout<<"intra aici "<< i<<endl;	
                	}
            	}
			}
		}
		
		//nu putem plati summa cu monedele date
		if( dp[S] == INT_MAX){
			return -1;
		}
		return dp[S];
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
