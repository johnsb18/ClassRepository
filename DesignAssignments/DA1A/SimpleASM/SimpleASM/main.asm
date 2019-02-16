;
; SimpleASM.asm
;
; Created: 2/16/2019 12:31:58 PM
; Author : Benjamin Johnson
; Student #: 5003284489
; Email: johnsb18@unlv.nevada.edu


.org 0			; burn into ROM starting at 0
ldi R25, 0xFF	; load upper 8 bits of multiplicand
ldi R24, 0xFF	; load lower 8 bits of multiplicand (d'449)
ldi R22, 0xFF	; load 8 bit multiplier (d'5)
ldi R18, 0		; initialize result register to zero
ldi R19, 0		; initialize result register to zero
ldi R20, 0		; initialize result register to zero
ldi R21, 0		; used to add carry into R20


LOOP:
add R18, R24	; add lower 8 bits
adc R19, R25	; add upper 8 bits
adc R20, R21	; add carry
dec R22			; decrement counter (multiplier)
brne LOOP		; loop while counter > 0

END:
jmp END			; end program