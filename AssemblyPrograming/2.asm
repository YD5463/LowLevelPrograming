org 100h

jmp main

	chrs db  'M','I','M','I','H','S','G','A','M','$'
    chrs_ptr dw offset chrs
main:
	mov bp, sp

	mov ax,offset chrs
	PRINTN "before:"
	call print_ax_str
	PRINTN 
	call reverse 
    PRINTN "after:"    
	mov ax,chrs_ptr
	call print_ax_str   
	jmp stop

reverse proc
	; First save the old BP  
	push bp	
	; Now establish new BP 
	mov bp, sp  
	;make space for 2 local variables
	add sp,4
	mov si,chrs_ptr
	mov dx,8
	mov cx,4
	rev:
	    add si,cx
	    mov al,[si]
	    mov si,chrs_ptr
	    sub dx,cx
	    add si,dx 
	    mov bl,[si]
	    mov dx,8
	    mov si,chrs_ptr
	    xchg al,bl
	    add si,cx
	    mov [si],al
	    mov si,chrs_ptr
	    sub dx,cx
	    add si,dx 
	    mov [si],bl
	    mov dx,8
	    mov si,chrs_ptr      
	    loop rev
	                
	mov sp, bp 
	; Restore OLD BP 
	pop bp
	ret  
reverse endp

stop:
	mov ah, 0 
	int 16h 
	ret

include magshimim.inc