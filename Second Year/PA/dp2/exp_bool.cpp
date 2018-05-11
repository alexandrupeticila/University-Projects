#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

const int pasMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	string expr;

	void read_input() {
		ifstream fin("in");
		fin >> n >> expr;
		expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
		fin.close();
	}

	bool is_operand(string expr, int index){
		if(expr[index] == 'T' ||expr[index] == 'F') return true;
		return false;
	}

	bool is_operator(string expr, int index){
		if(expr[index] == 'T' || expr[index] == 'F') return false;
		return true;
	}

	vector<char> parse_operator(string expr){
		vector<char> v;
		for(int i = 1; i < expr.size(); i++){
			if(is_operator(expr, i)) v.push_back(expr[i]);
		}
		return v;
	}

	vector<char> parse_operand(string expr){
		vector<char> v;
		for(int i = 1; i < expr.size(); i++){
			if(is_operand(expr, i)) v.push_back(expr[i]);
		}
		return v;
	}

	
	
	int get_result() {
		/*
		Calculati numarul de parantezari ale expresiei date astfel incat
		rezultatul sa dea true si returnati restul impartirii numarului
		la 10^9 + 7.
		*/
		vector<char> oper = parse_operator(expr);
		vector<char> operand = parse_operand(expr);
		int max = operand.size();
		long long T[max][max];
		long long F[max][max];

//cazul de baza; diagonala principala
		for(int i = 0; i < max; i++){
			for (int j = 0; j < max; ++j)
			{
				F[i][j] = 0;
				T[i][j] = 0;
			}
			if(operand[i] == 'F'){
				F[i][i] = 1;
				T[i][i] = 0;
			}
			else{
				F[i][i] = 0;
				T[i][i] = 1;
			}
		}

		for (int i = 0; i < max; ++i)
		{		
			cout<<oper[i];
		}
		for (int i = 0; i < max ; ++i)
		{		
			cout<<operand[i];
		}
		
	
		cout<<"max este "<<max<<endl;
		//pentru fiecare distanta
		for(int pas = 1; pas < max; pas++){
			for(int i = 0, j = pas; j < max; i++, j++ ){ //calulcam F[i][j], j-i = pas;
				for(int l = 0; l < pas; l++){
					int k = i+l; //minim i si maxim j

					 // Store Total[i][k] and Total[k+1][j]
                	long long total_ik = (T[i][k] + F[i][k])%pasMod;
                	long long total_kj = (T[k+1][j] + F[k+1][j])%pasMod;
 
        
                	// operator
                	if (oper[k] == '&')
                	{
                		cout<<"a intrat pe 1 ";
                    	T[i][j] = (T[i][j] + 1LL*T[i][k]*T[k+1][j]%pasMod)%pasMod;
                    	F[i][j] = (F[i][j] + (1LL*total_ik*total_kj%pasMod - 1LL*T[i][k]*T[k+1][j]%pasMod +pasMod))%pasMod;
                	}
                	if (oper[k] == '|')
                	{
                		cout<<"a intrat pe 2 ";
                    	F[i][j] = (F[i][j]+1LL*F[i][k]*F[k+1][j]%pasMod)%pasMod;
                    	T[i][j] = (T[i][j] + (1LL*total_ik*total_kj%pasMod - 1LL*F[i][k]*F[k+1][j]%pasMod+pasMod))%pasMod;
                	}
                	if (oper[k] == '^')
                	{
                		cout<<"a intrat pe 3 ";
                    	T[i][j] =(T[i][j]+ 1LL*F[i][k]*T[k+1][j]%pasMod + 1LL*T[i][k]*F[k+1][j]%pasMod)%pasMod;
                    	F[i][j] = (F[i][j] +1LL*T[i][k]*T[k+1][j]%pasMod + 1LL*F[i][k]*F[k+1][j]%pasMod)%pasMod;
					} 
				}
			}	
		}

	for (int i = 0; i < max; ++i)
		{
			for (int j = 0; j < max; ++j)
			{
				cout<<T[i][j]<<" ";
			}
			cout <<endl;	
		}	
	return T[0][max-1];
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
