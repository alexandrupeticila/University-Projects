    extern puts
extern printf

section .data
filename: db "./input.dat",0
inputlen: dd 2263
fmtstr: db "Key: %d",0xa,0

section .text
global main

; TODO: define functions and helper functions

;################################################## TASK 1 #################################################
xor_strings:
    push ebp
    mov ebp,esp
    mov eax, [ebp + 8]          ;stringul
    mov edx, [ebp + 12]         ;cheia
    xor ecx, ecx                ;contor, fac xor byte cu byte
    mov  bl, byte [eax+ecx]     ;iau cate un byte
    mov  bh, byte [edx+ecx]
    

xor_untill_null:
    xor bl,bh           
    mov byte [eax+ecx], bl      ;actualizez stringul pe care il decriptez
    inc ecx                     ;actualizez pozitia
    mov  bl, byte [eax+ecx]
    mov  bh, byte [edx+ecx]
    cmp bl, 0x00                 ;merg cat timp nu gasesc null  
    jnz xor_untill_null  
    
    leave
    ret

;################################################## TASK 2 #################################################
rolling_xor:
    push ebp
    mov ebp,esp
    mov eax, [ebp + 8]          ;stringul care trebuie decriptat
    xor ecx, ecx                ;contor, fac xor byte cu byte
    mov  bl, byte [eax+ecx]     ;iau primul byte
    inc ecx                     ;incrementez ecx pentru a lua byte-ul urmator
    mov  bh, byte [eax+ecx]     ;iau al doilea byte
    

roll_xor_untill_null:
    xor bh,bl                   ;xor intre byte-ul de pe poz i+1 si de pe poz i
    mov bl, byte [eax+ecx]      ;pun in bl byte-ul inainte de a-l decripta pentru a-l folosi drept cheie   
    mov byte [eax+ecx], bh      ;actualizez stringul pe care il decriptez
    inc ecx                     ;actualizez pozitia
    mov  bh, byte [eax+ecx]     ;actualizez noul byte de decriptat
    cmp bh, 0x00                ;merg cat timp nu gasesc null  
    jnz roll_xor_untill_null
    
    leave
    ret         

;################################################## TASK 3 #################################################        
xor_hex_strings:
    push ebp
    mov ebp, esp
    xor ecx, ecx
    mov edi, [ebp + 8]          ;cheia
    mov esi, [ebp + 12]         ;stringul
    mov al, [esi+ecx]           ;prima litera din string
    mov bl, [edi+ecx]           ;primul caracter din cheie
    inc ecx        
    mov ah, [esi+ecx]           ;al doilea din string
    mov bh, [edi+ecx]           ;al doilea din cheie

    
for_each_2_char:
    cmp ah, 96                  ;verific pe rand daca ah,al,bh,bl sunt cifre sau litere
    jle sub_48_V1               ;si in functie de asta scad 48 sau 87 pentru a obtine ce ne trebuie
    sub ah,39
    
sub_48_V1:
    sub ah,48
    cmp al, 96
    jle sub_48_V2
    sub al,39
    
sub_48_V2:
    sub al,48
   
    shl al, 4                  ;retin in Al numarul in hexa din string
    add al, ah  
                               ;pentru primele doua caractere din string             
    cmp bh, 96
    jle sub_48_V3
    sub bh,39
    
sub_48_V3:
    sub bh,48
    
    cmp bl, 96
    jle sub_48_V4
    sub bl,39
    
sub_48_V4:
    sub bl,48
    
    shl bl, 4                   ;iar in bl numarul in hexa din cheie
    add bl, bh                  ;pentru primele doua caractere din cheie 
   
    xor al,bl                   ;fac xor intre cele doua numere
    dec ecx
    mov byte [esi+ecx], al      ;pun in string caracterul corespunzator     
    add ecx,2 
    mov al, [esi+ecx]           ;actualizez caracterul din string
    mov bl, [edi+ecx]           ;actualizez caracter din cheie
    cmp al, 0x00                ;verific daca am ajuns la null
    jz set_correct_order        ;daca da, sar la next
    
    inc ecx        
    mov ah, [esi+ecx]           ;actualizez al doilea caracter din numarul aferent stringului
    mov bh, [edi+ecx]           ;actualizez al doilea carcater din numarul pentru cheie
      
    cmp ah, 0x00                ;verific daca al doilea caracter a ajuns la null
    jnz for_each_2_char         ;daca nu, trec la urmatorul caracter

