#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define ARR_SIZE 3

struct birthday {
    int year;
    int month;
    int date;
};

int main() {
    int fd, i;
    struct birthday birthdays[ARR_SIZE] = {{2002, 2, 25},
        {2004, 11, 10},
        {2002, 3, 25}};

    fd = open("birthdays.bin", O_WRONLY | O_CREAT, 0644);
    for (i = 0; i < ARR_SIZE; i++) {
        write(fd, &birthdays[i], sizeof(struct birthday));
    }
    close(fd);
}

