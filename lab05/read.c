#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct birthday {
    int year;
    int month;
    int date;
};

int main ()
{
    int fd, n;
    struct birthday birth;

    fd = open("birthdays.bin", O_RDONLY);
    while (read(fd, &birth, sizeof(struct birthday)) > 0) {
        printf("%d %d %d\n", birth.year, birth.month, birth.date);
    }

    close(fd);
}
