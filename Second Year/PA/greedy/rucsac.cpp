#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct Object {
	int weight;
	int price;

	Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, w;
	vector<Object> objs;


	void read_input() {
		ifstream fin("in");
		fin >> n >> w;
		for (int i = 0, weight, price; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}


	bool static comp(Object o1, Object o2){
		return (1.0*o1.price/o1.weight >= 1.0*o2.price/o2.weight);
	}


	

	double get_result() {
		/*
		TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
		*/
		
		sort(objs.begin(), objs.end(), comp); //sortam vectorul dupa pret/unitate
		
		double result = 0;//profitul strans
		int weight = 0;	//greutatea pe care o vom pune in rucsac				
		int i = 0;//parcurgem vectorul

		while(weight < w && i < n) {	//conditia de iesire: am umplut rucsacul sau am terminat vectorul
			
			if(w - weight >= objs[i].weight){	//mai avem loc sa punem tot obiectu;
				
				result = result + objs[i].price;
				weight = weight + objs[i].weight;
			}
			else{ 
				result = result + ((double)objs[i].price/objs[i].weight) * (double)(w - weight);
				weight = w;
			} 
			i++;

		}
		cout<< result<<endl;
		return result;
	}

	void print_output(double result) {
		ofstream fout("out");
		
		fout << setprecision(4) << fixed << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}