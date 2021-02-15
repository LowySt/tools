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

MOVREL16O MACRO reg1, reg2, reg3, off

MOVREL8O reg1, reg2, reg3, off
MOVREL8O reg1, reg2, reg3, off + 64

ENDM

MOVREL32O MACRO reg1, reg2, reg3, off

MOVREL16O reg1, reg2, reg3, off
MOVREL16O reg1, reg2, reg3, off + 128

ENDM

MOVREL64O MACRO reg1, reg2, reg3, off

MOVREL32O reg1, reg2, reg3, off
MOVREL32O reg1, reg2, reg3, off + 256

ENDM

MOVREL16 MACRO reg1, reg2, reg3

MOVREL8O reg1, reg2, reg3, 0
MOVREL8O reg1, reg2, reg3, 64

ENDM

MOVREL32 MACRO reg1, reg2, reg3

MOVREL16O reg1, reg2, reg3, 0
MOVREL16O reg1, reg2, reg3, 128

ENDM

MOVREL64 MACRO reg1, reg2, reg3

MOVREL32O reg1, reg2, reg3, 0
MOVREL32O reg1, reg2, reg3, 256

ENDM

MOVREL128 MACRO reg1, reg2, reg3

MOVREL64O reg1, reg2, reg3, 0
MOVREL64O reg1, reg2, reg3, 512

ENDM

MOVREL256 MACRO reg1, reg2, reg3

MOVREL64O reg1, reg2, reg3, 0
MOVREL64O reg1, reg2, reg3, 512
MOVREL64O reg1, reg2, reg3, 1024
MOVREL64O reg1, reg2, reg3, 1536

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

ADC16 MACRO reg1, off

ADC8 reg1, off
ADC8 reg1, off + 64

ENDM

ADC32 MACRO reg1, off

ADC16 reg1, off
ADC16 reg1, off + 128

ENDM

ADC64 MACRO reg1, off

ADC32 reg1, off
ADC32 reg1, off + 256

ENDM

ADD16 MACRO reg1, reg2

ADD8 reg1, reg2
ADC8 reg1, 64

ENDM

ADD32 MACRO reg1, reg2

ADD8 reg1, reg2
ADC16 reg1, 64
ADC8 reg1, 192

ENDM

ADD64 MACRO reg1, reg2

ADD8 reg1, reg2
ADC32 reg1, 64
ADC16 reg1, 320
ADC8 reg1, 448

ENDM

ADD128 MACRO reg1, reg2

ADD8 reg1, reg2
ADC64 reg1, 64
ADC32 reg1, 576
ADC16 reg1, 832
ADC8 reg1, 960

ENDM

ADD256 MACRO reg1, reg2

ADD8 reg1, reg2
ADC64 reg1, 64
ADC64 reg1, 576
ADC64 reg1, 1088
ADC32 reg1, 1600
ADC16 reg1, 1856
ADC8 reg1, 1984

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

SBB16 MACRO reg1, off

SBB8 reg1, off
SBB8 reg1, off + 64

ENDM

SBB32 MACRO reg1, off

SBB16 reg1, off
SBB16 reg1, off + 128

ENDM

SBB64 MACRO reg1, off

SBB32 reg1, off
SBB32 reg1, off + 256

ENDM

SUB16 MACRO reg1, reg2

SUB8 reg1, reg2
SBB8 reg1, 64

ENDM

SUB32 MACRO reg1, reg2

SUB8 reg1, reg2
SBB16 reg1, 64
SBB8 reg1, 192

ENDM

SUB64 MACRO reg1, reg2

SUB8 reg1, reg2
SBB32 reg1, 64
SBB16 reg1, 320
SBB8 reg1, 448

ENDM

SUB128 MACRO reg1, reg2

SUB8 reg1, reg2
SBB64 reg1, 64
SBB32 reg1, 576
SBB16 reg1, 832
SBB8 reg1, 960

ENDM

SUB256 MACRO reg1, reg2

SUB8 reg1, reg2
SBB64 reg1, 64
SBB64 reg1, 576
SBB64 reg1, 1088
SBB32 reg1, 1600
SBB16 reg1, 1856
SBB8 reg1, 1984

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

MOVADC16 MACRO reg1, reg2, addreg, off

MOVADC8 reg1, reg2, addreg, off
MOVADC8 reg1, reg2, addreg, off + 64

ENDM

MOVADC32 MACRO reg1, reg2, addreg, off

MOVADC16 reg1, reg2, addreg, off
MOVADC16 reg1, reg2, addreg, off + 128

ENDM

MOVADC64 MACRO reg1, reg2, addreg, off

MOVADC32 reg1, reg2, addreg, off
MOVADC32 reg1, reg2, addreg, off + 256

ENDM

MOVADD16 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC8 reg1, reg2, addreg, 64

ENDM

MOVADD32 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC16 reg1, reg2, addreg, 64
MOVADC8 reg1, reg2, addreg, 192

ENDM

MOVADD64 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC32 reg1, reg2, addreg, 64
MOVADC16 reg1, reg2, addreg, 320
MOVADC8 reg1, reg2, addreg, 448

ENDM

MOVADD128 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC64 reg1, reg2, addreg, 64
MOVADC32 reg1, reg2, addreg, 576
MOVADC16 reg1, reg2, addreg, 832
MOVADC8 reg1, reg2, addreg, 960

ENDM

MOVADD256 MACRO reg1, reg2, addreg

MOVADD8 reg1, reg2, addreg
MOVADC64 reg1, reg2, addreg, 64
MOVADC64 reg1, reg2, addreg, 576
MOVADC64 reg1, reg2, addreg, 1088
MOVADC32 reg1, reg2, addreg, 1600
MOVADC16 reg1, reg2, addreg, 1856
MOVADC8 reg1, reg2, addreg, 1984

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

MOVSBB16 MACRO reg1, reg2, subreg, off

MOVSBB8 reg1, reg2, subreg, off
MOVSBB8 reg1, reg2, subreg, off + 64

ENDM

MOVSBB32 MACRO reg1, reg2, subreg, off

MOVSBB16 reg1, reg2, subreg, off
MOVSBB16 reg1, reg2, subreg, off + 128

ENDM

MOVSBB64 MACRO reg1, reg2, subreg, off

MOVSBB32 reg1, reg2, subreg, off
MOVSBB32 reg1, reg2, subreg, off + 256

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
MOVSBB16 reg1, reg2, subreg, 64
MOVSBB8 reg1, reg2, subreg, 192

ENDM

MOVSUB64 MACRO reg1, reg2, subreg

MOVSUB8 reg1, reg2, subreg
MOVSBB32 reg1, reg2, subreg, 64
MOVSBB16 reg1, reg2, subreg, 320
MOVSBB8 reg1, reg2, subreg, 448

ENDM

MOVSUB128 MACRO reg1, reg2, subreg

MOVSUB8 reg1, reg2, subreg
MOVSBB64 reg1, reg2, subreg, 64
MOVSBB32 reg1, reg2, subreg, 576
MOVSBB16 reg1, reg2, subreg, 832
MOVSBB8 reg1, reg2, subreg, 960

ENDM

MOVSUB256 MACRO reg1, reg2, subreg

MOVSUB8 reg1, reg2, subreg
MOVSBB64 reg1, reg2, subreg, 64
MOVSBB64 reg1, reg2, subreg, 576
MOVSBB64 reg1, reg2, subreg, 1088
MOVSBB32 reg1, reg2, subreg, 1600
MOVSBB16 reg1, reg2, subreg, 1856
MOVSBB8 reg1, reg2, subreg, 1984

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

AACMP MACRO dest1, dest2, src, popreg

ADD dest1, src
ADC popreg, 0
MOV dest2, popreg
POP popreg

ENDM

AACAP MACRO dest1, dest2, src, popreg

ADD dest1, src
ADC dest2, 0
ADD dest2, popreg
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

ZERO128 MACRO reg, off

ZERO64 reg, 0 + off
ZERO64 reg, 512 + off

ENDM

ZERO256 MACRO reg, off

ZERO128 reg, 0 + off
ZERO128 reg, 1024 + off

ENDM


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

BSRFOUND8 MACRO reg1, reg2, src, off

BSRFOUND4 reg1, reg2, src, off + 32
BSRFOUND4 reg1, reg2, src, off

ENDM

BSRFOUND16 MACRO reg1, reg2, src, off

BSRFOUND8 reg1, reg2, src, off + 64
BSRFOUND8 reg1, reg2, src, off

ENDM

BSRFOUND32 MACRO reg1, reg2, src, off

BSRFOUND16 reg1, reg2, src, off + 128
BSRFOUND16 reg1, reg2, src, off

ENDM

BSRFOUND64 MACRO reg1, reg2, src, off

BSRFOUND32 reg1, reg2, src, off + 256
BSRFOUND32 reg1, reg2, src, off

ENDM



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

GOE8 MACRO reg1, remainder, divisor, off

GOE4 reg1, remainder, divisor, off + 32
GOE4 reg1, remainder, divisor, off

ENDM

GOE16 MACRO reg1, remainder, divisor, off

GOE8 reg1, remainder, divisor, off + 64
GOE8 reg1, remainder, divisor, off

ENDM


GOE32 MACRO reg1, remainder, divisor, off

GOE16 reg1, remainder, divisor, off + 128
GOE16 reg1, remainder, divisor, off

ENDM

GOE64 MACRO reg1, remainder, divisor, off

GOE32 reg1, remainder, divisor, off + 256
GOE32 reg1, remainder, divisor, off

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

SHLBLCK16 MACRO shiftreg, reg2, reg3, off1, off2

SHLBLCK8 shiftreg, reg2, reg3, off1, off2
SHLBLCK8 shiftreg, reg2, reg3, off1 - 64, off2 - 64

ENDM

SHLBLCK32 MACRO shiftreg, reg2, reg3, off1, off2

SHLBLCK16 shiftreg, reg2, reg3, off1, off2
SHLBLCK16 shiftreg, reg2, reg3, off1 - 128, off2 - 128

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
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 + 8, off2 + 8
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 + 16, off2 + 16
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 + 24, off2 + 24
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 + 32, off2 + 32
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 + 40, off2 + 40
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 + 48, off2 + 48
SHRBLCK shiftreg1, shiftreg2, reg2, reg3, off1 + 56, off2 + 56

ENDM

SHRBLCK16 MACRO shiftreg1, shiftreg2, reg2, reg3, off1, off2

SHRBLCK8 shiftreg1, shiftreg2, reg2, reg3, off1, off2
SHRBLCK8 shiftreg1, shiftreg2, reg2, reg3, off1 + 64, off2 + 64

ENDM

SHRBLCK32 MACRO shiftreg1, shiftreg2, reg2, reg3, off1, off2

SHRBLCK16 shiftreg1, shiftreg2, reg2, reg3, off1, off2
SHRBLCK16 shiftreg1, shiftreg2, reg2, reg3, off1 + 128, off2 + 128

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

MULBLCK16 MACRO reg1, pushreg, mulreg, dest1, dest2, offset

MULBLCK8 reg1, pushreg, mulreg, dest1, dest2, offset
MULBLCK8 reg1, pushreg, mulreg, dest2, dest1, offset - 64

ENDM

MULBLCK32 MACRO reg1, pushreg, mulreg, dest1, dest2, offset

MULBLCK16 reg1, pushreg, mulreg, dest1, dest2, offset
MULBLCK16 reg1, pushreg, mulreg, dest2, dest1, offset - 128

ENDM

MULBLCK64 MACRO reg1, pushreg, mulreg, dest1, dest2, offset

MULBLCK32 reg1, pushreg, mulreg, dest1, dest2, offset
MULBLCK32 reg1, pushreg, mulreg, dest2, dest1, offset - 256

ENDM

MULBIGONCE MACRO reg1, reg2, reg3, reg4, reg5, off

MPM2 reg1, reg2, off, reg3, 0
AACP2 reg4, reg5, reg1, reg2

ENDM

MULBIGTWICE MACRO reg1, reg2, reg3, reg4, reg5, off

MPM2 reg1, reg2, off - 8, reg3, 8
AACP2 reg4, reg5, reg1, reg2

MPM2 reg1, reg2, off, reg3, 0
AACP2 reg4, reg5, reg1, reg2

ENDM

MULBIGTHRICE MACRO reg1, reg2, reg3, reg4, reg5, off

MPM2 reg1, reg2, off - 16, reg3, 16
AACP2 reg4, reg5, reg1, reg2

MPM2 reg1, reg2, off - 8, reg3, 8
AACP2 reg4, reg5, reg1, reg2

MPM2 reg1, reg2, off, reg3, 0
AACP2 reg4, reg5, reg1, reg2

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

MULBIGBLCK2 MACRO reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff 

MPM2 reg1, pushreg, pushOff, mulreg, mulOff
AACAP reg2, reg3, reg1, pushreg

MPM2 reg1, pushreg, pushOff + 8, mulreg, mulOff - 8
AACAP reg2, reg3, reg1, pushreg

MPM2 reg1, pushreg, pushOff + 16, mulreg, mulOff - 16
AACAP reg2, reg3, reg1, pushreg

MPM2 reg1, pushreg, pushOff + 24, mulreg, mulOff - 24
AACAP reg2, reg3, reg1, pushreg

ENDM

MULBIGBLCK4 MACRO reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff

MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff
MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff + 32, mulreg, mulOff - 32
MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff + 64, mulreg, mulOff - 64
MULBIGBLCK reg1, reg2, reg3, pushreg, pushOff + 96, mulreg, mulOff - 96

ENDM

MULBIGBLCK8 MACRO reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff

MULBIGBLCK4 reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff
MULBIGBLCK4 reg1, reg2, reg3, pushreg, pushOff + 128, mulreg, mulOff - 128

ENDM

MULBIGBLCK16 MACRO reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff

MULBIGBLCK8 reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff
MULBIGBLCK8 reg1, reg2, reg3, pushreg, pushOff + 256, mulreg, mulOff - 256

ENDM

MULBIGBLCK32 MACRO reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff

MULBIGBLCK16 reg1, reg2, reg3, pushreg, pushOff, mulreg, mulOff
MULBIGBLCK16 reg1, reg2, reg3, pushreg, pushOff + 512, mulreg, mulOff - 512

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

NOT16 MACRO reg1, reg2, reg3, off

NOT4 reg1, reg2, reg3, off
NOT4 reg1, reg2, reg3, off + 32
NOT4 reg1, reg2, reg3, off + 64
NOT4 reg1, reg2, reg3, off + 96

ENDM

NOT32 MACRO reg1, reg2, reg3, off

NOT16 reg1, reg2, reg3, off
NOT16 reg1, reg2, reg3, off + 128

ENDM

NOT64 MACRO reg1, reg2, reg3, off

NOT32 reg1, reg2, reg3, off
NOT32 reg1, reg2, reg3, off + 256

ENDM

NOT128 MACRO reg1, reg2, reg3, off

NOT64 reg1, reg2, reg3, off
NOT64 reg1, reg2, reg3, off + 512

ENDM

NOT256 MACRO reg1, reg2, reg3, off

NOT128 reg1, reg2, reg3, off
NOT128 reg1, reg2, reg3, off + 1024

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

VECAND8 MACRO reg1, reg2, dest, off

VECAND4 reg1, reg2, dest, off
VECAND4 reg1, reg2, dest, off + 128

ENDM

VECAND16 MACRO reg1, reg2, dest, off

VECAND8 reg1, reg2, dest, off
VECAND8 reg1, reg2, dest, off + 256

ENDM

VECAND32 MACRO reg1, reg2, dest, off

VECAND16 reg1, reg2, dest, off
VECAND16 reg1, reg2, dest, off + 512

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

VECOR8 MACRO reg1, reg2, dest, off

VECOR4 reg1, reg2, dest, off
VECOR4 reg1, reg2, dest, off + 128

ENDM

VECOR16 MACRO reg1, reg2, dest, off

VECOR8 reg1, reg2, dest, off
VECOR8 reg1, reg2, dest, off + 256

ENDM

VECOR32 MACRO reg1, reg2, dest, off

VECOR16 reg1, reg2, dest, off
VECOR16 reg1, reg2, dest, off + 512

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

VECXOR8 MACRO reg1, reg2, dest, off

VECXOR4 reg1, reg2, dest, off
VECXOR4 reg1, reg2, dest, off + 128

ENDM

VECXOR16 MACRO reg1, reg2, dest, off

VECXOR8 reg1, reg2, dest, off
VECXOR8 reg1, reg2, dest, off + 256

