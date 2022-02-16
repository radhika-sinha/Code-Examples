#---------------------------------------------------------------
# Radhika Sinha, rasinha
# 2022 Winter CSE101 PA3
# Makefile
#
# make                      makes FindComponents and GraphClient
# make all                  makes FindComponents and GraphClient
# make FindComponents       makes FindComponents
# make GraphClient          makes GraphClient
# make clean                removes all binaries
# make checkFind            checks FindComponents for memory leaks on in8
# make checkclient          checks GraphClient for memory leaks
#---------------------------------------------------------------

EXEC = FindComponents GraphClient 

SOURCES1 = FindComponents.c Graph.c List.c
SOURCES2 = GraphClient.c Graph.c List.c

OBJECTS1 = $(SOURCES1:%.c=%.o)
OBJECTS2 = $(SOURCES2:%.c=%.o)

CC = gcc -std=c17
CFLAGS = -Wall -Wpedantic -Werror -Wextra

MEMCHECK = valgrind --leak-check=full

all: $(EXEC)

FindComponents: $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^

GraphClient: $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf $(EXEC)
	rm -rf $(OBJECTS1)
	rm -rf $(OBJECTS2)

checkFind: 
	$(MEMCHECK) FindComponents in8 junk8

checkClient:
	$(MEMCHECK) GraphClient

