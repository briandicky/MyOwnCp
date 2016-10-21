/*
 * Author: Wen-Chih Lo
 * Date: 2016.10.21
 * Purpose: Implement a utility like cp(1), call lcp, that copies a file containing holes, without writing the bytes of 0 to the output file.
 * */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#ifdef __DEBUG__
#define printINT(x) printf("%s = %d\n", #x, (x));
#define printSTR(x) printf("%s = %s\n", #x, (x));
#else
#define printINT(x)
#define printSRT(x)
#endif

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif


/* Print a command usage error message and terminate the process */
void usageError(const char *format, ...) {
    va_list argList;

    /* Flush any pending stdout */
    fflush(stdout);

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    /* In case stderr is not line-buffered */
    fflush(stderr);
    exit(EXIT_FAILURE);
}

/* Display error message including 'errno' diagnostic, and
 * terminate the process */
void errorExit(const char *format, ...) {
    va_list argList;
    
    /* Flush any pending stdout */
    fflush(stdout);

    fprintf(stderr, "lcp: cannot stat");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    /* In case stderr is not line-buffered */
    fflush(stderr);
    exit(EXIT_FAILURE);
}


int main(int argc, const char *argv[]) {
    int inputFD, outputFD;
    int openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if( argc != 3 || strcmp(argv[1], "--help") == 0 )
        usageError("%s old-file new-file\n", argv[0]);
    
    /* Open input and output files */
    inputFD = open(argv[1], O_RDONLY);
    if(inputFD == -1)
        errorExit("'%s': No such file or directory\n", argv[1]);

    /* A call to creat() is equivalent to calling open() 
     * with flags equal to O_CREAT|O_WRONLY|O_TRUNC. */
    openFlags = (O_CREAT | O_WRONLY | O_TRUNC);

    /* File permission is rw-rw-r-- */
    filePerms = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );     

    outputFD = open(argv[2], openFlags, filePerms);
    if(outputFD == -1)
        errorExit("'%s': Failed to create this file\n", argv[2]);

    /* Transfer data until we encounter end of input or an error */ 
    while( (numRead = read(inputFD, buf, BUF_SIZE)) > 0 ) {
        if( write(outputFD, buf, numRead) != numRead )
            errorExit("'%s': Failed to write this file\n", argv[2]); 
    }

    close(inputFD);
    close(outputFD);

    return EXIT_SUCCESS;
}
