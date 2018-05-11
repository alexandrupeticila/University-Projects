#include <fstream>
#include <vector>
#include <algorithm>
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

	vector<int> aparitie;

	
	void back(int k,vector<int> v,vector<vector<int> > *all){
			int i;
			if(k==0) 
				i = 1; //n am pus nici un element
			else i = v[k-1]+1; //pornesc cu ultimul pus
			for(;i<=n;i++){
				v.push_back(i);
				all->push_back(v);
				back(k+1,v,all);
				v.pop_back();	
		}
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate submultimile multimii {1, ..., N}.

		Pentru a adauga o noua submultime:
			vector<int> submultime;
			all.push_back(submultime);
		*/
		vector<int> v;
		all.push_back(v);
		back(0,v,&all);
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