set_correct_order:
    mov edx,0                   ;folosesc ecx si edx pentru a pune caracterele in ordinea ok
    mov ecx,0

set_value_2i_i:
    mov ah, byte [esi + edx]    ;atribui elementului de pe poz i, valoarea de pe poz 2*i
    mov byte [esi + ecx], ah
    inc ecx
    add edx,2
    cmp byte [esi + edx], 0x00
    jne set_value_2i_i
    
    mov byte [esi+ecx], 0x00            ; pun null la jumate              
    mov eax, esi
    
    leave
    ret

;################################################## TASK 4 #################################################                                          
convertor_base32:               ;transform in functie de input pentru a obtine tabele din cerinta
    push ebp
    mov ebp,esp
    mov eax,[ebp + 8]
    xor ecx, ecx                ;ecx = 0, il folosesc drept contor        

for_each_character:
    mov bl, byte [eax + ecx]
    cmp bl, 0x00
    jz base32_null_character
  
    cmp bl, 'A'                ;cifra scad 24
    jl scade_cifra
    jmp scade_litera
    
scade_cifra:
    sub bl,24
    jmp next_character

scade_litera:                  ;litera scad 65
    sub bl,65
    
next_character:
    mov byte [eax + ecx], bl    ;actualizez stringul
    inc ecx                     ;trec la pozitia urmtaore                                                                                                                       
    jmp for_each_character                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                        
base32_null_character:
    leave
    ret              
    
base32decode:
    push ebp
    mov ebp,esp
    mov eax, [ebp + 8]
    xor edi,edi                         ;contor
    xor esi,esi                         ;contor
    mov bl , byte [eax + edi]
    mov bh, byte [eax + edi + 1]
    
                 
repeat_each_5_char:                     ;m-am folosit de repetare relatiilor la fiecare grup de 5 octeti
    shl bl,3
    shr bh,2
    add bl,bh
    mov byte [eax + esi], bl
    inc esi
    inc edi
    
    mov bl, byte [eax + edi]            ;pentru obtinerea relatiilor de mai jos am facut calculele respective pe foaie
    mov bh, byte [eax + edi + 1]        ;am folosit faptul ca la fiecare octet erau folositi doar 5 biti
    mov dl, byte [eax + edi + 2]
    shl bl,6
    shl bh,1
    shr dl,4
    add bl,bh
    add bl,dl
    mov byte [eax + esi],bl
    inc esi
    add edi,2
    
    mov bl , byte [eax + edi]
    mov bh, byte [eax + edi + 1]
    shl bl,4
    shr bh,1
    add bl,bh
    mov byte [eax + esi], bl
    inc esi
    inc edi
    
    mov bl , byte [eax + edi]
    mov bh, byte [eax + edi + 1]
    mov dl, byte [eax + edi + 2]
    shl bl,7
    shl bh,2
    shr dl,3
    add bl,bh
    add bl,dl
    mov byte [eax + esi], bl
    inc esi
    add edi, 2
    
    mov bl , byte [eax + edi]
    mov bh, byte [eax + edi + 1]
    shl bl,5
    add bl, bh
    mov byte [eax + esi],bl 
    inc esi
    add edi, 2
    
    mov bl , byte [eax + edi]
    mov bh, byte [eax + edi + 1]
    cmp bl, 0x00
    jz null_out_of_repeat
    
    jmp repeat_each_5_char
    
            
null_out_of_repeat:     
    sub esi, 3                      ;scadem nr de iteratii suplimentare pana la iesirea din bucla 

