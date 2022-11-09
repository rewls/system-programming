#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

struct Node {
    int a;
    float b;
    char name[12];
};

int main() {
    int fd;
    struct Node node;

    fd = open("bbb.data", O_RDONLY);
    read(fd, &node, sizeof(struct Node));
    printf("a = %d, b = %f, name = %s\n",
            node.a, node.b, node.name);
    close(fd);

    return 0;
}
