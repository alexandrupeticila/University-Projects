function [rez a b] = coltliber (M)
%functia verifica daca mai este vreun colt liber al matricei M si intoarce coordonatele acestuia daca exista
rez=0;
a=0;b=0;
if(M(1,1)==' ')
  a=1;b=1;
  rez=1;
  return
elseif(M(1,3)==' ')
  rez=1;a=1;b=3;
  return
elseif(M(3,1)==' ')
  rez=1;a=3;b=1;
  return
elseif(M(3,3)==' ')
  rez=1;a=3;b=3;
  return
endif

endfunction
