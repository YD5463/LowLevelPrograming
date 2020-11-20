org  100h

jmp main
	
	toSwap1 	db 'a'
	toSwap2 	db 'b'
	result	 	dw ?
	numToNeg	dw -9
	string      db  'm', 'a', 'g', 's', 'h', 'i', 'm', 'i', 'm', 'v', 'e', 'n', 'e', 'h', 'e', 'n', 'i', 'm' ,0Dh,0Ah,'$'
	str_ptr dw offset string  
	count dw 0
	array		db "0000", 0Dh,0Ah, 24h ; line feed   return   and  stop symbol 24h=$ (ASCII).
	array_ptr dw offset array   
	num1        dw 0xAC45 
PROC convert
    push bp
    mov bp,sp
    mov di,array_ptr
    add di,3
    mov ax,num1
    mov cx,0
    mov bx,16
    con:
    mov dx,0
    div bx
    cmp dl,9
    jnb a
    add dl,48
    jmp b
    a:
    add dl,55
    b:
    mov [di],dl
    dec di
    
    inc cx
    cmp cx,4
    jle con
    
    pop ax
    pop bx
    mov cx,4
       
    mov sp,bp
    pop bp     
ret  
ENDP convert

PROC sort
    push bp
    mov bp,sp
    mov si,str_ptr
    mov bx,0
    mov dx,0
    bub1:
       mov cx,17
       mov si,str_ptr
    bub2:
       mov al,[si]
       mov bl,[si+1]
       cmp al,bl
       jng no_s
       xchg al,bl
       mov [si],al
       mov [si+1],bl
       no_s:
       add si,1 
       loop bub2
       inc dx
       cmp dx,16
       jne bub1                            
    mov sp,bp
    pop bp
    ret
ENDP sort

PROC swap
    push bp
    mov bp,sp 
    add sp,4
    pop ax
    pop cx
    mov sp,bp
    pop bp       
retn 4
ENDP swap

PROC to_neg
    push bp
    mov bp,sp 
    add sp,4
    pop ax
    not ax
    add ax,1
    mov sp,bp
    pop bp

retn 4
ENDP to_neg

main:    
;func 1
PRINTN "2's complement is:"
mov ax,numToNeg
call print_num
PRINTN
push numToNeg
call to_neg
PRINTN "is:"
call print_num
PRINTN 
;func 2 
PRINTN "values before swap:"
mov al,toSwap1
PRINTN " toSwap1="
call print_al_chr
PRINTN " toSwap2="
mov al,toSwap2
call print_al_chr
PRINTN 
mov al,toSwap1
mov cl,toSwap2
push ax 
push cx
call swap
PRINTN "values after swap:"
PRINTN " toSwap1="
call print_al_chr
mov ax,cx
PRINTN " toSwap2="
call print_al_chr
;func 3
call convert 
mov ax,array_ptr
PRINTN "after convertion:"
call print_ax_str
PRINTN 
;func 4
PRINTN "string before:"
mov ax,str_ptr
call print_ax_str
call sort
mov ax,str_ptr
PRINTN "str sorted: "
call print_ax_str
mov ah, 0
int 16h
ret 
include magshimim.inc 