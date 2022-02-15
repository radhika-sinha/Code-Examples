# Assignment 7 - The Great Firewall of Santa Cruz

A word filtering program for the GPRSC.
Filters out and reports bad words parsed from stdin.

# Building

To build this program, run:

...
$ make
...

# Running

To run the programs:

...
$./banhammer [-hs] [-t size] [-f size]
...

- -h             Prints out program help and usage.
- -s             Display verbose program output.
- -t size        Specify hash table size (default: 2^16).
- -f size        Specify Bloom filter size (default: 2^20).

# Cleaning

To remove all object files and executables, run:

...
$ make clean
...
