.data
.code

MOVREL MACRO reg1, reg2, reg3, offset

MOV reg1, qword ptr [reg2 + offset]
MOV qword ptr [reg3 + offset], reg1 

ENDM

MOVREL8 MACRO reg1, reg2, reg3

MOVREL reg1, reg2, reg3, 0
MOVREL reg1, reg2, reg3, 8
MOVREL reg1, reg2, reg3, 16
MOVREL reg1, reg2, reg3, 24
MOVREL reg1, reg2, reg3, 32
MOVREL reg1, reg2, reg3, 40
MOVREL reg1, reg2, reg3, 48
MOVREL reg1, reg2, reg3, 56

ENDM

MOVREL8O MACRO reg1, reg2, reg3, off

MOVREL reg1, reg2, reg3, 0 + off
MOVREL reg1, reg2, reg3, 8 + off
MOVREL reg1, reg2, reg3, 16 + off
MOVREL reg1, reg2, reg3, 24 + off
MOVREL reg1, reg2, reg3, 32 + off
MOVREL reg1, reg2, reg3, 40 + off
MOVREL reg1, reg2, reg3, 48 + off
MOVREL reg1, reg2, reg3, 56 + off

ENDM

MOVREL16 MACRO reg1, reg2, reg3

MOVREL8 reg1, reg2, reg3
MOVREL8O reg1, reg2, reg3, 64

ENDM

MOVREL32 MACRO reg1, reg2, reg3

MOVREL16 reg1, reg2, reg3
MOVREL8O reg1, reg2, reg3, 128
MOVREL8O reg1, reg2, reg3, 192

ENDM

MOVREL64 MACRO reg1, reg2, reg3

MOVREL16 reg1, reg2, reg3
MOVREL8O reg1, reg2, reg3, 128
MOVREL8O reg1, reg2, reg3, 192
MOVREL8O reg1, reg2, reg3, 256
MOVREL8O reg1, reg2, reg3, 320
MOVREL8O reg1, reg2, reg3, 384
MOVREL8O reg1, reg2, reg3, 448

ENDM

ADD8 MACRO reg1, reg2

ADD qword ptr [reg1], reg2
ADC qword ptr [reg1 + 8], 0
ADC qword ptr [reg1 + 16], 0
ADC qword ptr [reg1 + 24], 0
ADC qword ptr [reg1 + 32], 0
ADC qword ptr [reg1 + 40], 0
ADC qword ptr [reg1 + 48], 0
ADC qword ptr [reg1 + 56], 0

ENDM

ADC8 MACRO reg1, off

ADC qword ptr [reg1 + off], 0
ADC qword ptr [reg1 + off + 8], 0
ADC qword ptr [reg1 + off + 16], 0
ADC qword ptr [reg1 + off + 24], 0
ADC qword ptr [reg1 + off + 32], 0
ADC qword ptr [reg1 + off + 40], 0
ADC qword ptr [reg1 + off + 48], 0
ADC qword ptr [reg1 + off + 56], 0

ENDM

ADD16 MACRO reg1, reg2

ADD8 reg1, reg2
ADC8 reg1, 64

ENDM

ADD32 MACRO reg1, reg2

ADD8 reg1, reg2
ADC8 reg1, 64
ADC8 reg1, 128
ADC8 reg1, 192

ENDM

ADD64 MACRO reg1, reg2

ADD8 reg1, reg2
ADC8 reg1, 64
ADC8 reg1, 128
ADC8 reg1, 192
ADC8 reg1, 256
ADC8 reg1, 320
ADC8 reg1, 384
ADC8 reg1, 448

ENDM

SUB8 MACRO reg1, reg2

SUB qword ptr [reg1], reg2
SBB qword ptr [reg1 + 8], 0
SBB qword ptr [reg1 + 16], 0
SBB qword ptr [reg1 + 24], 0
SBB qword ptr [reg1 + 32], 0
SBB qword ptr [reg1 + 40], 0
SBB qword ptr [reg1 + 48], 0
SBB qword ptr [reg1 + 56], 0

ENDM

SBB8 MACRO reg1, off

SBB qword ptr [reg1 + off], 0
SBB qword ptr [reg1 + off + 8], 0
SBB qword ptr [reg1 + off + 16], 0
SBB qword ptr [reg1 + off + 24], 0
SBB qword ptr [reg1 + off + 32], 0
SBB qword ptr [reg1 + off + 40], 0
SBB qword ptr [reg1 + off + 48], 0
SBB qword ptr [reg1 + off + 56], 0

ENDM

SUB16 MACRO reg1, reg2

SUB8 reg1, reg2
SBB8 reg1, 64

ENDM

SUB32 MACRO reg1, reg2

SUB8 reg1, reg2
SBB8 reg1, 64
SBB8 reg1, 128
SBB8 reg1, 192

ENDM

SUB64 MACRO reg1, reg2

SUB8 reg1, reg2
SBB8 reg1, 64
SBB8 reg1, 128
SBB8 reg1, 192
SBB8 reg1, 256
SBB8 reg1, 320
SBB8 reg1, 384
SBB8 reg1, 448

ENDM

MOVADD MACRO reg1, reg2, addreg, offset
MOV reg1, qword ptr [reg2 + offset]
ADD qword ptr [addreg + offset], reg1
ENDM

MOVADC MACRO reg1, reg2, addreg, offset
MOV reg1, qword ptr [reg2 + offset]
ADC qword ptr [addreg + offset], reg1
ENDM

MOVADD8 MACRO reg1, reg2, addreg

MOVADD reg1, reg2, addreg, 0
MOVADC reg1, reg2, addreg, 8
MOVADC reg1, reg2, addreg, 16
MOVADC reg1, reg2, addreg, 24
MOVADC reg1, reg2, addreg, 32
MOVADC reg1, reg2, addreg, 40
MOVADC reg1, reg2, addreg, 48
MOVADC reg1, reg2, addreg, 56

ENDM

MOVADC8 MACRO reg1, reg2, addreg, off

MOVADC reg1, reg2, addreg, off
MOVADC reg1, reg2, addreg, off + 8
MOVADC reg1, reg2, addreg, off + 16
MOVADC reg1, reg2, addreg, off + 24
MOVADC reg1, reg2, addreg, off + 32
MOVADC reg1, reg2, addreg, off + 40
MOVADC reg1, reg2, addreg, off + 48
MOVADC reg1, reg2, addreg, off + 56

ENDM

MOVADD16 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC8 reg1, reg2, addreg, 64

ENDM

MOVADD32 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC8 reg1, reg2, addreg, 64
MOVADC8 reg1, reg2, addreg, 128
MOVADC8 reg1, reg2, addreg, 192

ENDM

MOVADD64 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC8 reg1, reg2, addreg, 64
MOVADC8 reg1, reg2, addreg, 128
MOVADC8 reg1, reg2, addreg, 192
MOVADC8 reg1, reg2, addreg, 256
MOVADC8 reg1, reg2, addreg, 320
MOVADC8 reg1, reg2, addreg, 384
MOVADC8 reg1, reg2, addreg, 448

ENDM

MOVSUB MACRO reg1, reg2, subreg, offset
MOV reg1, qword ptr [reg2 + offset]
SUB qword ptr [subreg + offset], reg1
ENDM

MOVSBB MACRO reg1, reg2, subreg, offset
MOV reg1, qword ptr [reg2 + offset]
SBB qword ptr [subreg + offset], reg1
ENDM

MOVSBB8 MACRO reg1, reg2, subreg, off

MOVSBB reg1, reg2, subreg, off
MOVSBB reg1, reg2, subreg, off + 8
MOVSBB reg1, reg2, subreg, off + 16
MOVSBB reg1, reg2, subreg, off + 24
MOVSBB reg1, reg2, subreg, off + 32
MOVSBB reg1, reg2, subreg, off + 40
MOVSBB reg1, reg2, subreg, off + 48
MOVSBB reg1, reg2, subreg, off + 56

ENDM

MOVSUB8 MACRO reg1, reg2, subreg

MOVSUB reg1, reg2, subreg, 0
MOVSBB reg1, reg2, subreg, 8
MOVSBB reg1, reg2, subreg, 16
MOVSBB reg1, reg2, subreg, 24
MOVSBB reg1, reg2, subreg, 32
MOVSBB reg1, reg2, subreg, 40
MOVSBB reg1, reg2, subreg, 48
MOVSBB reg1, reg2, subreg, 56

ENDM

MOVSUB16 MACRO reg1, reg2, subreg

MOVSUB8 reg1, reg2, subreg
MOVSBB8 reg1, reg2, subreg, 64

ENDM

MOVSUB32 MACRO reg1, reg2, subreg

MOVSUB8 reg1, reg2, subreg
MOVSBB8 reg1, reg2, subreg, 64
MOVSBB8 reg1, reg2, subreg, 128
MOVSBB8 reg1, reg2, subreg, 192

ENDM

MOVSUB64 MACRO reg1, reg2, subreg

MOVSUB8 reg1, reg2, subreg
MOVSBB8 reg1, reg2, subreg, 64
MOVSBB8 reg1, reg2, subreg, 128
MOVSBB8 reg1, reg2, subreg, 192
MOVSBB8 reg1, reg2, subreg, 256
MOVSBB8 reg1, reg2, subreg, 320
MOVSBB8 reg1, reg2, subreg, 384
MOVSBB8 reg1, reg2, subreg, 448

ENDM

MPM MACRO reg1, pushreg, mulreg, offset
MOV reg1, qword ptr [pushreg + offset]
PUSH pushreg
MUL mulreg
ENDM

MPM2 MACRO reg1, pushreg, proff, mulreg, mroff

MOV reg1, qword ptr [pushreg + proff]
PUSH pushreg
MUL qword ptr [mulreg + mroff]

ENDM

AMP MACRO addDest, movDest, addSrc, movSrc 

ADD addDest, addSrc
MOV movDest, movSrc
POP movSrc

ENDM

AAP MACRO dest1, dest2, src1, src2

ADD dest1, src1
ADD dest2, src2
POP src2

ENDM

AACP MACRO dest1, dest2, popreg

ADD dest1, popreg
ADC dest2, 0
POP popreg

ENDM

AACP2 MACRO dest1, dest2, src, popreg

ADD dest1, src
ADC dest2, popreg
POP popreg

ENDM

PUSHR MACRO 
PUSH rcx
PUSH rdx
PUSH r8
PUSH r9
PUSH r12
PUSH r13
ENDM

POPR MACRO
POP r13
POP r12
POP r9
POP r8
POP rdx
POP rcx
ENDM

ZERO4 MACRO reg, off
MOV qword ptr [reg + off], 0
MOV qword ptr [reg + off + 8], 0
MOV qword ptr [reg + off + 16], 0
MOV qword ptr [reg + off + 24], 0
ENDM

ZERO8 MACRO reg, off

ZERO4 reg, 0 + off
ZERO4 reg, 32 + off

ENDM

ZERO16 MACRO reg, off

ZERO8 reg, 0 + off
ZERO8 reg, 64 + off

ENDM

ZERO32 MACRO reg, off

ZERO16 reg, 0 + off
ZERO16 reg, 128 + off

ENDM

ZERO64 MACRO reg, off

ZERO32 reg, 0 + off
ZERO32 reg, 256 + off

ENDM

MSHRXM MACRO shiftreg, src, dest, offset
MOV shiftreg, qword ptr [src + offset]
SHRX shiftreg, shiftreg, rcx
MOV qword ptr [dest + offset], shiftreg
ENDM

SHLBLCK MACRO shiftreg, reg2, reg3, off1, off2

MOV cl, 64
SUB cl, r8b

MOV shiftreg, qword ptr [reg2 + off1]
MOV qword ptr [reg3 + off1], shiftreg
SHRX shiftreg, shiftreg, rcx

MOV cl, r8b

SAL qword ptr [reg3 + off1], cl
OR qword ptr [reg3 + off2], shiftreg

ENDM

SHLBLCK8 MACRO shiftreg, reg2, reg3, off1, off2

SHLBLCK shiftreg, reg2, reg3, off1, off2
SHLBLCK shiftreg, reg2, reg3, off1 - 8, off2 - 8
SHLBLCK shiftreg, reg2, reg3, off1 - 16, off2 - 16
SHLBLCK shiftreg, reg2, reg3, off1 - 24, off2 - 24
SHLBLCK shiftreg, reg2, reg3, off1 - 32, off2 - 32
SHLBLCK shiftreg, reg2, reg3, off1 - 40, off2 - 40
SHLBLCK shiftreg, reg2, reg3, off1 - 48, off2 - 48
SHLBLCK shiftreg, reg2, reg3, off1 - 56, off2 - 56

ENDM

SHRBLCK MACRO shiftreg1, shiftreg2, reg2, reg3, off1, off2

MOV cl, 64					
SUB cl, r8b			

MOV shiftreg1, qword ptr [reg2 + off1]
SAL shiftreg1, cl

MOV cl, r8b

MOV shiftreg2, qword ptr [reg2 + off2]
SHRX shiftreg2, shiftreg2, rcx
MOV qword ptr [reg3 + off2], shiftreg2
OR qword ptr [reg3 + off2], shiftreg1

ENDM

SHRBLCK8 MACRO shiftreg1, shiftreg2, reg2, reg3, off1, off2

SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1, off2
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 - 8, off2 - 8
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 - 16, off2 - 16
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 - 24, off2 - 24
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 - 32, off2 - 32
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 - 40, off2 - 40
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 - 48, off2 - 48
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 - 56, off2 - 56

ENDM

MULBLCK MACRO reg1, pushreg, mulreg, dest1, dest2, offset

MPM reg1, pushreg, mulreg, offset
AACP dest1, dest2, pushreg

MOV qword ptr [rcx + offset + 16], dest2
MOV dest2, rax					

ENDM

MULBLCK8 MACRO reg1, pushreg, mulreg, dest1, dest2, offset

MULBLCK reg1, pushreg, mulreg, dest1, dest2, offset
MULBLCK reg1, pushreg, mulreg, dest2, dest1, offset - 8
MULBLCK reg1, pushreg, mulreg, dest1, dest2, offset - 16
MULBLCK reg1, pushreg, mulreg, dest2, dest1, offset - 24
MULBLCK reg1, pushreg, mulreg, dest1, dest2, offset - 32
MULBLCK reg1, pushreg, mulreg, dest2, dest1, offset - 40
MULBLCK reg1, pushreg, mulreg, dest1, dest2, offset - 48
MULBLCK reg1, pushreg, mulreg, dest2, dest1, offset - 56

ENDM

MULBIGBLCK MACRO reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff 

MPM2 reg1, pushreg, pushOff, mulreg, mulOff
AACP2 reg2, reg3, reg1, pushreg

MPM2 reg1, pushreg, pushOff + 8, mulreg, mulOff - 8
AACP2 reg2, reg3, reg1, pushreg

MPM2 reg1, pushreg, pushOff + 16, mulreg, mulOff - 16
AACP2 reg2, reg3, reg1, pushreg

MPM2 reg1, pushreg, pushOff + 24, mulreg, mulOff - 24
AACP2 reg2, reg3, reg1, pushreg

