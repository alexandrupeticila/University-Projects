#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Result {
	int len;
	vector<int> subsequence;
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> v;
	vector<int> w;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		//v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 0, e; i < n; i++) {
			fin >> e;
			v.push_back(e);
		}

		//w.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 0, e; i < m; i++) {
			fin >> e;
			w.push_back(e);
		}

		fin.close();
	}

	Result get_result() {
		Result result;
		result.len = 0;

		/*
		TODO: Aflati cel mai lung subsir comun intre v (de lungime n)
		si w (de lungime m).
		Se puncteaza separat urmatoarele 2 cerinte:
		2.1. Lungimea CMLSC. Rezultatul pentru cerinta aceasta se va pune in
		``result.len``.
		2.2. Reconstructia CMLSC. Se puncteaza orice subsir comun maximal valid.
		Solutia pentru aceasta cerinta se va pune in ``result.subsequence``.
		*/

		//folosesc o matrice  auxiliara in care elementul de pe pozitia i,j reprezinta cel mai lung 
		//subsir comun folosind doar primele i elemente din v si primele j dinw
		//la final, lungimea va fi maximul acestei matrice
		int dp[n+1][m+1];
	//primul cuvant
		for (int i=0; i<=n; i++)
   		{//al doilea cuvant
     		for (int j=0; j<=m; j++)
     		{ //pun 0 pe prima linie si prima coloana
       			if (i == 0 || j == 0)
         		dp[i][j] = 0;
  
       			else if (v[i-1] == w[j-1]){
         			dp[i][j] = dp[i-1][j-1] + 1;
  					
  				}
       			else{
         		dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
         		}	
     		}
   		}



    /*
   for (int i = 0; i <= n; ++i)
   {
   		for (int j = 0; j <=m; ++j)
   		{
   			cout<<dp[i][j]<<" ";
   		}
   		cout<<endl;
   }*/

   		vector<int> afisare;
   		int i=n,j=m;
   		while(i>0 && j>0){
   			if(v[i-1] == w[j-1])
   			{
   				afisare.push_back(v[i-1]);
   				i--;
   				j--;
   			}
   			else if(dp[i-1][j]> dp[i][j-1])
   				i--;
   			else
   				j--;
   		}

   		reverse(afisare.begin(), afisare.end());
   		result.subsequence = afisare;

   result.len =  dp[n][m];	
		
		
    return result;
	}

	void print_output(Result result) {
		ofstream fout("out");
		fout << result.len << '\n';
		for (int x : result.subsequence) {
			fout << x << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