ENDM

VECXOR32 MACRO reg1, reg2, dest, off

VECXOR16 reg1, reg2, dest, off
VECXOR16 reg1, reg2, dest, off + 512

ENDM

;
;
;	U128 OPERATIONS START HERE
;
;

u128_add PROC

	PUSH r12

	MOVREL r12, rdx, rcx, 0	 ;mov low part of first param to return value into rcx
	MOVREL r12, rdx, rcx, 8	 ;mov high part of u128 return value into rcx

	ADD qword ptr [rcx], r8	 ;add second u64 param into low part.
	ADC qword ptr [rcx + 8], 0  ;if overflowed we advance the high part by the carry

	POP r12
	MOV rax, rcx
	RET
u128_add ENDP

u128_addBig PROC

	PUSH r12

	MOVREL r12, rdx, rcx, 0    ;mov low part of first param to return value into rcx
	MOVREL r12, rdx, rcx, 8	;mov high part of u128 return value into rcx

	MOVADD r12, r8, rcx, 0	 ;add second u128 low part param into low part
	MOVADC r12, r8, rcx, 8	 ;if overflowed we advance the high part by the carry
	
	POP r12
	MOV rax, rcx
	RET
u128_addBig ENDP

u128_sub PROC

	PUSH r12	

	MOVREL r12, rdx, rcx, 0	;mov low part of first param to return value into rcx
	MOVREL r12, rdx, rcx, 8	;mov high part of u128 return value into rcx

	SUB qword ptr [rcx], r8	;add second u64 param into low part.
	SBB qword ptr [rcx + 8], 0 ;if overflowed we advance the high part by the carry
	
	POP r12
	MOV rax, rcx
	RET
u128_sub ENDP

u128_subBig PROC

	PUSH r12

	MOVREL r12, rdx, rcx, 0    ;mov low part of first param to return value into rcx
	MOVREL r12, rdx, rcx, 8	;mov high part of u128 return value into rcx

	MOVSUB r12, r8, rcx, 0	 ;add second u128 low part param into low part.
	MOVSBB r12, r8, rcx, 8	 ;if overflowed we advance the high part by the carry

	POP r12
	MOV rax, rcx
	RET
u128_subBig ENDP

u128_mul PROC

	PUSH r12	

	MPM rax, rdx, r8, 8		   ;mul high bytes
	MOV r12, rax				  ;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 0	       ;mul rax with r8(2° param) -> result is stored in rdx:rax
	ADD r12, rdx				  ;sum the partial result of the mul together

	MOV qword ptr [rcx + 8], r12  ;mov high bytes of mul from r12 to result in rcx+8
	MOV qword ptr [rcx], rax	  ;mov low bytes of mul from r13 to result in rcx
	POP rdx					   ;i'm done with rdx so I can pop it from the stack

	POP r12
	MOV rax, rcx
	RET
u128_mul ENDP

u128_mulBig PROC

	PUSH r13
	PUSH r14

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

	MOV r14, rax					;store low half of mul (ignore overflow)
	POP rdx

	MPM2 rax, rdx, 0, r8, 0

	ADD r14, rdx					;sum the partial result of the mul together

	;
	;Add them correctly together and return
	;

	ADD r13, r14				 ;add the partial sums

	MOV qword ptr [rcx + 8], r13 ;mov high bytes of mul from r13 to result in rcx+8
	MOV qword ptr [rcx], rax	 ;moves low bytes of mul from rax to result in rcx
	POP rdx				  	;i'm done with rdx so I can pop it from the stack

	POP r14
	POP r13
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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	;
	; I HAVE TO RESTORE THE STACK?
	;
	ADD rsp, 16
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
	OR qword ptr [r15], r14

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

	ADD rsp, 16
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
	POP r15
	POP r14
	POP r13
	POP r12	

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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u128_shl ENDP

u128_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx 
	PUSH rcx					;Need to preserve rcx reg

	MOV rcx, 0

	MOV cl, 64					
	SUB cl, r8b					

	MOV r13, qword ptr [rdx + 8]
	SAL r13, cl				 ;I save the bottom bits to shift in low bytes

	MOV cl, r8b				 ;Get amount to shift

	MSHRXM r12, rdx, r15, 0	 ;Get value and Shift Right
	MSHRXM r12, rdx, r15, 8	 ;Get value and Shift Right

	OR qword ptr [r15], r13	 ;Or in the bits coming from the low bytes

	POP rcx					 ;Get back rcx to preserve the reg

	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12

	MOV r12, qword ptr [rdx]
	NOT r12
	MOV qword ptr [rcx], r12

	MOV r12, qword ptr [rdx + 8]
	NOT r12
	MOV qword ptr [rcx + 8], r12

	POP r12

	MOV rax, rcx
	RET

u128_not ENDP

;
;
;	U256 OPERATIONS START HERE
;
;

u256_add PROC

	PUSH r12

	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24		;mov into rcx u256 param

	ADD qword ptr [rcx], r8			;add u64 param into low part.
	ADC qword ptr [rcx + 8], 0
	ADC qword ptr [rcx + 16], 0
	ADC qword ptr [rcx + 24], 0		;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u256_add ENDP

u256_addBig PROC

	PUSH r12

	MOV rax, 0
	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24   ;mov into rcx first u256 param
	
	MOVADD r12, r8, rcx, 0
	MOVADC r12, r8, rcx, 8
	MOVADC r12, r8, rcx, 16
	MOVADC r12, r8, rcx, 24	;if overflowed we advance the high part by the carry

	POP r12
	MOV rax, rcx
	RET

u256_addBig ENDP

u256_sub PROC

	PUSH r12

	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24	;mov into rcx first u256 param

	SUB qword ptr [rcx], r8			
	SBB qword ptr [rcx + 8], 0
	SBB qword ptr [rcx + 16], 0
	SBB qword ptr [rcx + 24], 0	;if overflowed we add to the high part the carry

	POP r12
	MOV rax, rcx
	RET

u256_sub ENDP

u256_subBig PROC

	PUSH r12

	MOVREL r12, rdx, rcx, 0
	MOVREL r12, rdx, rcx, 8
	MOVREL r12, rdx, rcx, 16
	MOVREL r12, rdx, rcx, 24   ;mov into rcx first u256 param

	MOVSUB r12, r8, rcx, 0
	MOVSBB r12, r8, rcx, 8
	MOVSBB r12, r8, rcx, 16
	MOVSBB r12, r8, rcx, 24	;if overflowed we advance the high part by the carry

	POP r12
	MOV rax, rcx
	RET

u256_subBig ENDP

u256_mul PROC

	PUSH r12
	PUSH r13

	MPM rax, rdx, r8, 24				  ;store low half of multiplication (ignore overflow)
	MOV r12, rax					
	POP rdx

	MPM rax, rdx, r8, 16
	ADD r12, rdx						  ;sum the partial result of the mul together
	MOV r13, rax					
	POP rdx

	MULBLCK rax, rdx, r8, r13, r12, 8 	;possible carry from (+16) part

	MPM rax, rdx, r8, 0
	AACP r12, r13, rdx               	 ;possible carry from (+8) part

	MOV qword ptr [rcx + 16], r13
	MOV qword ptr [rcx + 8], r12
	MOV qword ptr [rcx], rax

	POP r13
	POP r12

	MOV rax, rcx
	RET

u256_mul ENDP

u256_mulBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	MULBIGONCE rax, rdx, r8, r12, r13, 8
	
	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MULBIGTWICE rax, rdx, r8, r13, r12, 16

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 24

	MOV qword ptr [rcx + 24], r12

	;
	;Return
	;

	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u256_mulBig ENDP

u256_divBig PROC

	;Q := 0					-- Init quotient and remainder to zero
	;R := 0
	;for i:= n-1 .. 0 do	   -- Where n is the number of bits in N
		;R := R << 1
		;R(0) := N(i)
		;if R >= D then
			;R := R - D
			;Q(i) := 1
		;end
	;end

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	ADD rsp, 32
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
	ADD rsp, 32
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

	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u256_shl ENDP

u256_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK r13, r12, rdx, r15, 8, 0
	SHRBLCK r13, r12, rdx, r15, 16, 8
	SHRBLCK r13, r12, rdx, r15, 24, 16

	MOV cl, r8b				 ;Get amount to shift

	MSHRXM r12, rdx, r15, 24	;Get value and Shift Right

	POP rcx					 ;Get back rcx to preserve the reg
	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12

	NOT4 r12, rdx, rcx, 0

	POP r12

	MOV rax, rcx
	RET

u256_not ENDP




;
;
;	U512 OPERATIONS START HERE
;
;

u512_add PROC

	PUSH r12

	MOVREL8 r12, rdx, rcx	;mov into rcx u512 param
	ADD8 rcx, r8		 	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u512_add ENDP

u512_addBig PROC

	PUSH r12
	
	MOVREL8 r12, rdx, rcx		;mov into rcx first u512 param
	MOVADD8 r12, r8, rcx		;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u512_addBig ENDP

u512_sub PROC

	PUSH r12

	MOVREL8 r12, rdx, rcx	;mov into rcx first u512 param
	SUB8 rcx, r8			;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u512_sub ENDP

u512_subBig PROC

	PUSH r12

	MOVREL8 r12, rdx, rcx		 ;mov into rcx first u256 param
	MOVSUB8 r12, r8, rcx		;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u512_subBig ENDP

u512_mul PROC

	PUSH r12
	PUSH r13

	MPM rax, rdx, r8, 56
	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 48
	ADD r12, rdx					;sum the partial result of the mul together
	MOV r13, rax					
	POP rdx

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

	POP r13
	POP r12

	MOV rax, rcx
	RET
u512_mul ENDP

u512_mulBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	MULBIGONCE rax, rdx, r8, r12, r13, 8
	
	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MULBIGTWICE rax, rdx, r8, r13, r12, 16

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 24

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

	MULBIGONCE rax, rdx, r8, r12, r13, 40

	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 48

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 56

	MOV qword ptr [rcx + 56], r12

	;
	;Return
	;

	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	MOVREL8 r12, r15, r9

	; RESTORE STACK POINTER !?!?!?
	ADD rsp, 64

	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u512_shl ENDP

u512_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	POP r15
	POP r14
	POP r13
	POP r12

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
	
	PUSH r12

	NOT4 r12, rdx, rcx, 0
	NOT4 r12, rdx, rcx, 32

	POP r12

	MOV rax, rcx
	RET

u512_not ENDP




;
;
;	U1024 OPERATIONS START HERE
;
;

u1024_add PROC

	PUSH r12

	MOVREL16 r12, rdx, rcx	;mov into rcx u1024 param
	ADD16 rcx, r8			;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u1024_add ENDP

u1024_addBig PROC

	PUSH r12

	MOVREL16 r12, rdx, rcx	;mov into rcx first u1024 param
	MOVADD16 r12, r8, rcx	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u1024_addBig ENDP

u1024_sub PROC

	PUSH r12

	MOVREL16 r12, rdx, rcx	;mov into rcx first u512 param
	SUB16 rcx, r8			;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u1024_sub ENDP

u1024_subBig PROC

	PUSH r12

	MOVREL16 r12, rdx, rcx	;mov into rcx first u256 param
	MOVSUB16 r12, r8, rcx	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u1024_subBig ENDP

u1024_mul PROC

	PUSH r12
	PUSH r13

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

	POP r13
	POP r12

	MOV rax, rcx
	RET
u1024_mul ENDP

u1024_mulBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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
    
	MULBIGONCE rax, rdx, r8, r12, r13, 8
    	
	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MULBIGTWICE rax, rdx, r8, r13, r12, 16

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 24

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

	MULBIGONCE rax, rdx, r8, r12, r13, 40

	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 48

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 56

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

	MULBIGONCE rax, rdx, r8, r12, r13, 72

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 80

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 88

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

	MULBIGONCE rax, rdx, r8, r12, r13, 104

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 112

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 120

	MOV qword ptr [rcx + 120], r12

	;
	;Return
	;

	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	ZERO16 rcx, 0	;Initialize Quotient to 0

	SUB rsp, 128
	MOV r15, rsp
	ZERO16 r15, 0	;Initialize Remainder to 0

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
	; ENTERING CALL TO u1024_subBig
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
	; EXITED CALL TO u1024_subBig
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

	MOVREL16 r12, r15, r9

	ADD rsp, 128
	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0

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

	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u1024_shl ENDP

u1024_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	POP r15
	POP r14
	POP r13
	POP r12

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

	PUSH r12

	NOT16 r12, rdx, rcx, 0

	POP r12

	MOV rax, rcx
	RET

u1024_not ENDP

;
;
;	U2048 OPERATIONS START HERE
;
;

u2048_add PROC

	PUSH r12
	
	MOVREL32 r12, rdx, rcx	;mov into rcx u2048 param
	ADD32 rcx, r8			;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u2048_add ENDP

u2048_addBig PROC

	PUSH r12

	MOVREL32 r12, rdx, rcx	;mov into rcx first u2048 param
	MOVADD32 r12, r8, rcx	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u2048_addBig ENDP

u2048_sub PROC

	PUSH r12

	MOVREL32 r12, rdx, rcx	;mov into rcx first u2048 param
	SUB32 rcx, r8			;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u2048_sub ENDP

u2048_subBig PROC

	PUSH r12

	MOVREL32 r12, rdx, rcx	;mov into rcx first u2048 param
	MOVSUB32 r12, r8, rcx	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u2048_subBig ENDP

u2048_mul PROC

	PUSH r12
	PUSH r13

	MPM rax, rdx, r8, 248

	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 240
	ADD r12, rdx
	MOV r13, rax
	POP rdx
	
	MULBLCK16 rax, rdx, r8, r13, r12, 232
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

	POP r13
	POP r12

	MOV rax, rcx
	RET

u2048_mul ENDP

u2048_mulBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	MULBIGONCE rax, rdx, r8, r12, r13, 8
	
	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MULBIGTWICE rax, rdx, r8, r13, r12, 16

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 24

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

	MULBIGONCE rax, rdx, r8, r12, r13, 40

	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 48

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 56

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

	MULBIGONCE rax, rdx, r8, r12, r13, 72

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 80

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 88

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

	MULBIGONCE rax, rdx, r8, r12, r13, 104

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 112

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 120

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

	MULBIGONCE rax, rdx, r8, r12, r13, 136

	MOV qword ptr [rcx + 136], r12

	;
	;Execution of the 19° Column
	;

	MPM2 rax, rdx, 0, r8, 144
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 144

	MOV qword ptr [rcx + 144], r13

	;
	;Execution of the 20° Column
	;				  
	
	MPM2 rax, rdx, 0, r8, 152
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 152

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

	MULBIGONCE rax, rdx, r8, r12, r13, 168

	MOV qword ptr [rcx + 168], r12

	;				  
	;Execution of the 23° Column
	;
	
	MPM2 rax, rdx, 0, r8, 176
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 176

	MOV qword ptr [rcx + 176], r13

	;				  
	;Execution of the 24° Column
	;
	
	MPM2 rax, rdx, 0, r8, 184
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 184

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

	MULBIGONCE rax, rdx, r8, r12, r13, 200

	MOV qword ptr [rcx + 200], r12

	;
	;Execution of the 27° Column
	;
	
	MPM2 rax, rdx, 0, r8, 208
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 208

	MOV qword ptr [rcx + 208], r13

	;
	;Execution of the 28° Column
	;

	MPM2 rax, rdx, 0, r8, 216
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 216

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

	MULBIGONCE rax, rdx, r8, r12, r13, 232

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

	MULBIGTWICE rax, rdx, r8, r13, r12, 240

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

	MULBIGTHRICE rax, rdx, r8, r12, r13, 248

	MOV qword ptr [rcx + 248], r12

	;
	;Return
	;

	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u2048_mulBig ENDP

u2048_divBig PROC

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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	ZERO32 rcx, 0	;Initialize Quotient to 0

	SUB rsp, 256
	MOV r15, rsp
	ZERO32 r15, 0	;Initialize Remainder to 0

	BSRFOUND16 r12, r13, rdx, 128
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

	GOE16 r13, r15, r8, 128
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
	; ENTERING CALL TO u2048_subBig
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
	; EXITED CALL TO u1024_subBig
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

	ADD rsp, 256
	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET


u2048_divBig ENDP

u2048_inc PROC

	ADD qword ptr [rcx], 1
	ADC16 rcx, 8
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
	SBB16 rcx, 8
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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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
	SHLBLCK16 r13, rdx, r15, 232, 240
	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u2048_shl ENDP

