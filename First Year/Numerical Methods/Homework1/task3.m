function M = morse ()
h={'H' {} {}};
v={'V' {} {} };
f={'F' {} {} };
l={'L' {} {} };
p={'P' {} {} };
j={'J' {} {} };
b={'B' {} {} };
x={'X' {} {} };
c={'C' {} {} };
y={'Y' {} {} };
z={'Z' {} {} };
q={'Q' {} {} };

% penultimul nivel
s={'S' h v};
u={'U' f {} };
r={'R' l {} };
w={'W' p j};
d={'D' b x};
k={'K' c y};
g={'G' z q};
o={'O' {} {}};

%al treilea nivel
i={'I' s u};
a={'A' r w};
n={'N' d k};
m={'M' g o};

%al patrulea nivel
e={'E' i a };
t={'T' n m };

%nivelul 5
M={'' e t }; 

function x = morse_decode(sir)
n=length(sir);
x='*';
a=morse();
%am initializat a cu arborele nostru
%am pus conditia ca sirul de caractere primit sa aiba lungime buna,maxim 4 si diferita de 0
if(n>4)
  display("EROARE! Incearca un cod mai scurt");
  return;
endif
if(n==0)
  display("Codul nu contine niciun caracter");
  return
endif
%apoi am verificat daca fiecare element al sirului este ori "." ori "_" si in caz contrar am returnat un cod de eroare si am iesit din functie
for i =1:n
  if(sir(i)!='.' && sir(i)!='-')
    display("Eroare! Codul introdus nu estse valid!");
    return
  endif
endfor
%dupa aceea am avansat in arbore in functie de sirul de caractere primit ca parametru
%pentru fiecare caracter am avansat la dreapta,prin a{3} sau la stanga prin a{2}
for i=1:n
  if(sir(i)=='.')
    a=a{2};
  elseif(sir(i)=='-')
    a=a{3};
  endif
endfor
%Apoi am verificat daca nodul gasit in pozitia determinata anterior este sau nu gol
%Daca da,afisam un mesaj,altfel luam valoarea respectiva.
if(!isempty(a))
   x=a{1};
else 
    display("Nu se afla niciun caracter");    
endif

endfunction
