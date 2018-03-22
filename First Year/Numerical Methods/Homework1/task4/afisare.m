function afisare(M)
%functia primeste ca parametru matricea M si o afiseaza intr-o forma mult mai placuta pentru utilizator
I=['_','|','_','|','_';'_','|','_','|','_';' ','|',' ','|',' '];
for i=1:3
  for j=1:3
    if(M(i,j)~=' ')
      I(i,2*j-1)=M(i,j);
    endif
  endfor
endfor
I
endfunction

     