u2048_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK16 r13, r12, rdx, r15, 8, 0
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

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u2048_shr ENDP

u2048_and PROC

	VECAND8 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u2048_and ENDP

u2048_or PROC

	VECOR8 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u2048_or ENDP

u2048_xor PROC

	VECXOR8 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u2048_xor ENDP

u2048_not PROC

	PUSH r12

	NOT32 r12, rdx, rcx, 0

	POP r12

	MOV rax, rcx
	RET

u2048_not ENDP

;
;
;	U4096 OPERATIONS START HERE
;
;

u4096_add PROC

	PUSH r12

	MOVREL64 r12, rdx, rcx	;mov into rcx u2048 param
	ADD64 rcx, r8			 ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u4096_add ENDP

u4096_addBig PROC

	PUSH r12

	MOVREL64 r12, rdx, rcx	;mov into rcx first u2048 param
	MOVADD64 r12, r8, rcx	 ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u4096_addBig ENDP

u4096_sub PROC

	PUSH r12

	MOVREL64 r12, rdx, rcx	;mov into rcx first u512 param
	SUB64 rcx, r8			 ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u4096_sub ENDP

u4096_subBig PROC

	PUSH r12

	MOVREL64 r12, rdx, rcx	;mov into rcx first u256 param
	MOVSUB64 r12, r8, rcx	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u4096_subBig ENDP

u4096_mul PROC

	PUSH r12
	PUSH r13

	MPM rax, rdx, r8, 504
	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 496
	ADD r12, rdx
	MOV r13, rax
	POP rdx

	MULBLCK32 rax, rdx, r8, r13, r12, 488
	MULBLCK16 rax, rdx, r8, r13, r12, 232
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

	POP r13
	POP r12

	MOV rax, rcx
	RET

u4096_mul ENDP

u4096_mulBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	MULBIGONCE rax, rdx, r8, r12, r13, 8
	
	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MULBIGTWICE rax, rdx, r8, r13, r12, 16

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 24

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

	MULBIGONCE rax, rdx, r8, r12, r13, 40

	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 48

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 56

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

	MULBIGONCE rax, rdx, r8, r12, r13, 72

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 80

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 88

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

	MULBIGONCE rax, rdx, r8, r12, r13, 104

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 112

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 120

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

	MULBIGONCE rax, rdx, r8, r12, r13, 136

	MOV qword ptr [rcx + 136], r12

	;
	;Execution of the 19° Column
	;

	MPM2 rax, rdx, 0, r8, 144
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 144

	MOV qword ptr [rcx + 144], r13

	;
	;Execution of the 20° Column
	;				  
	
	MPM2 rax, rdx, 0, r8, 152
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 152

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

	MULBIGONCE rax, rdx, r8, r12, r13, 168

	MOV qword ptr [rcx + 168], r12

	;				  
	;Execution of the 23° Column
	;
	
	MPM2 rax, rdx, 0, r8, 176
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 176

	MOV qword ptr [rcx + 176], r13

	;				  
	;Execution of the 24° Column
	;
	
	MPM2 rax, rdx, 0, r8, 184
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 184

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

	MULBIGONCE rax, rdx, r8, r12, r13, 200

	MOV qword ptr [rcx + 200], r12

	;
	;Execution of the 27° Column
	;
	
	MPM2 rax, rdx, 0, r8, 208
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 208

	MOV qword ptr [rcx + 208], r13

	;
	;Execution of the 28° Column
	;

	MPM2 rax, rdx, 0, r8, 216
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 216

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

	MULBIGONCE rax, rdx, r8, r12, r13, 232

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

	MULBIGTWICE rax, rdx, r8, r13, r12, 240

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

	MULBIGTHRICE rax, rdx, r8, r12, r13, 248

	MOV qword ptr [rcx + 248], r12

	;
	;Execution of the 33° Column
	;

	MPM2 rax, rdx, 0, r8, 256
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 248

	MOV qword ptr [rcx + 256], r13

	;
	;Execution of the 34° Column
	;

	MPM2 rax, rdx, 0, r8, 264
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 256
	
	MULBIGONCE rax, rdx, r8, r12, r13, 264

	MOV qword ptr [rcx + 264], r12

	;
	;Execution of the 35° Column
	;

	MPM2 rax, rdx, 0, r8, 272
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 264

	MULBIGTWICE rax, rdx, r8, r13, r12, 272

	MOV qword ptr [rcx + 272], r13

	;
	;Execution of the 36° Column
	;

	MPM2 rax, rdx, 0, r8, 280
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 272
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 280

	MOV qword ptr [rcx + 280], r12

	;
	;Execution of the 37° Column
	;

	MPM2 rax, rdx, 0, r8, 288
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 280
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 24

	MOV qword ptr [rcx + 288], r13

	;
	;Execution of the 38° Column
	;

	MPM2 rax, rdx, 0, r8, 296
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 288
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 296

	MOV qword ptr [rcx + 296], r12

	;
	;Execution of the 39° Column
	;

	MPM2 rax, rdx, 0, r8, 304
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 296
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 304

	MOV qword ptr [rcx + 304], r13

	;
	;Execution of the 40° Column
	;

	MPM2 rax, rdx, 0, r8, 312
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 304
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 312

	MOV qword ptr [rcx + 312], r12

	;
	;Execution of the 41° Column
	;

	MPM2 rax, rdx, 0, r8, 320
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 312
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 24

	MOV qword ptr [rcx + 320], r13
	;
	;Execution of the 42° Column
	;

	MPM2 rax, rdx, 0, r8, 328
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 320
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 328

	MOV qword ptr [rcx + 328], r12
	;
	;Execution of the 43° Column
	;

	MPM2 rax, rdx, 0, r8, 336
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 328
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 336

	MOV qword ptr [rcx + 336], r13
	;
	;Execution of the 44° Column
	;

	MPM2 rax, rdx, 0, r8, 344
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 336
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 344

	MOV qword ptr [rcx + 344], r12
	;
	;Execution of the 45° Column
	;

	MPM2 rax, rdx, 0, r8, 352
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 344
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 24

	MOV qword ptr [rcx + 352], r13
	;
	;Execution of the 46° Column
	;

	MPM2 rax, rdx, 0, r8, 360
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 352
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 360

	MOV qword ptr [rcx + 360], r12
	;
	;Execution of the 47° Column
	;

	MPM2 rax, rdx, 0, r8, 368
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 360
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 368

	MOV qword ptr [rcx + 368], r13
	;
	;Execution of the 48° Column
	;

	MPM2 rax, rdx, 0, r8, 376
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 368
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 376

	MOV qword ptr [rcx + 376], r12
	;
	;Execution of the 49° Column
	;

	MPM2 rax, rdx, 0, r8, 384
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 120

	MOV qword ptr [rcx + 384], r13
	;
	;Execution of the 50° Column
	;

	MPM2 rax, rdx, 0, r8, 392
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 392

	MOV qword ptr [rcx + 392], r12
	;
	;Execution of the 51° Column
	;

	MPM2 rax, rdx, 0, r8, 400
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 400

	MOV qword ptr [rcx + 400], r13
	;
	;Execution of the 52° Column
	;

	MPM2 rax, rdx, 0, r8, 408
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 408

	MOV qword ptr [rcx + 408], r12
	;
	;Execution of the 53° Column
	;

	MPM2 rax, rdx, 0, r8, 416
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 24

	MOV qword ptr [rcx + 416], r13
	;
	;Execution of the 54° Column
	;

	MPM2 rax, rdx, 0, r8, 424
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 424

	MOV qword ptr [rcx + 424], r12
	;
	;Execution of the 55° Column
	;

	MPM2 rax, rdx, 0, r8, 432
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 432

	MOV qword ptr [rcx + 432], r13
	;
	;Execution of the 56° Column
	;

	MPM2 rax, rdx, 0, r8, 440
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 440

	MOV qword ptr [rcx + 440], r12
	;
	;Execution of the 57° Column
	;

	MPM2 rax, rdx, 0, r8, 448
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 24

	MOV qword ptr [rcx + 448], r13
	;
	;Execution of the 58° Column
	;

	MPM2 rax, rdx, 0, r8, 456
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 456

	MOV qword ptr [rcx + 456], r12
	;
	;Execution of the 59° Column
	;

	MPM2 rax, rdx, 0, r8, 464
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 464

	MOV qword ptr [rcx + 464], r13
	;
	;Execution of the 60° Column
	;

	MPM2 rax, rdx, 0, r8, 472
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 472

	MOV qword ptr [rcx + 472], r12
	;
	;Execution of the 61° Column
	;

	MPM2 rax, rdx, 0, r8, 480
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 472
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
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 488

	MOV qword ptr [rcx + 488], r12
	;
	;Execution of the 63° Column
	;

	MPM2 rax, rdx, 0, r8, 496
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 456, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 496

	MOV qword ptr [rcx + 496], r13

	;
	;Execution of the 64° Column
	;

	MPM2 rax, rdx, 0, r8, 504
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 504

	MOV qword ptr [rcx + 504], r12

	;
	;Return
	;

	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u4096_mulBig ENDP

u4096_divBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	ZERO64 rcx, 0	;Initialize Quotient to 0

	SUB rsp, 512
	MOV r15, rsp
	ZERO64 r15, 0	;Initialize Remainder to 0
	
	BSRFOUND32 r12, r13, rdx, 256
	BSRFOUND16 r12, r13, rdx, 128
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
	; ENTERING CALL TO u4096_shl
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
	; EXITED CALL TO u4096_shl
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

	GOE32 r13, r15, r8, 256
	GOE16 r13, r15, r8, 128
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
	; ENTERING CALL TO u4096_subBig
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
	; EXITED CALL TO u4096_subBig
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

	ADD rsp, 512
	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u4096_divBig ENDP

u4096_inc PROC

	ADD qword ptr [rcx], 1
	ADC32 rcx, 8
	ADC16 rcx, 264
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
	SBB32 rcx, 8
	SBB16 rcx, 264
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

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0

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

	SHLBLCK32 r13, rdx, r15, 488, 496
	SHLBLCK16 r13, rdx, r15, 232, 240
	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u4096_shl ENDP

u4096_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK32 r13, r12, rdx, r15, 8, 0
	SHRBLCK16 r13, r12, rdx, r15, 264, 256
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

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u4096_shr ENDP

u4096_and PROC

	VECAND16 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u4096_and ENDP

u4096_or PROC

	VECOR16 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u4096_or ENDP

u4096_xor PROC

	VECXOR16 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u4096_xor ENDP

u4096_not PROC

	PUSH r12

	NOT64 r12, rdx, rcx, 0

	POP r12

	MOV rax, rcx
	RET

u4096_not ENDP










;
;
;	U8192 OPERATIONS START HERE
;
;

u8192_add PROC

	PUSH r12

	MOVREL128 r12, rdx, rcx   ;mov into rcx u8192 param
	ADD128 rcx, r8		    ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u8192_add ENDP

u8192_addBig PROC

	PUSH r12

	MOVREL128 r12, rdx, rcx   ;mov into rcx first u8192 param
	MOVADD128 r12, r8, rcx	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u8192_addBig ENDP

u8192_sub PROC

	PUSH r12

	MOVREL128 r12, rdx, rcx	;mov into rcx first u8192 param
	SUB128 rcx, r8			 ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u8192_sub ENDP

u8192_subBig PROC

	PUSH r12

	MOVREL128 r12, rdx, rcx	;mov into rcx first u8192 param
	MOVSUB128 r12, r8, rcx	 ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u8192_subBig ENDP

u8192_mul PROC

	PUSH r12
	PUSH r13

	MPM rax, rdx, r8, 1016

	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 1008
	ADD r12, rdx
	MOV r13, rax
	POP rdx

	MULBLCK64 rax, rdx, r8, r13, r12, 1000
	MULBLCK32 rax, rdx, r8, r13, r12, 488
	MULBLCK16 rax, rdx, r8, r13, r12, 232
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

	POP r13
	POP r12

	MOV rax, rcx
	RET

u8192_mul ENDP

