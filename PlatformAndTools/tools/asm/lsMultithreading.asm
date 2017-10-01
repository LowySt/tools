.data
.code

asmCall PROC

POP r12
MOV r13, r12
SUB r13, 0
JE FN_CALL

MOV r15, 1
MOV rdi, r8

FIRST_FOUR:
MOV r13, r12
SUB r13, 0
JE FN_CALL
MOV r13d, dword ptr [r9]	;Get Param Size in Bytes
SUB r13d, 8
JG PASS_BY_POINTER

PASS_BY_VALUE:
MOV r14, r15
SUB r14, 1
JL PARAM_2_V
MOV r13d, dword ptr [r9]
MOV rsi, 0
MOV_LOOP_1:
MOV dl + rsi, byte ptr [rdi + rsi]
INC rsi
SUB r13d, 1
JG MOV_LOOP_1
ADD rdi, rsi
JMP ADVANCE
PARAM_2_V:
MOV r14, r15
SUB r14, 2
JL PARAM_3_V
MOV r13d, dword ptr [r9]
MOV rsi, 0
MOV_LOOP_2:
MOV dl + rsi, byte ptr [rdi + rsi]
INC rsi
SUB r13d, 1
JG MOV_LOOP_2
ADD rdi, rsi
JMP ADVANCE
PARAM_3_V:
MOV r13d, dword ptr [r9]
MOV rsi, 0
MOV_LOOP_3:
MOV dl + rsi, byte ptr [rdi + rsi]
INC rsi
SUB r13d, 1
JG MOV_LOOP_3
ADD rdi, rsi
JMP ADVANCE

PASS_BY_POINTER:
MOV r14, r15
SUB r14, 1
JL PARAM_2_P
MOV rdx, qword ptr [rdi]
ADD rdi, 8
JMP ADVANCE
PARAM_2_P:
MOV r14, r15
SUB r14, 2
JL PARAM_3_P
MOV r8, qword ptr[rdi]
ADD rdi, 8
JMP ADVANCE
PARAM_3_P:
MOV r8, qword ptr[rdi]
ADD rdi, 8

ADVANCE:
DEC r12
MOV r14, r15
SUB r14, 3
JGE FIRST_FOUR

STACK_PARAMS:
MOV r13, r12
SUB r13, 0
JE FN_CALL

MOV r14, qword ptr[rdi+rsi]
PUSH r14

DEC r12
JMP STACK_PARAMS:


FN_CALL:
CALL r12
MOV rax, rcx
RET

asmCall ENDP

END