ENDM

MULBIGBLCK4 MACRO reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff

MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff
MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff + 32, mulreg, mulOff - 32
MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff + 64, mulreg, mulOff - 64
MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff + 96, mulreg, mulOff - 96

ENDM

NOT4 MACRO reg1, reg2, reg3, off

MOV reg1, qword ptr [reg2 + off]
NOT reg1
MOV qword ptr [reg3 + off], reg1

MOV reg1, qword ptr [reg2 + off + 8]
NOT reg1
MOV qword ptr [reg3 + off + 8], reg1

MOV reg1, qword ptr [reg2 + off + 16]
NOT reg1
MOV qword ptr [reg3 + off + 16], reg1

MOV reg1, qword ptr [reg2 + off + 24]
NOT reg1
MOV qword ptr [reg3 + off + 24], reg1

ENDM

NOT32 MACRO reg1, reg2, reg3, off

NOT4 reg1, reg2, reg3, off
NOT4 reg1, reg2, reg3, off + 32
NOT4 reg1, reg2, reg3, off + 64
NOT4 reg1, reg2, reg3, off + 96
NOT4 reg1, reg2, reg3, off + 128
NOT4 reg1, reg2, reg3, off + 160
NOT4 reg1, reg2, reg3, off + 192
NOT4 reg1, reg2, reg3, off + 224

ENDM

VECAND4 MACRO reg1, reg2, dest, off

VMOVDQU ymm0, ymmword ptr [reg1 + off]
VANDPD ymm1, ymm0, ymmword ptr [reg2 + off]
VMOVDQU ymmword ptr [dest + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 32 + off]
VANDPD ymm1, ymm0, ymmword ptr [reg2 + 32 + off]
VMOVDQU ymmword ptr [dest + 32 + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 64 + off]
VANDPD ymm1, ymm0, ymmword ptr [reg2 + 64 + off]
VMOVDQU ymmword ptr [dest + 64 + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 96 + off]
VANDPD ymm1, ymm0, ymmword ptr [reg2 + 96 + off]
VMOVDQU ymmword ptr [dest + 96 + off], ymm1

ENDM

VECOR4 MACRO reg1, reg2, dest, off

VMOVDQU ymm0, ymmword ptr [reg1 + off]
VORPD ymm1, ymm0, ymmword ptr [reg2 + off]
VMOVDQU ymmword ptr [dest + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 32 + off]
VORPD ymm1, ymm0, ymmword ptr [reg2 + 32 + off]
VMOVDQU ymmword ptr [dest + 32 + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 64 + off]
VORPD ymm1, ymm0, ymmword ptr [reg2 + 64 + off]
VMOVDQU ymmword ptr [dest + 64 + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 96 + off]
VORPD ymm1, ymm0, ymmword ptr [reg2 + 96 + off]
VMOVDQU ymmword ptr [dest + 96 + off], ymm1

ENDM

VECXOR4 MACRO reg1, reg2, dest, off

VMOVDQU ymm0, ymmword ptr [reg1 + off]
VXORPD ymm1, ymm0, ymmword ptr [reg2 + off]
VMOVDQU ymmword ptr [dest + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 32 + off]
VXORPD ymm1, ymm0, ymmword ptr [reg2 + 32 + off]
VMOVDQU ymmword ptr [dest + 32 + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 64 + off]
VXORPD ymm1, ymm0, ymmword ptr [reg2 + 64 + off]
VMOVDQU ymmword ptr [dest + 64 + off], ymm1

VMOVDQU ymm0, ymmword ptr [reg1 + 96 + off]
VORPD ymm1, ymm0, ymmword ptr [reg2 + 96 + off]
VMOVDQU ymmword ptr [dest + 96 + off], ymm1

ENDM


;
;
;	U128 OPERATIONS START HERE
;
;

u128_add PROC

	MOVREL r12, rdx, rcx, 0			;mov low part of u128 first param to return value into rcx
	MOVREL r12, rdx, rcx, 8			;mov high part of u128 return value into rcx

	ADD qword ptr [rcx], r8			;add second u64 param into low part.
	ADC qword ptr [rcx + 8], 0	;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u128_add ENDP

u128_addBig PROC

	MOVREL r12, rdx, rcx, 0			;mov low part of u128 first param to return value into rcx
	MOVREL r12, rdx, rcx, 8			;mov high part of u128 return value into rcx

	MOVADD r12, r8, rcx, 0			;add second u128 low part param into low part
	MOVADC r12, r8, rcx, 8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u128_addBig ENDP

u128_sub PROC
	
	MOVREL r12, rdx, rcx, 0			;mov low part of u128 first param to return value into rcx
	MOVREL r12, rdx, rcx, 8			;mov high part of u128 return value into rcx

	SUB qword ptr [rcx], r8			;add second u64 param into low part.
	SBB qword ptr [rcx + 8], 0		;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u128_sub ENDP

u128_subBig PROC

	MOVREL r12, rdx, rcx, 0			;mov low part of u128 first param to return value into rcx
	MOVREL r12, rdx, rcx, 8			;mov high part of u128 return value into rcx

	MOVSUB r12, r8, rcx, 0			;add second u128 low part param into low part.
	MOVSBB r12, r8, rcx, 8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u128_subBig ENDP

u128_mul PROC
	
	MPM rax, rdx, r8, 8				;mul high bytes
	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 0				;multiply rax with r8 (2Â° param) -> result is stored in rdx:rax
	ADD r12, rdx					;sum the partial result of the mul together

	MOV qword ptr [rcx + 8], r12	;moves high bytes of mul from r12 to result in rcx + 8
	MOV qword ptr [rcx], rax		;moves low bytes of mul from r13 to result in rcx
	POP rdx							;i'm done with rdx so I can repopulate it from the stack

	MOV rax, rcx
	RET
u128_mul ENDP

u128_mulBig PROC

	;
	;Multiplication of the 1 param by high part of 2
	;
	MPM2 rax, rdx, 0, r8, 8

	MOV r13, rax
	POP rdx

	;
	;Multiplication of the 1 param by low part of 2
	;
	MPM2 rax, rdx, 8, r8, 0

	MOV r14, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM2 rax, rdx, 0, r8, 0

	ADD r14, rdx					;sum the partial result of the mul together

	;
	;Add them correctly together and return
	;

	ADD r13, r14					;add the partial sums

	MOV qword ptr [rcx + 8], r13	;moves high bytes of mul from r13 to result in rcx + 8
	MOV qword ptr [rcx], rax		;moves low bytes of mul from rax to result in rcx
	POP rdx							;i'm done with rdx so I can repopulate it from the stack

	MOV rax, rcx
	RET
u128_mulBig ENDP

u128_divBig PROC

	;Q := 0						-- Init quotient and remainder to zero
	;R := 0
	;for i:= n-1 .. 0 do		-- Where n is the number of bits in N
		;R := R << 1
		;R(0) := N(i)
		;if R >= D then
			;R := R - D
			;Q(i) := 1
		;end
	;end

	MOV qword ptr [rcx], 0
	MOV qword ptr [rcx + 8], 0	;Initialize Quotient to 0

	;
	; TESTING ALLOCATING SPACE IN STACK FOR REMAINDER
	;

	SUB rsp, 16
	MOV r15, rsp
	MOV qword ptr [r15], 0
	MOV qword ptr [r15 + 8], 0 ;Initialize Remainder to 0

	;
	; TESTING !!!
	;

	BSR r12, qword ptr [rdx + 8]
	JNE FOUND_HIGH

	BSR r12, qword ptr [rdx]
	JNE DIVISION_LOOP

	MOV rax, rcx
	RET

	FOUND_HIGH:
	ADD r12, 64

	DIVISION_LOOP:

	;
	; TESTING: ENTERING CALL TO u128_shl
	;

	PUSHR

	SUB rsp, 16
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u128_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL r12, rax, r15, 0
	MOVREL r12, rax, r15, 8
	ADD rsp, 16

	POPR

	;
	; TESTING: EXITED CALL TO u128_shl
	;

	MOV r13, r12
	SUB r13, 64
	JGE EXTRACT_HIGH_BIT
	MOV r13, r12
	MOV r14, qword ptr [rdx]
	JMP SET

	EXTRACT_HIGH_BIT:
	MOV r14, qword ptr [rdx + 8]
	
	SET:
	PUSH rcx
	MOV cl, r13b
	SHR r14, cl
	POP rcx

	AND r14, 1

	;
	; TESTING: ENTERING CALL TO u128_or
	;

	PUSHR

	SUB rsp, 16
	MOV rcx, rsp
	MOV rdx, r15

	SUB rsp, 16
	MOV r8, rsp
	MOV qword ptr [r8 + 8], 0
	MOV qword ptr [r8], r14
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u128_or

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL r12, rax, r15, 0
	MOVREL r12, rax, r15, 8
	ADD rsp, 32
	
	POPR

	;
	; TESTING: EXITED CALL TO u128_or
	;

	;
	; CHECK IF Remainder(R15) IS GREATER OR EQUAL THAN DIVISOR (R8)
	;

	MOV r13, qword ptr [r15 + 8]
	SUB r13, qword ptr [r8 + 8]
	JG ADV_QUOTIENT
	JE CHECK_REM_LOWER
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	CHECK_REM_LOWER:
	MOV r13, qword ptr [r15]
	SUB r13, qword ptr [r8]
	JGE ADV_QUOTIENT
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	ADV_QUOTIENT:
	;
	; TESTING: ENTERING CALL TO u128_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	SUB rsp, 16
	MOV rcx, rsp
	MOV rdx, r15

	SUB rsp, 16
	MOV rcx, rsp
	MOV qword ptr [rcx + 8], 0
	MOV qword ptr [rcx], 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u128_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL r12, rax, r15, 0
	MOVREL r12, rax, r15, 8

	ADD rsp, 32
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx
	
	;
	; TESTING: EXITED CALL TO u128_subBig
	;

	;
	; SET THE nth bit of Quotient
	;
	MOV r13, r12
	SUB r13, 64
	JGE SET_HIGH
	MOV r14, qword ptr [rcx]
	JMP EXEC

	SET_HIGH:
	MOV r14, qword ptr [rcx + 8]

	EXEC:
	PUSH rcx
	MOV r13, 1
	MOV cl, r12b
	SHL r13, cl

	OR r14, r13
	SUB cl, 64
	JGE MOV_TO_HIGH
	POP rcx
	MOV qword ptr [rcx], r14
	
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	MOV_TO_HIGH:
	POP rcx
	MOV qword ptr [rcx + 8], r14

	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	;
	; END LOOP
	;

	END_LOOP:
	MOVREL r12, r15, r9, 0
	MOVREL r12, r15, r9, 8
	
	ADD rsp, 16

	MOV rax, rcx
	RET
u128_divBig ENDP

u128_inc PROC

	ADD qword ptr [rcx], 1
	ADC qword ptr [rcx + 8], 0

	RET

u128_inc ENDP

u128_dec PROC

	SUB qword ptr [rcx], 1
	SBB qword ptr [rcx + 8], 0

	RET

u128_dec ENDP

u128_shl PROC

	MOV r15, rcx 
	PUSH rcx					;Need to preserve rcx reg

	MOV rcx, 0

	MOV cl, 64					
	SUB cl, r8b					

	MOV r13, qword ptr [rdx]
	SHRX r13, r13, rcx			;Making sure I save the top bits to shift in high bytes

	MOV cl, r8b					;Get amount to shift

	MOVREL r12, rdx, r15, 0
	MOVREL r12, rdx, r15, 8		;Get value to be shifted

	SAL qword ptr [r15 + 8], cl
	SAL qword ptr [r15], cl			;Shift Left

	OR qword ptr [r15 + 8], r13		;Or in the bits coming from the low bytes

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15

	RET
u128_shl ENDP

u128_shr PROC

	MOV r15, rcx 
	PUSH rcx					;Need to preserve rcx reg

	MOV rcx, 0

	MOV cl, 64					
	SUB cl, r8b					

	MOV r13, qword ptr [rdx + 8]
	SAL r13, cl						;Making sure I save the bottom bits to shift in low bytes

	MOV cl, r8b						;Get amount to shift

	MSHRXM r12, rdx, r15, 0			;Get value and Shift Right
	MSHRXM r12, rdx, r15, 8			;Get value and Shift Right

	OR qword ptr [r15], r13			;Or in the bits coming from the low bytes

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15

	RET
u128_shr ENDP

u128_and PROC

	VMOVDQU xmm0, xmmword ptr [rdx]
	VANDPD xmm1, xmm0, xmmword ptr [r8]
	VMOVDQU xmmword ptr [rcx], xmm1

	MOV rax, rcx
	RET

u128_and ENDP

u128_or PROC

	VMOVDQU xmm0, xmmword ptr [rdx]
	VORPD xmm1, xmm0, xmmword ptr [r8]
	VMOVDQU xmmword ptr [rcx], xmm1

	MOV rax, rcx
	RET

u128_or ENDP

u128_xor PROC

	VMOVDQU xmm0, xmmword ptr [rdx]
	VXORPD xmm1, xmm0, xmmword ptr [r8]
	VMOVDQU xmmword ptr [rcx], xmm1

	MOV rax, rcx
	RET

u128_xor ENDP

u128_not PROC

	MOV r12, qword ptr [rdx]
	NOT r12
	MOV qword ptr [rcx], r12

	MOV r12, qword ptr [rdx + 8]
	NOT r12
	MOV qword ptr [rcx + 8], r12

	MOV rax, rcx
	RET

u128_not ENDP

;
;
;	U256 OPERATIONS START HERE
;
;

u256_add PROC

	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24		;mov into rcx u256 param

	ADD qword ptr [rcx], r8			;add u64 param into low part.
	ADC qword ptr [rcx + 8], 0
	ADC qword ptr [rcx + 16], 0
	ADC qword ptr [rcx + 24], 0		;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u256_add ENDP

u256_addBig PROC

	MOV rax, 0
	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24		;mov into rcx first u256 param
	
	MOVADD r12, r8, rcx, 0
	MOVADC r12, r8, rcx, 8
	MOVADC r12, r8, rcx, 16
	MOVADC r12, r8, rcx, 24			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u256_addBig ENDP

u256_sub PROC

	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24		;mov into rcx first u256 param

	SUB qword ptr [rcx], r8			
	SBB qword ptr [rcx + 8], 0
	SBB qword ptr [rcx + 16], 0
	SBB qword ptr [rcx + 24], 0		;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u256_sub ENDP

u256_subBig PROC

	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24	;mov into rcx first u256 param

	MOVSUB r12, r8, rcx, 0
	MOVSBB r12, r8, rcx, 8
	MOVSBB r12, r8, rcx, 16
	MOVSBB r12, r8, rcx, 24		;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u256_subBig ENDP

