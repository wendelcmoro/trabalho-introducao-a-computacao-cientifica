CC = gcc
CFLAGS = -O3 -mavx -march=native -DLIKWID_PERFMON -I/home/soft/likwid/include -L/home/soft/likwid/lib -llikwid -Wall -lm
DEPS = sistLinearUtils.h gsUtils.h auxUtils.h timeUtils.h

OBJ = pdeSolver.o sistLinearUtils.o gsUtils.o auxUtils.o timeUtils.o

pdeSolver: pdeSolver.o sistLinearUtils.o gsUtils.o auxUtils.o timeUtils.o
	$(CC) -o pdeSolver pdeSolver.o sistLinearUtils.o gsUtils.o auxUtils.o timeUtils.o $(CFLAGS)
	
all: pdeSolver.c $(DEPS)
	$(CC)  -c -o pdeSolver.o pdeSolver.c
	
clean:
	rm -f $(OBJ) pdeSolver
	
doc:
	doxygen docsgen
	rm -rf latex/