u8192_mulBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	MULBIGONCE rax, rdx, r8, r12, r13, 8
	
	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MULBIGTWICE rax, rdx, r8, r13, r12, 16

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 24

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

	MULBIGONCE rax, rdx, r8, r12, r13, 40

	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 48

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 56

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

	MULBIGONCE rax, rdx, r8, r12, r13, 72

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 80

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 88

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

	MULBIGONCE rax, rdx, r8, r12, r13, 104

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 112

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 120

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

	MULBIGONCE rax, rdx, r8, r12, r13, 136

	MOV qword ptr [rcx + 136], r12

	;
	;Execution of the 19° Column
	;

	MPM2 rax, rdx, 0, r8, 144
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 144

	MOV qword ptr [rcx + 144], r13

	;
	;Execution of the 20° Column
	;				  
	
	MPM2 rax, rdx, 0, r8, 152
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 152

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

	MULBIGONCE rax, rdx, r8, r12, r13, 168

	MOV qword ptr [rcx + 168], r12

	;				  
	;Execution of the 23° Column
	;
	
	MPM2 rax, rdx, 0, r8, 176
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 176

	MOV qword ptr [rcx + 176], r13

	;				  
	;Execution of the 24° Column
	;
	
	MPM2 rax, rdx, 0, r8, 184
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 184

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

	MULBIGONCE rax, rdx, r8, r12, r13, 200

	MOV qword ptr [rcx + 200], r12

	;
	;Execution of the 27° Column
	;
	
	MPM2 rax, rdx, 0, r8, 208
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 208

	MOV qword ptr [rcx + 208], r13

	;
	;Execution of the 28° Column
	;

	MPM2 rax, rdx, 0, r8, 216
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 216

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

	MULBIGONCE rax, rdx, r8, r12, r13, 232

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

	MULBIGTWICE rax, rdx, r8, r13, r12, 240

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

	MULBIGTHRICE rax, rdx, r8, r12, r13, 248

	MOV qword ptr [rcx + 248], r12

	;
	;Execution of the 33° Column
	;

	MPM2 rax, rdx, 0, r8, 256
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 248

	MOV qword ptr [rcx + 256], r13

	;
	;Execution of the 34° Column
	;

	MPM2 rax, rdx, 0, r8, 264
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 256
	
	MULBIGONCE rax, rdx, r8, r12, r13, 264

	MOV qword ptr [rcx + 264], r12

	;
	;Execution of the 35° Column
	;

	MPM2 rax, rdx, 0, r8, 272
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 264

	MULBIGTWICE rax, rdx, r8, r13, r12, 272

	MOV qword ptr [rcx + 272], r13

	;
	;Execution of the 36° Column
	;

	MPM2 rax, rdx, 0, r8, 280
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 272
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 280

	MOV qword ptr [rcx + 280], r12

	;
	;Execution of the 37° Column
	;

	MPM2 rax, rdx, 0, r8, 288
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 280
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 24

	MOV qword ptr [rcx + 288], r13

	;
	;Execution of the 38° Column
	;

	MPM2 rax, rdx, 0, r8, 296
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 288
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 296

	MOV qword ptr [rcx + 296], r12

	;
	;Execution of the 39° Column
	;

	MPM2 rax, rdx, 0, r8, 304
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 296
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 304

	MOV qword ptr [rcx + 304], r13

	;
	;Execution of the 40° Column
	;

	MPM2 rax, rdx, 0, r8, 312
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 304
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 312

	MOV qword ptr [rcx + 312], r12

	;
	;Execution of the 41° Column
	;

	MPM2 rax, rdx, 0, r8, 320
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 312
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 24

	MOV qword ptr [rcx + 320], r13
	;
	;Execution of the 42° Column
	;

	MPM2 rax, rdx, 0, r8, 328
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 320
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 328

	MOV qword ptr [rcx + 328], r12
	;
	;Execution of the 43° Column
	;

	MPM2 rax, rdx, 0, r8, 336
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 328
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 336

	MOV qword ptr [rcx + 336], r13
	;
	;Execution of the 44° Column
	;

	MPM2 rax, rdx, 0, r8, 344
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 336
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 344

	MOV qword ptr [rcx + 344], r12
	;
	;Execution of the 45° Column
	;

	MPM2 rax, rdx, 0, r8, 352
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 344
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 24

	MOV qword ptr [rcx + 352], r13
	;
	;Execution of the 46° Column
	;

	MPM2 rax, rdx, 0, r8, 360
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 352
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 360

	MOV qword ptr [rcx + 360], r12
	;
	;Execution of the 47° Column
	;

	MPM2 rax, rdx, 0, r8, 368
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 360
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 368

	MOV qword ptr [rcx + 368], r13
	;
	;Execution of the 48° Column
	;

	MPM2 rax, rdx, 0, r8, 376
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 368
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 376

	MOV qword ptr [rcx + 376], r12
	;
	;Execution of the 49° Column
	;

	MPM2 rax, rdx, 0, r8, 384
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 120

	MOV qword ptr [rcx + 384], r13
	;
	;Execution of the 50° Column
	;

	MPM2 rax, rdx, 0, r8, 392
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 392

	MOV qword ptr [rcx + 392], r12
	;
	;Execution of the 51° Column
	;

	MPM2 rax, rdx, 0, r8, 400
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 400

	MOV qword ptr [rcx + 400], r13
	;
	;Execution of the 52° Column
	;

	MPM2 rax, rdx, 0, r8, 408
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 408

	MOV qword ptr [rcx + 408], r12
	;
	;Execution of the 53° Column
	;

	MPM2 rax, rdx, 0, r8, 416
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 24

	MOV qword ptr [rcx + 416], r13
	;
	;Execution of the 54° Column
	;

	MPM2 rax, rdx, 0, r8, 424
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 424

	MOV qword ptr [rcx + 424], r12
	;
	;Execution of the 55° Column
	;

	MPM2 rax, rdx, 0, r8, 432
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 432

	MOV qword ptr [rcx + 432], r13
	;
	;Execution of the 56° Column
	;

	MPM2 rax, rdx, 0, r8, 440
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 440

	MOV qword ptr [rcx + 440], r12
	;
	;Execution of the 57° Column
	;

	MPM2 rax, rdx, 0, r8, 448
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 24

	MOV qword ptr [rcx + 448], r13
	;
	;Execution of the 58° Column
	;

	MPM2 rax, rdx, 0, r8, 456
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 456

	MOV qword ptr [rcx + 456], r12
	;
	;Execution of the 59° Column
	;

	MPM2 rax, rdx, 0, r8, 464
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 464

	MOV qword ptr [rcx + 464], r13
	;
	;Execution of the 60° Column
	;

	MPM2 rax, rdx, 0, r8, 472
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 472

	MOV qword ptr [rcx + 472], r12
	;
	;Execution of the 61° Column
	;

	MPM2 rax, rdx, 0, r8, 480
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 472
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
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 488

	MOV qword ptr [rcx + 488], r12
	;
	;Execution of the 63° Column
	;

	MPM2 rax, rdx, 0, r8, 496
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 456, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 496

	MOV qword ptr [rcx + 496], r13

	;
	;Execution of the 64° Column
	;

	MPM2 rax, rdx, 0, r8, 504
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 504

	MOV qword ptr [rcx + 504], r12

	;
	;Execution of the 65° Column
	;

	MPM2 rax, rdx, 0, r8, 512
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 504

	MOV qword ptr [rcx + 512], r13

	;
	;Execution of the 66° Column
	;

	MPM2 rax, rdx, 0, r8, 520
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 512

	MULBIGONCE rax, rdx, r8, r12, r13, 520

	MOV qword ptr [rcx + 520], r12

	;
	;Execution of the 67° Column
	;

	MPM2 rax, rdx, 0, r8, 528
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 520

	MULBIGTWICE rax, rdx, r8, r13, r12, 528

	MOV qword ptr [rcx + 528], r13

	;
	;Execution of the 68° Column
	;

	MPM2 rax, rdx, 0, r8, 536
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 528

	MULBIGTHRICE rax, rdx, r8, r12, r13, 536

	MOV qword ptr [rcx + 536], r12

	;
	;Execution of the 69° Column
	;

	MPM2 rax, rdx, 0, r8, 544
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 536
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 24

	MOV qword ptr [rcx + 544], r13

	;
	;Execution of the 70° Column
	;

	MPM2 rax, rdx, 0, r8, 552
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 544
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 552

	MOV qword ptr [rcx + 552], r12

	;
	;Execution of the 71° Column
	;

	MPM2 rax, rdx, 0, r8, 560
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 552
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 560

	MOV qword ptr [rcx + 560], r13

	;
	;Execution of the 72° Column
	;

	MPM2 rax, rdx, 0, r8, 568
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 560
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 568

	MOV qword ptr [rcx + 568], r12

	;
	;Execution of the 73° Column
	;

	MPM2 rax, rdx, 0, r8, 576
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 568
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 24

	MOV qword ptr [rcx + 576], r13

	;
	;Execution of the 74° Column
	;

	MPM2 rax, rdx, 0, r8, 584
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 576
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 584

	MOV qword ptr [rcx + 584], r12

	;
	;Execution of the 75° Column
	;

	MPM2 rax, rdx, 0, r8, 592
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 584
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 592

	MOV qword ptr [rcx + 592], r13

	;
	;Execution of the 76° Column
	;

	MPM2 rax, rdx, 0, r8, 600
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 592
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 600

	MOV qword ptr [rcx + 600], r12

	;
	;Execution of the 77° Column
	;

	MPM2 rax, rdx, 0, r8, 608
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 600
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 584, r8, 24

	MOV qword ptr [rcx + 608], r13

	;
	;Execution of the 78° Column
	;

	MPM2 rax, rdx, 0, r8, 616
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 608
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 584, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 616

	MOV qword ptr [rcx + 616], r12

	;
	;Execution of the 79° Column
	;

	MPM2 rax, rdx, 0, r8, 624
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 616
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 584, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 624

	MOV qword ptr [rcx + 624], r13

	;
	;Execution of the 80° Column
	;

	MPM2 rax, rdx, 0, r8, 632
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 624
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 584, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 632

	MOV qword ptr [rcx + 632], r12

	;
	;Execution of the 81° Column
	;

	MPM2 rax, rdx, 0, r8, 640
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 632
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 120

	MOV qword ptr [rcx + 640], r13

	;
	;Execution of the 82° Column
	;

	MPM2 rax, rdx, 0, r8, 648
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 640
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 648

	MOV qword ptr [rcx + 648], r12

	;
	;Execution of the 83° Column
	;

	MPM2 rax, rdx, 0, r8, 656
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 648
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 656

	MOV qword ptr [rcx + 656], r13

	;
	;Execution of the 84° Column
	;

	MPM2 rax, rdx, 0, r8, 664
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 656
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 664

	MOV qword ptr [rcx + 664], r12

	;
	;Execution of the 85° Column
	;

	MPM2 rax, rdx, 0, r8, 672
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 664
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 24

	MOV qword ptr [rcx + 672], r13

	;
	;Execution of the 86° Column
	;

	MPM2 rax, rdx, 0, r8, 680
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 672
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 680

	MOV qword ptr [rcx + 680], r12

	;
	;Execution of the 87° Column
	;

	MPM2 rax, rdx, 0, r8, 688
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 680
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 32

	MULBIGTWICE rax, rdx, r8, r13, r12, 688

	MOV qword ptr [rcx + 688], r13

	;
	;Execution of the 88° Column
	;

	MPM2 rax, rdx, 0, r8, 696
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 688
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 40

	MULBIGTHRICE rax, rdx, r8, r12, r13, 696

	MOV qword ptr [rcx + 696], r12

	;
	;Execution of the 89° Column
	;

	MPM2 rax, rdx, 0, r8, 704
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 696
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 48
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 24

	MOV qword ptr [rcx + 704], r13

	;
	;Execution of the 90° Column
	;

	MPM2 rax, rdx, 0, r8, 712
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 704
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 56
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 712

	MOV qword ptr [rcx + 712], r12

	;
	;Execution of the 91° Column
	;

	MPM2 rax, rdx, 0, r8, 720
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 712
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 64
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 720

	MOV qword ptr [rcx + 720], r13

	;
	;Execution of the 92° Column
	;

	MPM2 rax, rdx, 0, r8, 728
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 720
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 72
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 728

	MOV qword ptr [rcx + 728], r12

	;
	;Execution of the 93° Column
	;

	MPM2 rax, rdx, 0, r8, 736
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 728
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 80
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 712, r8, 24

	MOV qword ptr [rcx + 736], r13

	;
	;Execution of the 94° Column
	;

	MPM2 rax, rdx, 0, r8, 744
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 736
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 88
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 712, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 744

	MOV qword ptr [rcx + 744], r12

	;
	;Execution of the 95° Column
	;

	MPM2 rax, rdx, 0, r8, 752
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 744
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 96
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 712, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 752

	MOV qword ptr [rcx + 752], r13

	;
	;Execution of the 96° Column
	;

	MPM2 rax, rdx, 0, r8, 760
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 752
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 104
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 712, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 760

	MOV qword ptr [rcx + 760], r12

	;
	;Execution of the 97° Column
	;

	MPM2 rax, rdx, 0, r8, 768
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 760
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 248

	MOV qword ptr [rcx + 768], r13

	;
	;Execution of the 98° Column
	;

	MPM2 rax, rdx, 0, r8, 776
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 768
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 256

	MULBIGONCE rax, rdx, r8, r12, r13, 776

	MOV qword ptr [rcx + 776], r12

	;
	;Execution of the 99° Column
	;

	MPM2 rax, rdx, 0, r8, 784
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 776
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 264

	MULBIGTWICE rax, rdx, r8, r13, r12, 784

	MOV qword ptr [rcx + 784], r13

	;
	;Execution of the 100° Column
	;

	MPM2 rax, rdx, 0, r8, 792
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 784
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 272

	MULBIGTHRICE rax, rdx, r8, r12, r13, 792

	MOV qword ptr [rcx + 792], r12

	;
	;Execution of the 101° Column
	;

	MPM2 rax, rdx, 0, r8, 800
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 792
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 280
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 24

	MOV qword ptr [rcx + 800], r13

	;
	;Execution of the 102° Column
	;

	MPM2 rax, rdx, 0, r8, 808
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 800
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 288
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 808

	MOV qword ptr [rcx + 808], r12

	;
	;Execution of the 103° Column
	;

	MPM2 rax, rdx, 0, r8, 816
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 808
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 296
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 816

	MOV qword ptr [rcx + 816], r13

	;
	;Execution of the 104° Column
	;

	MPM2 rax, rdx, 0, r8, 824
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 816
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 304
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 824

	MOV qword ptr [rcx + 824], r12

	;
	;Execution of the 105° Column
	;

	MPM2 rax, rdx, 0, r8, 832
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 824
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 312
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 24

	MOV qword ptr [rcx + 832], r13

	;
	;Execution of the 106° Column
	;

	MPM2 rax, rdx, 0, r8, 840
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 832
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 320
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 840

	MOV qword ptr [rcx + 840], r12

	;
	;Execution of the 107° Column
	;

	MPM2 rax, rdx, 0, r8, 848
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 840
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 328
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 848

	MOV qword ptr [rcx + 848], r13

	;
	;Execution of the 108° Column
	;

	MPM2 rax, rdx, 0, r8, 856
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 848
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 336
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 856

	MOV qword ptr [rcx + 856], r12

	;
	;Execution of the 109° Column
	;

	MPM2 rax, rdx, 0, r8, 864
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 856
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 344
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 840, r8, 24

	MOV qword ptr [rcx + 864], r13

	;
	;Execution of the 110° Column
	;

	MPM2 rax, rdx, 0, r8, 872
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 864
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 352
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 840, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 872

	MOV qword ptr [rcx + 872], r12

	;
	;Execution of the 111° Column
	;

	MPM2 rax, rdx, 0, r8, 880
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 872
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 360
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 840, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 880

	MOV qword ptr [rcx + 880], r13

	;
	;Execution of the 112° Column
	;

	MPM2 rax, rdx, 0, r8, 888
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 880
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 368
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 840, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 888

	MOV qword ptr [rcx + 888], r12

	;
	;Execution of the 113° Column
	;

	MPM2 rax, rdx, 0, r8, 896
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 888
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 120

	MOV qword ptr [rcx + 896], r13

	;
	;Execution of the 114° Column
	;

	MPM2 rax, rdx, 0, r8, 904
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 896
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 904

	MOV qword ptr [rcx + 904], r12

	;
	;Execution of the 115° Column
	;

	MPM2 rax, rdx, 0, r8, 912
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 904
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 912

	MOV qword ptr [rcx + 912], r13

	;
	;Execution of the 116° Column
	;

	MPM2 rax, rdx, 0, r8, 920
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 912
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 920

	MOV qword ptr [rcx + 920], r12

	;
	;Execution of the 117° Column
	;

	MPM2 rax, rdx, 0, r8, 928
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 920
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 24

	MOV qword ptr [rcx + 928], r13

	;
	;Execution of the 118° Column
	;

	MPM2 rax, rdx, 0, r8, 936
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 928
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 936

	MOV qword ptr [rcx + 936], r12

	;
	;Execution of the 119° Column
	;

	MPM2 rax, rdx, 0, r8, 944
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 936
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 944

	MOV qword ptr [rcx + 944], r13

	;
	;Execution of the 120° Column
	;

	MPM2 rax, rdx, 0, r8, 952
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 944
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 952

	MOV qword ptr [rcx + 952], r12

	;
	;Execution of the 121° Column
	;

	MPM2 rax, rdx, 0, r8, 960
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 952
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 24

	MOV qword ptr [rcx + 960], r13

	;
	;Execution of the 122° Column
	;

	MPM2 rax, rdx, 0, r8, 968
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 960
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 968

	MOV qword ptr [rcx + 968], r12

	;
	;Execution of the 123° Column
	;

	MPM2 rax, rdx, 0, r8, 976
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 968
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 976

	MOV qword ptr [rcx + 976], r13

	;
	;Execution of the 124° Column
	;

	MPM2 rax, rdx, 0, r8, 984
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 976
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 984

	MOV qword ptr [rcx + 984], r12

	;
	;Execution of the 125° Column
	;

	MPM2 rax, rdx, 0, r8, 992
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 984
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 472
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 968, r8, 24

	MOV qword ptr [rcx + 992], r13

	;
	;Execution of the 126° Column
	;

	MPM2 rax, rdx, 0, r8, 1000
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 992
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 968, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1000

	MOV qword ptr [rcx + 1000], r12

	;
	;Execution of the 127° Column
	;

	MPM2 rax, rdx, 0, r8, 1008
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 1000
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 968, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1008

	MOV qword ptr [rcx + 1008], r13

	;
	;Execution of the 128° Column
	;

	MPM2 rax, rdx, 0, r8, 1016
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 1008
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 968, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1016

	MOV qword ptr [rcx + 1016], r12

	;
	;Return
	;

	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u8192_mulBig ENDP

u8192_divBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	ZERO128 rcx, 0	;Initialize Quotient to 0

	SUB rsp, 1024
	MOV r15, rsp
	ZERO128 r15, 0	;Initialize Remainder to 0

	BSRFOUND64 r12, r13, rdx, 512
	BSRFOUND32 r12, r13, rdx, 256
	BSRFOUND16 r12, r13, rdx, 128
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
	; ENTERING CALL TO u8192_shl
	;

	PUSHR

	SUB rsp, 1024
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u8192_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL128 r12, rax, r15

	ADD rsp, 1024
	POPR
	;
	; EXITED CALL TO u8192_shl
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

	GOE64 r13, r15, r8, 512
	GOE32 r13, r15, r8, 256
	GOE16 r13, r15, r8, 128
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
	; ENTERING CALL TO u8192_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	MOV rdx, r15

	SUB rsp, 1024
	MOV rcx, rsp
	ZERO128 rcx, 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u8192_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL128 r12, rax, r15

	ADD rsp, 1024
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx

	;
	; EXITED CALL TO u8192_subBig
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

	MOVREL128 r12, r15, r9

	ADD rsp, 1024
	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u8192_divBig ENDP

u8192_inc PROC

	ADD qword ptr [rcx], 1
	ADC64 rcx, 8
	ADC32 rcx, 520
	ADC16 rcx, 776
	ADC8 rcx, 904
	ADC qword ptr [rcx + 968], 0
	ADC qword ptr [rcx + 976], 0
	ADC qword ptr [rcx + 984], 0
	ADC qword ptr [rcx + 992], 0
	ADC qword ptr [rcx + 1000], 0
	ADC qword ptr [rcx + 1008], 0
	ADC qword ptr [rcx + 1016], 0

	RET

u8192_inc ENDP

u8192_dec PROC

	SUB qword ptr [rcx], 1
	SBB64 rcx, 8
	SBB32 rcx, 520
	SBB16 rcx, 776
	SBB8 rcx, 904
	SBB qword ptr [rcx + 968], 0
	SBB qword ptr [rcx + 976], 0
	SBB qword ptr [rcx + 984], 0
	SBB qword ptr [rcx + 992], 0
	SBB qword ptr [rcx + 1000], 0
	SBB qword ptr [rcx + 1008], 0
	SBB qword ptr [rcx + 1016], 0

	RET

