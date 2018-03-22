function N = eval_interpolator_c(tip,eps)
% eval_interpolator - determina cat de repede converge un polinom de interpolare
% tip - 1 lagrange
        % 2 newton
        % 3 linear spline
        % 4 natural 
        % 5 cubic spline
        % 6 fourrier
 % eps - toleranta acceptata pentru convergenta

%Se defineste o functie octave corespunzatore lui f(x) data in cerinta,reprezentand modul de evolutie al petelor solare 
function ans=f(x)
  a=3;
  ans=exp(a*cos(x))/(2*pi*besseli(0,a));
endfunction

%initializez n cu 1000 ca in cerinta
N=1000;
a=3;

%initializez o constanta dupa care ciclul se va opri daca metoda nu converge
nrmax=6;

%vom folosi o variabila nr in care retinem numarul de cicluri
nr=1;

%ciclul se opreste cand toleranta este mai mica sau egala cu cea primita ca parametru,eps
%De aceea avem nevoie de doua variabile pentru a testa aceasta conditiie,actualizandu-se

E=0; 
E0=2*eps;

while (abs(E-E0)>eps && nr< nrmax )
  nr=nr+1; %actualizez nr de cicluri
  Nk=2^(nr); %actualizez numarul de noduri de interpolare conform cerintei               
  xk=linspace(-pi,pi,Nk); %Generez suportul de interpolare,distanta devenind tot mai mica  
 
 %Aplic apoi formula din suportul temei pentru fiecare valoare,folosind vectorizari
 %calculand valoare functiei in punctele xk
  y(1:Nk)=exp(a*cos(xk(1:Nk)))/(2*pi*besseli(0,a));
  
  x=linspace(-pi,pi,N+1); 
  %am generat punctele in care se va analiza functia,folosind N-ul din pdf
 
  eroare=0;
  %am initializat eroarea cu 0;
  
  %apoi pentru fiecare valoare,in funcite de N,vom face operatia data de tip
  
  for i=1:Nk
    valoare=x(i);
    if(tip==1) %Lagrange
    
      polinom=0;
      aux=Nk;
      for i=1:Nk
        produs=y(i);
        for j=1:Nk
          if(i!=j)
             produs=produs*(valoare-xk(j))/(xk(i)-xk(j));
          endif
        endfor
        polinom=polinom+produs;
      endfor
    
    
     elseif(tip==2) %Newton
      polinom=0;
      aux=y;
      for i=1:Nk-1
        for j=i+1:Nk
          aux(j)=(aux(j)-aux(i))/(xk(j)-xk(i));
        endfor
      endfor
      polinom=aux(1);
      coeficient=1;
      for i=2:Nk
        coeficient=coeficient*(valoare-xk(i-1));
        polinom=polinom+coeficient*aux(i);
      endfor
      
      elseif(tip==3) %Spline liniar
        for i=1:Nk-1
          if(valoare>=xk(i))
            break;
          endif
        endfor
      
        m=(y(i+1)-y(i))/(xk(i+1)-xk(i));
        n=y(i)-xk(i)*(y(i+1)-y(i))/(xk(i+1)-xk(i));
        polinom=m*valoare+n;
      
        elseif
          display('Tipul nu exista');
        endif

      eroare=eroare+(abs(f(valoare)-polinom))^2;
   endfor

   E0=E;
   E=(((2*pi)/(Nk+1))*eroare)^(1/2); 
   %Se aplica formula finala pentru calculul erorii
   n=Nk;
   if (nr>nrmax && E>E0)             
     %In cazul in care s-a depasit un numarul de iteratii prestabilit ciclul se opreste
     %functia returneaza inf ceea ce inseamna ca  metoda nu converge  
        N=inf;
        break;
    endif 

 endwhile    
 
endfunction
