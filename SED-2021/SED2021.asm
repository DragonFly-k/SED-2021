.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "D:\лабы\€п\курсач\SED-2021\Debug\SED2021Lib.lib"
ExitProcess PROTO : DWORD
WriteW PROTO: SDWORD
WriteN PROTO: DWORD
stringLen PROTO: DWORD
StrConcat PROTO: DWORD, :DWORD
.stack 4096
.CONST
null_division BYTE 'ERROR: DIVISION BY ZERO', 0
	L0 SDWORD 11
	L1 SDWORD 1
	L2 BYTE 'Control example', 0
	L3 SDWORD 5
	L4 SDWORD 2
	L5 BYTE 'a is bigger than b', 0
	L6 BYTE 'b is bigger than a', 0
	L7 BYTE 'Combine two strings and output their length', 0
	L8 BYTE 'HELLO,jdjfslkf ', 0
	L9 BYTE 'WORLD!dsghj', 0
	L10 SDWORD 58
	L11 BYTE 'Control example completed successfully', 0
	L12 SDWORD 0
.DATA
	resultfact SDWORD 0
	desttask DWORD ?
	lentask SDWORD 0
	aSTART SDWORD 0
	bSTART SDWORD 0
	cSTART SDWORD 0
	firstSTART DWORD ?
	secondSTART DWORD ?
.CODE
factEXTERN PROC numbfact:SDWORD
	push L0
	pop eax
	mov resultfact, eax
	mov eax, numbfact
	cmp eax, resultfact
		jg ifi1
		jle else1
ifi1:
	push resultfact
	push numbfact
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	mov resultfact, eax
	push numbfact
	push L1
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	mov numbfact, eax
else1:
	push resultfact
	jmp local0
local0:
	pop eax
	ret
factEXTERN ENDP

taskEXTERN PROC etask:DWORD, ttask:DWORD
	push ttask
	push etask
	call StrConcat
	push eax
	pop desttask

	push desttask
	call stringLen
	push eax
	pop eax
	mov lentask, eax
	push lentask

	call WriteN
	push desttask
	jmp local1
local1:
	pop eax
	ret
taskEXTERN ENDP

main PROC
	push offset L2

call WriteW
	push L3
	pop eax
	mov aSTART, eax
	push L4
	pop eax
	mov bSTART, eax
	mov eax, aSTART
	cmp eax, bSTART
		jg ifi2
		jle else2
ifi2:
	push offset L5

call WriteW
	jmp ifEnd2
else2:
	push offset L6

call WriteW
ifEnd2:
	push offset L7

call WriteW
	push offset L8
	pop secondSTART

	push offset L9
	pop firstSTART

	push firstSTART
	push secondSTART
	call taskEXTERN
	push eax

call WriteW
	push L10
	call factEXTERN
	push eax

	call WriteN
	push offset L11

call WriteW
	push L12
	jmp theend
theend:
	call ExitProcess
SMTH:
	push offset null_division
	call WriteW
	jmp konec
konec:
	push -1
	call ExitProcess
main ENDP
end main