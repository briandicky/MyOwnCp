#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char buf1[] = "abcdefghij", buf2[] = "ABCDEFGHIJ";

int main(void) {
    int fd;

    if( (fd = open("file.hole", (O_CREAT | O_WRONLY | O_TRUNC), 0664)) < 0 )
        fprintf(stderr, "creat error\n");

    if( write(fd, buf1, 10) != 10 )
        fprintf(stderr, "buf1 write error\n");

    if( lseek(fd, 16384, SEEK_SET) == -1 )
        fprintf(stderr, "lseek erroer\n");

    if( write(fd, buf2, 10) != 10 )
        fprintf(stderr, "buf2 write error\n");

    return 0;
}
