;
; SimpleASM_Verification.asm
;
; Created: 2/16/2019 2:24:14 PM
; Author : Benjamin Johnson
; Student #: 5003284489
; Email: johnsb18@unlv.nevada.edu


.org 0			; burn into ROM starting at 0
ldi R25, 0xFF	; load upper 8 bits of multiplicand
ldi R24, 0xFF	; load lower 8 bits of multiplicand
ldi R22, 0xFF	; load 8 bit multiplier


mul R24, R22	; multiply lower 8 bits of multiplicand
mov R18, R0		; store lower 8 bits of final answer
mov R19, R1		; store upper 8 bits of mul result
mul R25, R22	; multiply upper 8 bits of multiplicand
add R19, R0		; get final value of middle 8 bits of final answer
mov R20, R1		; store upper 8 bits of final answer

END:
jmp END			; end program