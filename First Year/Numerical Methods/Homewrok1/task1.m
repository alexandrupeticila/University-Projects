function r = baza(sursa,b1,b2)
%functia trece numarul sursa din baza b1 in baza b2
v='0123456789abcdefghijklmnopqrst';
%v este un vector care cuprinde toate posibilele simboluri 
s=sursa;
n=length(sursa);
l1=length(v);
for i=1:n
  for j=b1+1:l1
    if(sursa(i)==v(j))
      display("Ati introdus o cifra  sau litera prea mare pentru baza data");
      return 
    endif
  endfor
  ok=0;
  for j=1:l1
    if(sursa(i)==v(j))
      ok=1;
    endif
  endfor
  if(ok==0)
    display("Ati introdus un element diferit de cele 10 cifre si primle 20de litere");
   return
  endif
endfor

%trec numarul intai in baza 10
nou10=0;
for i=1:n
  for j=1:l1
    if(s(i)==v(j))
      nou10=nou10+(b1^(n-i))*(j-1);
    endif
  endfor
endfor
aaa=nou10;
if(nou10!=0)
  cat=1;
  else
  cat=0;
endif
i=1;
while(cat!=0)
    cat=floor(nou10/b2);
  rest=mod(nou10,b2);
 for j=0:29
 if(rest==j)
 
 rezultat(i)=v(j+1);
 endif
 endfor
 
  i++;
  nou10=cat;

endwhile
%prin impartiri repetate transfor numarul din baza 10 in baza b2
if (aaa !=0)
  r=rezultat(length(rezultat):-1:1);
else
  r=0;
endif
endfunction