set_space_after_decode_string:    
    mov byte [eax + esi],' '        ;'golim' caracterele suplimentare obtinute pana la intalnirea 0x00
    inc esi
    cmp byte[eax + esi],0x00
    jne set_space_after_decode_string
    
    leave
    ret             
                     
 ;################################################## TASK 5 #################################################       
bruteforce_singlebyte_xor:
      push ebp
      mov ebp,esp
      mov eax, [ebp + 8]     ; stringul
      mov ebx, [ebp +12]     ;in ebx se ma gasi cheia la final   
      xor dl,dl              ;tin cheia
      xor ecx,ecx            ;ma plimb prin string 
        
try_key:
       inc dl
       xor ecx,ecx
       mov dh,dl
      
try_untill_null:
      mov dl,dh  
      
      inc ecx  
      cmp byte [eax + ecx], 0x00             ;la fiecare caracter verific intai daca am ajuns la final
      jz try_key                             ;daca am ajuns, incerc urmatoarea cheia   
      mov dh,dl
      xor dl, byte [eax + ecx]                ;aplic codificarea pe caracterul curent si verific daca obtin litera cautata
      cmp dl, 'f'
      jnz try_untill_null                     ;daca nu,trec la urmator caracter
      
      cmp byte [eax+ ecx +1], 0x00            ;repet pentru celelalte 4 litere pana gasesc cuvantul
      jz try_key
      mov dl,dh
      xor dl, byte[eax + ecx +1]
      cmp dl, 'o'
      jnz try_untill_null
      
      cmp byte [eax+ ecx + 2], 0x00
      jz try_key
      mov dl,dh
      xor dl, byte[eax + ecx+ 2]
      cmp dl, 'r'
      jnz try_untill_null
      
      cmp byte [eax+ ecx+ 3], 0x00
      jz try_key
      mov dl,dh
      xor dl, byte[eax + ecx+ 3]
      cmp dl, 'c'
      jnz try_untill_null
      
      cmp byte [eax+ ecx+ 4], 0x00
      jz try_key
      mov dl,dh
      xor dl, byte[eax + ecx+ 4]
      cmp dl, 'e'
      jnz try_untill_null
      mov dl, dh


      movzx ebx,dl                      ;transfer cheia intr-un reg pe mai multi biti
      
      xor ecx, ecx
      mov dh, byte [eax + ecx]           ; tin cate un caracter din string       
       
aplly_for_all_char:
       xor dh, dl                         ;aplic codificarea
       mov byte [eax + ecx], dh           ;actualizez stringul
       inc ecx
       mov dh, byte [eax + ecx] 
       cmp dh, 0x00
       jne aplly_for_all_char            ;repet pana la null      
      
      leave 
      ret

;################################################## TASK 6 #################################################
break_substitution:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    mov ebx, [ebp + 12]
    xor ecx,ecx
    mov dl, 'a'
    
fill_table_in_order:
    mov byte [ebx + ecx], dl        ;alfabetul original
    add ecx,2
    add dl, 1
    cmp ecx,50
    jle fill_table_in_order
    
    mov byte [ebx + ecx],' '
    add ecx,2
    mov byte [ebx + ecx], '.'
    
    mov byte [ebx + 1], 'q'        ;alfabetul folosit la codare
    mov byte [ebx + 3], 'r'        ;l-am obtinut prin observarea frecventei cu care apar literele in mesaj
    mov byte [ebx + 5], 'w'
    mov byte [ebx + 7], 'e'
    mov byte [ebx + 9], ' '
    mov byte [ebx + 11], 'u'
    mov byte [ebx + 13], 't'
    mov byte [ebx + 15], 'y'
    mov byte [ebx + 17], 'i'
    mov byte [ebx + 19], 'o'
    mov byte [ebx + 21], 'p'
    mov byte [ebx + 23], 'f'
    mov byte [ebx + 25], 'h'
    mov byte [ebx + 27], '.'
    mov byte [ebx + 29], 'g'
    mov byte [ebx + 31], 'd'
    mov byte [ebx + 33], 'a'
    mov byte [ebx + 35], 's'
    mov byte [ebx + 37], 'l'
    mov byte [ebx + 39], 'k'
    mov byte [ebx + 41], 'm'
    mov byte [ebx + 43], 'j'
    mov byte [ebx + 45], 'n'
    mov byte [ebx + 47], 'b'
    mov byte [ebx + 49], 'z'
    mov byte [ebx + 51], 'v'
    mov byte [ebx + 53], 'c'
    mov byte [ebx + 55], 'x'
    mov byte [ebx + 56], 0x00
                                                                                                                                                                                                                                                                                                        

    xor ecx, ecx
    
