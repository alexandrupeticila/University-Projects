function [ a b] = coltbun (M)
%Aceasta functie va fi folosita doar cand utilizatorul incepe cu "x" si va fi apelata doar dupa ce vor fi facute exact doua mutari de utilizator
%Ea cauta astfel primele coordonatele celor doua elemente "x" si le salveaza intr-un vector de lungime 4 (linie,coloana in ordinea gasirii)

rez=0;a=0;b=0;
n=zeros(1,4);
i=1;
for j=1:3
  for k=1:3
    if(M(j,k)=='x')
      n(i)=j;n(i+1)=k;
      i=i+2;
     endif
   endfor
endfor
%In functie de aceste coordonate vor fi tratrate 4 cazuri,cate unul pentru fiecare colt,pentru o mutare cat mai eficienta a calculatorului.
if((n(1)==1 && (n(2)==2 || n(2)==1) && (n(3)==2 || n(3)==3) && n(4)==3))
  a=1;b=3;
elseif(n(1)==1 && (n(2)==2 || n(2)==3) && (n(3)==2 || n(3)==3) && n(4)==1 ) 
  a=1;b=1;
elseif((n(1)==1 || n(1)==2) && n(2)==1 && n(3)==3 && (n(4)==2 || n(4)==3))
  a=3;b=1;
elseif((n(1)==1 || n(1)==2 ) && n(2)==3 && n(3)==3 && (n(4)==2 || n(4)==1))
  a=3;b=3;
endif
endfunction
