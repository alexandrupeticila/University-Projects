function [n]=win(A);
%functia verifica daca vreunul dintre jucatori a castigat si intoarce o valoare specifica ("1" daca 'x' a castigat,"0" daca '0' a castigat si "-1" altfel)
n=-1;
for i=1:3
  if(A(:,i)=='x' || A(i,:)=='x' )
    n=1;
   elseif( A(3,1)=='x' && A(2,2)=='x' && A(1,3)=='x')
    n=1;
    elseif((A(1,1)=='x'&& A(2,2)=='x' &&  A(3,3)=='x'))
    n=1;
     elseif(A(:,i)=='0' || A(i,:)=='0' )
    n=0;
   elseif( A(3,1)=='0' && A(2,2)=='0' && A(1,3)=='0')
    n=0;
    elseif((A(1,1)=='0'&& A(2,2)=='0' &&  A(3,3)=='0'))
    n=0;
 
   endif
endfor

endfunction