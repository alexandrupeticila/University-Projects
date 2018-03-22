#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//folosim o structura de tip bool pentru a vedea daca un nod e sau nu sfarsitul unui cuvant
typedef enum
{
	false,
	true
} bool;

/* definim structura pentru un nod care contine informatie(litera sau cifra),un vectori de pointeri
 la copiii nodului care urmeaza a fi alocat dinamic,o variabila prin care verificam daca
se termina sau nu un cuvant in acest nod si lungimea vectorului de copii*/
typedef struct trienode
{
	char info;
	struct trienode *parinte;
	struct trienode **copilasi;
	int lungime;
	bool end;
} Trienode;

Trienode* createnode(char a)
{
	Trienode *node =  calloc(1,sizeof(Trienode));
	if(!node ) return NULL;
	node->lungime = 0;
	node -> copilasi = NULL;
	node->parinte=NULL;
	node -> info = a;
	return node;
}


void free_node(Trienode* node)
{
	int i,n=node->parinte->lungime;
	for(i=0;i<node->parinte->lungime;i++)
	{

		if(node->parinte->copilasi[i]->info==node->info)
		{
			while(i < n-1)
			{
				node->parinte->copilasi[i]=node->parinte->copilasi[i+1];
				i++;
			}

		}


	}
		node->parinte->lungime--;
		node->end=false;
		node->parinte->copilasi=realloc(node->parinte->copilasi,(node->parinte->lungime)*sizeof(Trienode*));

}

void add( Trienode *root, char* cuv)
{
	int n=strlen(cuv),i,j,k;
	Trienode *cauta = root,*aux;
	if(n == 0) return;
	//primul for e pentru fiecare litera din cuvant
	for(i=0;i < n;i++)
	{
		int flag=0; // daca flag e 1 inseamna ca exista deja un nod cu info egala cu litera lui cuv[i]

		// al doilea e pentru toti copiii nodului in care ne aflam
		for(j=0;j < cauta->lungime; j++)
		{
			if(cauta->copilasi[j]->info == cuv[i])
			{
				cauta = cauta -> copilasi[j];
				flag=1;
			}
		}

		if(flag == 0)
		{
	//cat timp  cuvantul mai are litere
			while( i < n)
			{
	//maresc lungimea vectorului de copii al nodului in care ne aflam
			cauta -> lungime ++;
	//creem nodul cu litera din cuvant atunci cand aceasta nu mai exista in nodul curent.
			Trienode *nou = createnode(cuv[i]);
	//actualizam parintele
			nou->parinte=cauta;
	//realoc spaitul vecorului de copilasi folosind noua lungime si introduc pe ultima pozitie nodul nou creat
			cauta->copilasi = realloc(cauta->copilasi,cauta->lungime * sizeof(Trienode*));
			 cauta -> copilasi[cauta->lungime -1] = nou ;

		//ordonam crescator vectorul de copilasi,in  ordine alfabetica
		//amm facut acest lucru pentru a usura munca la taskul 5 s 6
		//am folosit interschimbari.
			for(k=0;k<cauta->lungime;k++)
		{
			//j-ul se duce prin toate nodurile ramase neordonate
			for(j=k;j<cauta->lungime;j++)
			{
				if(cauta->copilasi[k]->info > cauta->copilasi[j]->info)
				{
					//folosim aux pentru a interschimba
					aux=cauta->copilasi[k];
					cauta->copilasi[k]=cauta->copilasi[j];
					cauta->copilasi[j] = aux;
				}
			}
		}
	//ne mutam in nodul nou format pentru a continua formare cuvantului daca este necesare
			cauta = nou;
			i++;
			}

		}
	}

	cauta->end=true;

}

int find(Trienode *root,char* cuvant)
{
	int n=strlen(cuvant),i,j,gasit=1;
	Trienode *cauta=root;
	//pentru fiecare litera a cuvantului
	for(i=0;i<n;i++)
	{
		int flag=0;
		//pentru toti copiii din nodul curent
		for(j=0;j<cauta->lungime;j++)
		{
			if(cauta->copilasi[j]->info == cuvant[i])
			{
				flag=1;
				cauta=cauta->copilasi[j];
			}
			//nu am gasit o litera din cuvant,deci cuvantul nu exista

		}
		if(flag == 0) {  gasit=0; return 0;}

	}
	//daca sunt toate literele si e si final de cuvant
	if((cauta -> end == true) && gasit ==1)
	{
		return 1;
	}
	return 0;

}

