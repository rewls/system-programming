#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    int a, b, result;

    a = 0;
    b = 0;
    fd = open("aaa.data", O_RDONLY);
    result = read(fd, &a, sizeof(int));
    printf("result = %d\n", result);
    result = read(fd, &b, sizeof(int));
    printf("result = %d\n", result);
    result = read(fd, &b, sizeof(int));
    printf("result = %d\n", result);
    printf("a = %d, b = %x\n", a, b);
    close(fd);

    return 0;
}
