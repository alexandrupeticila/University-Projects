%include "io.inc"

section .data
    %include "input.inc"
   print_format db "Baza incorecta", 0
section .text
global CMAIN
CMAIN:
    mov ebp, esp
    xor ecx,ecx                         ;fac ecx 0 inainte de a intra in bucla si a-l compara cu nr de elemente   
    
for_each_element:
    mov eax,[nums_array+ecx*4]          ;pun in eax elementul ce trebuie convertit
    xor ebx,ebx                         ;pastrez in ebx numarul de caractere al nr in noua baza,folosit la printare

    cmp dword [base_array+ecx*4],2      ;daca baza nu respecta conditiile, se va afisa un mesaj corespunzator
    jl bad_base
    cmp dword [base_array+ecx*4],16
    jg bad_base

repeted_div:
    xor edx,edx                         ;pentru a putea efectua corect operatia de impartire
    div dword [base_array+ecx*4]        ; baza in care trebuie convertit
    push edx                            ;pun restul pe stiva pentru a afisa apoi in ordine inversa
    inc ebx
    cmp eax,0                           ;impart pana cand catul va fi 0
    jg repeted_div
     
good_print:                             ;scot de ebx ori numere de pe stiva 
    pop eax
    cmp eax,10  
    jl add_48                           ;daca nr scos este mai mic decat 10, adun 48 pentru a obine caracterul corespunzator
    add eax,39                          ;altfel adun 97=48+39

add_48:       
    add eax,48         
    PRINT_CHAR eax
    dec ebx
    cmp ebx,0
    jg good_print               
    NEWLINE                             ;dupa fiecare numar afisat trec pe randul urmator     
    jmp good_work                       ;daca totul a fost ok, trec peste printarea in cazul unei baze incorecte 
                                
bad_base:
    PRINT_STRING print_format           ;daca baza a fost incorecta,afisez mesaj corespunzator
    NEWLINE 
   
good_work:   
    inc ecx                             ;actualizez numarul de elemente parcuse 
    cmp ecx,[nums]                      ;verific daca am parcurs toate elementele
    jl for_each_element
     
    ret
    
