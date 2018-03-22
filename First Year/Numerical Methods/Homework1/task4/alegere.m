function a=alegere (s)
%functia compara elemnetul a si intoarce un mesaj corespunzator
%ea este folosita la inceputul fiecarui joc cand utilizatorul alege cu ce vrea sa joace
if(s=='x')
  display("Ai ales sa joci cu X.");
  a='x';
elseif(s=='0')
  display("Ai ales sa joci cu 0.");
  a='0';
elseif(s=='q')
    a='q';
     return
    
else
  
  a='1';
  
  
endif

endfunction
