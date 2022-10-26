#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    int a, b;

    a = 20;
    b = 0x12345678;
    fd = open("aaa.data", O_WRONLY | O_CREAT);
    write(fd, &a, sizeof(int));
    write(fd, &b, sizeof(int));
    close(fd);

    return 0;
}
