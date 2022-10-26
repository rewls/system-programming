#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096
#define COPY_MODE 0644  /* 8진수 */

void generate_error(char *s1, char *s2);

int main(int argc, char *argv[]) {
    int in_fd, out_fd, n_char;
    char buf[BUFFER_SIZE];

    if (argc != 3) {
        fprintf(stderr, "usage:%s source destination\n", argv[0]);
        exit(1);
    }

    if ((in_fd = open(argv[1], O_RDONLY)) == -1)
        generate_error("Cannot open", argv[1]);

    if ((out_fd = creat(argv[2], COPY_MODE)) == -1)
        generate_error("Cannot create", argv[2]);

    while ((n_char = read(in_fd, buf, BUFFER_SIZE)) > 0) {
        if (write(out_fd, buf, n_char) != n_char)
            generate_error("write error to", argv[2]);
    }
    if (n_char == -1)
        generate_error("read error from", argv[1]);

    if (close(in_fd) == -1 || close(out_fd) == -1)
        generate_error("error closing file", "");
}

void generate_error(char *s1, char *s2) {
    fprintf(stderr, "error:%s ", s1);
    perror(s2);
    exit(1);
}