u256_mul PROC

	MPM rax, rdx, r8, 24			;store low half of multiplication (ignore overflow)
	MOV r12, rax					
	POP rdx

	MPM rax, rdx, r8, 16
	ADD r12, rdx					;sum the partial result of the mul together
	MOV r13, rax					
	POP rdx

	MPM rax, rdx, r8, 8
	ADD r13, rdx					
	ADC r12, 0						;possible carry from (+16) part
	POP rdx

	MOV qword ptr [rcx + 24], r12
	MOV r12, rax

	MPM rax, rdx, r8, 0
	ADD r12, rdx					
	ADC r13, 0						;possible carry from (+8) part
	POP rdx

	MOV qword ptr [rcx + 16], r13
	MOV qword ptr [rcx + 8], r12
	MOV qword ptr [rcx], rax

	MOV rax, rcx
	RET

u256_mul ENDP

u256_mulBig PROC

	;
	;Multiplication of the 1 low -> 2
	;
	MPM2 rax, rdx, 0, r8, 0

	MOV qword ptr [rcx], rax
	MOV r12, rdx
	POP rdx

	MPM2 rax, rdx, 0, r8, 8
	AMP r12, r13, rax, rdx

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r14, rax, rdx

	MPM2 rax, rdx, 0, r8, 24

	ADD r14, rax
	POP rdx

	;
	;Multiplication of the 1 medium -> 2 (Not all muls are performed because it would overflow anyway)
	;
	MPM2 rax, rdx, 8, r8, 0
									
	ADD r12, rax
	MOV qword ptr [rcx + 8], r12
	MOV r12, rdx
	POP rdx

	MPM2 rax, rdx, 8, r8, 8

	ADD r13, rax
	ADD r13, r12

	MOV r12, rdx
	POP rdx

	MPM2 rax, rdx, 8, r8, 16

	ADD r12, rax
	ADD r12, r14
	POP rdx

	;
	;Multiplication of the 1 tall -> 2 (Not all muls are performed because it would overflow anyway)
	;
	MPM2 rax, rdx, 16, r8, 0

	ADD r13, rax
	MOV qword ptr [rcx + 16], r13
	MOV r13, rdx
	POP rdx

	MPM2 rax, rdx, 16, r8, 8

	ADD r12, r13
	ADD r12, rax
	POP rdx

	;
	;Multiplication of the 1 high -> 2 (Only 1 is performed because it would overflow anyway)
	;
	MPM2 rax, rdx, 24, r8, 0

	ADD r12, rax
	MOV qword ptr [rcx + 24], r12
	POP rdx

	MOV rax, rcx
	RET

u256_mulBig ENDP

u256_divBig PROC

	;Q := 0						-- Init quotient and remainder to zero
	;R := 0
	;for i:= n-1 .. 0 do		-- Where n is the number of bits in N
		;R := R << 1
		;R(0) := N(i)
		;if R >= D then
			;R := R - D
			;Q(i) := 1
		;end
	;end

	ZERO4 rcx, 0			;Initialize Quotient to 0

	;
	; TESTING ALLOCATING SPACE IN STACK FOR REMAINDER
	;
	SUB rsp, 32
	MOV r15, rsp

	ZERO4 r15, 0			;Initialize Remainder to 0
	;
	; TESTING !!!
	;

	BSR r12, qword ptr [rdx + 24]
	JNE FOUND_HIGH

	BSR r12, qword ptr [rdx + 16]
	JNE FOUND_TALL

	BSR r12, qword ptr [rdx + 8]
	JNE FOUND_MED

	BSR r12, qword ptr [rdx]
	JNE DIVISION_LOOP

	MOV rax, rcx
	RET

	FOUND_MED:
	ADD r12, 64
	JNE DIVISION_LOOP

	FOUND_TALL:
	ADD r12, 128
	JNE DIVISION_LOOP

	FOUND_HIGH:
	ADD r12, 192

	;
	; Beginning of Division Loop
	;

	DIVISION_LOOP:

	;
	; ENTERING CALL TO u256_shl
	;

	PUSHR

	SUB rsp, 32
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u256_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL r12, rax, r15, 0
	MOVREL r12, rax, r15, 8
	MOVREL r12, rax, r15, 16
	MOVREL r12, rax, r15, 24
	ADD rsp, 32
	POPR

	;
	; EXITED CALL TO u256_shl
	;

	MOV r13, r12
	SUB r13, 192
	JGE EXTRACT_HIGH_BIT
	MOV r13, r12
	SUB r13, 128
	JGE EXTRACT_TALL_BIT
	MOV r13, r12
	SUB r13, 64
	JGE EXTRACT_MED_BIT

	MOV r13, r12
	MOV r14, qword ptr [rdx]
	JMP SET

	EXTRACT_HIGH_BIT:
	MOV r14, qword ptr [rdx + 24]
	JMP SET

	EXTRACT_TALL_BIT:
	MOV r14, qword ptr [rdx + 16]
	JMP SET

	EXTRACT_MED_BIT:
	MOV r14, qword ptr [rdx + 8]

	SET:
	PUSH rcx
	MOV cl, r13b
	SHR r14, cl
	POP rcx

	AND r14, 1
	OR qword ptr [r15], r14

	;
	; CHECK IF Remainder(R15) IS GREATER OR EQUAL THAN DIVISOR (R8)
	;

	MOV r13, qword ptr [r15 + 24]
	SUB r13, qword ptr [r8 + 24]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 16]
	SUB r13, qword ptr [r8 + 16]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 8]
	SUB r13, qword ptr [r8 + 8]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15]
	SUB r13, qword ptr [r8]
	JGE ADV_QUOTIENT
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	ADV_QUOTIENT:
	;
	; TESTING: ENTERING CALL TO u256_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	SUB rsp, 32
	MOV rcx, rsp
	MOV rdx, r15

	SUB rsp, 32
	MOV rcx, rsp
	ZERO4 rcx, 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u256_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL r12, rax, r15, 0
	MOVREL r12, rax, r15, 8
	MOVREL r12, rax, r15, 16
	MOVREL r12, rax, r15, 24
	ADD rsp, 64
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx

	;
	; TESTING: EXITED CALL TO u256_subBig
	;

	;
	; SET THE nth bit of Quotient
	;
	MOV r13, r12
	SUB r13, 192
	JGE SET_HIGH
	
	MOV r13, r12
	SUB r13, 128
	JGE SET_TALL

	MOV r13, r12
	SUB r13, 64
	JGE SET_MED

	MOV r14, qword ptr [rcx]
	JMP EXEC

	SET_HIGH:
	MOV r14, qword ptr [rcx + 24]
	JMP EXEC

	SET_TALL:
	MOV r14, qword ptr [rcx + 16]
	JMP EXEC

	SET_MED:
	MOV r14, qword ptr [rcx + 8]

	EXEC:
	PUSH rcx
	MOV rcx, 0
	MOV r13, 1
	MOV cl, r12b
	SHL r13, cl

	OR r14, r13

	SUB cx, 192
	JGE MOV_TO_HIGH
	MOV cx, r12w
	SUB cx, 128
	JGE MOV_TO_TALL
	MOV cx, r12w
	SUB cl, 64
	JGE MOV_TO_MED

	POP rcx
	MOV qword ptr [rcx], r14
	
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	MOV_TO_HIGH:
	POP rcx
	MOV qword ptr [rcx + 24], r14
	JMP ADV_LOOP
	
	MOV_TO_TALL:
	POP rcx
	MOV qword ptr [rcx + 16], r14
	JMP ADV_LOOP

	MOV_TO_MED:
	POP rcx
	MOV qword ptr [rcx + 8], r14

	ADV_LOOP:
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	;
	; END LOOP
	;

	END_LOOP:

	MOVREL r12, r15, r9, 0
	MOVREL r12, r15, r9, 8
	MOVREL r12, r15, r9, 16
	MOVREL r12, r15, r9, 24
	
	; RESTORE STACK POINTER !?!?!?
	ADD rsp, 32

	MOV rax, rcx
	RET

u256_divBig ENDP

u256_inc PROC

	ADD qword ptr [rcx], 1
	ADC qword ptr [rcx + 8], 0
	ADC qword ptr [rcx + 16], 0
	ADC qword ptr [rcx + 24], 0

	RET

u256_inc ENDP

u256_dec PROC

	SUB qword ptr [rcx], 1
	SBB qword ptr [rcx + 8], 0
	SBB qword ptr [rcx + 16], 0
	SBB qword ptr [rcx + 24], 0

	RET

u256_dec ENDP

u256_shl PROC

	MOV r15, rcx 
	PUSH rcx					

	MOV rcx, 0

	MOV cl, 64					
	SUB cl, r8b					

	MOV r13, qword ptr [rdx + 16]		;Save top bits of top part
	SHRX r13, r13, rcx			

	MOV cl, r8b					

	MOVREL r12, rdx, r15, 16
	MOVREL r12, rdx, r15, 24

	SAL qword ptr [r15 + 16], cl
	SAL qword ptr [r15 + 24], cl	;Shift Left

	OR qword ptr [r15 + 24], r13	;Or in the bits coming from the top part
	;
	;
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15
	RET

u256_shl ENDP

u256_shr PROC

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK r13, r12, rdx, r15, 8, 0
	SHRBLCK r13, r12, rdx, r15, 16, 8
	SHRBLCK r13, r12, rdx, r15, 24, 16

	MOV cl, r8b						;Get amount to shift

	MSHRXM r12, rdx, r15, 24		;Get value and Shift Right

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15

	RET

u256_shr ENDP

u256_and PROC

	VMOVDQU ymm0, ymmword ptr [rdx]
	VANDPD ymm1, ymm0, ymmword ptr [r8]
	VMOVDQU ymmword ptr [rcx], ymm1

	MOV rax, rcx
	RET

u256_and ENDP

u256_or PROC

	VMOVDQU ymm0, ymmword ptr [rdx]
	VORPD ymm1, ymm0, ymmword ptr [r8]
	VMOVDQU ymmword ptr [rcx], ymm1

	MOV rax, rcx
	RET

u256_or ENDP

u256_xor PROC

	VMOVDQU ymm0, ymmword ptr [rdx]
	VXORPD ymm1, ymm0, ymmword ptr [r8]
	VMOVDQU ymmword ptr [rcx], ymm1

	MOV rax, rcx
	RET

u256_xor ENDP

u256_not PROC

	NOT4 r12, rdx, rcx, 0

	MOV rax, rcx
	RET

u256_not ENDP

;
;
;	U512 OPERATIONS START HERE
;
;

u512_add PROC

	MOVREL8 r12, rdx, rcx			;mov into rcx u512 param
	ADD8 rcx, r8					;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u512_add ENDP

u512_addBig PROC
	
	MOVREL8 r12, rdx, rcx		;mov into rcx first u512 param
	MOVADD8 r12, r8, rcx		;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u512_addBig ENDP

u512_sub PROC

	MOVREL8 r12, rdx, rcx	;mov into rcx first u512 param
	SUB8 rcx, r8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u512_sub ENDP

u512_subBig PROC

	MOVREL8 r12, rdx, rcx		 ;mov into rcx first u256 param
	MOVSUB8 r12, r8, rcx		;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u512_subBig ENDP

u512_mul PROC

	MPM rax, rdx, r8, 56
	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 48
	ADD r12, rdx					;sum the partial result of the mul together
	MOV r13, rax					
	POP rdx

	MPM rax, rdx, r8, 40
	ADD r13, rdx
	ADC r12, 0						;possible carry from (+48) part
	POP rdx

	MOV qword ptr [rcx + 56], r12	;Done with +56 part, so storing it
	MOV r12, rax					;Now r12 becomes the holder of +40

	MPM rax, rdx, r8, 32
	ADD r12, rdx
	ADC r13, 0
	POP rdx

	MOV qword ptr [rcx + 48], r13	;Done with +48 part, so storing it
	MOV r13, rax					;Now r13 becomes the holder of +36
					
	MPM rax, rdx, r8, 24
	ADD r13, rdx
	ADC r12, 0
	POP rdx

	MOV qword ptr [rcx + 40], r12	;Done with +40 part, so storing it
	MOV r12, rax					;Now r12 becomes the holder of +24

	MPM rax, rdx, r8, 16
	ADD r12, rdx
	ADC r13, 0
	POP rdx

	MOV qword ptr [rcx + 32], r13	;Done with +32 part, so storing it
	MOV r13, rax					;Now r13 becomes the holder of +16

	MPM rax, rdx, r8, 8
	ADD r13, rdx
	ADC r12, 0
	POP rdx

	MOV qword ptr [rcx + 24], r12	;Done with +24 part, so storing it
	MOV r12, rax					;Now r12 becomes the holder of +8

	MPM rax, rdx, r8, 0
	ADD r12, rdx
	ADC r13, 0
	POP rdx

	MOV qword ptr [rcx + 16], r13	;Done with +16 part, so storing it
	MOV qword ptr [rcx + 8], r12	;Done with +8 part, so storing it
	MOV qword ptr [rcx], rax		;Done

	MOV rax, rcx
	RET
u512_mul ENDP

u512_mulBig PROC

	;This time I'm multiplying in a strange pattern
	;Because I just don't have enough registers
	;I'll multipy so that I only use at most 2 registers at a time
	;Producing directly 1 result for each section
	;Rather than accumulating the sub-results, and summing/storing them at the end

	;Possible bug, might wanna ADC all the parts that get rdx (Possible Fix)

	;
	;Execution of the 1° Column
	;

	MPM rax, rdx, r8, 0

	MOV qword ptr [rcx], rax
	MOV r12, rdx
	POP rdx

	;
	;Execution of the 2° Column
	;

	MPM2 rax, rdx, 0, r8, 8
	AMP r12, r13, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx

	MPM2 rax, rdx, 8, r8, 8
	AACP2 r13, r12, rax, rdx
	
	MPM2 rax, rdx, 16, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx

	MPM2 rax, rdx, 8, r8, 16
	AACP2 r12, r13, rax, rdx
	
	MPM2 rax, rdx, 16, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 24, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 24], r12

	;
	;Execution of the 5° Column
	;

	MPM2 rax, rdx, 0, r8, 32
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK r13, r12, rax, rdx, 8, r8, 24 
	
	MOV qword ptr [rcx + 32], r13

	;
	;Execution of the 6° Column
	;

	MPM2 rax, rdx, 0, r8, 40
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK r13, r12, rax, rdx, 8, r8, 32 
	
	MPM2 rax, rdx, 40, r8, 0
	AACP2 r12, r13, rax, rdx
	
	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK r13, r12, rax, rdx, 8, r8, 40
	
	MPM2 rax, rdx, 40, r8, 8
	AACP2 r13, r12, rax, rdx
	
	MPM2 rax, rdx, 48, r8, 0
	AACP2 r13, r12, rax, rdx
	
	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	
	ADD r12, rax
	POP rdx

	MPM2 rax, rdx, 8, r8, 48
	
	ADD r12, rax
	POP rdx

	MPM2 rax, rdx, 16, r8, 40

	ADD r12, rax
	POP rdx

	MPM2 rax, rdx, 24, r8, 32
	
	ADD r12, rax
	POP rdx

	MPM2 rax, rdx, 32, r8, 24
	
	ADD r12, rax
	POP rdx

	MPM2 rax, rdx, 40, r8, 16
	
	ADD r12, rax
	POP rdx

	MPM2 rax, rdx, 48, r8, 8
	
	ADD r12, rax
	POP rdx

	MPM2 rax, rdx, 56, r8, 0

	ADD r12, rax
	POP rdx

	MOV qword ptr [rcx + 56], r12

	;
	;Return
	;

	MOV rax, rcx
	RET

