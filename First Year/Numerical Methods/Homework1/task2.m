function Z = zigzag(n)
%functia returneaza o matrice zig-zag
Z=zeros(n);
k=0;
j=1;
i=1;
while(i<=n)
  Z(1,i)=k;
  if((i+1)<=n)
    Z(1,i+1)=k+1;
  endif
  k=k+4*j+1;
  j=j+1;
  i=i+2;
endwhile
%pana aici am creat prima linie a matricei observand ca intre un element par 
%si unul impar diferenta este 1 iar intre unul impar si unul par diferenta este 
%un multiplu de 4,care creste liniar odata cu cresterea numarului care indica coloana
for i=1:n
  a=2;
  if(mod(i,2)==1)
    urm=Z(1,i);
    b=i-1;
    while(a<=i)
      Z(a,b)=urm-1;
      urm=Z(a,b);
      a++;
      b--;
    endwhile
  else
    urm=Z(1,i);
    b=i-1;
    while(a<=i)
      Z(a,b)=urm+1;
      urm=Z(a,b);
      a++;
      b--;
    endwhile
  endif
 endfor
 %completam diagonalele secundare in functie de paritatea indicelui care 
 %arata coloana.
  
 if(mod(n,2)==0)
  b=n/2-1;
  for i=2:n
   a=i+1;
   c=n-1;
    if(mod(i,2)==0)
      Z(n,i)=Z(n,i-1)+1;
      ultim=Z(n,i);
      while(a<=n)
        Z(c,a)=ultim+1;
        ultim=Z(c,a);
        c--;
        a++;  
      endwhile
    else 
      Z(n,i)=Z(n,i-1)+4*b;
      b--;
      ultim=Z(n,i);
      while(a<=n)
        Z(c,a)=ultim-1;
        ultim=Z(c,a);
        c--;
        a++;
      endwhile
   endif
  
   endfor
 else
  b=(n+1)/2-1; 
  for i=2:n
    a=i+1;
    c=n-1;
    if(mod(i,2)==0)
      Z(n,i)=Z(n,i-1)+4*b;
      b--;
      ultim=Z(n,i);
      while(a<=n)
        Z(c,a)=ultim-1;
        ultim=Z(c,a);
        c--;
        a++;
      endwhile
    else 
      Z(n,i)=Z(n,i-1)+1;
      ultim=Z(n,i);
      while(a<=n)
        Z(c,a)=ultim+1;
        ultim=Z(c,a);
        c--;
        a++;  
      endwhile
    endif
  endfor
 endif
%Apoi,in functie de paritatea lui n am completat si ultima linie observand
%relatiile ce se stabilesc intre termeni,iar in functie de indicii 
%coloanelor am completat si ultimii termeni ai lui Z.
endfunction
