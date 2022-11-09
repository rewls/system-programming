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
    node.a = 20;
    node.b = 3.14;
    strcpy(node.name, "Kim");

    fd = open("bbb.data", O_WRONLY | O_CREAT);
    write(fd, &node, sizeof(node));
    close(fd);

    return 0;
}
