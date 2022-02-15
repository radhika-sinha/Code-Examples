# Assignment 6 - Public Key Cryptography

encrypt: Encrypts data using RSA encryption.
decrypt: Decrypts data uing RSA decryption.
keygen: Generates an RSA public/private key pair.

# Building

To build this program, run:

...
$ make
...

# Running

To run the programs:

...
$./encrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey
$./decrypt [-hvi:o:] [-i infile] [-o outfile]
$./keygen [-hv] [-b bits] -n pbfile -d pvfile
...

- -h             Prints out program help and usage.
- -v             Display verbose program output..
- -i infile      Input file of data to encrypt or decrypt (default: stdin).
- -o outfile     Output file for encrypted or decrypted data (default: stdout).
- -n pbfile      Public key file (default: rsa.pub).
- -d pvfile      Private key file (default: rsa.priv).
- -b bits        Minimum number of bits needed for public key n.
- -c confidence  Miller-Rabin iterations for testing primes (default: 50).
- -s seed        Random seed for testing.

# Cleaning

To remove all object files and executables, run:

...
$ make clean
...
