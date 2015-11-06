GLOBAL playNote
section .text

playNote:

        
        mov     al, 182         ; Prepare the speaker for the note.
        out     43h, al         
;       mov     rax,0           ; Kevin - seteo en 0 porque tengo ganas
        mov     rax, rdi        ; Kevin - guardo en rax la frecuencia que me pasan por parametro
;       mov     ax, 9121        ; Frequency number (in decimal) for middle C.
        out     42h, al         ; Output low byte.
        mov     al, ah          ; Output high byte.
        out     42h, al 
        in      al, 61h         ; Turn on note (get value from port 61h).
       ;or     al,3            ;Kevin - hago lo que esta abajo pero en decimal para que quede mas lindo

       or      al, 00000011b   ; Set bits 1 and 0.
       out     61h, al         ; Send new value.

raro:
        jmp raro

       mov     bx, 25          ; Pause for duration of note.


.pause1:
        mov     cx, 65535
.pause2:
        dec     cx
        jne     .pause2
        dec     bx
        jne     .pause1
        in      al, 61h         ; Turn off note (get value from port 61h).

        ;and    al,252          ;Kevin - lo mismo que esta abajo, pero pasado en decimal

        and     al, 11111100b   ; Reset bits 1 and 0.
        out     61h, al         ; Send new value.