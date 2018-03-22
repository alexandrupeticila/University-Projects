function [ A M] = mutarecalculator (c,A, M)
%Aceasta functie alege,in functie de elemntul cu care joaca pc-ul,cea mai buna pozitie unde sa mute pentru a castiga(daca se poate) iar daca nu pentru a nu pierde sau pentru a nu ajunge in situatia sa piarda

if(c=='x')
%daca pc-ul este cu 'x',va ocupa intai pozitia din centru
  if(M(2,2)==' ')
    M(2,2)=c;A(2,2)=0;
  else
%altfel verifica intai daca poate castiga si apoi daca exista sansa sa piarda si ocupa pozitia in functie de rezultat

    [r x y]=sansacastig(M,'x');
    [r2 x2 y2]=sansacastig(M,'0');
      if(r==1)
        M(x,y)=c;A(x,y)=0;
      elseif(r2==1)
        M(x2,y2)=c;A(x2,y2)=0;
      elseif(r==0 && r2==0)
        [r3 x3 y3]=coltliber(M);
%daca nu poate castiga si nici pierde,atucni  pune in colt daca este liber,iar daca nu,unde gasseste un loc liber
        if(r3==1)
          M(x3,y3)=c;A(x3,y3)=0;
        else 
          [A M]=mutarecalculator1('x',A,M);
        endif
      endif  
  endif
elseif(c=='0')
%daca joaca cu '0',verifica daca este libera pozitia din centru si in caz afirmativ pune acolo
  if(M(2,2)==' ')
    M(2,2)=c;A(2,2)=0;
  else
%Altfel verifica daca poate castiga sau daca poate pierdesi muta in functie de rezultat
    [r x y]=sansacastig(M,'x');
    [r2 x2 y2]=sansacastig(M,'0');
    if(r2==1)
      M(x2,y2)=c;A(x2,y2)=0;
    elseif(r==1)
      M(x,y)=c;A(x,y)=0;
    elseif(r==0 && r2==0)
%daca nu exista nicio posibilitate din cele mai sus,se verifica daca vreuna din diagoanle este ocupata      
      rez=diagocupata(M)
      if(rez==1 && M(2,2)==M(3,3))
%aceasta este o mutare particulara care necesita o conditie suplimentara
        M(1,3)=c;A(1,3)=0;
      elseif(rez==1)
 %daca se ajunge aici,calulatorul va muta unde gaseste o pozitie libera,diferita de colt sis centru     
        [A M]=mutarecalculator1('0',A,M);
      else
        if((M(2,:)!=' ')||(M(:,2)!=' '))
%daca linia sau coloana 2 sunt complet pline,atunci se foloseste functia coltliber pentru a muta intr-un colt liber
         
          [r3 x3 y3]=coltliber(M);
          M(x3,y3)=c;A(x3,y3)=0;
        elseif (M(1,:)==' ' && M(3,:)==' ' && M(2,2)=='x')
%de asemenea,daca prima mutare a jucatorului va fi in centru,atunci calculatorul va cauta un colt liber si va muta acolo
 
          [r3 x3 y3]=coltliber(M);
          M(x3,y3)=c;A(x3,y3)=0;          
          
        else
%daca nu se intra pe nicio ramura pana acum,inseamna ca se ajunge la una dintre situatile analizate in functia coltbun,folosita pentru a gasi poztia perfecta pentru mutare
        [x4 y4]=coltbun(M);
          M(x4,y4)=c;A(x4,y4)=0;
        endif  
      endif
    endif
  endif
     
endif
endfunction