u8192_dec ENDP

u8192_shl PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0

	MOV cl, 64
	SUB cl, r8b

	MOV r13, qword ptr [rdx + 1008]	;Save top bits of top part
	MOV qword ptr [r15 + 1008], r13
	SHRX r13, r13, rcx

	MOV cl, r8b

	MOV r12, qword ptr [rdx + 1016]
	MOV qword ptr [r15 + 1016], r12

	SAL qword ptr [r15 + 1008], cl
	SAL qword ptr [r15 + 1016], cl	

	OR qword ptr [r15 + 1008], r13	

	SHLBLCK32 r13, rdx, r15, 1000, 1008
	SHLBLCK32 r13, rdx, r15, 744, 752
	SHLBLCK32 r13, rdx, r15, 488, 496
	SHLBLCK16 r13, rdx, r15, 232, 240
	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u8192_shl ENDP

u8192_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK32 r13, r12, rdx, r15, 8, 0
	SHRBLCK32 r13, r12, rdx, r15, 264, 256
	SHRBLCK32 r13, r12, rdx, r15, 520, 512
	SHRBLCK16 r13, r12, rdx, r15, 776, 768
	SHRBLCK8 r13, r12, rdx, r15, 904, 896

	SHRBLCK r13, r12, rdx, r15, 968, 960
	SHRBLCK r13, r12, rdx, r15, 976, 968
	SHRBLCK r13, r12, rdx, r15, 984, 976
	SHRBLCK r13, r12, rdx, r15, 992, 984
	SHRBLCK r13, r12, rdx, r15, 1000, 992
	SHRBLCK r13, r12, rdx, r15, 1008, 1000
	SHRBLCK r13, r12, rdx, r15, 1016, 1008

	MOV cl, r8b						;Get amount to shift

	MOV r12, qword ptr [rdx + 1016]
	SHRX r12, r12, rcx
	MOV qword ptr [r15 + 1016], r12	;Get value and Shift Right

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u8192_shr ENDP

u8192_and PROC

	VECAND32 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u8192_and ENDP

u8192_or PROC

	VECOR32 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u8192_or ENDP

u8192_xor PROC

	VECXOR32 rdx, r8, rcx, 0

	MOV rax, rcx
	RET

u8192_xor ENDP

u8192_not PROC

	PUSH r12

	NOT128 r12, rdx, rcx, 0

	POP r12

	MOV rax, rcx
	RET

u8192_not ENDP







;
;
;	U16384 OPERATIONS START HERE
;
;

u16384_add PROC

	PUSH r12

	MOVREL256 r12, rdx, rcx   ;mov into rcx u16384 param
	ADD256 rcx, r8		    ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u16384_add ENDP

u16384_addBig PROC

	PUSH r12

	MOVREL256 r12, rdx, rcx   ;mov into rcx first u16384 param
	MOVADD256 r12, r8, rcx	;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET
u16384_addBig ENDP

u16384_sub PROC

	PUSH r12

	MOVREL256 r12, rdx, rcx	;mov into rcx first u16384 param
	SUB256 rcx, r8			 ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u16384_sub ENDP

u16384_subBig PROC

	PUSH r12

	MOVREL256 r12, rdx, rcx	;mov into rcx first u16384 param
	MOVSUB256 r12, r8, rcx	 ;if overflowed we advance the high part by the carry

	POP r12

	MOV rax, rcx
	RET

u16384_subBig ENDP

u16384_mul PROC

	PUSH r12
	PUSH r13

	MPM rax, rdx, r8, 2040

	MOV r12, rax					;store low half of multiplication (ignore overflow)
	POP rdx

	MPM rax, rdx, r8, 2032
	ADD r12, rdx
	MOV r13, rax
	POP rdx

	MULBLCK64 rax, rdx, r8, r13, r12, 2024
	MULBLCK64 rax, rdx, r8, r13, r12, 1512
	MULBLCK64 rax, rdx, r8, r13, r12, 1000
	MULBLCK32 rax, rdx, r8, r12, r13, 488
	MULBLCK16 rax, rdx, r8, r13, r12, 232
	MULBLCK8 rax, rdx, r8, r12, r13, 104
	MULBLCK rax, rdx, r8, r13, r12, 40
	MULBLCK rax, rdx, r8, r13, r12, 32
	MULBLCK rax, rdx, r8, r13, r12, 24
	MULBLCK rax, rdx, r8, r13, r12, 16
	MULBLCK rax, rdx, r8, r13, r12, 8

	MPM rax, rdx, r8, 0
	AACP r12, r13, rdx

	MOV qword ptr [rcx + 16], r13	;Done with +16 part, so storing it
	MOV qword ptr [rcx + 8], r12	;Done with +8 part, so storing it
	MOV qword ptr [rcx], rax		;Done

	POP r13
	POP r12

	MOV rax, rcx
	RET

u16384_mul ENDP

