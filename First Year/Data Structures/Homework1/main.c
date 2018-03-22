#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Definim structurile de care avem nevoie
typedef struct celula
{
	void* info;
	struct celula *urm;
} TCelula,*TLista,**ALista;

typedef struct
{
	int id;
	char tip;
} TParanteza;

typedef struct
{
	TLista* vf;
} TStiva,*AStiva;

typedef struct
{
	
	TLista *vf,*ic;
} TCoada, *ACoada;

//am alocat un vector de pointeri la elemente de tip TStiva
TStiva* initS(int n)
{
	AStiva s=(AStiva) malloc(sizeof(TStiva));
	if(s==NULL) return NULL;
	s->vf=(ALista) malloc(n*sizeof(TLista));
	if(s->vf==NULL) return NULL;
	return s;
}
//am alocat un vector de pointeri la elemente de tip TCoada
ACoada initC(int n)
{
	ACoada c=(ACoada) malloc(sizeof(TCoada));
	if(c==NULL) return NULL;
	c->ic=(ALista) malloc(n*sizeof(TLista));
	if(c->ic==NULL) return NULL;
	c->vf=(ALista) malloc(n*sizeof(TLista));
	if(c->vf==NULL) return NULL;
	return c;
	
}
/*folosesc un inf in care introduc elementele pe care le am de pus in stiva.
Folosesc o lista auxiliara in care bag elementul de introdus. Apoi faclegatura cu varful stivei. */
void push(int id_stiva,char a,int id1,AStiva s)
{
	TParanteza *inf=(TParanteza*)malloc(sizeof(TParanteza));
	if(inf==NULL) return ;
	inf->id=id1;
	inf->tip=a;
	TLista aux=(TLista)malloc(sizeof(TCelula));
	if(aux==NULL) return ;
	aux->info=(void*)inf;
	aux->urm=s->vf[id_stiva];
	s->vf[id_stiva]=aux;
}
/* fac acelasi lucru ca mai sus insa schimb conditiile cand fac legaturile */
void intrq(int id_coada,int id_p,char a,ACoada c)
{
	TParanteza *inf=(TParanteza*)malloc(sizeof(TParanteza));
	if(inf==NULL) return ;
	inf->id=id_p;
	inf->tip=a;
	TLista aux=(TLista)malloc(sizeof(TCelula));
	if(aux==NULL) return ;
	aux->info=(void*)inf;
	if(c->ic[id_coada]==NULL || c->vf[id_coada] == NULL)
	{
		
		c->ic[id_coada]=aux;
		c->ic[id_coada]->urm=NULL;
		c->vf[id_coada]=c->ic[id_coada];
	}
	else 
	{
		
		c->vf[id_coada]->urm=aux;
		c->vf[id_coada]=aux;
		c->vf[id_coada]->urm=NULL;
		
	}
}
/* actualizez varful stivei astfel incat sa fie eliminat elementul din varf */
void pop(int id_stiva,AStiva s)
{
	
	if(s->vf[id_stiva] != NULL)
	s->vf[id_stiva]=s->vf[id_stiva]->urm;
		
}
/* aici schimb locul de unde extrag elementul si anume va fi inceputul cozii*/
void extrq (int id_coada,ACoada c)
{
	TLista p=c->ic[id_coada];
	if(c->ic[id_coada]==NULL) return;
	c->ic[id_coada]=c->ic[id_coada]->urm;
	free(p);
}

/*folosesc un vector de stive auxiliar (stiu ca folosesc multa memorie inutil)
pentru a baga intr-una din stive. Apoi le bag inapoi in stiva initiala si le afisez */
void prints(AStiva s, int nr, FILE *output)
{
	int i;
	AStiva aux;
	TParanteza *p;
	p = (TParanteza*)calloc(1,sizeof(TParanteza));
	aux = initS(nr);
	
	for (i = 0; i < nr; i++)
	{
		fprintf(output, "\"");
		if(s->vf[i])
		{
			while(s->vf[i])
			{

				p=(TParanteza*)s->vf[i]->info;
				push(i, p -> tip, p -> id, aux);
				pop(i, s);
			}
			while (aux->vf[i])
			{
				p=(TParanteza*)aux->vf[i]->info;
				fprintf(output, "%c", p -> tip);
				push(i, p-> tip, p -> id, s);
				pop(i, aux);
			}
		} 
		fprintf(output, "\"\n");

	}
	
}
/* folosesc doua stive auxiliare. fac acest lucru pentru a obtine intr-una o stiva sortata dar descrescator.
Apoi folosesc push pentru a le transfera in stiva initiala .*/

