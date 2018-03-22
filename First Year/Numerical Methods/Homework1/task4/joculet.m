function   joculet(w ,e, l)
%functia incepe un joc de x si 0 si il termina prin apasarea oricand a tasteti "q".
%in plus,aceasta tine scorul si il afiseaza de fiecare data cand se termina o partida 
A=[1,2,3;4,5,6;7,8,9];
M=[' ',' ',' ';' ',' ',' ';' ',' ',' '];
%matricea A este folosita pentru a vedea locurile libere. Un ,oc este ocupat daca pozitia corespunzatoare lui este 0;
%Cand alegi pozitia unde vrei sa pui,alegi elementul aflat pe acea pozitie din A
%matricea M este initial umpluta cu spatii si atat timp cand o pozitie contine spatiu,poti sa muti acolo

display("Regulile jocului sunt simple. La inceput alegi cu ce vrei sa joci: X sau 0");
display("Aceasta alegere va fi facuta la inceputul fiecarei partide!");
display("Poti termina oricand prinn apasarea tasteti 'q'");
display("Daca vei alege X vei incepe iar daca vei alege 0 calculatorul va incepe");
%sunt afisate regulile jocului
input("Alege cu ce vrei sa joci:  " ,"s");
a=alegere(ans);
if(a=='q')
  break;
  
endif

while(a!='x' && a!='0' && a~='q')
 
  input("Alegere incorecta. Alege din nou:  ","s");
  a=alegere(ans);
endwhile
if(a=='x')
   display("Incepi primul")
  elseif(a=='0')
    display("Esti al doilea");
endif
%verificam alegerea si o repetam pana cand este una corecta,iar in functie de aceasta facem operatia dorita

afisare(M),A
%functia afisare este folosita pentru ca matricea M sa arate asa cum s-a cerut.
%in functie de ce alegem,vom intra pe una dintre cele doua ramuri
if(a=='x')
  while(   win(M)~=1 && win(M)~=0 && locliber(A)==1)
    %repetam procedeul cat timp nu a castigat nimeni si mai este un  loc libere
    input("Alege o pozitie libera (diferita de 0) cuprinsa intre 1 si 9   ","s");
    if(ans =='q')
      break
    endif
    %repetam procedeul pana cand se alege o pozitie valida si libera
    while(negasit(ans-48,A))
       input("Alege o pozitie libera (diferita de  0) cuprinsa intre 1 si 9   ","s");
    if(ans=='q')
      break
    endif
    endwhile
    while(ans>'9' || ans <'1')
      input("alege din nou o pozitie cuprinsa intre 1 si 9,din cele libere  ","s");
      if(ans=='q')
        break
      endif
    endwhile
    %Apoi completam matricele M si A corespunzator si verificam daca jocul s-a terminat (jucatorul a castigat sau s-a terminat egal)
    %in caz ca se termina,incepem un nou joc prin reapelarea functiei
    for(i=1:3)
       for(j=1:3)
        if(A(i,j)==ans-48)
           A(i,j)=0;
            M(i,j)='x';
            if(win(M)==1)
              w=w+1;
              w,l,e,afisare(M)  
              display("Ai castigat.Incepe un nou joc  ");
              joculet(w,e,l);
              return;          
            elseif(locliber(A)==0)
              e=e+1;
              w,e,l,afisare(M);
              display("Incepe un nou joc  ");
              joculet(w,e,l);
               return;    
            endif
        endif
      endfor
    endfor
    afisare(M),A
    %Aceleasi verificari vor fi facute si dupa ce calculatorul muta.
    display("E randul calculatorului");
    [A M]=mutarecalculator('0',A,M);
    A,afisare(M)
    if(win(M)==0)
      l=l+1;
      w,e,l,afisare(M)
      display("Ai pierdut.Incepe un nou joc  ");
      joculet(w,e,l); 
      return;
    elseif(locliber(A)==0)
       e=e+1;
       w,e,l,afisare(M)
       display("S-a terminat egal. Incepe un nou joc  ");
      joculet(w,e,l); 
      return;        
    endif
endwhile
%vor fi facute aceleasi verificari ca mai sus,doar ca intr-o alta ordine,pc-ul fiind cel care incepe.
%functia v-a fi reapelata de fiecare data cand se termina un joc.
elseif(a=='0')
  while(   win(M)~=1 && win(M)~=0 && locliber(A)==1)
   if(a~='q')
    display("E randul calculatorului");
    [A M]=mutarecalculator('x',A,M);
     if(win(M)==1)
      l=l+1;
      w,e,l,afisare(M)
      display("Ai pierdut.Incepe un nou joc  ");
      joculet(w,e,l);
      return; 
    elseif(locliber(A)==0)
       e=e+1;
       w,e,l,M
       display("S-a terminat egal. Incepe un nou joc  ");
      joculet(w,e,l);
      return; 
    endif
   endif
    A,afisare(M);
    input("Alege o pozitie libera (diferita de 0) cuprinsa intre 1 si 9   ","s");
    if(ans=='q')
      break
    endif
    while(negasit(ans-48,A))
      input("Alege o pozitie libera (diferita de 0) cuprinsa intre 1 si 9   ","s");
      if(ans=='q')
        return
      endif
    endwhile
    while(ans>'9' || ans <'1')
      input("alege din nou o pozitie cuprinsa intre 1 si 9,din cele libere  ","s");
      if(ans=='q')
        return
      endif
    endwhile
    for(i=1:3)
      for(j=1:3)
        if(A(i,j)==ans-48)
          A(i,j)=0;
          M(i,j)='0';
          if(win(M)==0)
            w=w+1;
            w,l,e,afisare(M)  
            display("Ai castigat.Incepe un nou joc  ");
            joculet(w,e,l);
            return;
         elseif(locliber(A)==0)
            e=e+1;
            w,e,l,afisare(M)
            display("Incepe un nou joc  ");
            joculet(w,e,l);
            return;    
         endif
        endif
      endfor
    endfor
    A,afisare(M);
  endwhile
  
endif

endfunction