u16384_mulBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

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

	MULBIGONCE rax, rdx, r8, r12, r13, 8
	
	MOV qword ptr [rcx + 8], r12

	;
	;Execution of the 3° Column
	;

	MPM2 rax, rdx, 0, r8, 16
	AMP r13, r12, rax, rdx
	
	MULBIGTWICE rax, rdx, r8, r13, r12, 16

	MOV qword ptr [rcx + 16], r13

	;
	;Execution of the 4° Column
	;

	MPM2 rax, rdx, 0, r8, 24
	AMP r12, r13, rax, rdx
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 24

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

	MULBIGONCE rax, rdx, r8, r12, r13, 40

	MOV qword ptr [rcx + 40], r12

	;
	;Execution of the 7° Column
	;
	
	MPM2 rax, rdx, 0, r8, 48
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 48

	MOV qword ptr [rcx + 48], r13

	;
	;Execution of the 8° Column
	;
	
	MPM2 rax, rdx, 0, r8, 56
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 56

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

	MULBIGONCE rax, rdx, r8, r12, r13, 72

	MOV qword ptr [rcx + 72], r12

	;
	;Execution of the 11° Column
	;

	MPM2 rax, rdx, 0, r8, 80
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 80

	MOV qword ptr [rcx + 80], r13

	;
	;Execution of the 12° Column
	;

	MPM2 rax, rdx, 0, r8, 88
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 88

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

	MULBIGONCE rax, rdx, r8, r12, r13, 104

	MOV qword ptr [rcx + 104], r12

	;
	;Execution of the 15° Column
	;

	MPM2 rax, rdx, 0, r8, 112
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK rax, r13, r12, rdx, 8, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 40, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 72, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 112

	MOV qword ptr [rcx + 112], r13

	;
	;Execution of the 16° Column
	;

	MPM2 rax, rdx, 0, r8, 120
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK rax, r12, r13, rdx, 8, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 40, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 72, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 120

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

	MULBIGONCE rax, rdx, r8, r12, r13, 136

	MOV qword ptr [rcx + 136], r12

	;
	;Execution of the 19° Column
	;

	MPM2 rax, rdx, 0, r8, 144
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 144

	MOV qword ptr [rcx + 144], r13

	;
	;Execution of the 20° Column
	;				  
	
	MPM2 rax, rdx, 0, r8, 152
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 152

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

	MULBIGONCE rax, rdx, r8, r12, r13, 168

	MOV qword ptr [rcx + 168], r12

	;				  
	;Execution of the 23° Column
	;
	
	MPM2 rax, rdx, 0, r8, 176
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 176

	MOV qword ptr [rcx + 176], r13

	;				  
	;Execution of the 24° Column
	;
	
	MPM2 rax, rdx, 0, r8, 184
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 184

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

	MULBIGONCE rax, rdx, r8, r12, r13, 200

	MOV qword ptr [rcx + 200], r12

	;
	;Execution of the 27° Column
	;
	
	MPM2 rax, rdx, 0, r8, 208
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK4 rax, r13, r12, rdx, 8, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 136, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 168, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 208

	MOV qword ptr [rcx + 208], r13

	;
	;Execution of the 28° Column
	;

	MPM2 rax, rdx, 0, r8, 216
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK4 rax, r12, r13, rdx, 8, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 136, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 168, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 216

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

	MULBIGONCE rax, rdx, r8, r12, r13, 232

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

	MULBIGTWICE rax, rdx, r8, r13, r12, 240

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

	MULBIGTHRICE rax, rdx, r8, r12, r13, 248

	MOV qword ptr [rcx + 248], r12

	;
	;Execution of the 33° Column
	;

	MPM2 rax, rdx, 0, r8, 256
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 248

	MOV qword ptr [rcx + 256], r13

	;
	;Execution of the 34° Column
	;

	MPM2 rax, rdx, 0, r8, 264
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 256
	
	MULBIGONCE rax, rdx, r8, r12, r13, 264

	MOV qword ptr [rcx + 264], r12

	;
	;Execution of the 35° Column
	;

	MPM2 rax, rdx, 0, r8, 272
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 264

	MULBIGTWICE rax, rdx, r8, r13, r12, 272

	MOV qword ptr [rcx + 272], r13

	;
	;Execution of the 36° Column
	;

	MPM2 rax, rdx, 0, r8, 280
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 272
	
	MULBIGTHRICE rax, rdx, r8, r12, r13, 280

	MOV qword ptr [rcx + 280], r12

	;
	;Execution of the 37° Column
	;

	MPM2 rax, rdx, 0, r8, 288
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 280
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 24

	MOV qword ptr [rcx + 288], r13

	;
	;Execution of the 38° Column
	;

	MPM2 rax, rdx, 0, r8, 296
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 288
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 296

	MOV qword ptr [rcx + 296], r12

	;
	;Execution of the 39° Column
	;

	MPM2 rax, rdx, 0, r8, 304
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 296
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 304

	MOV qword ptr [rcx + 304], r13

	;
	;Execution of the 40° Column
	;

	MPM2 rax, rdx, 0, r8, 312
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 304
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 312

	MOV qword ptr [rcx + 312], r12

	;
	;Execution of the 41° Column
	;

	MPM2 rax, rdx, 0, r8, 320
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 312
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 24

	MOV qword ptr [rcx + 320], r13
	;
	;Execution of the 42° Column
	;

	MPM2 rax, rdx, 0, r8, 328
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 320
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 328

	MOV qword ptr [rcx + 328], r12
	;
	;Execution of the 43° Column
	;

	MPM2 rax, rdx, 0, r8, 336
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 328
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 336

	MOV qword ptr [rcx + 336], r13
	;
	;Execution of the 44° Column
	;

	MPM2 rax, rdx, 0, r8, 344
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 336
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 344

	MOV qword ptr [rcx + 344], r12
	;
	;Execution of the 45° Column
	;

	MPM2 rax, rdx, 0, r8, 352
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 344
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 24

	MOV qword ptr [rcx + 352], r13
	;
	;Execution of the 46° Column
	;

	MPM2 rax, rdx, 0, r8, 360
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 352
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 360

	MOV qword ptr [rcx + 360], r12
	;
	;Execution of the 47° Column
	;

	MPM2 rax, rdx, 0, r8, 368
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 360
	MULBIGBLCK rax, r13, r12, rdx, 264, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 296, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 328, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 368

	MOV qword ptr [rcx + 368], r13
	;
	;Execution of the 48° Column
	;

	MPM2 rax, rdx, 0, r8, 376
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 368
	MULBIGBLCK rax, r12, r13, rdx, 264, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 296, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 328, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 376

	MOV qword ptr [rcx + 376], r12
	;
	;Execution of the 49° Column
	;

	MPM2 rax, rdx, 0, r8, 384
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 120

	MOV qword ptr [rcx + 384], r13
	;
	;Execution of the 50° Column
	;

	MPM2 rax, rdx, 0, r8, 392
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 392

	MOV qword ptr [rcx + 392], r12
	;
	;Execution of the 51° Column
	;

	MPM2 rax, rdx, 0, r8, 400
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 400

	MOV qword ptr [rcx + 400], r13
	;
	;Execution of the 52° Column
	;

	MPM2 rax, rdx, 0, r8, 408
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 408

	MOV qword ptr [rcx + 408], r12
	;
	;Execution of the 53° Column
	;

	MPM2 rax, rdx, 0, r8, 416
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 24

	MOV qword ptr [rcx + 416], r13
	;
	;Execution of the 54° Column
	;

	MPM2 rax, rdx, 0, r8, 424
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 424

	MOV qword ptr [rcx + 424], r12
	;
	;Execution of the 55° Column
	;

	MPM2 rax, rdx, 0, r8, 432
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 432

	MOV qword ptr [rcx + 432], r13
	;
	;Execution of the 56° Column
	;

	MPM2 rax, rdx, 0, r8, 440
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 440

	MOV qword ptr [rcx + 440], r12
	;
	;Execution of the 57° Column
	;

	MPM2 rax, rdx, 0, r8, 448
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 24

	MOV qword ptr [rcx + 448], r13
	;
	;Execution of the 58° Column
	;

	MPM2 rax, rdx, 0, r8, 456
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 456

	MOV qword ptr [rcx + 456], r12
	;
	;Execution of the 59° Column
	;

	MPM2 rax, rdx, 0, r8, 464
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 464

	MOV qword ptr [rcx + 464], r13
	;
	;Execution of the 60° Column
	;

	MPM2 rax, rdx, 0, r8, 472
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 472

	MOV qword ptr [rcx + 472], r12
	;
	;Execution of the 61° Column
	;

	MPM2 rax, rdx, 0, r8, 480
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 472
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
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 488

	MOV qword ptr [rcx + 488], r12
	;
	;Execution of the 63° Column
	;

	MPM2 rax, rdx, 0, r8, 496
	AMP r13, r12, rax, rdx
	
	MULBIGBLCK8 rax, r13, r12, rdx, 8, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 264, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 392, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 424, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 456, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 496

	MOV qword ptr [rcx + 496], r13

	;
	;Execution of the 64° Column
	;

	MPM2 rax, rdx, 0, r8, 504
	AMP r12, r13, rax, rdx
	
	MULBIGBLCK8 rax, r12, r13, rdx, 8, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 264, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 392, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 424, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 456, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 504

	MOV qword ptr [rcx + 504], r12

	;
	;Execution of the 65° Column
	;

	MPM2 rax, rdx, 0, r8, 512
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 504

	MOV qword ptr [rcx + 512], r13

	;
	;Execution of the 66° Column
	;

	MPM2 rax, rdx, 0, r8, 520
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 512

	MULBIGONCE rax, rdx, r8, r12, r13, 520

	MOV qword ptr [rcx + 520], r12

	;
	;Execution of the 67° Column
	;

	MPM2 rax, rdx, 0, r8, 528
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 520

	MULBIGTWICE rax, rdx, r8, r13, r12, 528

	MOV qword ptr [rcx + 528], r13

	;
	;Execution of the 68° Column
	;

	MPM2 rax, rdx, 0, r8, 536
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 528

	MULBIGTHRICE rax, rdx, r8, r12, r13, 536

	MOV qword ptr [rcx + 536], r12

	;
	;Execution of the 69° Column
	;

	MPM2 rax, rdx, 0, r8, 544
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 536
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 24

	MOV qword ptr [rcx + 544], r13

	;
	;Execution of the 70° Column
	;

	MPM2 rax, rdx, 0, r8, 552
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 544
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 552

	MOV qword ptr [rcx + 552], r12

	;
	;Execution of the 71° Column
	;

	MPM2 rax, rdx, 0, r8, 560
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 552
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 560

	MOV qword ptr [rcx + 560], r13

	;
	;Execution of the 72° Column
	;

	MPM2 rax, rdx, 0, r8, 568
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 560
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 568

	MOV qword ptr [rcx + 568], r12

	;
	;Execution of the 73° Column
	;

	MPM2 rax, rdx, 0, r8, 576
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 568
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 24

	MOV qword ptr [rcx + 576], r13

	;
	;Execution of the 74° Column
	;

	MPM2 rax, rdx, 0, r8, 584
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 576
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 584

	MOV qword ptr [rcx + 584], r12

	;
	;Execution of the 75° Column
	;

	MPM2 rax, rdx, 0, r8, 592
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 584
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 592

	MOV qword ptr [rcx + 592], r13

	;
	;Execution of the 76° Column
	;

	MPM2 rax, rdx, 0, r8, 600
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 592
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 600

	MOV qword ptr [rcx + 600], r12

	;
	;Execution of the 77° Column
	;

	MPM2 rax, rdx, 0, r8, 608
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 600
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 584, r8, 24

	MOV qword ptr [rcx + 608], r13

	;
	;Execution of the 78° Column
	;

	MPM2 rax, rdx, 0, r8, 616
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 608
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 584, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 616

	MOV qword ptr [rcx + 616], r12

	;
	;Execution of the 79° Column
	;

	MPM2 rax, rdx, 0, r8, 624
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 616
	MULBIGBLCK rax, r13, r12, rdx, 520, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 552, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 584, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 624

	MOV qword ptr [rcx + 624], r13

	;
	;Execution of the 80° Column
	;

	MPM2 rax, rdx, 0, r8, 632
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 624
	MULBIGBLCK rax, r12, r13, rdx, 520, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 552, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 584, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 632

	MOV qword ptr [rcx + 632], r12

	;
	;Execution of the 81° Column
	;

	MPM2 rax, rdx, 0, r8, 640
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 632
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 120

	MOV qword ptr [rcx + 640], r13

	;
	;Execution of the 82° Column
	;

	MPM2 rax, rdx, 0, r8, 648
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 640
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 648

	MOV qword ptr [rcx + 648], r12

	;
	;Execution of the 83° Column
	;

	MPM2 rax, rdx, 0, r8, 656
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 648
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 656

	MOV qword ptr [rcx + 656], r13

	;
	;Execution of the 84° Column
	;

	MPM2 rax, rdx, 0, r8, 664
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 656
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 664

	MOV qword ptr [rcx + 664], r12

	;
	;Execution of the 85° Column
	;

	MPM2 rax, rdx, 0, r8, 672
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 664
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 24

	MOV qword ptr [rcx + 672], r13

	;
	;Execution of the 86° Column
	;

	MPM2 rax, rdx, 0, r8, 680
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 672
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 680

	MOV qword ptr [rcx + 680], r12

	;
	;Execution of the 87° Column
	;

	MPM2 rax, rdx, 0, r8, 688
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 680
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 32

	MULBIGTWICE rax, rdx, r8, r13, r12, 688

	MOV qword ptr [rcx + 688], r13

	;
	;Execution of the 88° Column
	;

	MPM2 rax, rdx, 0, r8, 696
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 688
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 40

	MULBIGTHRICE rax, rdx, r8, r12, r13, 696

	MOV qword ptr [rcx + 696], r12

	;
	;Execution of the 89° Column
	;

	MPM2 rax, rdx, 0, r8, 704
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 696
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 48
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 24

	MOV qword ptr [rcx + 704], r13

	;
	;Execution of the 90° Column
	;

	MPM2 rax, rdx, 0, r8, 712
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 704
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 56
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 712

	MOV qword ptr [rcx + 712], r12

	;
	;Execution of the 91° Column
	;

	MPM2 rax, rdx, 0, r8, 720
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 712
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 64
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 720

	MOV qword ptr [rcx + 720], r13

	;
	;Execution of the 92° Column
	;

	MPM2 rax, rdx, 0, r8, 728
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 720
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 72
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 728

	MOV qword ptr [rcx + 728], r12

	;
	;Execution of the 93° Column
	;

	MPM2 rax, rdx, 0, r8, 736
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 728
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 80
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 712, r8, 24

	MOV qword ptr [rcx + 736], r13

	;
	;Execution of the 94° Column
	;

	MPM2 rax, rdx, 0, r8, 744
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 736
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 88
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 712, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 744

	MOV qword ptr [rcx + 744], r12

	;
	;Execution of the 95° Column
	;

	MPM2 rax, rdx, 0, r8, 752
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 744
	MULBIGBLCK4 rax, r13, r12, rdx, 520, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 648, r8, 96
	MULBIGBLCK rax, r13, r12, rdx, 680, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 712, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 752

	MOV qword ptr [rcx + 752], r13

	;
	;Execution of the 96° Column
	;

	MPM2 rax, rdx, 0, r8, 760
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 752
	MULBIGBLCK4 rax, r12, r13, rdx, 520, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 648, r8, 104
	MULBIGBLCK rax, r12, r13, rdx, 680, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 712, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 760

	MOV qword ptr [rcx + 760], r12

	;
	;Execution of the 97° Column
	;

	MPM2 rax, rdx, 0, r8, 768
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 760
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 248

	MOV qword ptr [rcx + 768], r13

	;
	;Execution of the 98° Column
	;

	MPM2 rax, rdx, 0, r8, 776
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 768
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 256

	MULBIGONCE rax, rdx, r8, r12, r13, 776

	MOV qword ptr [rcx + 776], r12

	;
	;Execution of the 99° Column
	;

	MPM2 rax, rdx, 0, r8, 784
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 776
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 264

	MULBIGTWICE rax, rdx, r8, r13, r12, 784

	MOV qword ptr [rcx + 784], r13

	;
	;Execution of the 100° Column
	;

	MPM2 rax, rdx, 0, r8, 792
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 784
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 272

	MULBIGTHRICE rax, rdx, r8, r12, r13, 792

	MOV qword ptr [rcx + 792], r12

	;
	;Execution of the 101° Column
	;

	MPM2 rax, rdx, 0, r8, 800
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 792
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 280
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 24

	MOV qword ptr [rcx + 800], r13

	;
	;Execution of the 102° Column
	;

	MPM2 rax, rdx, 0, r8, 808
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 800
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 288
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 808

	MOV qword ptr [rcx + 808], r12

	;
	;Execution of the 103° Column
	;

	MPM2 rax, rdx, 0, r8, 816
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 808
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 296
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 816

	MOV qword ptr [rcx + 816], r13

	;
	;Execution of the 104° Column
	;

	MPM2 rax, rdx, 0, r8, 824
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 816
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 304
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 824

	MOV qword ptr [rcx + 824], r12

	;
	;Execution of the 105° Column
	;

	MPM2 rax, rdx, 0, r8, 832
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 824
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 312
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 24

	MOV qword ptr [rcx + 832], r13

	;
	;Execution of the 106° Column
	;

	MPM2 rax, rdx, 0, r8, 840
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 832
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 320
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 840

	MOV qword ptr [rcx + 840], r12

	;
	;Execution of the 107° Column
	;

	MPM2 rax, rdx, 0, r8, 848
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 840
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 328
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 848

	MOV qword ptr [rcx + 848], r13

	;
	;Execution of the 108° Column
	;

	MPM2 rax, rdx, 0, r8, 856
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 848
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 336
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 856

	MOV qword ptr [rcx + 856], r12

	;
	;Execution of the 109° Column
	;

	MPM2 rax, rdx, 0, r8, 864
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 856
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 344
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 840, r8, 24

	MOV qword ptr [rcx + 864], r13

	;
	;Execution of the 110° Column
	;

	MPM2 rax, rdx, 0, r8, 872
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 864
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 352
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 840, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 872

	MOV qword ptr [rcx + 872], r12

	;
	;Execution of the 111° Column
	;

	MPM2 rax, rdx, 0, r8, 880
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 872
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 360
	MULBIGBLCK rax, r13, r12, rdx, 776, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 808, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 840, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 880

	MOV qword ptr [rcx + 880], r13

	;
	;Execution of the 112° Column
	;

	MPM2 rax, rdx, 0, r8, 888
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 880
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 368
	MULBIGBLCK rax, r12, r13, rdx, 776, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 808, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 840, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 888

	MOV qword ptr [rcx + 888], r12

	;
	;Execution of the 113° Column
	;

	MPM2 rax, rdx, 0, r8, 896
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 888
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 120

	MOV qword ptr [rcx + 896], r13

	;
	;Execution of the 114° Column
	;

	MPM2 rax, rdx, 0, r8, 904
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 896
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 904

	MOV qword ptr [rcx + 904], r12

	;
	;Execution of the 115° Column
	;

	MPM2 rax, rdx, 0, r8, 912
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 904
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 912

	MOV qword ptr [rcx + 912], r13

	;
	;Execution of the 116° Column
	;

	MPM2 rax, rdx, 0, r8, 920
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 912
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 920

	MOV qword ptr [rcx + 920], r12

	;
	;Execution of the 117° Column
	;

	MPM2 rax, rdx, 0, r8, 928
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 920
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 24

	MOV qword ptr [rcx + 928], r13

	;
	;Execution of the 118° Column
	;

	MPM2 rax, rdx, 0, r8, 936
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 928
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 936

	MOV qword ptr [rcx + 936], r12

	;
	;Execution of the 119° Column
	;

	MPM2 rax, rdx, 0, r8, 944
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 936
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 944

	MOV qword ptr [rcx + 944], r13

	;
	;Execution of the 120° Column
	;

	MPM2 rax, rdx, 0, r8, 952
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 944
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 952

	MOV qword ptr [rcx + 952], r12

	;
	;Execution of the 121° Column
	;

	MPM2 rax, rdx, 0, r8, 960
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 952
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 24

	MOV qword ptr [rcx + 960], r13

	;
	;Execution of the 122° Column
	;

	MPM2 rax, rdx, 0, r8, 968
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 960
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 968

	MOV qword ptr [rcx + 968], r12

	;
	;Execution of the 123° Column
	;

	MPM2 rax, rdx, 0, r8, 976
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 968
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 976

	MOV qword ptr [rcx + 976], r13

	;
	;Execution of the 124° Column
	;

	MPM2 rax, rdx, 0, r8, 984
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 976
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 984

	MOV qword ptr [rcx + 984], r12

	;
	;Execution of the 125° Column
	;

	MPM2 rax, rdx, 0, r8, 992
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 984
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 472
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 968, r8, 24

	MOV qword ptr [rcx + 992], r13

	;
	;Execution of the 126° Column
	;

	MPM2 rax, rdx, 0, r8, 1000
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 992
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 968, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1000

	MOV qword ptr [rcx + 1000], r12

	;
	;Execution of the 127° Column
	;

	MPM2 rax, rdx, 0, r8, 1008
	AMP r13, r12, rax, rdx

	MULBIGBLCK16 rax, r13, r12, rdx, 8, r8, 1000
	MULBIGBLCK8 rax, r13, r12, rdx, 520, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 776, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 904, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 936, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 968, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1008

	MOV qword ptr [rcx + 1008], r13

	;
	;Execution of the 128° Column
	;

	MPM2 rax, rdx, 0, r8, 1016
	AMP r12, r13, rax, rdx

	MULBIGBLCK16 rax, r12, r13, rdx, 8, r8, 1008
	MULBIGBLCK8 rax, r12, r13, rdx, 520, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 776, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 904, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 936, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 968, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1016

	MOV qword ptr [rcx + 1016], r12

	;
	;Execution of the 129° Column
	;

	MPM2 rax, rdx, 0, r8, 1024
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1016

	MOV qword ptr [rcx + 1024], r13

	;
	;Execution of the 130° Column
	;

	MPM2 rax, rdx, 0, r8, 1032
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1024

	MULBIGONCE rax, rdx, r8, r12, r13, 1032

	MOV qword ptr [rcx + 1032], r12

	;
	;Execution of the 131° Column
	;

	MPM2 rax, rdx, 0, r8, 1040
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1032

	MULBIGTWICE rax, rdx, r8, r13, r12, 1040

	MOV qword ptr [rcx + 1040], r13

	;
	;Execution of the 132° Column
	;

	MPM2 rax, rdx, 0, r8, 1048
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1040

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1048

	MOV qword ptr [rcx + 1048], r12

	;
	;Execution of the 133° Column
	;

	MPM2 rax, rdx, 0, r8, 1056
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1048
	MULBIGBLCK rax, r13, r12, rdx, 1032, r8, 24

	MOV qword ptr [rcx + 1056], r13

	;
	;Execution of the 134° Column
	;

	MPM2 rax, rdx, 0, r8, 1064
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1056
	MULBIGBLCK rax, r12, r13, rdx, 1032, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1064

	MOV qword ptr [rcx + 1064], r12

	;
	;Execution of the 135° Column
	;

	MPM2 rax, rdx, 0, r8, 1072
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1064
	MULBIGBLCK rax, r13, r12, rdx, 1032, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1072

	MOV qword ptr [rcx + 1072], r13

	;
	;Execution of the 136° Column
	;

	MPM2 rax, rdx, 0, r8, 1080
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1072
	MULBIGBLCK rax, r12, r13, rdx, 1032, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1080

	MOV qword ptr [rcx + 1080], r12

	;
	;Execution of the 137° Column
	;

	MPM2 rax, rdx, 0, r8, 1088
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1080
	MULBIGBLCK rax, r13, r12, rdx, 1032, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1064, r8, 24

	MOV qword ptr [rcx + 1088], r13

	;
	;Execution of the 138° Column
	;

	MPM2 rax, rdx, 0, r8, 1096
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1088
	MULBIGBLCK rax, r12, r13, rdx, 1032, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1064, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1096

	MOV qword ptr [rcx + 1096], r12

	;
	;Execution of the 139° Column
	;

	MPM2 rax, rdx, 0, r8, 1104
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1096
	MULBIGBLCK rax, r13, r12, rdx, 1032, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1064, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1104

	MOV qword ptr [rcx + 1104], r13

	;
	;Execution of the 140° Column
	;

	MPM2 rax, rdx, 0, r8, 1112
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1104
	MULBIGBLCK rax, r12, r13, rdx, 1032, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1064, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1112

	MOV qword ptr [rcx + 1112], r12

	;
	;Execution of the 141° Column
	;

	MPM2 rax, rdx, 0, r8, 1120
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1112
	MULBIGBLCK rax, r13, r12, rdx, 1032, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1064, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1096, r8, 24

	MOV qword ptr [rcx + 1120], r13

	;
	;Execution of the 142° Column
	;

	MPM2 rax, rdx, 0, r8, 1128
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1120
	MULBIGBLCK rax, r12, r13, rdx, 1032, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1064, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1096, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1128

	MOV qword ptr [rcx + 1128], r12

	;
	;Execution of the 143° Column
	;

	MPM2 rax, rdx, 0, r8, 1136
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1128
	MULBIGBLCK rax, r13, r12, rdx, 1032, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1064, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1096, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1136

	MOV qword ptr [rcx + 1136], r13

	;
	;Execution of the 144° Column
	;

	MPM2 rax, rdx, 0, r8, 1144
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1136
	MULBIGBLCK rax, r12, r13, rdx, 1032, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1064, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1096, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1144

	MOV qword ptr [rcx + 1144], r12

	;
	;Execution of the 145° Column
	;

	MPM2 rax, rdx, 0, r8, 1152
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1144
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 120

	MOV qword ptr [rcx + 1152], r13

	;
	;Execution of the 146° Column
	;

	MPM2 rax, rdx, 0, r8, 1160
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1152
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 1160

	MOV qword ptr [rcx + 1160], r12

	;
	;Execution of the 147° Column
	;

	MPM2 rax, rdx, 0, r8, 1168
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1160
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 1168

	MOV qword ptr [rcx + 1168], r13

	;
	;Execution of the 148° Column
	;

	MPM2 rax, rdx, 0, r8, 1176
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1168
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1176

	MOV qword ptr [rcx + 1176], r12

	;
	;Execution of the 149° Column
	;

	MPM2 rax, rdx, 0, r8, 1184
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1176
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 1160, r8, 24

	MOV qword ptr [rcx + 1184], r13

	;
	;Execution of the 150° Column
	;

	MPM2 rax, rdx, 0, r8, 1192
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1184
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 1160, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1192

	MOV qword ptr [rcx + 1192], r12

	;
	;Execution of the 151° Column
	;

	MPM2 rax, rdx, 0, r8, 1200
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1192
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 1160, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1200

	MOV qword ptr [rcx + 1200], r13

	;
	;Execution of the 152° Column
	;

	MPM2 rax, rdx, 0, r8, 1208
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1200
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 1160, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1208

	MOV qword ptr [rcx + 1208], r12

	;
	;Execution of the 153° Column
	;

	MPM2 rax, rdx, 0, r8, 1216
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1208
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 1160, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1192, r8, 24

	MOV qword ptr [rcx + 1216], r13

	;
	;Execution of the 154° Column
	;

	MPM2 rax, rdx, 0, r8, 1224
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1216
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 1160, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1192, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1224

	MOV qword ptr [rcx + 1224], r12

	;
	;Execution of the 155° Column
	;

	MPM2 rax, rdx, 0, r8, 1232
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1224
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 1160, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1192, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1232

	MOV qword ptr [rcx + 1232], r13

	;
	;Execution of the 156° Column
	;

	MPM2 rax, rdx, 0, r8, 1240
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1232
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 1160, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1192, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1240

	MOV qword ptr [rcx + 1240], r12

	;
	;Execution of the 157° Column
	;

	MPM2 rax, rdx, 0, r8, 1248
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1240
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 1160, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1192, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1224, r8, 24

	MOV qword ptr [rcx + 1248], r13

	;
	;Execution of the 158° Column
	;

	MPM2 rax, rdx, 0, r8, 1256
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1248
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 1160, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1192, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1224, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1256

	MOV qword ptr [rcx + 1256], r12

	;
	;Execution of the 159° Column
	;

	MPM2 rax, rdx, 0, r8, 1264
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1256
	MULBIGBLCK4 rax, r13, r12, rdx, 1032, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 1160, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1192, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1224, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1264

	MOV qword ptr [rcx + 1264], r13

	;
	;Execution of the 160° Column
	;

	MPM2 rax, rdx, 0, r8, 1272
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1264
	MULBIGBLCK4 rax, r12, r13, rdx, 1032, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 1160, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1192, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1224, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1272

	MOV qword ptr [rcx + 1272], r12

	;
	;Execution of the 161° Column
	;

	MPM2 rax, rdx, 0, r8, 1280
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1272
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 248

	MOV qword ptr [rcx + 1280], r13

	;
	;Execution of the 162° Column
	;

	MPM2 rax, rdx, 0, r8, 1288
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1280
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 256

	MULBIGONCE rax, rdx, r8, r12, r13, 1288

	MOV qword ptr [rcx + 1288], r12

	;
	;Execution of the 163° Column
	;

	MPM2 rax, rdx, 0, r8, 1296
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1288
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 264

	MULBIGTWICE rax, rdx, r8, r13, r12, 1296

	MOV qword ptr [rcx + 1296], r13

	;
	;Execution of the 164° Column
	;

	MPM2 rax, rdx, 0, r8, 1304
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1296
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 272

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1304

	MOV qword ptr [rcx + 1304], r12

	;
	;Execution of the 165° Column
	;

	MPM2 rax, rdx, 0, r8, 1312
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1304
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 280
	MULBIGBLCK rax, r13, r12, rdx, 1288, r8, 24

	MOV qword ptr [rcx + 1312], r13

	;
	;Execution of the 166° Column
	;

	MPM2 rax, rdx, 0, r8, 1320
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1312
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 288
	MULBIGBLCK rax, r12, r13, rdx, 1288, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1320

	MOV qword ptr [rcx + 1320], r12

	;
	;Execution of the 167° Column
	;

	MPM2 rax, rdx, 0, r8, 1328
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1320
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 296
	MULBIGBLCK rax, r13, r12, rdx, 1288, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1328

	MOV qword ptr [rcx + 1328], r13

	;
	;Execution of the 168° Column
	;

	MPM2 rax, rdx, 0, r8, 1336
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1328
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 304
	MULBIGBLCK rax, r12, r13, rdx, 1288, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1336

	MOV qword ptr [rcx + 1336], r12

	;
	;Execution of the 169° Column
	;

	MPM2 rax, rdx, 0, r8, 1344
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1336
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 312
	MULBIGBLCK rax, r13, r12, rdx, 1288, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1320, r8, 24

	MOV qword ptr [rcx + 1344], r13

	;
	;Execution of the 170° Column
	;

	MPM2 rax, rdx, 0, r8, 1352
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1344
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 320
	MULBIGBLCK rax, r12, r13, rdx, 1288, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1320, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1352

	MOV qword ptr [rcx + 1352], r12

	;
	;Execution of the 171° Column
	;

	MPM2 rax, rdx, 0, r8, 1360
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1352
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 328
	MULBIGBLCK rax, r13, r12, rdx, 1288, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1320, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1360

	MOV qword ptr [rcx + 1360], r13

	;
	;Execution of the 172° Column
	;

	MPM2 rax, rdx, 0, r8, 1368
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1360
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 336
	MULBIGBLCK rax, r12, r13, rdx, 1288, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1320, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1368

	MOV qword ptr [rcx + 1368], r12

	;
	;Execution of the 173° Column
	;

	MPM2 rax, rdx, 0, r8, 1376
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1368
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 344
	MULBIGBLCK rax, r13, r12, rdx, 1288, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1320, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1352, r8, 24

	MOV qword ptr [rcx + 1376], r13

	;
	;Execution of the 174° Column
	;

	MPM2 rax, rdx, 0, r8, 1384
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1376
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 352
	MULBIGBLCK rax, r12, r13, rdx, 1288, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1320, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1352, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1384

	MOV qword ptr [rcx + 1384], r12

	;
	;Execution of the 175° Column
	;

	MPM2 rax, rdx, 0, r8, 1392
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1384
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 360
	MULBIGBLCK rax, r13, r12, rdx, 1288, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1320, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1352, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1392

	MOV qword ptr [rcx + 1392], r13

	;
	;Execution of the 176° Column
	;

	MPM2 rax, rdx, 0, r8, 1400
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1392
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 368
	MULBIGBLCK rax, r12, r13, rdx, 1288, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1320, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1352, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1400

	MOV qword ptr [rcx + 1400], r12

	;
	;Execution of the 177° Column
	;

	MPM2 rax, rdx, 0, r8, 1408
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1400
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 120

	MOV qword ptr [rcx + 1408], r13

	;
	;Execution of the 178° Column
	;

	MPM2 rax, rdx, 0, r8, 1416
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1408
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 1416

	MOV qword ptr [rcx + 1416], r12

	;
	;Execution of the 179° Column
	;

	MPM2 rax, rdx, 0, r8, 1424
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1416
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 1424

	MOV qword ptr [rcx + 1424], r13

	;
	;Execution of the 180° Column
	;

	MPM2 rax, rdx, 0, r8, 1432
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1424
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1432

	MOV qword ptr [rcx + 1432], r12

	;
	;Execution of the 181° Column
	;

	MPM2 rax, rdx, 0, r8, 1440
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1432
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 1416, r8, 24

	MOV qword ptr [rcx + 1440], r13

	;
	;Execution of the 182° Column
	;

	MPM2 rax, rdx, 0, r8, 1448
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1440
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 1416, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1448

	MOV qword ptr [rcx + 1448], r12

	;
	;Execution of the 183° Column
	;

	MPM2 rax, rdx, 0, r8, 1456
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1448
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 1416, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1456

	MOV qword ptr [rcx + 1456], r13

	;
	;Execution of the 184° Column
	;

	MPM2 rax, rdx, 0, r8, 1464
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1456
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 1416, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1464

	MOV qword ptr [rcx + 1464], r12

	;
	;Execution of the 185° Column
	;

	MPM2 rax, rdx, 0, r8, 1472
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1464
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 1416, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1448, r8, 24

	MOV qword ptr [rcx + 1472], r13

	;
	;Execution of the 186° Column
	;

	MPM2 rax, rdx, 0, r8, 1480
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1472
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 1416, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1448, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1480

	MOV qword ptr [rcx + 1480], r12

	;
	;Execution of the 187° Column
	;

	MPM2 rax, rdx, 0, r8, 1488
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1480
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 1416, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1448, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1488

	MOV qword ptr [rcx + 1488], r13

	;
	;Execution of the 188° Column
	;

	MPM2 rax, rdx, 0, r8, 1496
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1488
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 1416, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1448, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1496

	MOV qword ptr [rcx + 1496], r12

	;
	;Execution of the 189° Column
	;

	MPM2 rax, rdx, 0, r8, 1504
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1496
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 472
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 1416, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1448, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1480, r8, 24

	MOV qword ptr [rcx + 1504], r13

	;
	;Execution of the 190° Column
	;

	MPM2 rax, rdx, 0, r8, 1512
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1504
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 1416, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1448, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1480, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1512

	MOV qword ptr [rcx + 1512], r12

	;
	;Execution of the 191° Column
	;

	MPM2 rax, rdx, 0, r8, 1520
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1512
	MULBIGBLCK8 rax, r13, r12, rdx, 1032, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 1288, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 1416, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1448, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1480, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1520

	MOV qword ptr [rcx + 1520], r13

	;
	;Execution of the 192° Column
	;

	MPM2 rax, rdx, 0, r8, 1528
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1520
	MULBIGBLCK8 rax, r12, r13, rdx, 1032, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 1288, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 1416, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1448, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1480, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1528

	MOV qword ptr [rcx + 1528], r12

	;
	;Execution of the 193° Column
	;

	MPM2 rax, rdx, 0, r8, 1536
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1528
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 504

	MOV qword ptr [rcx + 1536], r13

	;
	;Execution of the 194° Column
	;

	MPM2 rax, rdx, 0, r8, 1544
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1536
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 512

	MULBIGONCE rax, rdx, r8, r12, r13, 1544

	MOV qword ptr [rcx + 1544], r12

	;
	;Execution of the 195° Column
	;

	MPM2 rax, rdx, 0, r8, 1552
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1544
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 520

	MULBIGTWICE rax, rdx, r8, r13, r12, 1552

	MOV qword ptr [rcx + 1552], r13

	;
	;Execution of the 196° Column
	;

	MPM2 rax, rdx, 0, r8, 1560
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1552
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 528

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1560

	MOV qword ptr [rcx + 1560], r12

	;
	;Execution of the 197° Column
	;

	MPM2 rax, rdx, 0, r8, 1568
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1560
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 536
	MULBIGBLCK rax, r13, r12, rdx, 1544, r8, 24

	MOV qword ptr [rcx + 1568], r13

	;
	;Execution of the 198° Column
	;

	MPM2 rax, rdx, 0, r8, 1576
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1568
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 544
	MULBIGBLCK rax, r12, r13, rdx, 1544, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1576

	MOV qword ptr [rcx + 1576], r12

	;
	;Execution of the 199° Column
	;

	MPM2 rax, rdx, 0, r8, 1584
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1576
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 552
	MULBIGBLCK rax, r13, r12, rdx, 1544, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1584

	MOV qword ptr [rcx + 1584], r13

	;
	;Execution of the 200° Column
	;

	MPM2 rax, rdx, 0, r8, 1592
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1584
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 560
	MULBIGBLCK rax, r12, r13, rdx, 1544, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1592

	MOV qword ptr [rcx + 1592], r12

	;
	;Execution of the 201° Column
	;

	MPM2 rax, rdx, 0, r8, 1600
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1592
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 568
	MULBIGBLCK rax, r13, r12, rdx, 1544, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1576, r8, 24

	MOV qword ptr [rcx + 1600], r13

	;
	;Execution of the 202° Column
	;

	MPM2 rax, rdx, 0, r8, 1608
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1600
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 576
	MULBIGBLCK rax, r12, r13, rdx, 1544, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1576, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1608

	MOV qword ptr [rcx + 1608], r12

	;
	;Execution of the 203° Column
	;

	MPM2 rax, rdx, 0, r8, 1616
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1608
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 584
	MULBIGBLCK rax, r13, r12, rdx, 1544, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1576, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1616

	MOV qword ptr [rcx + 1616], r13

	;
	;Execution of the 204° Column
	;

	MPM2 rax, rdx, 0, r8, 1624
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1616
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 592
	MULBIGBLCK rax, r12, r13, rdx, 1544, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1576, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1624

	MOV qword ptr [rcx + 1624], r12

	;
	;Execution of the 205° Column
	;

	MPM2 rax, rdx, 0, r8, 1632
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1624
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 600
	MULBIGBLCK rax, r13, r12, rdx, 1544, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1576, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1608, r8, 24

	MOV qword ptr [rcx + 1632], r13

	;
	;Execution of the 206° Column
	;

	MPM2 rax, rdx, 0, r8, 1640
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1632
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 608
	MULBIGBLCK rax, r12, r13, rdx, 1544, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1576, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1608, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1640

	MOV qword ptr [rcx + 1640], r12

	;
	;Execution of the 207° Column
	;

	MPM2 rax, rdx, 0, r8, 1648
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1640
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 616
	MULBIGBLCK rax, r13, r12, rdx, 1544, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1576, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1608, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1648

	MOV qword ptr [rcx + 1648], r13

	;
	;Execution of the 208° Column
	;

	MPM2 rax, rdx, 0, r8, 1656
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1648
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 624
	MULBIGBLCK rax, r12, r13, rdx, 1544, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1576, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1608, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1656

	MOV qword ptr [rcx + 1656], r12

	;
	;Execution of the 209° Column
	;

	MPM2 rax, rdx, 0, r8, 1664
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1656
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 632
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 120

	MOV qword ptr [rcx + 1664], r13

	;
	;Execution of the 210° Column
	;

	MPM2 rax, rdx, 0, r8, 1672
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1664
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 640
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 1672

	MOV qword ptr [rcx + 1672], r12

	;
	;Execution of the 211° Column
	;

	MPM2 rax, rdx, 0, r8, 1680
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1672
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 648
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 1680

	MOV qword ptr [rcx + 1680], r13

	;
	;Execution of the 212° Column
	;

	MPM2 rax, rdx, 0, r8, 1688
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1680
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 656
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1688

	MOV qword ptr [rcx + 1688], r12

	;
	;Execution of the 213° Column
	;

	MPM2 rax, rdx, 0, r8, 1696
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1688
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 664
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 1672, r8, 24

	MOV qword ptr [rcx + 1696], r13

	;
	;Execution of the 214° Column
	;

	MPM2 rax, rdx, 0, r8, 1704
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1696
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 672
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 1672, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1704

	MOV qword ptr [rcx + 1704], r12

	;
	;Execution of the 215° Column
	;

	MPM2 rax, rdx, 0, r8, 1712
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1704
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 680
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 1672, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1712

	MOV qword ptr [rcx + 1712], r13

	;
	;Execution of the 216° Column
	;

	MPM2 rax, rdx, 0, r8, 1720
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1712
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 688
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 1672, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1720

	MOV qword ptr [rcx + 1720], r12

	;
	;Execution of the 217° Column
	;

	MPM2 rax, rdx, 0, r8, 1728
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1720
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 696
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 1672, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1704, r8, 24

	MOV qword ptr [rcx + 1728], r13

	;
	;Execution of the 218° Column
	;

	MPM2 rax, rdx, 0, r8, 1736
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1728
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 704
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 1672, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1704, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1736

	MOV qword ptr [rcx + 1736], r12

	;
	;Execution of the 219° Column
	;

	MPM2 rax, rdx, 0, r8, 1744
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1736
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 712
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 1672, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1704, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1744

	MOV qword ptr [rcx + 1744], r13

	;
	;Execution of the 220° Column
	;

	MPM2 rax, rdx, 0, r8, 1752
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1744
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 720
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 1672, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1704, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1752

	MOV qword ptr [rcx + 1752], r12

	;
	;Execution of the 221° Column
	;

	MPM2 rax, rdx, 0, r8, 1760
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1752
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 728
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 1672, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1704, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1736, r8, 24

	MOV qword ptr [rcx + 1760], r13

	;
	;Execution of the 222° Column
	;

	MPM2 rax, rdx, 0, r8, 1768
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1760
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 736
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 1672, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1704, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1736, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1768

	MOV qword ptr [rcx + 1768], r12

	;
	;Execution of the 223° Column
	;

	MPM2 rax, rdx, 0, r8, 1776
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1768
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 744
	MULBIGBLCK4 rax, r13, r12, rdx, 1544, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 1672, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1704, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1736, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1776

	MOV qword ptr [rcx + 1776], r13

	;
	;Execution of the 224° Column
	;

	MPM2 rax, rdx, 0, r8, 1784
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1776
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 752
	MULBIGBLCK4 rax, r12, r13, rdx, 1544, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 1672, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1704, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1736, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1784

	MOV qword ptr [rcx + 1784], r12

	;
	;Execution of the 225° Column
	;

	MPM2 rax, rdx, 0, r8, 1792
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1784
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 760
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 248

	MOV qword ptr [rcx + 1792], r13

	;
	;Execution of the 226° Column
	;

	MPM2 rax, rdx, 0, r8, 1800
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1792
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 768
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 256

	MULBIGONCE rax, rdx, r8, r12, r13, 1800

	MOV qword ptr [rcx + 1800], r12

	;
	;Execution of the 227° Column
	;

	MPM2 rax, rdx, 0, r8, 1808
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1800
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 776
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 264

	MULBIGTWICE rax, rdx, r8, r13, r12, 1808

	MOV qword ptr [rcx + 1808], r13

	;
	;Execution of the 228° Column
	;

	MPM2 rax, rdx, 0, r8, 1816
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1808
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 784
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 272

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1816

	MOV qword ptr [rcx + 1816], r12

	;
	;Execution of the 229° Column
	;

	MPM2 rax, rdx, 0, r8, 1824
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1816
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 792
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 280
	MULBIGBLCK rax, r13, r12, rdx, 1800, r8, 24

	MOV qword ptr [rcx + 1824], r13

	;
	;Execution of the 230° Column
	;

	MPM2 rax, rdx, 0, r8, 1832
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1824
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 800
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 288
	MULBIGBLCK rax, r12, r13, rdx, 1800, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1832

	MOV qword ptr [rcx + 1832], r12

	;
	;Execution of the 231° Column
	;

	MPM2 rax, rdx, 0, r8, 1840
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1832
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 808
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 296
	MULBIGBLCK rax, r13, r12, rdx, 1800, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1840

	MOV qword ptr [rcx + 1840], r13

	;
	;Execution of the 232° Column
	;

	MPM2 rax, rdx, 0, r8, 1848
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1840
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 816
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 304
	MULBIGBLCK rax, r12, r13, rdx, 1800, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1848

	MOV qword ptr [rcx + 1848], r12

	;
	;Execution of the 233° Column
	;

	MPM2 rax, rdx, 0, r8, 1856
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1848
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 824
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 312
	MULBIGBLCK rax, r13, r12, rdx, 1800, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1832, r8, 24

	MOV qword ptr [rcx + 1856], r13

	;
	;Execution of the 234° Column
	;

	MPM2 rax, rdx, 0, r8, 1864
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1856
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 832
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 320
	MULBIGBLCK rax, r12, r13, rdx, 1800, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1832, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1864

	MOV qword ptr [rcx + 1864], r12

	;
	;Execution of the 235° Column
	;

	MPM2 rax, rdx, 0, r8, 1872
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1864
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 840
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 328
	MULBIGBLCK rax, r13, r12, rdx, 1800, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1832, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1872

	MOV qword ptr [rcx + 1872], r13

	;
	;Execution of the 236° Column
	;

	MPM2 rax, rdx, 0, r8, 1880
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1872
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 848
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 336
	MULBIGBLCK rax, r12, r13, rdx, 1800, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1832, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1880

	MOV qword ptr [rcx + 1880], r12

	;
	;Execution of the 237° Column
	;

	MPM2 rax, rdx, 0, r8, 1888
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1880
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 856
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 344
	MULBIGBLCK rax, r13, r12, rdx, 1800, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1832, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1864, r8, 24

	MOV qword ptr [rcx + 1888], r13

	;
	;Execution of the 238° Column
	;

	MPM2 rax, rdx, 0, r8, 1896
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1888
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 864
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 352
	MULBIGBLCK rax, r12, r13, rdx, 1800, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1832, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1864, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1896

	MOV qword ptr [rcx + 1896], r12

	;
	;Execution of the 239° Column
	;

	MPM2 rax, rdx, 0, r8, 1904
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1896
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 872
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 360
	MULBIGBLCK rax, r13, r12, rdx, 1800, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1832, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1864, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1904

	MOV qword ptr [rcx + 1904], r13

	;
	;Execution of the 240° Column
	;

	MPM2 rax, rdx, 0, r8, 1912
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1904
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 880
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 368
	MULBIGBLCK rax, r12, r13, rdx, 1800, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1832, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1864, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1912

	MOV qword ptr [rcx + 1912], r12

	;
	;Execution of the 241° Column
	;

	MPM2 rax, rdx, 0, r8, 1920
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1912
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 888
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 376
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 120

	MOV qword ptr [rcx + 1920], r13

	;
	;Execution of the 242° Column
	;

	MPM2 rax, rdx, 0, r8, 1928
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1920
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 896
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 384
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 128

	MULBIGONCE rax, rdx, r8, r12, r13, 1928

	MOV qword ptr [rcx + 1928], r12

	;
	;Execution of the 243° Column
	;

	MPM2 rax, rdx, 0, r8, 1936
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1928
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 904
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 392
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 136

	MULBIGTWICE rax, rdx, r8, r13, r12, 1936

	MOV qword ptr [rcx + 1936], r13

	;
	;Execution of the 244° Column
	;

	MPM2 rax, rdx, 0, r8, 1944
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1936
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 912
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 400
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 144

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1944

	MOV qword ptr [rcx + 1944], r12

	;
	;Execution of the 245° Column
	;

	MPM2 rax, rdx, 0, r8, 1952
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1944
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 920
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 408
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 152
	MULBIGBLCK rax, r13, r12, rdx, 1928, r8, 24

	MOV qword ptr [rcx + 1952], r13

	;
	;Execution of the 246° Column
	;

	MPM2 rax, rdx, 0, r8, 1960
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1952
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 928
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 416
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 160
	MULBIGBLCK rax, r12, r13, rdx, 1928, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1960

	MOV qword ptr [rcx + 1960], r12

	;
	;Execution of the 247° Column
	;

	MPM2 rax, rdx, 0, r8, 1968
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1960
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 936
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 424
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 168
	MULBIGBLCK rax, r13, r12, rdx, 1928, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 1968

	MOV qword ptr [rcx + 1968], r13

	;
	;Execution of the 248° Column
	;

	MPM2 rax, rdx, 0, r8, 1976
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1968
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 944
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 432
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 176
	MULBIGBLCK rax, r12, r13, rdx, 1928, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 1976

	MOV qword ptr [rcx + 1976], r12

	;
	;Execution of the 249° Column
	;

	MPM2 rax, rdx, 0, r8, 1984
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1976
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 952
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 440
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 184
	MULBIGBLCK rax, r13, r12, rdx, 1928, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1960, r8, 24

	MOV qword ptr [rcx + 1984], r13

	;
	;Execution of the 250° Column
	;

	MPM2 rax, rdx, 0, r8, 1992
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 1984
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 960
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 448
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 192
	MULBIGBLCK rax, r12, r13, rdx, 1928, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1960, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 1992

	MOV qword ptr [rcx + 1992], r12

	;
	;Execution of the 251° Column
	;

	MPM2 rax, rdx, 0, r8, 2000
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 1992
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 968
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 456
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 200
	MULBIGBLCK rax, r13, r12, rdx, 1928, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1960, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 2000

	MOV qword ptr [rcx + 2000], r13

	;
	;Execution of the 252° Column
	;

	MPM2 rax, rdx, 0, r8, 2008
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 2000
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 976
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 464
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 208
	MULBIGBLCK rax, r12, r13, rdx, 1928, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1960, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 2008

	MOV qword ptr [rcx + 2008], r12

	;
	;Execution of the 253° Column
	;

	MPM2 rax, rdx, 0, r8, 2016
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 2008
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 984
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 472
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 216
	MULBIGBLCK rax, r13, r12, rdx, 1928, r8, 88
	MULBIGBLCK rax, r13, r12, rdx, 1960, r8, 56
	MULBIGBLCK rax, r13, r12, rdx, 1992, r8, 24

	MOV qword ptr [rcx + 2016], r13

	;
	;Execution of the 254° Column
	;

	MPM2 rax, rdx, 0, r8, 2024
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 2016
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 992
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 480
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 224
	MULBIGBLCK rax, r12, r13, rdx, 1928, r8, 96
	MULBIGBLCK rax, r12, r13, rdx, 1960, r8, 64
	MULBIGBLCK rax, r12, r13, rdx, 1992, r8, 32

	MULBIGONCE rax, rdx, r8, r12, r13, 2024

	MOV qword ptr [rcx + 2024], r12

	;
	;Execution of the 255° Column
	;

	MPM2 rax, rdx, 0, r8, 2032
	AMP r13, r12, rax, rdx

	MULBIGBLCK32 rax, r13, r12, rdx, 8, r8, 2024
	MULBIGBLCK16 rax, r13, r12, rdx, 1032, r8, 1000
	MULBIGBLCK8 rax, r13, r12, rdx, 1544, r8, 488
	MULBIGBLCK4 rax, r13, r12, rdx, 1800, r8, 232
	MULBIGBLCK rax, r13, r12, rdx, 1928, r8, 104
	MULBIGBLCK rax, r13, r12, rdx, 1960, r8, 72
	MULBIGBLCK rax, r13, r12, rdx, 1992, r8, 40

	MULBIGTWICE rax, rdx, r8, r13, r12, 2032

	MOV qword ptr [rcx + 2032], r13

	;
	;Execution of the 256° Column
	;

	MPM2 rax, rdx, 0, r8, 2040
	AMP r12, r13, rax, rdx

	MULBIGBLCK32 rax, r12, r13, rdx, 8, r8, 2032
	MULBIGBLCK16 rax, r12, r13, rdx, 1032, r8, 1008
	MULBIGBLCK8 rax, r12, r13, rdx, 1544, r8, 496
	MULBIGBLCK4 rax, r12, r13, rdx, 1800, r8, 240
	MULBIGBLCK rax, r12, r13, rdx, 1928, r8, 112
	MULBIGBLCK rax, r12, r13, rdx, 1960, r8, 80
	MULBIGBLCK rax, r12, r13, rdx, 1992, r8, 48

	MULBIGTHRICE rax, rdx, r8, r12, r13, 2040

	MOV qword ptr [rcx + 2040], r12

	;
	;Return
	;

	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u16384_mulBig ENDP

