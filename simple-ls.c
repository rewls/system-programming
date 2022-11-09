#include <stdio.h>
#include <dirent.h>  /* struct dirent (directory entry),
                        DIR, opendir, readdir, close dir */

void do_ls(char []);

int main(int argc, char *argv[]) {
    int i;

    if (argc == 1) {
        do_ls(".");
    } else {
        for (i = 0; i < argc; i++) {
            printf("%s:\n", argv[i]);
            do_ls(argv[i]);
        }
    }

    return 0;
}

void do_ls(char dirname[]) {
    DIR *dir_ptr;
    struct dirent *direntp;

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls1: cannot open %s\n", dirname);
    } else {
        while ((direntp = readdir(dir_ptr)) != NULL) {
            printf("%s\n", direntp->d_name);
        }
        closedir(dir_ptr);
    }
}