void sorts (AStiva s,int nr,int id_stiva)
{
	AStiva aux1,aux2;
	TParanteza *p=(TParanteza*) calloc(1,sizeof(TParanteza));
	TParanteza *p2=(TParanteza*) calloc(1,sizeof(TParanteza));
	aux1=initS(nr);
	aux2=initS(nr);
	if(s->vf[id_stiva])
	{
		while(s->vf[id_stiva])
		{
			p=(TParanteza*)s->vf[id_stiva]->info;
			if(aux1->vf[id_stiva]==NULL)
			{
				push(id_stiva,p->tip,p->id,aux1);
				pop(id_stiva,s);

			}
			else
			{
				p2=(TParanteza*)aux1->vf[id_stiva]->info;
				while(aux1 -> vf[id_stiva] != NULL && p->id > p2->id)
				{
					push(id_stiva,p2->tip,p2->id,aux2);
					pop(id_stiva,aux1);
					if(aux1->vf[id_stiva])
						p2=(TParanteza*)aux1->vf[id_stiva]->info;
				}
				push(id_stiva,p->tip,p->id,aux1);
				pop(id_stiva,s);
				while(aux2->vf[id_stiva])
				{
					p=(TParanteza*)aux2->vf[id_stiva]->info;
					push(id_stiva,p->tip,p->id,aux1);
					pop(id_stiva,aux2);
				}
			}	
		}
		
		while(aux1->vf[id_stiva])
		{
			p2=(TParanteza*)aux1->vf[id_stiva]->info;
			
			push(id_stiva,p2->tip,p2->id,s);
			pop(id_stiva,aux1);
				
		}

	}
}
/*folosesc aceeasi idee ca la prints doar ca am nevoie de  coada auxiliara pe care o iau 
din vectorul pe care il aloc. Afisez elementele in ordine in care le bag in coada auxiliara. */
void printq( ACoada c,int nr,FILE *output)
{
	int i;
	TParanteza *p=(TParanteza*)calloc(1,sizeof(TParanteza));
	ACoada aux=initC(nr);
	for(i=0;i<nr;i++)
	{
		fprintf(output,"\"");
		if(c->ic[i])
		{
			while(c->ic[i])
			{
				p=(TParanteza*)c->ic[i]->info;
				intrq(i,p->id,p->tip,aux);
				fprintf(output, "%c", p -> tip);
				extrq(i,c);
			}
			
				while (aux->ic[i])
			{
				p=(TParanteza*)aux->ic[i]->info;
				intrq(i,p->id,p->tip,c);
				extrq(i, aux);
			}
		}
		fprintf(output, "\"\n");
	}
	
}
//folosesc aceeasi idee ca la sorts
void sortq (ACoada c,int nr,int id_coada)
{
	AStiva aux1,aux2;
	TParanteza *p=(TParanteza*) calloc(1,sizeof(TParanteza));
	TParanteza *p2=(TParanteza*) calloc(1,sizeof(TParanteza));
	aux1=initS(nr);
	aux2=initS(nr);
	if(c->ic[id_coada])
	{
		while(c->ic[id_coada])
		{
			p=(TParanteza*)c->ic[id_coada]->info;
			if(aux1->vf[id_coada]==NULL)
			{
				push(id_coada,p->tip,p->id,aux1);
				extrq(id_coada,c);
			}

			else
			{
				p2=(TParanteza*)aux1->vf[id_coada]->info;
				while(aux1 -> vf[id_coada] != NULL && p->id > p2->id)
				{
					push(id_coada,p2->tip,p2->id,aux2);
					pop(id_coada,aux1);
					if(aux1->vf[id_coada])
						p2=(TParanteza*)aux1->vf[id_coada]->info;
				}
				push(id_coada,p->tip,p->id,aux1);
				extrq(id_coada,c);
				while(aux2->vf[id_coada])
				{
					p=(TParanteza*)aux2->vf[id_coada]->info;
					push(id_coada,p->tip,p->id,aux1);
					pop(id_coada,aux2);
				}
			}	
		}
		
		while(aux1->vf[id_coada])
		{
			p2=(TParanteza*)aux1->vf[id_coada]->info;
			
			intrq(id_coada,p2->id,p2->tip,c);
			pop(id_coada,aux1);
				
		}

	}

}

