;
; GPIOs_Part2_ASM.asm
;
; Created: 3/2/2019 2:58:59 PM
; Author : Benjamin Johnson
; Student #: 5003284489
; Email: johnsb18@unlv.nevada.edu


.org 0

cbi	DDRC, 2		; set PORTC.2 as input
sbi	PORTC, 2	; enable pull up

sbi	DDRB, 2		; set PORTB.2 as output
sbi PORTB, 2	; set LED off

WHILE:
sbic PINC, 2	; skip next instr if PINC is low
jmp	SKIP		; jump when PINC is high
cbi PORTB, 2	; set LED on

; Delay 20 000 000 cycles
; 1s 250ms at 16 MHz

    ldi  r18, 102
    ldi  r19, 118
    ldi  r20, 194
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1

jmp WHILE
SKIP:
sbi	PORTB, 2	; set LED off

jmp WHILE