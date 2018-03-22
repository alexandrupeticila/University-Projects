function n=negasit(a,A)
%Aceasta functie returneaza 1 in caz ca elementul a se gaseste in matricea M si 0 altfel;
ok =0;
for i=1:3
  for j=1:3
    if(A(i,j)==a)
      ok=1;
    endif
  endfor
endfor
if(ok==0) 
  n=1;
else 
  n=0;
endif
endfunction
