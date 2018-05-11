#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}

	bool static comparator(Homework t1, Homework t2){
		return (t1.score >  t2.score);
	} 
	int get_result() {
		/*
		TODO: Aflati punctajul maxim pe care il puteti obtine planificand
		optim temele.
		*/
		 cout<<"cine e prost?";
		//sortam vectorul descrescator dupa profit
		sort(hws.begin(), hws.end(), comparator);
	
		//aflam cel mai mare deadline pt a stii cate saptamani avem la dispozitie
		int max = 0;
		for(int i = 0; i < n; i++){
			if(max < hws[i].deadline) max = hws[i].deadline;
		}
		
		//construiesc un vector in care tin punctajele temelor pe care le fac in fiecare saptamana 
		//el are lungimea de max
		int deadline[max];
		for(int i = 0; i < n; i++) deadline[i]= 0;

		deadline[hws[0].deadline-1] = hws[0].score;
		
		/* mai intai pun tema cu punctaj maxim in ultima saptamana in care poate fi facuta
			apoi pentru celelalte teme, iau ultima saptamana disponibila in care pot fi faacute pana parcurg
			toate temele */
		for(int i = 1; i < n; i++){
			if(deadline[hws[i].deadline-1] == 0){
				deadline[hws[i].deadline-1] = hws[i].score;
			}
			else{//caut ultima saptamana disponibila
				for(int j = hws[i].deadline -2; j >= 0; j--){
					if(deadline[j] == 0){
						deadline[j] = hws[i].score;
						break;
					}
				}
			}	
		}

		//adun elementele din vector;
	int result = 0;
	for(int i = 0; i < max; i++){
		result = result + deadline[i];
	}	
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