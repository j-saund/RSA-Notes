#include "general.h"

void printBN(char *msg, BIGNUM * a)
{
    // convert BIGNUM to num string
    char *number_str = BN_bn2dec(a);

    // Print out num string
    printf(LR_FORMAT, KRED, msg, KYEL, number_str);

    // Free dynamically allocated mem
    OPENSSL_free(number_str);
}

void printLR(char *L, char *R)
{
    // print l and r sides same format 
    printf(LR_FORMAT, KRED, L, KYEL, R);
}

void convert_buff(char *arg1, char *arg2, char *buffer, size_t buffer_size)
{
    // arg is arg 1 (the secret to encrypt)
    // arg2 is the type of function we want (such as utf_hex )
    int fd[2];
    pid_t p;

    // pipe it supa (channel for py output)
    if (pipe(fd) == -1) { printf("%s\tPIPE FAILED%s\n", KRED, KNRM); exit(1);}
    
    // fork it (py process -- child)
    p = fork();
    if (p<0) {printf("\t%sFORK FAILED%s\n", KRED, KNRM); exit(1);}

    // PY PROCESS FOR STRING CONVERSION
    else if ( p == 0 ){
        close(fd[0]);
        // stdout 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("python3", "python3", "convert.py", arg1, arg2, NULL);

        printf(LR_FORMAT, KRED, "\tFAILURE", KYEL, "EXEC FAILED IN CHILD\n");
        exit(1);
    }

    // PARENT PROCESS - OUR PROGRAM

    else {
        close(fd[1]);

        int n= read(fd[0], buffer, buffer_size - 1);
        if (n > 0) {
            buffer[n] = '\0';
        }

        // when we finish reading, must wait for child process
        close(fd[0]);
        wait(NULL);
    }
    return; 
} // END PROCESS HANDLING // char buff conversion