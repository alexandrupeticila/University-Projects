function [n]=locliber(A)
%functia verifica daca mai este un loc liber si intoarce "1" in caz afirmmativ si "0" altfel

n=0;
for(i=1:3)
  for(j=1:3)
    if(A(i,j)~=0)
    n=1;
    break
    
    endif
  endfor
endfor
endfunction