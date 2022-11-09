#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#define MODE_SIZE 11
#define PATH_SIZE 1024
#define ID_SIZE 10

#define IS_NOT_NULL(p) ((p))
#define IS_NULL(p) (!(p))
#define REALLOC(p, s) \
	p = realloc(p, s); \
	if (IS_NULL(p)) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

struct file_info {
    char mode_str[MODE_SIZE];
    int nlink;
    char *user_name;
    char *group_name;
    long size;
    time_t mtime;
    char *file_name;
};

enum sort_type { none, sort_time, sort_size };

enum sort_type s_type;

int get_option(int argc, char **argv);
void do_ls(char file_name[], enum sort_type s_type);
void create_file_info(char *file_name, struct file_info *f_info);
int compare_time(const void *a, const void *b);
int compare_size(const void *a, const void *b);
void show_file_info(struct file_info f_info);
void mode_to_letters(int, char[]);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);
void free_files_info(struct file_info **array, int n);

int main(int argc, char* argv[]) {
    char current_dir[PATH_SIZE];
    int n_option, n_path, i;

    getcwd(current_dir, PATH_SIZE);
    n_option = get_option(argc, argv);
    n_path = argc - n_option - 1;

    if (n_path == 0) {
        do_ls(".", s_type);
    } else {
        for (i = 1; i < argc; i++) {
            if ((argv[i])[0] != '-') {
                if (n_path == 1) {
                    do_ls(argv[i], s_type);
                } else {
                    printf("%s:\n", argv[i]);
                    do_ls(argv[i], s_type);
                    chdir(current_dir);
                    if (i < argc - 1) {
                        printf("\n");
                    }
                }
            }
        }
    }
}

int get_option(int argc, char **argv) {
    int c, i;

    /* -1: parse all option */
    for (i = 0; (c = getopt(argc, argv, "bt")) != -1; i++) {
        switch (c) {
            case 'b':
                s_type = sort_size;
                break;
            case 't':
                s_type = sort_time;
        }
    }

    return i;
}


void do_ls(char path[], enum sort_type s_type) {
    DIR *dir_p;
    struct dirent *dirent_p;
    struct file_info *files_info = NULL;  /* NULL for realloc */
    int count = 0, i;
    long total_size = 0;

    dir_p = opendir(path);

    if (IS_NULL(dir_p)) {
        fprintf(stderr, "ls3: cannot open %s\n", path);
    } else {
        while (IS_NOT_NULL(dirent_p = readdir(dir_p))) {
            chdir(path);
            REALLOC(files_info, sizeof(*files_info)*(count + 1));
            create_file_info(dirent_p->d_name, files_info + count);
            total_size += files_info[count].size;
            count++;
        }

        switch (s_type) {
            case none:
                break;
            case sort_time:
                qsort(files_info, count, sizeof(struct file_info), compare_time);
                break;
            case sort_size:
                qsort(files_info, count, sizeof(struct file_info), compare_size);
        }

        for (i = 0; i < count; i++) {
            show_file_info(files_info[i]);
        }

        printf("total number of files: %d\n", count);
        printf("total file size: %ld\n", total_size);

        closedir(dir_p);
    }

    free(files_info);
}

void create_file_info(char *file_name, struct file_info *f_info) {
    struct stat info;
    char mode_str[MODE_SIZE];

    if (stat(file_name, &info) == -1) {
        perror(file_name);
    }

    mode_to_letters(info.st_mode, mode_str);

    strcpy(f_info->mode_str, mode_str);
    f_info->nlink = (int)info.st_nlink;
    f_info->user_name = uid_to_name(info.st_uid);
    f_info->group_name = gid_to_name(info.st_gid);
    f_info->size = (long)info.st_size;
    f_info->mtime = info.st_mtime;
    f_info->file_name = file_name;
}

int compare_time(const void *a, const void *b) {
    struct file_info f_info1 = *(struct file_info *)a;
    struct file_info f_info2 = *(struct file_info *)b;

    return f_info1.mtime < f_info2.mtime ? -1 :
        f_info1.mtime > f_info2.mtime ? 1 :
        0;
}

int compare_size(const void *a, const void *b) {
    struct file_info f_info1 = *(struct file_info *)a;
    struct file_info f_info2 = *(struct file_info *)b;

    return f_info1.size < f_info2.size ? -1 :
        f_info1.size > f_info2.size ? 1 :
        0;
}

void show_file_info(struct file_info f_info) {
    printf("%s", f_info.mode_str);
    printf("%4d ", f_info.nlink);
    printf("%-8s ", f_info.user_name);
    printf("%-8s ", f_info.group_name);
    printf("%-8ld ", f_info.size);
    printf("%.12s ", 4 + ctime(&(f_info.mtime)));
    printf("%s \n", f_info.file_name);
}

void mode_to_letters(int mode, char str[]) {
    strcpy(str, "----------");  /* default = no perms */

    if (S_ISDIR(mode)) str[0] = 'd';  /* directory */
    if (S_ISCHR(mode)) str[0] = 'c';  /* char device */
    if (S_ISBLK(mode)) str[0] = 'b';  /* block device */

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
    static char uid_str[ID_SIZE];
    pw_ptr = getpwuid(uid);
    if (IS_NULL(pw_ptr)) {
        sprintf(uid_str, "%d", uid);
        return uid_str;
    } else {
        return pw_ptr->pw_name;
    }
}

char *gid_to_name(gid_t gid) {
    struct group *grp_ptr;
    static char gid_str[ID_SIZE];
    grp_ptr = getgrgid(gid);
    if (IS_NULL(grp_ptr)) {
        sprintf(gid_str, "%d", gid);
        return gid_str;
    } else {
        return grp_ptr->gr_name;
    }
}
