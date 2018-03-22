#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
	
	int nr_states;												//numele sunt sugestive
	int nr_final_states;
	int nr_transitions;											//ok2, ok variabile folosite pentru a iesi din bucle			
	int nr = 8, aux, i,current_a = 1,current_b = 1,ok2,ok;		//8 stringuri sunt la fiecare tranzitie, curent_a folosit pt a retine pozitia de pe banda 1	
	string init_state;											// aux pentru a retine cateva valori 					
	string var, current_state, next_state;			// o folosesc sa citesc stringuri din fisier

	char banda1[10000];								//cele doua benzi
	char banda2[10000];
	vector<string> all_states;
	vector<string> final_states; 					//vectori de stringuri in care stochez starile  toate, respectiv  finale
	vector<vector<string> > trans;  				// vector de vectori in care fiecare linie reprezinta o tranzitie

	ifstream inFile;
	inFile.open("task1.in");						//deschid fisierul de citire
														
	if(!inFile){									//verific deschiderea corecta
		cout << "Unable to open file";
		return 1;
	}

	inFile >> nr_states;							//citesc nr de stari

	while (nr_states > 0 && inFile >> var ){		//introduc starile in vector
		nr_states --;
		all_states.push_back(var);
	}

	inFile >> nr_final_states;						//citesc nr de stari finale
	aux = nr_final_states;							// folosesc aux pentru a stii cand ma opresc din introdusul starilor in vector	
	while (aux > 0 && inFile >> var){				//introduc in vector starile finale
		aux --;
		final_states.push_back(var);
	}

	inFile >> init_state;							//citesc starea initiala
	inFile >> nr_transitions;						//citesc nr de tranzitii
	aux = nr_transitions;	

	while(aux > 0){									//bag fiecare trazitie(linie) intr-un vector auziliar
		vector<string> aux1;
		while (nr > 0 && inFile >> var){			// introduc vectorul in vectorul de vectori nunit trans
			nr --;
			aux1.push_back(var);
		}
		nr = 8;										//actualizez nr de stringuri citite de pe linie
		trans.push_back(aux1);
		aux --;
	}	
	
	inFile >> var;
	int lungime_a = var.size();
	strncpy(banda1, var.c_str(), sizeof(banda1));	//citesc banda cu string si introduc apoi in vector de caractere
	inFile >> var;
	int lungime_b  = var.size();					//folosesc lungimea pentru a sti unde se termina banda ca sa completez ulteorior cu #
	strncpy(banda2, var.c_str(), sizeof(banda2));


current_state = init_state;							//initializez starea curenta cu cea initiala inainte de a intra in bucla
ok = 0;

ofstream outfile;
outfile.open ("task1.out");
    
while ( 1 ){

	ok2=0;											//nu pot face nicio tranzitie
	for( i = 0; i < nr_transitions; i++){																						//verific daca se poate efectua vreo tranzitie				
		if(current_state == trans[i][0] && banda1[current_a] == trans[i][1][0] && banda2[current_b] == trans[i][2][0]){			//am gasit tranzitia corespunzatare
			ok2 = 1;
			next_state = trans[i][3];																							//actualizez starea in care ma duc pentru a verifica apoi daca e finala		
			banda1[current_a] = trans[i][4][0];																					//scriu pe banda si actualizez starea urmatoare			
			banda2[current_b] = trans[i][6][0];
			
			if( trans[i][5][0] == 'R') current_a++;
			else {
					if( trans[i][5][0] == 'L') current_a--;
			}																				//actualizez capatul de citire pentru fiecare banda
			if( trans[i][7][0] == 'R') current_b++;
			else{
				if( trans[i][7][0] == 'L') current_b--;		
			}
			
			break;																			//folosesc break pentru a iesi din bucla deoarece dupa ce actualizez valorile
		}																					//exista sansa sa intru intr-o noua tranzitie

	}

	current_state = next_state;
	if( ok2 == 0) {																			//n am gasit nici o tranzitie
		outfile<<"The machine has blocked!"<<endl;											//afisez mesajul corespunzator si ma duc la final	
		goto final;		
	}
	

	for (i = 0; i < nr_final_states; i++){
		if( next_state == final_states[i]){
			ok = 1;																			//starea este finala				
			break;
		}
	}
	
	if ( ok == 1 ) break;         															//iesim din bucla daca am ajuns in stare finala 
	if(current_b >= lungime_b){																//pun # cand termin banda 2 (banda infinita la dreapta)
		banda2[current_b] = '#';															//actualizez lungimea benzii
		lungime_b++;
	}
	if(current_a >= lungime_a){
		banda1[current_a] = '#';															//la fel si pentru banda 1
		lungime_a++;
	}
		
}

    outfile << banda1<<endl<<banda2<<endl;

final:    
	inFile.close();
	outfile.close();
	
	return 0;
}
