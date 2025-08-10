.syntax unified
.thumb

.text

.global div
div:
	push  {r4}

	mov   r2, r0
	movs  r3, #0x1
	lsls  r3, r3, #31 @ loop counter
	movs  r0, #0	  @ quotient
	movs  r4, #0	  @ temp
div_loop:
	lsls  r2, r2, #1  @ pop MSB into carry
	adcs  r4, r4, r4  @ double temp == left shift 1, add carry
	cmp   r4, r1
	bcc   div_less_than
	adds  r0, r0, r3  @ inc quotient
	subs  r4, r4, r1
div_less_than:
	lsrs  r3, r3, #1  @ N = N + 1
	bne   div_loop
	
	@ return
	mov   r1, r4	  @ move remainder to r1
	pop   {r4}
	bx    lr

