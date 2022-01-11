;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.6 #12539 (Mac OS X x86_64)
;--------------------------------------------------------
	.module testrand
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _waitpad
	.globl _arand
	.globl _initarand
	.globl _rand
	.globl _puts
	.globl _printf
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src/testrand.c:8: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
;src/testrand.c:10: while(TRUE) {
00103$:
;src/testrand.c:15: puts("press A on the GameBoy...");
	ld	de, #___str_0
	push	de
	call	_puts
	pop	hl
;src/testrand.c:22: waitpad(J_A);
	ld	a, #0x10
	push	af
	inc	sp
	call	_waitpad
	inc	sp
;src/testrand.c:23: initarand(sys_time);
	ld	hl, #_sys_time
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	push	de
	call	_initarand
	pop	hl
;src/testrand.c:24: for (uint8_t i = 0; i != 16; i++) 
	ld	c, #0x00
00106$:
	ld	a, c
	sub	a, #0x10
	jr	Z, 00103$
;src/testrand.c:25: printf("rand=%hx arand=%hx\n", (uint8_t)rand(), (uint8_t)arand());
	push	bc
	call	_arand
	pop	bc
	ld	b, e
	push	bc
	call	_rand
	ld	a, e
	pop	bc
	push	bc
	push	bc
	inc	sp
	push	af
	inc	sp
	ld	de, #___str_1
	push	de
	call	_printf
	add	sp, #4
	pop	bc
;src/testrand.c:24: for (uint8_t i = 0; i != 16; i++) 
	inc	c
;src/testrand.c:27: }
	jr	00106$
___str_0:
	.ascii "press A on the GameBoy..."
	.db 0x00
___str_1:
	.ascii "rand=%hx arand=%hx"
	.db 0x0a
	.db 0x00
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
