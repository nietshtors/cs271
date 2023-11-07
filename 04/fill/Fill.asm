// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(KEYBOARD)
@SCREEN
D=A                 // Load screen address to D
@R0
M=D                 // Save initial screen address to R0
@KBD
D=M                 // Load keyboard input to D
@BLACK
D;JGT               // If keyboard, jump to black
@WHITE
D;JEQ               // Else, jump to white
@KEYBOARD
0;JMP               // Backup catch

(WHITE)
@R1
M=0                 // Save "white" to R1
@FILL_SCREEN
0;JMP

(BLACK)
@R1 
M=-1                // Save "black" to R1
@FILL_SCREEN
0;JMP

(FILL_SCREEN)
@R1
D=M                 // Load color to D
@R0
A=M                 // Set address to screen point
M=D                 // Save color to row of pixels
@R0
MD=M+1              // Increment address to next set and save to D
@KBD
D=A-D               // Subtract KBD address from current point on screen
@FILL_SCREEN
D;JGT               // If difference is > 0, loop
@KEYBOARD
D;JLE               // Else, jump to keyboard loop