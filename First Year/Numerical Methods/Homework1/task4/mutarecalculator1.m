function [ A M] = mutarecalculator (c,A, M)
%functia cauta prima pozitie libera diferita de colt si centru si o umple cu elementul "c" primit ca parametru
a=0;
b=0;

for(i=1:3)
  for(j=1:3)
   
    if(A(i,j)!=0 && i!=j && i!=3-j+1 )
      a=i;
      b=j;
     
      break   
     endif
     
   endfor
   
endfor
A(a,b)=0;
M(a,b)=c;

endfunction
