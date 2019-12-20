# Tyler's Turing Machine Simulator
Originally written in C++ in December 2019. Inspired by [Anthony Morphett's online Turing Machine simulator](http://morphett.info/turing/turing.html).

## How to run
Compile the code locally and run it from the command line or your IDE of choice. The program does not require any command line arguments, but you may specify the code file for the Turing Machine in the first argument and the input for the input tape in the second argument. For instance:

./a.out examples/string_length_squared.txt aaa

## Syntax
The simulator relies on a "punch card" system by using states with numerous configurations. The general format is as follows:

St Rs Ws Di Ns

Where:
- St is the state identifier, or the state that the configuration belongs to
- Rs is the read symbol, or the symbol that the specific configuration must read to execute
- Ws is the write symbol, or the symbol that will be written at the tape head
- Di is the direction to move the head
- Ns is the next state to move to

As for actual keywords:
- States may be any string as long as there are no spaces
- The read and write symbols may be any symbols, as long as they are only one character
- The direction may be L, l, R, r, or *, which means do not move the head any direction
- The next state follows the same rules as states
- Starting a line with a ; will mark it as a comment and have the program ignore the line