u16384_divBig PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	ZERO256 rcx, 0	;Initialize Quotient to 0

	SUB rsp, 2048
	MOV r15, rsp
	ZERO256 r15, 0	;Initialize Remainder to 0

	BSRFOUND64 r12, r13, rdx, 1536
	BSRFOUND64 r12, r13, rdx, 1024
	BSRFOUND64 r12, r13, rdx, 512
	BSRFOUND32 r12, r13, rdx, 256
	BSRFOUND16 r12, r13, rdx, 128
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
	; ENTERING CALL TO u16384_shl
	;

	PUSHR

	SUB rsp, 2048
	MOV rcx, rsp
	MOV rdx, r15
	MOV r8, 1
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u16384_shl

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL256 r12, rax, r15

	ADD rsp, 2048
	POPR
	;
	; EXITED CALL TO u16384_shl
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

	GOE64 r13, r15, r8, 1536
	GOE64 r13, r15, r8, 1024
	GOE64 r13, r15, r8, 512
	GOE32 r13, r15, r8, 256
	GOE16 r13, r15, r8, 128
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
	; ENTERING CALL TO u16384_subBig
	;

	PUSH rcx
	PUSH rdx
	PUSH r9
	PUSH r12
	PUSH r13

	MOV rdx, r15

	SUB rsp, 2048
	MOV rcx, rsp
	ZERO256 rcx, 0
	PUSH r15

	PUSH rbp
	MOV rbp, rsp

	call u16384_subBig

	MOV rsp, rbp
	POP rbp

	POP r15
	MOVREL256 r12, rax, r15

	ADD rsp, 2048
	POP r13
	POP r12
	POP r9
	POP rdx
	POP rcx

	;
	; EXITED CALL TO u16384_subBig
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

	MOVREL256 r12, r15, r9

	ADD rsp, 2048
	POP r15
	POP r14
	POP r13
	POP r12

	MOV rax, rcx
	RET

