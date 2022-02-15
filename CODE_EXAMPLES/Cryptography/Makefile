EXEC = encrypt decrypt keygen
SOURCES1 = encrypt.c randstate.c numtheory.c rsa.c
SOURCES2 = decrypt.c randstate.c numtheory.c rsa.c
SOURCES3 = keygen.c randstate.c numtheory.c rsa.c

OBJECTS1 = $(SOURCES1:%.c=%.o)
OBJECTS2 = $(SOURCES2:%.c=%.o)
OBJECTS3 = $(SOURCES3:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra $(shell pkg-config --cflags gmp)
LDFLAGS = $(shell pkg-config --libs gmp)
all: $(EXEC)

encrypt: $(OBJECTS1)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ 

decrypt: $(OBJECTS2)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

keygen: $(OBJECTS3)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

tidy: 
	rm -rf $(OBJECTS1)
	rm -rf $(OBJECTS2)
	rm -rf $(OBJECTS3)

clean: tidy
	rm -rf $(EXEC)

format:
	clang-format -i -style=file *.c *.h
