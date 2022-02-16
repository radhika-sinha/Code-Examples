#---------------------------------------------------------------
# Radhika Sinha, rasinha
# 2022 Winter CSE101 PA2
# Makefile
#
# make                makes FindPath and GraphClient
# make all            makes FindPath and GraphClient
# make FindPath       makes FindPath
# make GraphClient    makes GraphClient
# make clean          removes all binaries
# make checkFind      checks FindPath for memory leaks on in7
# make checkclient    checks GraphClient for memory leaks
#---------------------------------------------------------------

EXEC = FindPath GraphClient 

SOURCES1 = FindPath.c Graph.c List.c
SOURCES2 = GraphClient.c Graph.c List.c

OBJECTS1 = $(SOURCES1:%.c=%.o)
OBJECTS2 = $(SOURCES2:%.c=%.o)

CC = gcc -std=c17
CFLAGS = -Wall -Wpedantic -Werror -Wextra

MEMCHECK = valgrind --leak-check=full

all: $(EXEC)

FindPath: $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^

GraphClient: $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf $(EXEC)
	rm -rf $(OBJECTS1)
	rm -rf $(OBJECTS2)

checkFind : 
	$(MEMCHECK) FindPath in7 junk7

checkClient :
	$(MEMCHECK) GraphClient

