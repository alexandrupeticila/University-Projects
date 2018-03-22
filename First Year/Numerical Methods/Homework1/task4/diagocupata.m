function [ret] = diagocupata (M)
%functia verifica daca cele doua diagonale sunt ocupata si intoarce 1 daca da si 0 altfel
ret=0;
if((M(1,1)~=' ' && M(2,2)~=' ' && M(3,3)~=' ') || (M(1,3)!=' ' && M(2,2)!=' ' && M(3,1)!=' '))
  ret=1;
endif
endfunction