int find_2(Trienode *root,char* cuvant)
{
	int n=strlen(cuvant),i,j;
	Trienode *cauta=root;
	//pentru fiecare litera a cuvantului
	for(i=0;i<n;i++)
	{
		int flag=0;
		//pentru toti copiii din nodul curent
		for(j=0;j< cauta->lungime;j++)
		{
			if(cauta->copilasi[j]->info == cuvant[i])
			{
				flag=1;
				cauta=cauta->copilasi[j];
			}
			//nu am gasit o litera din cuvant,deci cuvantul nu exista

		}
		if(flag == 0)  return 0;

	}
	//daca sunt toate literele 
	return 1;

}

void removec(Trienode* root,char* cuvant)
{
	int i,j,n=strlen(cuvant);
	Trienode* cauta=root;
	if(find(root,cuvant) == 0) return;
// pentru fiecare litera din cuvant
	for(i=0;i<n;i++)
	{
		//pentru toti copiii din nodul curent
		for(j=0;j < cauta->lungime;j++)
		{
			if(cauta->copilasi[j]->info == cuvant[i])
			{
				cauta=cauta->copilasi[j];
				break;
			}
		}
	}
	cauta->end=false;
	if(cauta->lungime > 0)  return;
	int k=0;
	while(cauta->lungime == 0  && cauta->end==false && k<n)
	{
		Trienode *aux=cauta->parinte;
		free_node(cauta);
		cauta=aux;
		k++;
	}
}

int find_longest_prefix(Trienode* root,char* cuvant)
{
	char *aux=cuvant;
	int n=strlen(aux);
	if(n == 0) return 0;
	Trienode* cauta=root;
	int i,j;
/*vedem care este lungimea maxima a prefixului existent in trie si salvez acest prefix in cuvant
*/
	while(n > 0)
	{
		if(find_2(root,aux) == 1)
		{
		for(i=0;i<n;i++)
		{	
		//pentru toti copiii din nodul curent
			for(j=0;j < cauta->lungime;j++)
			{
				if(cauta->copilasi[j]->info == cuvant[i])
				{
					cauta=cauta->copilasi[j];
					break;
				}
			}
		} 
		if(cauta->lungime > 0) return n;
		if(cauta->end == true) return n;
		}
		aux[n-1]='\0';
		n--;

	}
// daca nu exista  nici prima litera,rezulta lungimea e 0;
	if(n == 0) return 0;
	return n;

}


void print1(Trienode* root, char* cuv,FILE* f)
{
	int i,nr=strlen(cuv);
	char *cuv1;
	if(root->end == true) fprintf(f,"%s ",cuv);
	cuv1 = (char*) malloc(nr+1);
	strcpy(cuv1,cuv);
	for(i=0; i<root->lungime; i++)
	{
		cuv1[nr] = root->copilasi[i]->info;
		cuv1[nr+1] = '\0';
		print1(root->copilasi[i],cuv1,f);
	}
}
void find_all_with_prefix(Trienode* root,char* cuvant,FILE* f)
{
	Trienode* cauta = root;
	int i,n=strlen(cuvant),j;
	char *cuv;
	cuv = (char*) malloc(n+1);
	strcpy(cuv,cuvant);
	//am verificat daca exista in trie-ul meu  prefixul "cuvant",care nu trebuie sa fie cuvant
	//in caz ca nu exista,afisez "None" si ies din functie

	if(find_2(root,cuvant) == 0 )
	{
		fprintf(f,"None\n");
		return;
	}
//ajung in nodul corespunzator ultimului caracter din cuvant

	for(i=0;i<n;i++)
	{
		//pentru toti copiii din nodul curent
		for(j=0;j< cauta->lungime;j++)
		{
			if(cauta->copilasi[j]->info == cuvant[i])
			{
				cauta=cauta->copilasi[j];
				break;
			}
		}
	}
	
	if(cuvant == '\0')
	{
		print1(cauta,'\0',f);
		fprintf(f,"\n");
		return;
	}
	print1(cauta,cuv,f);
	fprintf(f,"\n");

}

