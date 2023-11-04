// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

@ARG
M=0                 // Zero output
@THIS
M=0                 // Zero run count
@SP
D=M                 // Load R0
@SKIP
D;JEQ               // Skips loop if R0 is 0
@LCL
D=M                 // Load R1
@SKIP
D;JEQ               // Skips loop if R1 is 0

(LOOP)
@ARG
D=M                 // Load total
@SP
D=D+M               // Add next to running total
@ARG
M=D                 // Save running total
@THIS
MD=M+1              // Increase run count
@LCL
D=M-D               // Subtract run count from R1
@LOOP
D;JGT
@INFINITE_LOOP
0;JMP

(SKIP)
@ARG
M=0

(INFINITE_LOOP)
@INFINITE_LOOP
0;JMP               // Infinite loop