u512_mulBig ENDP

u512_divBig PROC

	;Q := 0						-- Init quotient and remainder to zero
	;R := 0
	;for i:= n-1 .. 0 do		-- Where n is the number of bits in N
		;R := R << 1
		;R(0) := N(i)
		;if R >= D then
			;R := R - D
			;Q(i) := 1
		;end
	;end

	ZERO8 rcx, 0	;Initialize Quotient to 0

	;
	; TESTING ALLOCATING SPACE IN STACK FOR REMAINDER
	;
	SUB rsp, 64
	MOV r15, rsp
	ZERO8 r15, 0	;Initialize Remainder to 0
	;
	; TESTING !!!
	;

	BSR r12, qword ptr [rdx + 56]
	JNE FOUND_HIGHHIGH

	BSR r12, qword ptr [rdx + 48]
	JNE FOUND_TALLHIGH

	BSR r12, qword ptr [rdx + 40]
	JNE FOUND_MEDHIGH

	BSR r12, qword ptr [rdx + 32]
	JNE FOUND_LOWHIGH

	BSR r12, qword ptr [rdx + 24]
	JNE FOUND_HIGHLOW

	BSR r12, qword ptr [rdx + 16]
	JNE FOUND_TALLOW

	BSR r12, qword ptr [rdx + 8]
	JNE FOUND_MEDLOW

	BSR r12, qword ptr [rdx]
	JNE DIVISION_LOOP

	MOV rax, rcx
	RET

	FOUND_MEDLOW:
	ADD r12, 64
	JNE DIVISION_LOOP

	FOUND_TALLOW:
	ADD r12, 128
	JNE DIVISION_LOOP

	FOUND_HIGHLOW:
	ADD r12, 192
	JNE DIVISION_LOOP

	FOUND_LOWHIGH:
	ADD r12, 256
	JNE DIVISION_LOOP

	FOUND_MEDHIGH:
	ADD r12, 320
	JNE DIVISION_LOOP

	FOUND_TALLHIGH:
	ADD r12, 384
	JNE DIVISION_LOOP

	FOUND_HIGHHIGH:
	ADD r12, 448

	;
	; Beginning of Division Loop
	;

	DIVISION_LOOP:

	;
	; ENTERING CALL TO u512_shl
	;

	PUSHR

	SUB rsp, 64
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u512_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL8 r12, rax, r15
	ADD rsp, 64
	POPR

	;
	; EXITED CALL TO u512_shl
	;
	MOV r13, r12
	SUB r13, 448
	JGE EXTRACT_HIGHHIGH_BIT
	MOV r13, r12
	SUB r13, 384
	JGE EXTRACT_TALLHIGH_BIT
	MOV r13, r12
	SUB r13, 320
	JGE EXTRACT_MEDHIGH_BIT
	MOV r13, r12
	SUB r13, 256
	JGE EXTRACT_LOWHIGH_BIT
	MOV r13, r12
	SUB r13, 192
	JGE EXTRACT_HIGHLOW_BIT
	MOV r13, r12
	SUB r13, 128
	JGE EXTRACT_TALLOW_BIT
	MOV r13, r12
	SUB r13, 64
	JGE EXTRACT_MEDLOW_BIT

	MOV r13, r12
	MOV r14, qword ptr [rdx]
	JMP SET

	EXTRACT_HIGHHIGH_BIT:
	MOV r14, qword ptr [rdx + 56]
	JMP SET

	EXTRACT_TALLHIGH_BIT:
	MOV r14, qword ptr [rdx + 48]
	JMP SET

	EXTRACT_MEDHIGH_BIT:
	MOV r14, qword ptr [rdx + 40]
	JMP SET

	EXTRACT_LOWHIGH_BIT:
	MOV r14, qword ptr [rdx + 32]

	EXTRACT_HIGHLOW_BIT:
	MOV r14, qword ptr [rdx + 24]
	JMP SET

	EXTRACT_TALLOW_BIT:
	MOV r14, qword ptr [rdx + 16]
	JMP SET

	EXTRACT_MEDLOW_BIT:
	MOV r14, qword ptr [rdx + 8]

	SET:
	PUSH rcx
	MOV cl, r13b
	SHR r14, cl
	POP rcx

	AND r14, 1
	OR qword ptr [r15], r14

	;
	; CHECK IF Remainder(R15) IS GREATER OR EQUAL THAN DIVISOR (R8)
	;
	MOV r13, qword ptr [r15 + 56]
	SUB r13, qword ptr [r8 + 56]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 48]
	SUB r13, qword ptr [r8 + 48]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 40]
	SUB r13, qword ptr [r8 + 40]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 32]
	SUB r13, qword ptr [r8 + 32]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 24]
	SUB r13, qword ptr [r8 + 24]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 16]
	SUB r13, qword ptr [r8 + 16]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 8]
	SUB r13, qword ptr [r8 + 8]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15]
	SUB r13, qword ptr [r8]
	JGE ADV_QUOTIENT
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	ADV_QUOTIENT:
	;
	; TESTING: ENTERING CALL TO u512_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	MOV rdx, r15

	SUB rsp, 64
	MOV rcx, rsp
	ZERO8 rcx, 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u512_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL8 r12, rax, r15
	ADD rsp, 64
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx

	;
	; TESTING: EXITED CALL TO u512_subBig
	;

	;
	; SET THE nth bit of Quotient
	;
	MOV r13, r12
	SUB r13, 448
	JGE SET_HIGHHIGH

	MOV r13, r12
	SUB r13, 384
	JGE SET_TALLHIGH
	
	MOV r13, r12
	SUB r13, 320
	JGE SET_MEDHIGH

	MOV r13, r12
	SUB r13, 256
	JGE SET_LOWHIGH

	MOV r13, r12
	SUB r13, 192
	JGE SET_HIGHLOW
	
	MOV r13, r12
	SUB r13, 128
	JGE SET_TALLOW

	MOV r13, r12
	SUB r13, 64
	JGE SET_MEDLOW

	MOV r14, qword ptr [rcx]
	JMP EXEC

	SET_HIGHHIGH:
	MOV r14, qword ptr [rcx + 56]
	JMP EXEC

	SET_TALLHIGH:
	MOV r14, qword ptr [rcx + 48]
	JMP EXEC

	SET_MEDHIGH:
	MOV r14, qword ptr [rcx + 40]
	JMP EXEC

	SET_LOWHIGH:
	MOV r14, qword ptr [rcx + 32]
	JMP EXEC

	SET_HIGHLOW:
	MOV r14, qword ptr [rcx + 24]
	JMP EXEC

	SET_TALLOW:
	MOV r14, qword ptr [rcx + 16]
	JMP EXEC

	SET_MEDLOW:
	MOV r14, qword ptr [rcx + 8]

	EXEC:
	PUSH rcx
	MOV rcx, 0
	MOV r13, 1
	MOV cx, r12w
	SHL r13, cl

	OR r14, r13

	SUB cx, 448
	JGE MOV_TO_HIGHHIGH
	MOV cx, r12w
	SUB cx, 384
	JGE MOV_TO_TALLHIGH
	MOV cx, r12w
	SUB cx, 320
	JGE MOV_TO_MEDHIGH
	MOV cx, r12w
	SUB cx, 256
	JGE MOV_TO_LOWHIGH
	MOV cx, r12w
	SUB cx, 192
	JGE MOV_TO_HIGHLOW
	MOV cx, r12w
	SUB cx, 128
	JGE MOV_TO_TALLOW
	MOV cx, r12w
	SUB cl, 64
	JGE MOV_TO_MEDLOW

	POP rcx
	MOV qword ptr [rcx], r14
	
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	MOV_TO_HIGHHIGH:
	POP rcx
	MOV qword ptr [rcx + 56], r14
	JMP ADV_LOOP

	MOV_TO_TALLHIGH:
	POP rcx
	MOV qword ptr [rcx + 48], r14
	JMP ADV_LOOP

	MOV_TO_MEDHIGH:
	POP rcx
	MOV qword ptr [rcx + 40], r14
	JMP ADV_LOOP

	MOV_TO_LOWHIGH:
	POP rcx
	MOV qword ptr [rcx + 32], r14
	JMP ADV_LOOP

	MOV_TO_HIGHLOW:
	POP rcx
	MOV qword ptr [rcx + 24], r14
	JMP ADV_LOOP
	
	MOV_TO_TALLOW:
	POP rcx
	MOV qword ptr [rcx + 16], r14
	JMP ADV_LOOP

	MOV_TO_MEDLOW:
	POP rcx
	MOV qword ptr [rcx + 8], r14

	ADV_LOOP:
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	;
	; END LOOP
	;

	END_LOOP:

	MOVREL8 r12, r15, r9

	; RESTORE STACK POINTER !?!?!?
	ADD rsp, 64

	MOV rax, rcx
	RET

u512_divBig ENDP

u512_inc PROC

	ADD qword ptr [rcx], 1
	ADC qword ptr [rcx + 8], 0
	ADC qword ptr [rcx + 16], 0
	ADC qword ptr [rcx + 24], 0
	ADC qword ptr [rcx + 32], 0
	ADC qword ptr [rcx + 40], 0
	ADC qword ptr [rcx + 48], 0
	ADC qword ptr [rcx + 56], 0

	RET

u512_inc ENDP

u512_dec PROC

	SUB qword ptr [rcx], 1
	SBB qword ptr [rcx + 8], 0
	SBB qword ptr [rcx + 16], 0
	SBB qword ptr [rcx + 24], 0
	SBB qword ptr [rcx + 32], 0
	SBB qword ptr [rcx + 40], 0
	SBB qword ptr [rcx + 48], 0
	SBB qword ptr [rcx + 56], 0

	RET

u512_dec ENDP

u512_shl PROC

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0

	MOV cl, 64
	SUB cl, r8b

	MOV r13, qword ptr [rdx + 48]	;Save top bits of top part
	MOV qword ptr [r15 + 48], r13
	SHRX r13, r13, rcx

	MOV cl, r8b

	MOV r12, qword ptr [rdx + 56]
	MOV qword ptr [r15 + 56], r12

	SAL qword ptr [r15 + 48], cl
	SAL qword ptr [r15 + 56], cl	;Shift Left

	OR qword ptr [r15 + 48], r13	;Or in the bits coming from the top part
	;
	;
	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8
	
	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15
	RET

u512_shl ENDP

u512_shr PROC

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK r13, r12, rdx, r15, 8, 0
	SHRBLCK r13, r12, rdx, r15, 16, 8
	SHRBLCK r13, r12, rdx, r15, 24, 16
	SHRBLCK r13, r12, rdx, r15, 32, 24
	SHRBLCK r13, r12, rdx, r15, 40, 32
	SHRBLCK r13, r12, rdx, r15, 48, 40
	SHRBLCK r13, r12, rdx, r15, 56, 48

	MOV cl, r8b						;Get amount to shift

	MOV r12, qword ptr [rdx + 56]
	SHRX r12, r12, rcx
	MOV qword ptr [r15 + 56], r12	;Get value and Shift Right

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15
	RET

u512_shr ENDP

u512_and PROC

	VMOVDQU ymm0, ymmword ptr [rdx]
	VANDPD ymm1, ymm0, ymmword ptr [r8]
	VMOVDQU ymmword ptr [rcx], ymm1

	VMOVDQU ymm0, ymmword ptr [rdx + 32]
	VANDPD ymm1, ymm0, ymmword ptr [r8 + 32]
	VMOVDQU ymmword ptr [rcx + 32], ymm1

	MOV rax, rcx
	RET

u512_and ENDP

u512_or PROC

	VMOVDQU ymm0, ymmword ptr [rdx]
	VORPD ymm1, ymm0, ymmword ptr [r8]
	VMOVDQU ymmword ptr [rcx], ymm1

	VMOVDQU ymm0, ymmword ptr [rdx + 32]
	VORPD ymm1, ymm0, ymmword ptr [r8 + 32]
	VMOVDQU ymmword ptr [rcx + 32], ymm1

	MOV rax, rcx
	RET

u512_or ENDP

u512_xor PROC
	
	VMOVDQU ymm0, ymmword ptr [rdx]
	VXORPD ymm1, ymm0, ymmword ptr [r8]
	VMOVDQU ymmword ptr [rcx], ymm1

	VMOVDQU ymm0, ymmword ptr [rdx + 32]
	VXORPD ymm1, ymm0, ymmword ptr [r8 + 32]
	VMOVDQU ymmword ptr [rcx + 32], ymm1

	MOV rax, rcx
	RET

u512_xor ENDP

u512_not PROC
	
	NOT4 r12, rdx, rcx, 0
	NOT4 r12, rdx, rcx, 32

	MOV rax, rcx
	RET

u512_not ENDP

;
;
;	U1024 OPERATIONS START HERE
;
;

u1024_add PROC

	MOVREL16 r12, rdx, rcx	;mov into rcx u1024 param
	ADD16 rcx, r8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u1024_add ENDP

u1024_addBig PROC

	MOVREL16 r12, rdx, rcx	;mov into rcx first u1024 param
	MOVADD16 r12, r8, rcx	;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u1024_addBig ENDP

u1024_sub PROC

	MOVREL16 r12, rdx, rcx	;mov into rcx first u512 param
	SUB16 rcx, r8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u1024_sub ENDP

u1024_subBig PROC

	MOVREL16 r12, rdx, rcx	;mov into rcx first u256 param
	MOVSUB16 r12, r8, rcx	;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u1024_subBig ENDP

u1024_mul PROC

	MPM rax, rdx, r8, 120

	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 112
	
	ADD r12, rdx
	MOV r13, rax
	POP rdx
	
	MULBLCK8 rax, rdx, r8, r13, r12, 104

	MULBLCK rax, rdx, r8, r13, r12, 40
	MULBLCK rax, rdx, r8, r12, r13, 32
	MULBLCK rax, rdx, r8, r13, r12, 24
	MULBLCK rax, rdx, r8, r12, r13, 16
	MULBLCK rax, rdx, r8, r13, r12, 8

	MPM rax, rdx, r8, 0
	AACP r12, r13, rdx

	MOV qword ptr [rcx + 16], r13	;Done with +16 part, so storing it
	MOV qword ptr [rcx + 8], r12	;Done with +8 part, so storing it
	MOV qword ptr [rcx], rax		;Done

	MOV rax, rcx
	RET
u1024_mul ENDP

