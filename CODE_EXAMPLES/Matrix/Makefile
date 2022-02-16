#---------------------------------------------------------------
# Radhika Sinha, rasinha
# 2022 Winter CSE101 PA4
# Makefile
#
# make                      makes Sparse, MatrixTest, and ListTest
# make all                  makes Sparse, MatrixTest, and ListTest
# make Sparse               makes Sparse
# make MatrixTest           makes MatrixTest 
# make ListTest             makes ListTest
# make clean                removes all binaries
# make SparseCheck          runs Sparse in valgrind on in5
# make MatrixCheck          runs MatrixTest in valgrind
# make ListCheck            runs ListTest in valgrind
#---------------------------------------------------------------

EXEC = Sparse MatrixTest ListTest

SOURCES1 = Sparse.c Matrix.c List.c
SOURCES2 = MatrixTest.c Matrix.c List.c
SOURCES3 = ListTest.c Matrix.c List.c

OBJECTS1 = $(SOURCES1:%.c=%.o)
OBJECTS2 = $(SOURCES2:%.c=%.o)
OBJECTS3 = $(SOURCES3:%.c=%.o)

CC = gcc -std=c17
CFLAGS = -Wall -Wpedantic -Werror -Wextra

MEMCHECK = valgrind --leak-check=full

all: $(EXEC)

Sparse: $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^

MatrixTest: $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^

ListTest: $(OBJECTS3)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf $(EXEC)
	rm -rf $(OBJECTS1)
	rm -rf $(OBJECTS2)
	rm -rf $(OBJECTS3)

SparseCheck : 
	$(MEMCHECK) Sparse in1 out1

MatrixCheck:
	$(MEMCHECK) MatrixTest

ListCheck:
	$(MEMCHECK) ListTest