u16384_divBig ENDP

u16384_inc PROC

	ADD qword ptr [rcx], 1
	ADC64 rcx, 8
	ADC64 rcx, 520
	ADC64 rcx, 1032
	ADC32 rcx, 1544
	ADC16 rcx, 1800
	ADC8 rcx, 1928
	ADC qword ptr [rcx + 1992], 0
	ADC qword ptr [rcx + 2000], 0
	ADC qword ptr [rcx + 2008], 0
	ADC qword ptr [rcx + 2016], 0
	ADC qword ptr [rcx + 2024], 0
	ADC qword ptr [rcx + 2032], 0
	ADC qword ptr [rcx + 2040], 0

	RET

u16384_inc ENDP

u16384_dec PROC

	SUB qword ptr [rcx], 1
	SBB64 rcx, 8
	SBB64 rcx, 520
	SBB64 rcx, 1032
	SBB32 rcx, 1544
	SBB16 rcx, 1800
	SBB8 rcx, 1928
	SBB qword ptr [rcx + 1992], 0
	SBB qword ptr [rcx + 2000], 0
	SBB qword ptr [rcx + 2008], 0
	SBB qword ptr [rcx + 2016], 0
	SBB qword ptr [rcx + 2024], 0
	SBB qword ptr [rcx + 2032], 0
	SBB qword ptr [rcx + 2040], 0

	RET

u16384_dec ENDP

u16384_shl PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx
	PUSH rcx

	MOV rcx, 0

	MOV cl, 64
	SUB cl, r8b

	MOV r13, qword ptr [rdx + 2032]	;Save top bits of top part
	MOV qword ptr [r15 + 2032], r13
	SHRX r13, r13, rcx

	MOV cl, r8b

	MOV r12, qword ptr [rdx + 2040]
	MOV qword ptr [r15 + 2040], r12

	SAL qword ptr [r15 + 2032], cl
	SAL qword ptr [r15 + 2040], cl	

	OR qword ptr [r15 + 2032], r13	

	SHLBLCK32 r13, rdx, r15, 2024, 2032
	SHLBLCK32 r13, rdx, r15, 1768, 1776
	SHLBLCK32 r13, rdx, r15, 1512, 1520
	SHLBLCK32 r13, rdx, r15, 1256, 1264
	SHLBLCK32 r13, rdx, r15, 1000, 1008
	SHLBLCK32 r13, rdx, r15, 744, 752
	SHLBLCK32 r13, rdx, r15, 488, 496
	SHLBLCK16 r13, rdx, r15, 232, 240
	SHLBLCK8 r13, rdx, r15, 104, 112

	SHLBLCK r13, rdx, r15, 40, 48
	SHLBLCK r13, rdx, r15, 32, 40
	SHLBLCK r13, rdx, r15, 24, 32
	SHLBLCK r13, rdx, r15, 16, 24
	SHLBLCK r13, rdx, r15, 8, 16
	SHLBLCK r13, rdx, r15, 0, 8

	POP rcx							;Get back rcx to preserve the reg
	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u16384_shl ENDP

u16384_shr PROC

	PUSH r12
	PUSH r13
	PUSH r14
	PUSH r15

	MOV r15, rcx 
	PUSH rcx

	MOV rcx, 0

	SHRBLCK32 r13, r12, rdx, r15, 8, 0
	SHRBLCK32 r13, r12, rdx, r15, 264, 256
	SHRBLCK32 r13, r12, rdx, r15, 520, 512
	SHRBLCK32 r13, r12, rdx, r15, 776, 768
	SHRBLCK32 r13, r12, rdx, r15, 1032, 1024
	SHRBLCK32 r13, r12, rdx, r15, 1288, 1280
	SHRBLCK32 r13, r12, rdx, r15, 1544, 1536
	SHRBLCK16 r13, r12, rdx, r15, 1800, 1792
	SHRBLCK8 r13, r12, rdx, r15, 1928, 1920

	SHRBLCK r13, r12, rdx, r15, 1992, 1984
	SHRBLCK r13, r12, rdx, r15, 2000, 1992
	SHRBLCK r13, r12, rdx, r15, 2008, 2000
	SHRBLCK r13, r12, rdx, r15, 2016, 2008
	SHRBLCK r13, r12, rdx, r15, 2024, 2016
	SHRBLCK r13, r12, rdx, r15, 2032, 2024
	SHRBLCK r13, r12, rdx, r15, 2040, 2032

	MOV cl, r8b						;Get amount to shift

	MOV r12, qword ptr [rdx + 2040]
	SHRX r12, r12, rcx
	MOV qword ptr [r15 + 2040], r12	;Get value and Shift Right

	POP rcx							;Get back rcx to preserve the reg

	MOV rax, r15

	POP r15
	POP r14
	POP r13
	POP r12

	RET

u16384_shr ENDP

u16384_and PROC

	VECAND32 rdx, r8, rcx, 0
	VECAND32 rdx, r8, rcx, 1024

	MOV rax, rcx
	RET

u16384_and ENDP

u16384_or PROC

	VECOR32 rdx, r8, rcx, 0
	VECOR32 rdx, r8, rcx, 1024

	MOV rax, rcx
	RET

u16384_or ENDP

u16384_xor PROC

	VECXOR32 rdx, r8, rcx, 0
	VECXOR32 rdx, r8, rcx, 1024

	MOV rax, rcx
	RET

u16384_xor ENDP

u16384_not PROC

	PUSH r12

	NOT256 r12, rdx, rcx, 0

	POP r12

	MOV rax, rcx
	RET

u16384_not ENDP

END