u1024_mulBig PROC

	;This time I'm multiplying in a strange pattern
	;Because I just don't have enough registers
	;I'll multipy so that I only use at most 2 registers at a time
	;Producing directly 1 result for each section
	;Rather than accumulating the sub-results, and summing/storing them at the end

	;Possible bug, might wanna ADC all the parts that get rdx (Possible Fix)

	;
	;Execution of the 1° Column
	;

	MPM2 rax, rdx, 0, r8, 0

	MOV qword ptr [rcx], rax
	MOV r12, rdx
	POP rdx

	;
	;Execution of the 2° Column
	;

	MPM2 rax, rdx, 0, r8, 8
	AMP r12, r13, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 16, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 16
	AACP2 r12, r13, rax, rdx
	
	MPM2 rax, rdx, 16, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 24, r8, 0
	AACP2 r12, r13, rax, rdx
	
	MOV qword ptr [rcx + 24], r12

	;
	;Execution of the 5° Column
	;

	MPM2 rax, rdx, 0, r8, 32
	AMP r13, r12, rax, rdx

	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 24

	MOV qword ptr [rcx + 32], r13

	;
	;Execution of the 6° Column
	;

	MPM2 rax, rdx, 0, r8, 40
	AMP r12, r13, rax, rdx

	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 32

	MPM2 rax, rdx, 40, r8, 0
	AACP2 r12, r13, rax, rdx
	
	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MPM2 rax, rdx, 40, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 48, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MPM2 rax, rdx, 40, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 48, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 56, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 56], r12

	;
	;Execution of the 9° Column
	;

	MPM2 rax, rdx, 0, r8, 64
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 24

	MOV qword ptr [rcx + 64], r13

	;
	;Execution of the 10° Column
	;

	MPM2 rax, rdx, 0, r8, 72
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 32

	MPM2 rax, rdx, 72, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MPM2 rax, rdx, 72, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 80, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MPM2 rax, rdx, 72, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 80, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 88, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 88], r12

	;
	;Execution of the 13° Column
	;

	MPM2 rax, rdx, 0, r8, 96
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 24

	MOV qword ptr [rcx + 96], r13

	;
	;Execution of the 14° Column
	;

	MPM2 rax, rdx, 0, r8, 104
	AMP r12, r13, rax, rdx

	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 32

	MPM2 rax, rdx, 104, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MPM2 rax, rdx, 104, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 112, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MPM2 rax, rdx, 104, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 112, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 120, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 120], r12

	;
	;Return
	;

	MOV rax, rcx
	RET

u1024_mulBig ENDP

u1024_divBig PROC

	;Q := 0						-- Init quotient and remainder to zero
	;R := 0
	;for i:= n-1 .. 0 do		-- Where n is the number of bits in N
		;R := R << 1
		;R(0) := N(i)
		;if R >= D then
			;R := R - D
			;Q(i) := 1
		;end
	;end

	ZERO16 rcx, 0	;Initialize Quotient to 0

	;
	; TESTING ALLOCATING SPACE IN STACK FOR REMAINDER
	;
	SUB rsp, 128
	MOV r15, rsp
	ZERO16 r15, 0	;Initialize Remainder to 0
	;
	; TESTING !!!
	;

	BSR r12, qword ptr [rdx + 120]
	JNE FOUND_HIGHHIGH

	BSR r12, qword ptr [rdx + 112]
	JNE FOUND_TALLHIGH

	BSR r12, qword ptr [rdx + 104]
	JNE FOUND_MEDHIGH

	BSR r12, qword ptr [rdx + 96]
	JNE FOUND_LOWHIGH

	BSR r12, qword ptr [rdx + 88]
	JNE FOUND_HIGHTALL

	BSR r12, qword ptr [rdx + 80]
	JNE FOUND_TALLTALL

	BSR r12, qword ptr [rdx + 72]
	JNE FOUND_MEDTALL

	BSR r12, qword ptr [rdx + 64]
	JNE FOUND_LOWTALL

	BSR r12, qword ptr [rdx + 56]
	JNE FOUND_HIGHMED

	BSR r12, qword ptr [rdx + 48]
	JNE FOUND_TALLMED

	BSR r12, qword ptr [rdx + 40]
	JNE FOUND_MEDMED

	BSR r12, qword ptr [rdx + 32]
	JNE FOUND_LOWMED

	BSR r12, qword ptr [rdx + 24]
	JNE FOUND_HIGHLOW

	BSR r12, qword ptr [rdx + 16]
	JNE FOUND_TALLOW

	BSR r12, qword ptr [rdx + 8]
	JNE FOUND_MEDLOW

	BSR r12, qword ptr [rdx]
	JNE DIVISION_LOOP

	MOV rax, rcx
	RET

	FOUND_MEDLOW:
	ADD r12, 64
	JNE DIVISION_LOOP

	FOUND_TALLOW:
	ADD r12, 128
	JNE DIVISION_LOOP

	FOUND_HIGHLOW:
	ADD r12, 192
	JNE DIVISION_LOOP

	FOUND_LOWMED:
	ADD r12, 256
	JNE DIVISION_LOOP

	FOUND_MEDMED:
	ADD r12, 320
	JNE DIVISION_LOOP

	FOUND_TALLMED:
	ADD r12, 384
	JNE DIVISION_LOOP

	FOUND_HIGHMED:
	ADD r12, 448
	JNE DIVISION_LOOP

	FOUND_LOWTALL:
	ADD r12, 512
	JNE DIVISION_LOOP

	FOUND_MEDTALL:
	ADD r12, 576
	JNE DIVISION_LOOP

	FOUND_TALLTALL:
	ADD r12, 640
	JNE DIVISION_LOOP

	FOUND_HIGHTALL:
	ADD r12, 704
	JNE DIVISION_LOOP

	FOUND_LOWHIGH:
	ADD r12, 768
	JNE DIVISION_LOOP

	FOUND_MEDHIGH:
	ADD r12, 832
	JNE DIVISION_LOOP

	FOUND_TALLHIGH:
	ADD r12, 896
	JNE DIVISION_LOOP

	FOUND_HIGHHIGH:
	ADD r12, 960

	;
	; Beginning of Division Loop
	;

	DIVISION_LOOP:

	;
	; ENTERING CALL TO u1024_shl
	;

	PUSHR

	SUB rsp, 128
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u1024_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL16 r12, rax, r15

	ADD rsp, 128
	POPR

	;
	; EXITED CALL TO u1024_shl
	;
	MOV r13, r12
	SUB r13, 960
	JGE EXTRACT_HIGHHIGH_BIT
	MOV r13, r12
	SUB r13, 896
	JGE EXTRACT_TALLHIGH_BIT
	MOV r13, r12
	SUB r13, 832
	JGE EXTRACT_MEDHIGH_BIT
	MOV r13, r12
	SUB r13, 768
	JGE EXTRACT_LOWHIGH_BIT
	MOV r13, r12
	SUB r13, 704
	JGE EXTRACT_HIGHTALL_BIT
	MOV r13, r12
	SUB r13, 640
	JGE EXTRACT_TALLTALL_BIT
	MOV r13, r12
	SUB r13, 576
	JGE EXTRACT_MEDTALL_BIT
	MOV r13, r12
	SUB r13, 512
	JGE EXTRACT_LOWTALL_BIT
	MOV r13, r12
	SUB r13, 448
	JGE EXTRACT_HIGHMED_BIT
	MOV r13, r12
	SUB r13, 384
	JGE EXTRACT_TALLMED_BIT
	MOV r13, r12
	SUB r13, 320
	JGE EXTRACT_MEDMED_BIT
	MOV r13, r12
	SUB r13, 256
	JGE EXTRACT_LOWMED_BIT
	MOV r13, r12
	SUB r13, 192
	JGE EXTRACT_HIGHLOW_BIT
	MOV r13, r12
	SUB r13, 128
	JGE EXTRACT_TALLOW_BIT
	MOV r13, r12
	SUB r13, 64
	JGE EXTRACT_MEDLOW_BIT

	MOV r13, r12
	MOV r14, qword ptr [rdx]
	JMP SET

	EXTRACT_HIGHHIGH_BIT:
	MOV r14, qword ptr [rdx + 120]
	JMP SET

	EXTRACT_TALLHIGH_BIT:
	MOV r14, qword ptr [rdx + 112]
	JMP SET

	EXTRACT_MEDHIGH_BIT:
	MOV r14, qword ptr [rdx + 104]
	JMP SET

	EXTRACT_LOWHIGH_BIT:
	MOV r14, qword ptr [rdx + 96]

	EXTRACT_HIGHTALL_BIT:
	MOV r14, qword ptr [rdx + 88]
	JMP SET

	EXTRACT_TALLTALL_BIT:
	MOV r14, qword ptr [rdx + 80]
	JMP SET

	EXTRACT_MEDTALL_BIT:
	MOV r14, qword ptr [rdx + 72]
	JMP SET

	EXTRACT_LOWTALL_BIT:
	MOV r14, qword ptr [rdx + 64]
	JMP SET

	EXTRACT_HIGHMED_BIT:
	MOV r14, qword ptr [rdx + 56]
	JMP SET

	EXTRACT_TALLMED_BIT:
	MOV r14, qword ptr [rdx + 48]
	JMP SET

	EXTRACT_MEDMED_BIT:
	MOV r14, qword ptr [rdx + 40]
	JMP SET

	EXTRACT_LOWMED_BIT:
	MOV r14, qword ptr [rdx + 32]
	JMP SET

	EXTRACT_HIGHLOW_BIT:
	MOV r14, qword ptr [rdx + 24]
	JMP SET

	EXTRACT_TALLOW_BIT:
	MOV r14, qword ptr [rdx + 16]
	JMP SET

	EXTRACT_MEDLOW_BIT:
	MOV r14, qword ptr [rdx + 8]

	SET:
	PUSH rcx
	MOV cl, r13b
	SHR r14, cl
	POP rcx

	AND r14, 1
	OR qword ptr [r15], r14

	;
	; CHECK IF Remainder(R15) IS GREATER OR EQUAL THAN DIVISOR (R8)
	;
	MOV r13, qword ptr [r15 + 120]
	SUB r13, qword ptr [r8 + 120]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 112]
	SUB r13, qword ptr [r8 + 112]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 104]
	SUB r13, qword ptr [r8 + 104]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 96]
	SUB r13, qword ptr [r8 + 96]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 88]
	SUB r13, qword ptr [r8 + 88]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 80]
	SUB r13, qword ptr [r8 + 80]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 72]
	SUB r13, qword ptr [r8 + 72]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 64]
	SUB r13, qword ptr [r8 + 64]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 56]
	SUB r13, qword ptr [r8 + 56]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 48]
	SUB r13, qword ptr [r8 + 48]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 40]
	SUB r13, qword ptr [r8 + 40]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 32]
	SUB r13, qword ptr [r8 + 32]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 24]
	SUB r13, qword ptr [r8 + 24]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 16]
	SUB r13, qword ptr [r8 + 16]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 8]
	SUB r13, qword ptr [r8 + 8]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15]
	SUB r13, qword ptr [r8]
	JGE ADV_QUOTIENT
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	ADV_QUOTIENT:
	;
	; TESTING: ENTERING CALL TO u1024_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	MOV rdx, r15

	SUB rsp, 128
	MOV rcx, rsp
	ZERO16 rcx, 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u1024_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL16 r12, rax, r15

	ADD rsp, 128
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx

	;
	; TESTING: EXITED CALL TO u1024_subBig
	;

	;
	; SET THE nth bit of Quotient
	;
	MOV r13, r12
	SUB r13, 960
	JGE SET_HIGHHIGH

	MOV r13, r12
	SUB r13, 896
	JGE SET_TALLHIGH
	
	MOV r13, r12
	SUB r13, 832
	JGE SET_MEDHIGH

	MOV r13, r12
	SUB r13, 768
	JGE SET_LOWHIGH

	MOV r13, r12
	SUB r13, 704
	JGE SET_HIGHTALL

	MOV r13, r12
	SUB r13, 640
	JGE SET_TALLTALL
	
	MOV r13, r12
	SUB r13, 576
	JGE SET_MEDTALL

	MOV r13, r12
	SUB r13, 512
	JGE SET_LOWTALL

	MOV r13, r12
	SUB r13, 448
	JGE SET_HIGHMED
	
	MOV r13, r12
	SUB r13, 384
	JGE SET_TALLMED

	MOV r13, r12
	SUB r13, 320
	JGE SET_MEDMED

	MOV r13, r12
	SUB r13, 256
	JGE SET_LOWMED

	MOV r13, r12
	SUB r13, 192
	JGE SET_HIGHLOW
	
	MOV r13, r12
	SUB r13, 128
	JGE SET_TALLOW

	MOV r13, r12
	SUB r13, 64
	JGE SET_MEDLOW

	MOV r14, qword ptr [rcx]
	JMP EXEC

	SET_HIGHHIGH:
	MOV r14, qword ptr [rcx + 120]
	JMP EXEC

	SET_TALLHIGH:
	MOV r14, qword ptr [rcx + 112]
	JMP EXEC

	SET_MEDHIGH:
	MOV r14, qword ptr [rcx + 104]
	JMP EXEC

	SET_LOWHIGH:
	MOV r14, qword ptr [rcx + 96]
	JMP EXEC

	SET_HIGHTALL:
	MOV r14, qword ptr [rcx + 88]
	JMP EXEC

	SET_TALLTALL:
	MOV r14, qword ptr [rcx + 80]
	JMP EXEC

	SET_MEDTALL:
	MOV r14, qword ptr [rcx + 72]
	JMP EXEC

	SET_LOWTALL:
	MOV r14, qword ptr [rcx + 64]
	JMP EXEC

	SET_HIGHMED:
	MOV r14, qword ptr [rcx + 56]
	JMP EXEC

	SET_TALLMED:
	MOV r14, qword ptr [rcx + 48]
	JMP EXEC

	SET_MEDMED:
	MOV r14, qword ptr [rcx + 40]
	JMP EXEC

	SET_LOWMED:
	MOV r14, qword ptr [rcx + 32]
	JMP EXEC

	SET_HIGHLOW:
	MOV r14, qword ptr [rcx + 24]
	JMP EXEC

	SET_TALLOW:
	MOV r14, qword ptr [rcx + 16]
	JMP EXEC

	SET_MEDLOW:
	MOV r14, qword ptr [rcx + 8]

	EXEC:
	PUSH rcx
	MOV rcx, 0
	MOV r13, 1
	MOV cx, r12w
	SHL r13, cl

	OR r14, r13

	SUB cx, 960
	JGE MOV_TO_HIGHHIGH
	MOV cx, r12w
	SUB cx, 896
	JGE MOV_TO_TALLHIGH
	MOV cx, r12w
	SUB cx, 832
	JGE MOV_TO_MEDHIGH
	MOV cx, r12w
	SUB cx, 768
	JGE MOV_TO_LOWHIGH
	SUB cx, 704
	JGE MOV_TO_HIGHTALL
	MOV cx, r12w
	SUB cx, 640
	JGE MOV_TO_TALLTALL
	MOV cx, r12w
	SUB cx, 576
	JGE MOV_TO_MEDTALL
	MOV cx, r12w
	SUB cx, 512
	JGE MOV_TO_LOWTALL
	SUB cx, 448
	JGE MOV_TO_HIGHMED
	MOV cx, r12w
	SUB cx, 384
	JGE MOV_TO_TALLMED
	MOV cx, r12w
	SUB cx, 320
	JGE MOV_TO_MEDMED
	MOV cx, r12w
	SUB cx, 256
	JGE MOV_TO_LOWMED
	MOV cx, r12w
	SUB cx, 192
	JGE MOV_TO_HIGHLOW
	MOV cx, r12w
	SUB cx, 128
	JGE MOV_TO_TALLOW
	MOV cx, r12w
	SUB cl, 64
	JGE MOV_TO_MEDLOW

	POP rcx
	MOV qword ptr [rcx], r14
	
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	MOV_TO_HIGHHIGH:
	POP rcx
	MOV qword ptr [rcx + 120], r14
	JMP ADV_LOOP

	MOV_TO_TALLHIGH:
	POP rcx
	MOV qword ptr [rcx + 112], r14
	JMP ADV_LOOP

	MOV_TO_MEDHIGH:
	POP rcx
	MOV qword ptr [rcx + 104], r14
	JMP ADV_LOOP

	MOV_TO_LOWHIGH:
	POP rcx
	MOV qword ptr [rcx + 96], r14
	JMP ADV_LOOP

	MOV_TO_HIGHTALL:
	POP rcx
	MOV qword ptr [rcx + 88], r14
	JMP ADV_LOOP

	MOV_TO_TALLTALL:
	POP rcx
	MOV qword ptr [rcx + 80], r14
	JMP ADV_LOOP

	MOV_TO_MEDTALL:
	POP rcx
	MOV qword ptr [rcx + 72], r14
	JMP ADV_LOOP

	MOV_TO_LOWTALL:
	POP rcx
	MOV qword ptr [rcx + 64], r14
	JMP ADV_LOOP

	MOV_TO_HIGHMED:
	POP rcx
	MOV qword ptr [rcx + 56], r14
	JMP ADV_LOOP

	MOV_TO_TALLMED:
	POP rcx
	MOV qword ptr [rcx + 48], r14
	JMP ADV_LOOP

	MOV_TO_MEDMED:
	POP rcx
	MOV qword ptr [rcx + 40], r14
	JMP ADV_LOOP

	MOV_TO_LOWMED:
	POP rcx
	MOV qword ptr [rcx + 32], r14
	JMP ADV_LOOP

	MOV_TO_HIGHLOW:
	POP rcx
	MOV qword ptr [rcx + 24], r14
	JMP ADV_LOOP
	
	MOV_TO_TALLOW:
	POP rcx
	MOV qword ptr [rcx + 16], r14
	JMP ADV_LOOP

	MOV_TO_MEDLOW:
	POP rcx
	MOV qword ptr [rcx + 8], r14

	ADV_LOOP:
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	;
	; END LOOP
	;

	END_LOOP:

	MOVREL16 r12, r15, r9
	; RESTORE STACK POINTER !?!?!?
	ADD rsp, 128

	MOV rax, rcx
	RET