//fac o copie stivei s utilizand doua stive auxliare in care introduc elementele din stiva initiala. 
//apoi din una le bag inapoi in cea initiala iar din a doua auxiliara in prima pe care o returnez 
AStiva copie (AStiva s,int nr,int id_stiva)
{
	
	AStiva aux1=initS(nr);
	AStiva aux2=initS(nr);
	TParanteza *p=(TParanteza*)calloc(1,sizeof(TParanteza));
	while(s->vf[id_stiva] != NULL)
	{
		p=(TParanteza*)s->vf[id_stiva]->info;
		push(id_stiva,p->tip,p->id,aux1);
		push(id_stiva,p->tip,p->id,aux2);
		pop(id_stiva,s);

	}
	while(aux1->vf[id_stiva] != NULL)
	{
		p=(TParanteza*)aux1->vf[id_stiva]->info;
		push(id_stiva,p->tip,p->id,s);
		pop(id_stiva,aux1);
	}
	
	while(aux2->vf[id_stiva] != NULL)
	{
		p=(TParanteza*)aux2->vf[id_stiva]->info;
		push(id_stiva,p->tip,p->id,aux1);
		pop(id_stiva,aux2);
	}
	return aux1;


}
/*aceasta functie returneaza o inversa a srivei initiale,atat elementele fiind pus in ordine inversa
(varful devine baza) cat si tipul parantezelor este inversat */
AStiva inversa(AStiva s,int id_stiva,int nr)
{
	AStiva aux=copie(s,nr,id_stiva);
	AStiva aux2=initS(nr);
	TParanteza *p=(TParanteza*)calloc(1,sizeof(TParanteza));
	while(aux->vf[id_stiva] != NULL)
	{
		p=(TParanteza*)aux->vf[id_stiva]->info;
		if(p->tip =='[') {p->tip=']';}
		else if(p->tip =='{') {p->tip='}';}
		else if(p->tip =='(') {p->tip=')';}
		else if(p->tip ==')') {p->tip='(';}
		else if(p->tip ==']') {p->tip='[';}
		else if(p->tip =='}') {p->tip='{';}
		push(id_stiva,p->tip,p->id,aux2);

		pop(id_stiva,aux);

	}
	return aux2;
}
/* folosesc o copie a stivei intiale si inca o stiva auxiliara(din un vector de stive alocat)
Introduc in stiva auxiliara cat timp avem in varf paranteze deschise.
Apoi compar elementele ramase din copie cu cele din varful stivei auxiliare iar daca gasesc paranteze inchise corect
maresc nr curent iar daca nu,verific daca trebuie sa actualizez maximul  si eliberez coada. */
int corrects(AStiva ss,int nr,int id_stiva)
{
	AStiva aux1=initS(nr);
	AStiva s=initS(nr);
	TParanteza *p=(TParanteza*)calloc(1,sizeof(TParanteza));
	TParanteza *p2=(TParanteza*)calloc(1,sizeof(TParanteza));
	int max=0,nrc;	
	s=copie(ss,nr,id_stiva);
	if(s->vf[id_stiva])
	{ nrc=0;
		while(s->vf[id_stiva])
		{	
			p=(TParanteza*)s->vf[id_stiva]->info;
			while((p->tip=='}' || p->tip == ')' || p->tip == ']') && s->vf[id_stiva]!=NULL)
			{
				push(id_stiva,p->tip,p->id,aux1);
				pop(id_stiva,s);
				if(s->vf[id_stiva]!=NULL) 
					p=(TParanteza*)s->vf[id_stiva]->info;

			}	
			while(s->vf[id_stiva] !=NULL && (p->tip=='{' || p->tip == '(' || p->tip == '['))
			{
				pop(id_stiva,s);
				if(aux1->vf[id_stiva] != NULL)
				{
					p2=(TParanteza*)aux1->vf[id_stiva]->info;
				}
				else 
				{
					if(max<nrc	) max=nrc;
					nrc=0;
					break;
				}
				
				if((p2->tip==']' && p->tip == '[') || (p->tip=='{' && p2->tip == '}') || (p->tip=='(' && p2->tip == ')'))
				{
					pop(id_stiva,aux1);
					nrc+=2;
				}
				else 
				{
					while(aux1->vf[id_stiva] != NULL)
					{
							pop(id_stiva,aux1);
					}
					
					if(max<nrc) max=nrc;
					nrc=0;
					break;
				}
				
				if(s->vf[id_stiva]!=NULL) p=(TParanteza*)s->vf[id_stiva]->info;
			}
			if(max < nrc) max = nrc;

		}
	}
	return max;
}
//fac copie unei cozi utilizand doua cozi auxilliare pentru a pastra una si a o returna iar
//iar din una sa introduc  inapoi in coada initiala
ACoada copieq(ACoada c,int nr,int id_coada)
{
	ACoada aux1=initC(nr);
	ACoada aux2=initC(nr);
	TParanteza *p=(TParanteza*)calloc(1,sizeof(TParanteza));
	while(c->ic[id_coada] != NULL)
	{
		p=(TParanteza*)c->ic[id_coada]->info;
		intrq(id_coada,p->id,p->tip,aux1);
		intrq(id_coada,p->id,p->tip,aux2);
		extrq(id_coada,c);
	}

	while(aux1->ic[id_coada] != NULL)
	{
		p=(TParanteza*)aux1->ic[id_coada]->info;
		intrq(id_coada,p->id,p->tip,c);
		extrq(id_coada,aux1);
	}
	return aux2;
}

