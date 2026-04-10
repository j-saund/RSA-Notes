#ifndef GENERAL_H
#define GENERAL_H

#include <openssl/bn.h>
#include <stdio.h>

#include <stdbool.h>

// create process to run a quick py script
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define KRED "\x1B[31m" // RED
#define KYEL "\x1B[33m" // yellow
#define KGRN "\x1B[32m" // green
#define KNRM "\x1B[0m"  // normal - reset color

#define LR_FORMAT "%s%-20s %s%-20s\n"

#define NBITS 256  // our desired bit amt

// #### prototypes #####

void printBN(char *msg, BIGNUM * a);

void printLR(char *L, char *R);

void convert_buff(char *arg1, char *arg2, char *buffer, size_t buffer_size);



#endif // GENERAL.H