u1024_divBig ENDP

u1024_inc PROC

	ADD qword ptr [rcx], 1
	ADC8 rcx, 8
	ADC qword ptr [rcx + 72], 0
	ADC qword ptr [rcx + 80], 0
	ADC qword ptr [rcx + 88], 0
	ADC qword ptr [rcx + 96], 0
	ADC qword ptr [rcx + 104], 0
	ADC qword ptr [rcx + 112], 0
	ADC qword ptr [rcx + 120], 0

	RET

u1024_inc ENDP

u1024_dec PROC

	SUB qword ptr [rcx], 1
	SBB8 rcx, 8
	SBB qword ptr [rcx + 72], 0
	SBB qword ptr [rcx + 80], 0
	SBB qword ptr [rcx + 88], 0
	SBB qword ptr [rcx + 96], 0
	SBB qword ptr [rcx + 104], 0
	SBB qword ptr [rcx + 112], 0
	SBB qword ptr [rcx + 120], 0

	RET

u1024_dec ENDP

u1024_shl PROC

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0
	;
	;
	MOV cl, 64
	SUB cl, r8b

	MOV r13, qword ptr [rdx + 112]	;Save top bits of top part
	MOV qword ptr [r15 + 112], r13
	SHRX r13, r13, rcx

	MOV cl, r8b

	MOV r12, qword ptr [rdx + 120]
	MOV qword ptr [r15 + 120], r12

	SAL qword ptr [r15 + 112], cl
	SAL qword ptr [r15 + 120], cl	

	OR qword ptr [r15 + 112], r13	
	;
	;
	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15
	RET

u1024_shl ENDP

u1024_shr PROC

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK8 r13, r12, rdx, r15, 8, 0
	
	SHRBLCK r13, r12, rdx, r15, 72, 64
	SHRBLCK r13, r12, rdx, r15, 80, 72
	SHRBLCK r13, r12, rdx, r15, 88, 80
	SHRBLCK r13, r12, rdx, r15, 96, 88
	SHRBLCK r13, r12, rdx, r15, 104, 96
	SHRBLCK r13, r12, rdx, r15, 112, 104
	SHRBLCK r13, r12, rdx, r15, 120, 112

	MOV cl, r8b						;Get amount to shift

	MOV r12, qword ptr [rdx + 120]
	SHRX r12, r12, rcx
	MOV qword ptr [r15 + 120], r12	;Get value and Shift Right

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15
	RET

u1024_shr ENDP

u1024_and PROC

	VECAND4 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u1024_and ENDP

u1024_or PROC

	VECOR4 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u1024_or ENDP

u1024_xor PROC

	VECXOR4 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u1024_xor ENDP

u1024_not PROC

	NOT4 r12, rdx, rcx, 0
	NOT4 r12, rdx, rcx, 32
	NOT4 r12, rdx, rcx, 64
	NOT4 r12, rdx, rcx, 96

	MOV rax, rcx
	RET

u1024_not ENDP

;
;
;	U2048 OPERATIONS START HERE
;
;

u2048_add PROC

	MOVREL32 r12, rdx, rcx	;mov into rcx u2048 param
	ADD32 rcx, r8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u2048_add ENDP

u2048_addBig PROC

	MOVREL32 r12, rdx, rcx	;mov into rcx first u2048 param
	MOVADD32 r12, r8, rcx	;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u2048_addBig ENDP

u2048_sub PROC

	MOVREL32 r12, rdx, rcx	;mov into rcx first u512 param
	SUB32 rcx, r8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u2048_sub ENDP

u2048_subBig PROC

	MOVREL32 r12, rdx, rcx	;mov into rcx first u256 param
	MOVSUB32 r12, r8, rcx	;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u2048_subBig ENDP

u2048_mul PROC

	MPM rax, rdx, r8, 248

	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 240
	ADD r12, rdx
	MOV r13, rax
	POP rdx
	
	MULBLCK8 rax, rdx, r8, r13, r12, 232
	MULBLCK8 rax, rdx, r8, r13, r12, 168
	MULBLCK8 rax, rdx, r8, r13, r12, 104

	MULBLCK rax, rdx, r8, r13, r12, 40
	MULBLCK rax, rdx, r8, r12, r13, 32
	MULBLCK rax, rdx, r8, r13, r12, 24
	MULBLCK rax, rdx, r8, r12, r13, 16
	MULBLCK rax, rdx, r8, r13, r12, 8

	MPM rax, rdx, r8, 0
	AACP r12, r13, rdx

	MOV qword ptr [rcx + 16], r13	;Done with +16 part, so storing it
	MOV qword ptr [rcx + 8], r12	;Done with +8 part, so storing it
	MOV qword ptr [rcx], rax		;Done

	MOV rax, rcx
	RET

u2048_mul ENDP

u2048_mulBig PROC
	;
	;Execution of the 1° Column
	;

	MPM2 rax, rdx, 0, r8, 0

	MOV qword ptr [rcx], rax
	MOV r12, rdx
	POP rdx

	;
	;Execution of the 2° Column
	;

	MPM2 rax, rdx, 0, r8, 8
	AMP r12, r13, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 16, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 16
	AACP2  r12, r13, rax, rdx
	
	MPM2 rax, rdx, 16, r8, 8
	AACP2  r12, r13, rax, rdx

	MPM2 rax, rdx, 24, r8, 0
	AACP2  r12, r13, rax, rdx
	
	MOV qword ptr [rcx + 24], r12

	;
	;Execution of the 5° Column
	;

	MPM2 rax, rdx, 0, r8, 32
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 24

	MOV qword ptr [rcx + 32], r13

	;
	;Execution of the 6° Column
	;

	MPM2 rax, rdx, 0, r8, 40
	AMP r12, r13, rax, rdx

	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 32

	MPM2 rax, rdx, 40, r8, 0
	AACP2 r12, r13, rax, rdx
	
	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MPM2 rax, rdx, 40, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 48, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MPM2 rax, rdx, 40, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 48, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 56, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 56], r12

	;
	;Execution of the 9° Column
	;

	MPM2 rax, rdx, 0, r8, 64
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 24

	MOV qword ptr [rcx + 64], r13

	;
	;Execution of the 10° Column
	;

	MPM2 rax, rdx, 0, r8, 72
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 32

	MPM2 rax, rdx, 72, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MPM2 rax, rdx, 72, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 80, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MPM2 rax, rdx, 72, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 80, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 88, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 88], r12

	;
	;Execution of the 13° Column
	;

	MPM2 rax, rdx, 0, r8, 96
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 24

	MOV qword ptr [rcx + 96], r13

	;
	;Execution of the 14° Column
	;

	MPM2 rax, rdx, 0, r8, 104
	AMP r12, r13, rax, rdx

	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 32

	MPM2 rax, rdx, 104, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MPM2 rax, rdx, 104, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 112, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MPM2 rax, rdx, 104, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 112, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 120, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 120], r12

	;
	;Execution of the 17° Column
	;

	MPM2 rax, rdx, 0, r8, 128
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 120

	MOV qword ptr [rcx + 128], r13

	;
	;Execution of the 18° Column
	;

	MPM2 rax, rdx, 0, r8, 136
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 128

	MPM2 rax, rdx, 136, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 136], r12

	;
	;Execution of the 19° Column
	;

	MPM2 rax, rdx, 0, r8, 144
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 136

	MPM2 rax, rdx, 136, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 144, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 144], r13

	;
	;Execution of the 20° Column
	;				  
	
	MPM2 rax, rdx, 0, r8, 152
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 144

	MPM2 rax, rdx, 136, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 144, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 152, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 152], r12

	;				  
	;Execution of the 21° Column
	;
	
	MPM2 rax, rdx, 0, r8, 160
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 24

	MOV qword ptr [rcx + 160], r13

	;				  
	;Execution of the 22° Column
	;
	
	MPM2 rax, rdx, 0, r8, 168
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 32

	MPM2 rax, rdx, 168, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 168], r12

	;				  
	;Execution of the 23° Column
	;
	
	MPM2 rax, rdx, 0, r8, 176
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 40

	MPM2 rax, rdx, 168, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 176, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 176], r13

	;				  
	;Execution of the 24° Column
	;
	
	MPM2 rax, rdx, 0, r8, 184
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 48

	MPM2 rax, rdx, 168, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 176, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 184, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 184], r12

	;
	;Execution of the 25° Column
	;
		
	MPM2 rax, rdx, 0, r8, 192
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 24

	MOV qword ptr [rcx + 192], r13

	;
	;Execution of the 26° Column
	;
	
	MPM2 rax, rdx, 0, r8, 200
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 32

	MPM2 rax, rdx, 200, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 200], r12

	;
	;Execution of the 27° Column
	;
	
	MPM2 rax, rdx, 0, r8, 208
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 40

	MPM2 rax, rdx, 200, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 208, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 208], r13

	;
	;Execution of the 28° Column
	;

	MPM2 rax, rdx, 0, r8, 216
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 48

	MPM2 rax, rdx, 200, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 208, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 216, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 216], r12

	;
	;Execution of the 29° Column
	;

	MPM2 rax, rdx, 0, r8, 224
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 200, r8, 24

	MOV qword ptr [rcx + 224], r13

	;
	;Execution of the 30° Column
	;

	MPM2 rax, rdx, 0, r8, 232
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 200, r8, 32

	MPM2 rax, rdx, 232, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 232], r12

	;
	;Execution of the 31° Column
	;

	MPM2 rax, rdx, 0, r8, 240
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 200, r8, 40

	MPM2 rax, rdx, 232, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 240, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 240], r13

	;
	;Execution of the 32° Column
	;

	MPM2 rax, rdx, 0, r8, 248
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 200, r8, 48

	MPM2 rax, rdx, 232, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 240, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 248, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 248], r12

	;
	;Return
	;

	MOV rax, rcx
	RET

u2048_mulBig ENDP

u2048_divBig PROC

	ZERO32 rcx, 0	;Initialize Quotient to 0

	;
	; TESTING ALLOCATING SPACE IN STACK FOR REMAINDER
	;
	SUB rsp, 256
	MOV r15, rsp
	ZERO32 r15, 0	;Initialize Remainder to 0
	;
	; TESTING !!!
	;

	; Macro definition is here because I wouldn't have been able to use lables otherwise
	BSRFOUND4 MACRO reg1, reg2, src, off
	BSR reg1, qword ptr [src + off + 24]
	MOV reg2, ((off + 24)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off + 16]
	MOV reg2, ((off + 16)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off + 8]
	MOV reg2, ((off + 8)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off]
	MOV reg2, ((off)*8)
	JNE FOUND
	ENDM

	BSRFOUND4 r12, r13, rdx, 224
	BSRFOUND4 r12, r13, rdx, 192
	BSRFOUND4 r12, r13, rdx, 160
	BSRFOUND4 r12, r13, rdx, 128
	BSRFOUND4 r12, r13, rdx, 96
	BSRFOUND4 r12, r13, rdx, 64
	BSRFOUND4 r12, r13, rdx, 32

	BSR r12, qword ptr [rdx + 24]
	MOV r13, 192
	JNE FOUND

	BSR r12, qword ptr [rdx + 16]
	MOV r13, 128
	JNE FOUND

	BSR r12, qword ptr [rdx + 8]
	MOV r13, 64
	JNE FOUND

	BSR r12, qword ptr [rdx]
	JNE DIVISION_LOOP

	MOV rax, rcx
	RET

	FOUND:
	ADD r12, r13

	DIVISION_LOOP:

	;
	; ENTERING CALL TO u2048_shl
	;

	PUSHR

	SUB rsp, 256
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u2048_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL32 r12, rax, r15

	ADD rsp, 256
	POPR
	;
	; EXITED CALL TO u2048_shl
	;
	PUSH r15
	PUSH rax
	PUSH rdx
	MOV rax, r12
	MOV rdx, 0
	MOV r13, 64
	DIV r13
	MOV r13, rax
	MOV r15, rdx
	POP rdx
	POP rax
	
	MOV r14, qword ptr [rdx + (r13*8)]
	MOV r13, r15
	POP r15

	PUSH rcx
	MOV cl, r13b
	SHR r14, cl
	POP rcx

	AND r14, 1
	OR qword ptr [r15], r14

	;
	; CHECK IF Remainder(R15) IS GREATER OR EQUAL THAN DIVISOR (R8)
	;

	GOE4 MACRO reg1, remainder, divisor, off
	MOV reg1, qword ptr [remainder + off + 24]
	SUB reg1, qword ptr [divisor + off + 24]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 16]
	SUB reg1, qword ptr [divisor + off + 16]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 8]
	SUB reg1, qword ptr [divisor + off + 8]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off]
	SUB reg1, qword ptr [divisor + off]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	ENDM

	GOE4 r13, r15, r8, 224
	GOE4 r13, r15, r8, 192
	GOE4 r13, r15, r8, 160
	GOE4 r13, r15, r8, 128
	GOE4 r13, r15, r8, 96
	GOE4 r13, r15, r8, 64
	GOE4 r13, r15, r8, 32

	MOV r13, qword ptr [r15 + 24]
	SUB r13, qword ptr [r8 + 24]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 16]
	SUB r13, qword ptr [r8 + 16]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 8]
	SUB r13, qword ptr [r8 + 8]
	JG ADV_QUOTIENT

	MOV r13, qword ptr [r15]
	SUB r13, qword ptr [r8]
	JGE ADV_QUOTIENT
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	ADV_QUOTIENT:
	;
	; TESTING: ENTERING CALL TO u2048_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	MOV rdx, r15

	SUB rsp, 256
	MOV rcx, rsp
	ZERO32 rcx, 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u2048_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL32 r12, rax, r15

	ADD rsp, 256
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx

	;
	; TESTING: EXITED CALL TO u1024_subBig
	;

	;
	; SET THE nth bit of Quotient
	;
	PUSH r15
	PUSH rax
	PUSH rdx
	MOV rax, r12
	MOV rdx, 0
	MOV r13, 64
	DIV r13
	MOV r13, rax
	MOV r15, rdx
	POP rdx
	POP rax

	MOV r14, qword ptr [rdx + (r13*8)]
	PUSH r12
	MOV r12, r13
	
	PUSH rcx
	MOV rcx, 0
	MOV r13, 1
	MOV cl, r15b
	SHL r13, cl

	POP rcx
	OR qword ptr [rcx + (r12*8)], r13
	POP r12
	POP r15

	ADV_LOOP:
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	;
	; END LOOP
	;

	END_LOOP:

	MOVREL32 r12, r15, r9
	; RESTORE STACK POINTER !?!?!?
	ADD rsp, 256

	MOV rax, rcx
	RET


