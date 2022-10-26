#include <stdio.h>
#include <string.h>
#include <dirent.h>  /* struct dirent, DIR, opendir,
                        closedir */
#include <sys/stat.h>  /* system call stat, struct stat,
                          macros */
#include <pwd.h>  /* uid_t, struct passwd, getpwuid */
#include <grp.h>  /* gid_t, struct group, getgrgid */

void do_ls(char []);
void do_stat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int, char[]);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);

int main(int argc, char* argv[]) {
    int i;

    if (argc == 1) {
        do_ls(".");
    } else {
        for (i = 0; i < argc; i++) {
            printf("%s:\n", argv[i]);
            do_ls(argv[i]);
        }
    }
}

void do_ls(char dirname[]) {
    /*
     * list files in directory called dirname
     */
    DIR *dir_ptr;  /* the directory */
    struct dirent *direntp;  /* each entry */
    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls2: cannot open %s\n", dirname);
    } else {
        while ((direntp = readdir(dir_ptr)) != NULL) {
            do_stat(direntp->d_name);
        }
        closedir(dir_ptr);
    }
}

void do_stat(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1) {
        perror(filename); /* say why */
    } else {
        show_file_info(filename, &info);
    }
}

void show_file_info(char *filename, struct stat *info_p) {
    char *uid_to_name(), *ctime(), *git_to_name(), *filemode();
    void mode_to_letters();
    char modestr[11];

    mode_to_letters(info_p->st_mode, modestr);
    printf("%s", modestr);
    printf("%4d ", (int)info_p->st_nlink);
    printf("%-8s ", uid_to_name(info_p->st_uid));
    printf("%-8s ", gid_to_name(info_p->st_gid));
    printf("%-8ld ", (long)info_p->st_size);
    printf("%.12s ", 4+ctime(&info_p->st_mtime));
    printf("%s \n", filename);
}

void mode_to_letters(int mode, char str[])
{
    strcpy(str, "----------");  /* default = no perms */

    if (S_ISDIR(mode)) str[0] = 'd';  /* directory */
    if (S_ISCHR(mode)) str[0] = 'c';  /* char device */
    if (S_ISBLK(mode)) str[0] = 'b'; /* block device */

    if (mode & S_IRUSR) str[1] = 'r';  /* 3 bits for user */
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';  /* 3 bits for group */
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';  /* 3 bits for other */
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}

char *uid_to_name(uid_t uid) {
    struct passwd *pw_ptr;
    static char numstr[10];
    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d", uid);
        return numstr;
    } else {
        return pw_ptr->pw_name;
    }
}

char *gid_to_name(gid_t gid) {
     struct group *grp_ptr;
     static char numstr[10];
     if ((grp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    } else {
        return grp_ptr->gr_name;
    }
}
