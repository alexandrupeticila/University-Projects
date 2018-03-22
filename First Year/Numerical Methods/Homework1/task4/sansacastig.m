function [rez c b] = sansacastig (M,a)
%functia verifica daca este vreo sansa de castiag si in caz afirmativ intoarce rez "1" si coordonatele pozitiei de castig
rez=0;
c=0;b=0;
%se verifica intai toate liniile,apoi coloanele si apoi cele doua diagonale
for i=1:3
 
  if((M(i,1)==a && M(i,2)==a && M(i,3)==' ') || (M(i,1)==a && M(i,3)==a && M(i,2)==' ')|| (M(i,2)==a && M(i,3)==a && M(i,1)==' ') )
    rez=1;
    for j=1:3
     if(M(i,j)==' ')
      c=i;
      b=j;
      return;
    endif
   endfor
  elseif((M(1,i)==a &&  M(2,i)==a && M(3,i)==' ')||( M(1,i)==a && M(3,i)==a && M(2,i)==' ')||( M(2,i)==a && M(3,i)==a && M(1,i)==' '))
    rez=1;
    for j=1:3
     if(M(j,i)==' ')
      b=i;
      c=j;
      return;
    endif
   endfor
    endif
  
endfor
%aici se verifica diagonala principala intai si apoi diagonala secundara
if((M(1,1)==a && M(2,2)==1 && M(3,3)==' ')||(M(1,1)==a && M(3,3)==a && M(2,2)==' ')|| (M(1,1)==' ' && M(2,2)==a && M(3,3)==a)) 
  rez=1;
  for i=1:3
    if(M(i,i)==' ')
      c=i;b=i;
      return
    endif
  endfor
elseif ((M(1,3)==a && M(2,2)==a && M(3,1)==' ')|| (M(1,3)==a && M(2,2)==' ' && M(3,1)==a) ||(M(1,3)==' ' && M(2,2)==a && M(3,1)==a))
  rez=1;
  for i=1:3
    if(M(i,3-i+1)==' ')
      c=i;
      b=3-i+1;
      return
    endif
  endfor
endif
endfunction