u2048_divBig ENDP

u2048_inc PROC

	ADD qword ptr [rcx], 1
	ADC8 rcx, 8
	ADC8 rcx, 72
	ADC8 rcx, 136
	ADC qword ptr [rcx + 200], 0
	ADC qword ptr [rcx + 208], 0
	ADC qword ptr [rcx + 216], 0
	ADC qword ptr [rcx + 224], 0
	ADC qword ptr [rcx + 232], 0
	ADC qword ptr [rcx + 240], 0
	ADC qword ptr [rcx + 248], 0

	RET

u2048_inc ENDP

u2048_dec PROC

	SUB qword ptr [rcx], 1
	SBB8 rcx, 8
	SBB8 rcx, 72
	SBB8 rcx, 136
	SBB qword ptr [rcx + 200], 0
	SBB qword ptr [rcx + 208], 0
	SBB qword ptr [rcx + 216], 0
	SBB qword ptr [rcx + 224], 0
	SBB qword ptr [rcx + 232], 0
	SBB qword ptr [rcx + 240], 0
	SBB qword ptr [rcx + 248], 0

	RET

u2048_dec ENDP

u2048_shl PROC

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0
	;
	;
	MOV cl, 64
	SUB cl, r8b

	MOV r13, qword ptr [rdx + 240]	;Save top bits of top part
	MOV qword ptr [r15 + 240], r13
	SHRX r13, r13, rcx

	MOV cl, r8b

	MOV r12, qword ptr [rdx + 248]
	MOV qword ptr [r15 + 248], r12

	SAL qword ptr [r15 + 240], cl
	SAL qword ptr [r15 + 248], cl	

	OR qword ptr [r15 + 240], r13	
	;
	;
	SHLBLCK8 r13, rdx, r15, 232, 240
	SHLBLCK8 r13, rdx, r15, 168, 176
	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15
	RET

u2048_shl ENDP

u2048_shr PROC

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK8 r13, r12, rdx, r15, 8, 0
	SHRBLCK8 r13, r12, rdx, r15, 72, 64
	SHRBLCK8 r13, r12, rdx, r15, 136, 128

	SHRBLCK r13, r12, rdx, r15, 200, 192
	SHRBLCK r13, r12, rdx, r15, 208, 200
	SHRBLCK r13, r12, rdx, r15, 216, 208
	SHRBLCK r13, r12, rdx, r15, 224, 216
	SHRBLCK r13, r12, rdx, r15, 232, 224
	SHRBLCK r13, r12, rdx, r15, 240, 232
	SHRBLCK r13, r12, rdx, r15, 248, 240

	MOV cl, r8b						;Get amount to shift

	MOV r12, qword ptr [rdx + 248]
	SHRX r12, r12, rcx
	MOV qword ptr [r15 + 248], r12	;Get value and Shift Right

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15
	RET

u2048_shr ENDP

u2048_and PROC

	VECAND4 rdx, r8, rcx, 0
	VECAND4 rdx, r8, rcx, 128

	MOV rax, rcx
	RET

u2048_and ENDP

u2048_or PROC

	VECOR4 rdx, r8, rcx, 0
	VECOR4 rdx, r8, rcx, 128

	MOV rax, rcx
	RET

u2048_or ENDP

u2048_xor PROC

	VECXOR4 rdx, r8, rcx, 0
	VECXOR4 rdx, r8, rcx, 128

	MOV rax, rcx
	RET

u2048_xor ENDP

u2048_not PROC

	NOT32 r12, rdx, rcx, 0

	MOV rax, rcx
	RET

u2048_not ENDP

;
;
;	U4096 OPERATIONS START HERE
;
;

u4096_add PROC

	MOVREL64 r12, rdx, rcx	;mov into rcx u2048 param
	ADD64 rcx, r8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u4096_add ENDP

u4096_addBig PROC

	MOVREL64 r12, rdx, rcx	;mov into rcx first u2048 param
	MOVADD64 r12, r8, rcx	;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET
u4096_addBig ENDP

u4096_sub PROC

	MOVREL64 r12, rdx, rcx	;mov into rcx first u512 param
	SUB64 rcx, r8			;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u4096_sub ENDP

u4096_subBig PROC

	MOVREL64 r12, rdx, rcx	;mov into rcx first u256 param
	MOVSUB64 r12, r8, rcx	;if overflowed we advance the high part by the carry

	MOV rax, rcx
	RET

u4096_subBig ENDP

u4096_mul PROC

	MPM rax, rdx, r8, 504

	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 496
	ADD r12, rdx
	MOV r13, rax
	POP rdx

	MULBLCK8 rax, rdx, r8, r13, r12, 488
	MULBLCK8 rax, rdx, r8, r13, r12, 424
	MULBLCK8 rax, rdx, r8, r13, r12, 360
	MULBLCK8 rax, rdx, r8, r13, r12, 296
	MULBLCK8 rax, rdx, r8, r13, r12, 232
	MULBLCK8 rax, rdx, r8, r13, r12, 168
	MULBLCK8 rax, rdx, r8, r13, r12, 104

	MULBLCK rax, rdx, r8, r13, r12, 40
	MULBLCK rax, rdx, r8, r12, r13, 32
	MULBLCK rax, rdx, r8, r13, r12, 24
	MULBLCK rax, rdx, r8, r12, r13, 16
	MULBLCK rax, rdx, r8, r13, r12, 8

	MPM rax, rdx, r8, 0
	AACP r12, r13, rdx

	MOV qword ptr [rcx + 16], r13	;Done with +16 part, so storing it
	MOV qword ptr [rcx + 8], r12	;Done with +8 part, so storing it
	MOV qword ptr [rcx], rax		;Done

	MOV rax, rcx
	RET

u4096_mul ENDP

u4096_mulBig PROC

	;
	;Execution of the 1° Column
	;

	MPM2 rax, rdx, 0, r8, 0

	MOV qword ptr [rcx], rax
	MOV r12, rdx
	POP rdx

	;
	;Execution of the 2° Column
	;

	MPM2 rax, rdx, 0, r8, 8
	AMP r12, r13, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 16, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MPM2 rax, rdx, 8, r8, 16
	AACP2  r12, r13, rax, rdx
	
	MPM2 rax, rdx, 16, r8, 8
	AACP2  r12, r13, rax, rdx

	MPM2 rax, rdx, 24, r8, 0
	AACP2  r12, r13, rax, rdx
	
	MOV qword ptr [rcx + 24], r12

	;
	;Execution of the 5° Column
	;

	MPM2 rax, rdx, 0, r8, 32
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 24

	MOV qword ptr [rcx + 32], r13

	;
	;Execution of the 6° Column
	;

	MPM2 rax, rdx, 0, r8, 40
	AMP r12, r13, rax, rdx

	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 32

	MPM2 rax, rdx, 40, r8, 0
	AACP2 r12, r13, rax, rdx
	
	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MPM2 rax, rdx, 40, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 48, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MPM2 rax, rdx, 40, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 48, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 56, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 56], r12

	;
	;Execution of the 9° Column
	;

	MPM2 rax, rdx, 0, r8, 64
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 24

	MOV qword ptr [rcx + 64], r13

	;
	;Execution of the 10° Column
	;

	MPM2 rax, rdx, 0, r8, 72
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 32

	MPM2 rax, rdx, 72, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MPM2 rax, rdx, 72, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 80, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MPM2 rax, rdx, 72, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 80, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 88, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 88], r12

	;
	;Execution of the 13° Column
	;

	MPM2 rax, rdx, 0, r8, 96
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 24

	MOV qword ptr [rcx + 96], r13

	;
	;Execution of the 14° Column
	;

	MPM2 rax, rdx, 0, r8, 104
	AMP r12, r13, rax, rdx

	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 32

	MPM2 rax, rdx, 104, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MPM2 rax, rdx, 104, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 112, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MPM2 rax, rdx, 104, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 112, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 120, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 120], r12

	;
	;Execution of the 17° Column
	;

	MPM2 rax, rdx, 0, r8, 128
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 120

	MOV qword ptr [rcx + 128], r13

	;
	;Execution of the 18° Column
	;

	MPM2 rax, rdx, 0, r8, 136
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 128

	MPM2 rax, rdx, 136, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 136], r12

	;
	;Execution of the 19° Column
	;

	MPM2 rax, rdx, 0, r8, 144
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 136

	MPM2 rax, rdx, 136, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 144, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 144], r13

	;
	;Execution of the 20° Column
	;				  
	
	MPM2 rax, rdx, 0, r8, 152
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 144

	MPM2 rax, rdx, 136, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 144, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 152, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 152], r12

	;				  
	;Execution of the 21° Column
	;
	
	MPM2 rax, rdx, 0, r8, 160
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 24

	MOV qword ptr [rcx + 160], r13

	;				  
	;Execution of the 22° Column
	;
	
	MPM2 rax, rdx, 0, r8, 168
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 32

	MPM2 rax, rdx, 168, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 168], r12

	;				  
	;Execution of the 23° Column
	;
	
	MPM2 rax, rdx, 0, r8, 176
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 40

	MPM2 rax, rdx, 168, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 176, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 176], r13

	;				  
	;Execution of the 24° Column
	;
	
	MPM2 rax, rdx, 0, r8, 184
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 48

	MPM2 rax, rdx, 168, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 176, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 184, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 184], r12

	;
	;Execution of the 25° Column
	;
		
	MPM2 rax, rdx, 0, r8, 192
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 24

	MOV qword ptr [rcx + 192], r13

	;
	;Execution of the 26° Column
	;
	
	MPM2 rax, rdx, 0, r8, 200
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 32

	MPM2 rax, rdx, 200, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 200], r12

	;
	;Execution of the 27° Column
	;
	
	MPM2 rax, rdx, 0, r8, 208
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 40

	MPM2 rax, rdx, 200, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 208, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 208], r13

	;
	;Execution of the 28° Column
	;

	MPM2 rax, rdx, 0, r8, 216
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 48

	MPM2 rax, rdx, 200, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 208, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 216, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 216], r12

	;
	;Execution of the 29° Column
	;

	MPM2 rax, rdx, 0, r8, 224
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 200, r8, 24

	MOV qword ptr [rcx + 224], r13

	;
	;Execution of the 30° Column
	;

	MPM2 rax, rdx, 0, r8, 232
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 200, r8, 32

	MPM2 rax, rdx, 232, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 232], r12

	;
	;Execution of the 31° Column
	;

	MPM2 rax, rdx, 0, r8, 240
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 200, r8, 40

	MPM2 rax, rdx, 232, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 240, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 240], r13

	;
	;Execution of the 32° Column
	;

	MPM2 rax, rdx, 0, r8, 248
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 200, r8, 48

	MPM2 rax, rdx, 232, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 240, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 248, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 248], r12

	;
	;Execution of the 33° Column
	;

	MPM2 rax, rdx, 0, r8, 256
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 248
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 120

	MOV qword ptr [rcx + 256], r13

	;
	;Execution of the 34° Column
	;

	MPM2 rax, rdx, 0, r8, 264
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 256
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 128
	
	MPM2 rax, rdx, 264, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 264], r12

	;
	;Execution of the 35° Column
	;

	MPM2 rax, rdx, 0, r8, 272
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 264
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 136

	MPM2 rax, rdx, 264, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 272, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 272], r13

	;
	;Execution of the 36° Column
	;

	MPM2 rax, rdx, 0, r8, 280
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 272
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 144
	
	MPM2 rax, rdx, 264, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 272, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 280, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 280], r12

	;
	;Execution of the 37° Column
	;

	MPM2 rax, rdx, 0, r8, 288
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 280
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 24

	MOV qword ptr [rcx + 288], r13

	;
	;Execution of the 38° Column
	;

	MPM2 rax, rdx, 0, r8, 296
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 288
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 32

	MPM2 rax, rdx, 296, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 296], r12

	;
	;Execution of the 39° Column
	;

	MPM2 rax, rdx, 0, r8, 304
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 296
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 40

	MPM2 rax, rdx, 296, r8, 8
	AACP2 r13, r12, rax, rdx	

	MPM2 rax, rdx, 304, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 304], r13

	;
	;Execution of the 40° Column
	;

	MPM2 rax, rdx, 0, r8, 312
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 304
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 48

	MPM2 rax, rdx, 296, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 304, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 312, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 312], r12

	;
	;Execution of the 41° Column
	;

	MPM2 rax, rdx, 0, r8, 320
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 312
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 24

	MOV qword ptr [rcx + 320], r13
	;
	;Execution of the 42° Column
	;

	MPM2 rax, rdx, 0, r8, 328
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 320
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 32

	MPM2 rax, rdx, 328, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 328], r12
	;
	;Execution of the 43° Column
	;

	MPM2 rax, rdx, 0, r8, 336
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 328
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 40

	MPM2 rax, rdx, 328, r8, 8
	AACP2 r13, r12, rax, rdx	

	MPM2 rax, rdx, 336, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 336], r13
	;
	;Execution of the 44° Column
	;

	MPM2 rax, rdx, 0, r8, 344
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 336
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 48

	MPM2 rax, rdx, 328, r8, 0
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 336, r8, 0
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 344, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 344], r12
	;
	;Execution of the 45° Column
	;

	MPM2 rax, rdx, 0, r8, 352
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 344
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 24

	MOV qword ptr [rcx + 352], r13
	;
	;Execution of the 46° Column
	;

	MPM2 rax, rdx, 0, r8, 360
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 352
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 32

	MPM2 rax, rdx, 360, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 360], r12
	;
	;Execution of the 47° Column
	;

	MPM2 rax, rdx, 0, r8, 368
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 360
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 40

	MPM2 rax, rdx, 360, r8, 8
	AACP2 r13, r12, rax, rdx	

	MPM2 rax, rdx, 368, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 368], r13
	;
	;Execution of the 48° Column
	;

	MPM2 rax, rdx, 0, r8, 376
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 368
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 48

	MPM2 rax, rdx, 360, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 368, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 376, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 376], r12
	;
	;Execution of the 49° Column
	;

	MPM2 rax, rdx, 0, r8, 384
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 248
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 120

	MOV qword ptr [rcx + 384], r13
	;
	;Execution of the 50° Column
	;

	MPM2 rax, rdx, 0, r8, 392
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 256
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 128

	MPM2 rax, rdx, 392, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 392], r12
	;
	;Execution of the 51° Column
	;

	MPM2 rax, rdx, 0, r8, 400
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 264
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 136

	MPM2 rax, rdx, 392, r8, 8
	AACP2 r13, r12, rax, rdx
	
	MPM2 rax, rdx, 400, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 400], r13
	;
	;Execution of the 52° Column
	;

	MPM2 rax, rdx, 0, r8, 408
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 272
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 144

	MPM2 rax, rdx, 392, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 400, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 408, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 408], r12
	;
	;Execution of the 53° Column
	;

	MPM2 rax, rdx, 0, r8, 416
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 280
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 24

	MOV qword ptr [rcx + 416], r13
	;
	;Execution of the 54° Column
	;

	MPM2 rax, rdx, 0, r8, 424
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 288
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 32

	MPM2 rax, rdx, 424, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 424], r12
	;
	;Execution of the 55° Column
	;

	MPM2 rax, rdx, 0, r8, 432
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 296
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 40

	MPM2 rax, rdx, 424, r8, 0
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 432, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 432], r13
	;
	;Execution of the 56° Column
	;

	MPM2 rax, rdx, 0, r8, 440
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 304
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 48

	MPM2 rax, rdx, 424, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 432, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 440, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 440], r12
	;
	;Execution of the 57° Column
	;

	MPM2 rax, rdx, 0, r8, 448
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 312
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 24

	MOV qword ptr [rcx + 448], r13
	;
	;Execution of the 58° Column
	;

	MPM2 rax, rdx, 0, r8, 456
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 320
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 32

	MPM2 rax, rdx, 456, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 456], r12
	;
	;Execution of the 59° Column
	;

	MPM2 rax, rdx, 0, r8, 464
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 328
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 40

	MPM2 rax, rdx, 456, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 464, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 464], r13
	;
	;Execution of the 60° Column
	;

	MPM2 rax, rdx, 0, r8, 472
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 336
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 48

	MPM2 rax, rdx, 456, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 464, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 472, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 472], r12
	;
	;Execution of the 61° Column
	;

	MPM2 rax, rdx, 0, r8, 480
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 472
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 344
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 456, r8, 24

	MOV qword ptr [rcx + 480], r13
	;
	;Execution of the 62° Column
	;

	MPM2 rax, rdx, 0, r8, 488
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 352
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 32

	MPM2 rax, rdx, 488, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 488], r12
	;
	;Execution of the 63° Column
	;

	MPM2 rax, rdx, 0, r8, 496
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 136, r8, 360
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 456, r8, 40

	MPM2 rax, rdx, 488, r8, 8
	AACP2 r13, r12, rax, rdx

	MPM2 rax, rdx, 496, r8, 0
	AACP2 r13, r12, rax, rdx

	MOV qword ptr [rcx + 496], r13
	;
	;Execution of the 64° Column
	;

	MPM2 rax, rdx, 0, r8, 504
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 136, r8, 368
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 48

	MPM2 rax, rdx, 488, r8, 16
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 496, r8, 8
	AACP2 r12, r13, rax, rdx

	MPM2 rax, rdx, 504, r8, 0
	AACP2 r12, r13, rax, rdx

	MOV qword ptr [rcx + 504], r12
	;
	;Return
	;

	MOV rax, rcx
	RET

