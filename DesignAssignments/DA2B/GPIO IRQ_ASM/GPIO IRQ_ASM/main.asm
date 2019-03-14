;
; GPIO IRQ_ASM.asm
;
; Created: 3/9/2019 4:58:56 PM
; Author : Benjamin Johnson
; Student #: 5003284489
; Email: johnsb18@unlv.nevada.edu


.org 0			; location for reset
jmp MAIN
.org 0x02		; location for external interrupt INT0
jmp EX0_ISR

MAIN:
ldi R20, HIGH(RAMEND)	; initialize stack
out SPH, R20
ldi R20, LOW(RAMEND)
out SPL, R20

ldi R20, 2		; make INT0 falling edge triggered
sts EICRA, R20

sbi DDRB, 2		; set PORTB.2 as output
sbi PORTB, 2	; set LED off
sbi PORTD, 2	; turn on pull-up
cbi DDRC, 2		; set PORTC.2 as input
sbi PORTC, 2	; enable pull up

ldi R20, 1<<INT0	; enable INT0
out EIMSK, R20
sei				; enable interrupts

WHILE:
jmp	WHILE		; wait for interrupt


EX0_ISR:
in	R21, PORTB	; R21 = PORTB
ldi R22, (1<<2)	; load mask for toggling
eor R21, R22	; toggle LED
out	PORTB, R21	; PORTB = R21

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

reti			; return from interrupt