void Cauta1(Trienode* root,char* cuv, int*suma, int* nr)
{
	int i,dim=strlen(cuv);
	char *cuv1;
	if(root->end == true) 
	{
		(*suma)+= dim;
		(*nr)++;
	}
	cuv1 = (char*) malloc(dim+1);
	strcpy(cuv1,cuv);
	for(i=0; i<root->lungime; i++)
	{
		cuv1[dim] = root->copilasi[i]->info;
		cuv1[dim+1] = '\0';
		Cauta1(root->copilasi[i],cuv1,suma,nr);
	}
}

void mean_length(Trienode* root,char* cuvant,int *suma,int*nr)
{
	Trienode* cauta = root;
	int i,n=strlen(cuvant),j;
	char *cuv;
	cuv = (char*) malloc(n+1);
	strcpy(cuv,cuvant);
	if(find_2(root,cuvant) == 0 )
	{
		*suma = 0;
		return;
	}

		for(i=0;i<n;i++)
	{
		//pentru toti copiii din nodul curent
		for(j=0;j< cauta->lungime;j++)
		{
			if(cauta->copilasi[j]->info == cuvant[i])
			{
				cauta=cauta->copilasi[j];
				break;
			}
		}
	}
	if(cuvant == '\0')
	{
		Cauta1(cauta,'\0',suma,nr);
		return;
	}

	Cauta1(cauta,cuv,suma,nr);

}
int main(int argc, char *argv[])
{
	int  n,i,k,j,suma,nr;
	Trienode *root=createnode('\0');
	char command[20], cuv[100];
	FILE *input, *output;
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	fscanf(input, "%d", &n);
	float valoare;
    bool ok=false;
	for (i = 0; i < n; i++)
	{
	    if(ok == false)
		fscanf(input, "%s", command);
		else
            ok = false;
		if (strcmp(command, "add") == 0)
		{
			fscanf(input, "%s", cuv);
			add(root,cuv);
		}

		if(strcmp(command, "remove") == 0)
		{
			fscanf(input, "%s", cuv);
			removec(root,cuv);
		}
		if(strcmp(command, "find") == 0)
		{
			fscanf(input, "%s", cuv);
			if (find(root,cuv) == 1) fprintf (output,"True\n");
			else fprintf(output,"False\n");
		}
		if(strcmp(command, "find_longest_prefix") == 0)
		{
			fscanf(input, "%s", cuv);
			k=find_longest_prefix(root,cuv);
			if (k == 0) fprintf(output, "None\n");
			else
			{
				for(j=0;j<k;j++) fprintf(output,"%c",cuv[j]);
				fprintf(output, "\n");
			}
		}
		if(strcmp(command, "find_all_with_prefix") == 0)
		{
			fscanf(input, "%s", cuv);
			if(!strcmp(cuv,"add") || !strcmp(cuv,"remove") || !strcmp(cuv,"find") || !strcmp(cuv,"find_longest_prefix") || !strcmp(cuv,"mean_length") || !strcmp(cuv,"find_all_with_prefix"))
			{
			    strcpy(command,cuv);
			    ok = true;
			    strcpy(cuv,"\0");
			}
			find_all_with_prefix(root,cuv,output);

		}
		if(strcmp(command, "mean_length") == 0 && ok == false)
		{
			fscanf(input, "%s", cuv);
			if(!strcmp(cuv,"add") || !strcmp(cuv,"remove") || !strcmp(cuv,"find") || !strcmp(cuv,"find_longest_prefix") || !strcmp(cuv,"mean_length") || !strcmp(cuv,"find_all_with_prefix"))
			{
			    strcpy(command,cuv);
			    ok = true;
			    strcpy(cuv,"\0");
			}
			suma = nr =0;
			mean_length(root,cuv,&suma,&nr);
			if(suma)
			{
				valoare = (float) suma/nr;
				fprintf(output, "%.3f\n",valoare);
			}
			else fprintf(output, "0\n");
		}

	}

	return 0;
}
