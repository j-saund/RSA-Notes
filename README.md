# RSA NOTES - Based on SEED RSA lab
  This repo acts as notes for understanding basic RSA encryption and the math behind it.<br>
  It can be ran using a unix-like system if desired.<br>
  Uses Python for simple string conversions, creating a subprocess to run python3.<br>

  _Note_:  Does not compute Chinese Remainder Theorem as 
  one _should_ when performing RSA calculations. Signature shown also does not show
  in practice signatures, just the basic concept of using priv key (does not compute hash --> encrypt)
  p and q are not generated here nor is e. Simply, the math and principle behind RSA is shown.

# HOW TO RUN + General info/dependencies
  Uses OpenSSL BIGNUM  
  Requires unistd subprocesses (use unix-like system) & python3 (written python3.8.10)<br>
  compile: _make <insert desired %.c>_ ----- Output as default executable (a.out)<br>
          --> example: make step_3_1   --- ./a.out<br>
  run: ./a.out<br>
  make clean to remove (rm a.out)<br>

# NOTATION + MATH 
- M or m --> message
- S --> signature
- e --> pub key
- d --> priv key
- p, q --> two large, distinct, prime numbers
- c --> encrypted output
- n --> our modulus (p*q)

e: 1 < e < totient(n) && gcd(e, totient(n)) = 1 (coprime)<br>
Above, use Extended Euclidean Alg. to validate e. (e * x + totient(n) * y = gcd(e, totient(n))<br>

d : 1/e mod totient(n) --> same as d*e = 1 mod totient(n)<br>
n = p * q<br>
totient(n) = (p-1)(q-1)<br>  
Enc: C = M^e<br>   
Dec: M = C^d<br>

_Reminder_: n,e constitutes the pub key. n,d constitutes the priv key.<br> 


# FILES INCLUDED
- **Makefile**: you know what this does >:l
- **convert.py**: accepts arguments for hex string conversion
- **general.c and general.h**: contains required libraries, sub process func for running python, and string print formats
- **step_2_1_basics.c**: basic operations for BIGNUM vals
- **step_2_2_basics.c**: basic operations more closely related to RSA and BIGNUMs
- **step_3_1.c**: computes private key given p, q, and pub key
- **step_3_2.c**: displays RSA encryption and decryption given n, e, M, d
- **step_3_4_sign.c**: shows the concept behind how a signature is computed   
                       (Note: a normal signature would hash the msg and encrypt with priv key)   
                       (Reminder: unlike encrypt then MAC for Authenticaed Encryption, here, you would HASH then Encrypt)   
- **step_3_5_verify.c**: verifies a signature M, S, e, n