u4096_mulBig ENDP

u4096_divBig PROC

	ZERO64 rcx, 0	;Initialize Quotient to 0

	;
	; TESTING ALLOCATING SPACE IN STACK FOR REMAINDER
	;
	SUB rsp, 512
	MOV r15, rsp
	ZERO64 r15, 0	;Initialize Remainder to 0
	;
	; TESTING !!!
	;

	; Macro definition is here because I wouldn't have been able to use lables otherwise
	BSRFOUND8 MACRO reg1, reg2, src, off
	
	BSR reg1, qword ptr [src + off + 56]
	MOV reg2, ((off + 56)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off + 48]
	MOV reg2, ((off + 48)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off + 40]
	MOV reg2, ((off + 40)*8)
	JNE FOUND
	
	BSR reg1, qword ptr [src + off + 32]
	MOV reg2, ((off + 32)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off + 24]
	MOV reg2, ((off + 24)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off + 16]
	MOV reg2, ((off + 16)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off + 8]
	MOV reg2, ((off + 8)*8)
	JNE FOUND

	BSR reg1, qword ptr [src + off]
	MOV reg2, ((off)*8)
	JNE FOUND
	ENDM

	BSRFOUND8 r12, r13, rdx, 448
	BSRFOUND8 r12, r13, rdx, 384
	BSRFOUND8 r12, r13, rdx, 320
	BSRFOUND8 r12, r13, rdx, 256
	BSRFOUND8 r12, r13, rdx, 192
	BSRFOUND8 r12, r13, rdx, 128
	BSRFOUND8 r12, r13, rdx, 64
	BSRFOUND4 r12, r13, rdx, 32

	BSR r12, qword ptr [rdx + 24]
	MOV r13, 192
	JNE FOUND

	BSR r12, qword ptr [rdx + 16]
	MOV r13, 128
	JNE FOUND

	BSR r12, qword ptr [rdx + 8]
	MOV r13, 64
	JNE FOUND

	BSR r12, qword ptr [rdx]
	JNE DIVISION_LOOP

	MOV rax, rcx
	RET

	FOUND:
	ADD r12, r13

	DIVISION_LOOP:

	;
	; ENTERING CALL TO u2048_shl
	;

	PUSHR

	SUB rsp, 512
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u4096_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL64 r12, rax, r15

	ADD rsp, 512
	POPR
	;
	; EXITED CALL TO u2048_shl
	;
	PUSH r15
	PUSH rax
	PUSH rdx
	MOV rax, r12
	MOV rdx, 0
	MOV r13, 64
	DIV r13
	MOV r13, rax
	MOV r15, rdx
	POP rdx
	POP rax
	
	MOV r14, qword ptr [rdx + (r13*8)]
	MOV r13, r15
	POP r15

	PUSH rcx
	MOV cl, r13b
	SHR r14, cl
	POP rcx

	AND r14, 1
	OR qword ptr [r15], r14

	;
	; CHECK IF Remainder(R15) IS GREATER OR EQUAL THAN DIVISOR (R8)
	;

	GOE8 MACRO reg1, remainder, divisor, off

	MOV reg1, qword ptr [remainder + off + 56]
	SUB reg1, qword ptr [divisor + off + 56]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 48]
	SUB reg1, qword ptr [divisor + off + 48]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 40]
	SUB reg1, qword ptr [divisor + off + 40]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 32]
	SUB reg1, qword ptr [divisor + off + 32]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 24]
	SUB reg1, qword ptr [divisor + off + 24]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 16]
	SUB reg1, qword ptr [divisor + off + 16]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off + 8]
	SUB reg1, qword ptr [divisor + off + 8]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV reg1, qword ptr [remainder + off]
	SUB reg1, qword ptr [divisor + off]
	JG ADV_QUOTIENT
	JL ADV_LOOP

	ENDM

	GOE8 r13, r15, r8, 448
	GOE8 r13, r15, r8, 384
	GOE8 r13, r15, r8, 320
	GOE8 r13, r15, r8, 256
	GOE8 r13, r15, r8, 192
	GOE8 r13, r15, r8, 128
	GOE8 r13, r15, r8, 64
	GOE4 r13, r15, r8, 32

	MOV r13, qword ptr [r15 + 24]
	SUB r13, qword ptr [r8 + 24]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 16]
	SUB r13, qword ptr [r8 + 16]
	JG ADV_QUOTIENT
	JL ADV_LOOP
	MOV r13, qword ptr [r15 + 8]
	SUB r13, qword ptr [r8 + 8]
	JG ADV_QUOTIENT

	MOV r13, qword ptr [r15]
	SUB r13, qword ptr [r8]
	JGE ADV_QUOTIENT
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	ADV_QUOTIENT:
	;
	; TESTING: ENTERING CALL TO u2048_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	MOV rdx, r15

	SUB rsp, 512
	MOV rcx, rsp
	ZERO64 rcx, 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u4096_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL64 r12, rax, r15

	ADD rsp, 512
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx

	;
	; TESTING: EXITED CALL TO u1024_subBig
	;

	;
	; SET THE nth bit of Quotient
	;
	PUSH r15
	PUSH rax
	PUSH rdx
	MOV rax, r12
	MOV rdx, 0
	MOV r13, 64
	DIV r13
	MOV r13, rax
	MOV r15, rdx
	POP rdx
	POP rax

	MOV r14, qword ptr [rdx + (r13*8)]
	PUSH r12
	MOV r12, r13
	
	PUSH rcx
	MOV rcx, 0
	MOV r13, 1
	MOV cl, r15b
	SHL r13, cl

	POP rcx
	OR qword ptr [rcx + (r12*8)], r13
	POP r12
	POP r15

	ADV_LOOP:
	DEC r12
	JGE DIVISION_LOOP
	JMP END_LOOP

	;
	; END LOOP
	;

	END_LOOP:

	MOVREL64 r12, r15, r9
	; RESTORE STACK POINTER !?!?!?
	ADD rsp, 512

	MOV rax, rcx
	RET

u4096_divBig ENDP

u4096_inc PROC

	ADD qword ptr [rcx], 1
	ADC8 rcx, 8
	ADC8 rcx, 72
	ADC8 rcx, 136
	ADC8 rcx, 200
	ADC8 rcx, 264
	ADC8 rcx, 328
	ADC8 rcx, 392
	ADC qword ptr [rcx + 456], 0
	ADC qword ptr [rcx + 464], 0
	ADC qword ptr [rcx + 472], 0
	ADC qword ptr [rcx + 480], 0
	ADC qword ptr [rcx + 488], 0
	ADC qword ptr [rcx + 496], 0
	ADC qword ptr [rcx + 504], 0

	RET

u4096_inc ENDP

u4096_dec PROC

	SUB qword ptr [rcx], 1
	SBB8 rcx, 8
	SBB8 rcx, 72
	SBB8 rcx, 136
	SBB8 rcx, 200
	SBB8 rcx, 264
	SBB8 rcx, 328
	SBB8 rcx, 392
	SBB qword ptr [rcx + 456], 0
	SBB qword ptr [rcx + 464], 0
	SBB qword ptr [rcx + 472], 0
	SBB qword ptr [rcx + 480], 0
	SBB qword ptr [rcx + 488], 0
	SBB qword ptr [rcx + 496], 0
	SBB qword ptr [rcx + 504], 0

	RET

u4096_dec ENDP

u4096_shl PROC

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0
	;
	;
	MOV cl, 64
	SUB cl, r8b

	MOV r13, qword ptr [rdx + 496]	;Save top bits of top part
	MOV qword ptr [r15 + 496], r13
	SHRX r13, r13, rcx

	MOV cl, r8b

	MOV r12, qword ptr [rdx + 504]
	MOV qword ptr [r15 + 504], r12

	SAL qword ptr [r15 + 496], cl
	SAL qword ptr [r15 + 504], cl	

	OR qword ptr [r15 + 496], r13	
	;
	;
	SHLBLCK8 r13, rdx, r15, 488, 496
	SHLBLCK8 r13, rdx, r15, 424, 432
	SHLBLCK8 r13, rdx, r15, 360, 368
	SHLBLCK8 r13, rdx, r15, 296, 304
	SHLBLCK8 r13, rdx, r15, 232, 240
	SHLBLCK8 r13, rdx, r15, 168, 176
	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15
	RET

u4096_shl ENDP

u4096_shr PROC

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK8 r13, r12, rdx, r15, 8, 0
	SHRBLCK8 r13, r12, rdx, r15, 72, 64
	SHRBLCK8 r13, r12, rdx, r15, 136, 128
	SHRBLCK8 r13, r12, rdx, r15, 200, 192
	SHRBLCK8 r13, r12, rdx, r15, 264, 256
	SHRBLCK8 r13, r12, rdx, r15, 328, 320
	SHRBLCK8 r13, r12, rdx, r15, 392, 384

	SHRBLCK r13, r12, rdx, r15, 456, 448
	SHRBLCK r13, r12, rdx, r15, 464, 456
	SHRBLCK r13, r12, rdx, r15, 472, 464
	SHRBLCK r13, r12, rdx, r15, 480, 472
	SHRBLCK r13, r12, rdx, r15, 488, 480
	SHRBLCK r13, r12, rdx, r15, 496, 488
	SHRBLCK r13, r12, rdx, r15, 504, 496

	MOV cl, r8b						;Get amount to shift

	MOV r12, qword ptr [rdx + 504]
	SHRX r12, r12, rcx
	MOV qword ptr [r15 + 504], r12	;Get value and Shift Right

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15
	RET

u4096_shr ENDP

u4096_and PROC

	VECAND4 rdx, r8, rcx, 0
	VECAND4 rdx, r8, rcx, 128
	VECAND4 rdx, r8, rcx, 256
	VECAND4 rdx, r8, rcx, 384

	MOV rax, rcx
	RET

u4096_and ENDP

u4096_or PROC

	VECOR4 rdx, r8, rcx, 0
	VECOR4 rdx, r8, rcx, 128
	VECOR4 rdx, r8, rcx, 256
	VECOR4 rdx, r8, rcx, 384

	MOV rax, rcx
	RET

u4096_or ENDP

u4096_xor PROC

	VECXOR4 rdx, r8, rcx, 0
	VECXOR4 rdx, r8, rcx, 128
	VECXOR4 rdx, r8, rcx, 256
	VECXOR4 rdx, r8, rcx, 384

	MOV rax, rcx
	RET

u4096_xor ENDP

u4096_not PROC

	NOT32 r12, rdx, rcx, 0
	NOT32 r12, rdx, rcx, 232

	MOV rax, rcx
	RET

u4096_not ENDP

END