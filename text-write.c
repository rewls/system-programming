#include <stdio.h>

int main() {
    FILE *fp;
    int x = 20;

    fp = fopen("data.txt", "w");
    fprintf(fp, "x = %d", x);
    fclose(fp);

    return 0;
}

