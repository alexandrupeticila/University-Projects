#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

const int kMod = 1e9 + 7;


class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		v.push_back(0); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	unsigned long long pow2(int base, int exp){
		if(exp == 0) return 1ULL;
		return 1ULL*(base%1000000007)*(pow2(base,exp-1)%1000000007)%1000000007;
	}
	int get_result() {
		/*
		Calculati numarul de subsiruri ale lui v cu suma numerelor para si
		returnati restul impartirii numarului la 10^9 + 7.
		*/

		/*calculez  nr de nr pare si impare, parcurgand vectorul => O(n)
		Nr de subsiruri cerute va fi egal cu nr de subsiruri generate doar de elementele pare+
		nr de sub geenrate doar de elementele impare + nr de subisurir generate impreuna
		Daca avem doar el pare => po(2,n) - 1
		altfel pow(2,n) - 1;
		*/
		int result;
		/* FORMULA MATEMATICA
		calculez nr de nr pare si impare. 
		Avem doua cazuri:
		1) daca toate nr sunt pare => vor fi 2^n -1(formula cu combinari)
		2) daca apare un nr impar (cel putin unul) nr  va fi 2^(n-1)-1
			Ideea e ca la primul nr impar aparut tu nu poti face nimic cu el, nici un
			subsir in plus care sa dea suma para (e primul impar). Apoi se va comporta identic 
			cu nr pare. De aceea ai 2^(n-1), pt ca la un pas nu faci nimic.

		*/
		int nr_odd = 0, nr_even = 0;

		for(int i = 1; i <= n; i++){
			if(v[i]%2 == 0) nr_even++;
			else nr_odd++;
		}

		cout<< nr_odd<<" impar  par "<<nr_even<<endl; 
		
		result= pow2(2,n) -1;
		if(nr_odd > 0)
			result = pow2(2,n-1) -1;
		
		//DP varianta 1
		/*
		int dp[n+1];
		dp[0] = 0;
		bool odd = false;
		for (int i = 1; i <= n; ++i)
		{
			if(v[i]%2 == 0){
				dp[i] = 2*dp[i-1]%1000000007 +1;
			}
			else{
				if(!odd) dp[i] = dp[i-1];
				else dp[i] = 2*dp[i-1]%1000000007 +1;
				odd = true;

			}
		}
		return dp[n];*/
/*		Varianta dp 2
		--formulele sunt date de profa(jumate din ele)
		faci pt i-1
		1) daca la i ai par inseamna ca ai toate subirurile precente+toate alea dar cu v[i] la sfarsit
		+v[i] = 2*v[i-1]+1;
		2) daca ai impar raman cele pare de la pasul precedent si se adauga si cele impare
		pt ca poti construi subsiruri cu sume pare daca mai ai impare inainte.
		
		Cand le calculezi pe cele impare faci la analog
		1) v[i] par => dublezi impar[i-1] pentru ca le ai pt toate alea plus la fiecare mai pui la sf nr v[i]
		2) v[i] impar => patrezi imparele de pana atunci. La toate parele de pana atunci mai pui nr asta impar si faci impare
		--d-asta aduni si parele precedente si il mai aduni pe el ca e impar
		int par[n+1], impar[n+1];
		par[0] = 0;
		impar[0] = 0;

		for(int i = 1; i <=n; i++){
			if(v[i]%2 == 0){
				par[i] = (2*par[i-1] +1)%kMod;
				impar[i] = 2*impar[i-1]%kMod;
				
			}
			else{
				par[i] = (par[i-1] + impar[i-1])%kMod;
				impar[i] = (par[i-1] +1+ impar[i-1])%kMod;
			}
		}
		return par[n];
*/	
		return result;
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
