app:
    ALLOC R1, 256*512
    ALLOC R2, 256*512

    CALL init_game, R1
    CALL draw, R1
    CALL update, R1, R2
app_loop:
    CALL draw, R1
    CALL update, R1, R2
    JMP app_loop

init_game:
    MOV R3, 0
init_loop:
    CMP R4, R3, 256
    JMPEQ R4, 1, init_end
    CALL SIM_RAND
    MOD R6, R5, 2
    STORE R6, [R1, R3]
    ADD R3, R3, 1
    JMP init_loop
init_end:
    RET

draw:
    MOV R3, 0
draw_loop:
    CMP R4, R3, 256
    JMPEQ R4, 1, draw_end
    CALL SIM_FLUSH
    LOAD R5, [R1, R3]
    CMP R6, R5, 0
    SELECT R7, R6, -16777216, -16711936
    CALL SIM_PUTPIXEL R3, R3, R7
    ADD R3, R3, 1
draw_end:
    RET

count_neighbors:
    MOV R4, -1
    MOV R5, -1
    MOV R6, 0

count_x_loop:
    ADD R4, R4, 1
    CMP R7, R4, 2
    JMPEQ R7, 1, count_y_loop

count_y_loop:
    ADD R5, R5, 1
    CMP R8, R5, 2
    JMPEQ R8, 1, count_exit
    ADD R9, R4, R0
    ADD R10, R5, R1
    CMPG R11, R9, 0
    CMPL R12, R9, 256
    AND R13, R11, R12
    CMPG R14, R10, 0
    CMP_LT R15, R10, 512
    AND R16, R14, R15
    AND R17, R13, R16
    LOAD R18, [R2, R9, R10]
    ADD R6, R6, R18
    JMP count_y_loop
count_exit:
    RET

update:
    MOV R3, 0
update_loop:
    CMP R4, R3, 256
    JMPEQ R4, 1, update_end
    CALL count_neighbors R3, R4, R1
    LOAD R6, [R1, R3]
    CMPN R7, R6, 0
    AND R8, R5, -2
    CMP R9, R8, 2
    SELECT R10, R7, R9, 0
    STORE R10, [R2, R3]
    ADD R3, R3, 1
    JMP update_loop
update_end:
    RET