//mut elementele dintr-o coada intr-o lista
AStiva correctq2(ACoada c,int id_coada,int nr)
{
	ACoada cc=initC(nr);
	cc=copieq(c,nr,id_coada);
	AStiva aux=initS(nr);
	TParanteza *p=(TParanteza*)calloc(1,sizeof(TParanteza));
	while(cc->ic[id_coada] != NULL)
	{
		p=(TParanteza*)cc->ic[id_coada]->info;
		push(id_coada,p->tip,p->id,aux);
		extrq(id_coada,cc);
	}

	return aux;		
}
int main(int argc, char *argv[])
{
	int s, c, n, i, nr, id;
	char command[10], p,c1;
	FILE *input, *output;
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	fscanf(input, "%d", &n);
	fscanf(input, "%d", &s);
	fscanf(input, "%d", &c);
	AStiva stiva = initS(s);
	AStiva st;
	ACoada coada = initC(c);
	for (i = 0; i < n; i++)
	{
		fscanf(input, "%s", command);
	
		if (strcmp(command, "push") == 0)
		{
			fscanf(input, "%d", &nr);
			fscanf(input, "%d", &id);
			fscanf(input, "%c", &c1);
			fscanf(input, "%c", &p);
			push(nr, p, id, stiva);
		}
		if (strcmp(command,"pop") == 0)
		{
			fscanf(input, "%d", &nr);
			pop(nr,stiva);
		}
		
		if (strcmp(command, "intrq") == 0)
		{
			fscanf(input, "%d", &nr);
			fscanf(input, "%d", &id);
			fscanf(input, "%c", &c1);
			fscanf(input, "%c", &p);
			intrq(nr, id, p, coada);
		}
		if (strcmp(command,"extrq") == 0)
		{
			fscanf(input, "%d", &nr);
			extrq(nr,coada);
		}
		if (strcmp(command, "sortq") == 0)
		{
			fscanf(input, "%d", &nr);
			sortq(coada, c, nr);
		}
		if (strcmp(command, "sorts") == 0)
		{
			fscanf(input, "%d", &nr);
			sorts(stiva, s, nr);
		}	
		if(strcmp(command,"prints") == 0)
		{
			prints(stiva,s,output);
		}
		if(strcmp(command,"printq") == 0)
		{
			printq(coada,c,output);	
		}	
		if(strcmp(command,"corrects") == 0)
		{
			fscanf(input,"%d",&nr);
			st=inversa(stiva,nr,s);
			if(corrects(stiva,s,nr)<corrects(st,s,nr))
			{
				fprintf(output,"%d\n", corrects(stiva,s,nr));
			}
			else  fprintf(output,"%d\n",corrects(st,s,nr));
			
		}
		if(strcmp(command,"correctq") == 0)
		{
			fscanf(input,"%d",&nr);
			st=inversa(correctq2(coada,nr,c),nr,s);
			if(corrects(st,c,nr)<corrects(correctq2(coada,nr,c),c,nr))
			{
				fprintf(output,"%d\n", corrects(st,c,nr));
			}
			else  fprintf(output,"%d\n",corrects(correctq2(coada,nr,c),c,nr));
			
		}

	}
	return 0;
}
