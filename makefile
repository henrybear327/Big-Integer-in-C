all:
	clang-format -i -style=LLVM *.c
	astyle --style=linux *.c
	gcc -Wall -Wextra -Wshadow -std=c99 bigInt.c -o bigInt
