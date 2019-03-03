;
; GPIOs_Part1_ASM.asm
;
; Created: 3/2/2019 4:19:44 PM
; Author : Benjamin Johnson
; Student #: 5003284489
; Email: johnsb18@unlv.nevada.edu


.org 0

sbi DDRB, 2		; set PORTB.2 as output
sbi PORTB, 2	; set LED off

; generate waveform with 60% DC and .725 sec period
BEGIN:
cbi PORTB, 2	; set LED on

; Delay 6 960 000 cycles
; 435ms at 16 MHz
    ldi  r18, 36
    ldi  r19, 79
    ldi  r20, 221
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
    nop

sbi PORTB, 2	; set LED off

; Delay 4 640 000 cycles
; 290ms at 16 MHz
    ldi  r18, 24
    ldi  r19, 138
    ldi  r20, 232
L2: dec  r20
    brne L2
    dec  r19
    brne L2
    dec  r18
    brne L2
    rjmp PC+1

jmp BEGIN