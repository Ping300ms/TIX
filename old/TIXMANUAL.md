## Usage
./TIX COMPILER RUNPATH
## Description
Testsuite manager for the Tiger Compiler.

COMPILER is the path of the tested compiler.
RUNPATH is the path of the directory or the test file.

A test file is composed of code snippets to be tested and header. Expected test
 results are given to TIX via the headers: 

	/*#TIX ECODE = 0; EOUT = ""; EERR = ""; NAME = "" */

	/*#TIX ECODE = 0; EOUT = ""; EERR = ""; ARGS = "" NAME = "" */

Where ECODE is the expected return code, EOUT the expected output on stdout, 
EERR the expected output on stderr, ARGS the argument to pass to the compiler
and NAME the name of the test.

If the RUNPATH argument is a file, TIX will run every test of the file. If the
RUNPATH argument is a directory, it will run every test file inside.
