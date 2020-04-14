; Задание:
; 4.3.1. Перекрыть прерывание клавиатуры и сделать так, 
; чтобы одна из букв (например “a”) подменялась другой (например “b”).



ideal
    model tiny
    codeseg
            org     100h
    start:
			mov 	dx, offset msg
			mov 	ah, 09h
			int 	21h
            jmp     install
    hook:
            cmp     ah, 4fh         ; это функция 4fh ?
            jne     jmp_old
			
            cmp     al, 1eh			; скан-код клавиши 'a'
            jne     jmp_old
            add     al, 12h			; добавляем 18 для перехода на клавишу 'b'
      
									; прыгаем на старый обработчик
    jmp_old:
            stc                     ; устанавливаем флаг переноса
            db      0eah            ; jmp far на старый обработчик
    to_ofs  dw      ?
    to_seg  dw      ?
    install:
            mov     ax, 3515h       ; получаем адрес обработчика прерывания 15h
            int     21h
            mov     [to_seg], es
            mov     [to_ofs], bx
            push    cs
            pop     ds
            mov     dx, offset hook
            mov     ax, 2515h
            int     21h             ; устанавливаем свой
									; вечный цикл опроса клавиатуры, пока не будет нажата Enter
    input:
            mov     ah, 1
            int     21h
            cmp     al, 13
            jne     input
     
									; восстанавливаем обработчик Int 15h
            mov     dx, [to_ofs]
            mov     ds, [to_seg]
            mov     ax, 2515h
            int     21h
									; и уходим в DOS
            ret

	msg db "Enter a string: $"
    end start