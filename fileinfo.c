#include <stdio.h>
#include <sys/stat.h>  /* struct stat */

void show_stat_info(char *, struct stat );

int main(int argc, char *argv[]) {
    struct stat info;

    if (argc > 1) {
        if (stat(argv[1], &info) != -1) {
            show_stat_info(argv[1], info);
            return 0;
        } else {
            perror(argv[1]);
        }
        return 1;
    }
}

void show_stat_info(char *fname, struct stat buf) {
    printf("   mode: %o\n", buf.st_mode);
    printf("  links: %lu\n", buf.st_nlink);
    printf("   user: %d\n", buf.st_uid);
    printf(" groups: %d\n", buf.st_gid);
    printf("   size: %li\n", buf.st_size);
    printf("modtime: %li\n", buf.st_mtime);
    printf("   name: %s\n", fname);
}