repeat_for_all_char:   
    
    mov dh, byte[eax + ecx]             ;pentru fiecare caracter din string
    cmp dh, 0x00                        ;verific daca am ajuns la null
    je final_task_6                     ;daca da, ies din functie
    mov esi,1                           ;plec cu contorul de la prima pozitie impara
    
find_in_alphabet:
    mov dl, byte [ebx + esi]            ;caut in buffer pozitia pe care apara litera
    add esi,2
    cmp dl, dh
    jnz find_in_alphabet
    
    sub esi,3
    mov dl, byte [ebx + esi]            ;si pun litera precendta pe pozitia curenta din string
    mov byte [eax + ecx ], dl 
    inc ecx
    jmp repeat_for_all_char

final_task_6:
    leave
    ret

main:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    sub esp, 2300
    
    ; fd = open("./input.dat", O_RDONLY);
    mov eax, 5
    mov ebx, filename
    xor ecx, ecx
    xor edx, edx
    int 0x80

    
	; read(fd, ebp-2300, inputlen);
	mov ebx, eax
	mov eax, 3
	lea ecx, [ebp-2300]    ;stringul
	mov edx, [inputlen]    ;lungimea
	int 0x80
        
        
;############################### TASK 1 ##########################################
      
       mov al, 0x0                 ; compar cu null
       mov edi, ecx                ; pun cheia in edi  
       repne scasb                
       lea ecx, [ebp - 2300]       ;pastrez stringul in ecx
       push ecx
       push edi
       call xor_strings             ;apelez functia care face decriptare
       add esp, 8                   ;actualizez varful stivei
       push eax                     ;afisez stringul decriptat
       call puts
       add esp, 4


;################################ TASK 2 ##################################################
    
        mov al, 0x00
        repne scasb
        push edi
        call rolling_xor
        add esp, 4
        push eax
        call puts
        add esp,4
 
;################################ TASK 3 ##################################################
        
        mov al, 0x00
        repne scasb
        mov esi, edi         ;stringul in esi 
        mov al, 0x00
        repne scasb          ;cheia in edi
        push esi
        push edi
        call xor_hex_strings    
        add esp,8
        push eax
        call puts
        add esp,4
        
                         
;################################ TASK 4 ##################################################
        
        mov al, 0x00
        repne scasb
        mov esi, edi
        
        mov al, 0x00
        repne scasb
        push edi                ;il pun pe stiva pentru ca voi modifica structura
        
        push esi                   
        call convertor_base32
        add esp, 4
        
        push eax
        call base32decode
        add esp,4
        
        push eax
        call puts
        add esp, 4
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
     
;################################ TASK 5 ##################################################
        
        pop edi             ;il salvez inainte de a face operatii pt task 4
        
        push ebx
        push edi
        call  bruteforce_singlebyte_xor
        add esp,8
        
        
        push eax
        call puts
        add esp,4
        
        push ebx
        push fmtstr
        call printf
        add esp,8 
       
            
;################################ TASK 6 ##################################################
        mov al, 0x00        
        repne scasb
   
        sub esp, 57                 ;loc pentru bufferul unde stochez "dictionarul" = cele doua alfabete
        lea ebx, [esp]
    
        push ebx
        push edi 
        call break_substitution     
        add esp, 8
    
        push eax
        call puts
        add esp,4
     
        push ebx
        call puts
        add esp,4                  
    
;################################################## FINAL :) #################################################    
        leave
        ret
