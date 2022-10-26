#include <stdio.h>
#include <stdlib.h>

int *return_local_variable(int num) {
    int result;
    result = num + 3;
    printf("result's address = %p\n", &result);
    return &result;
}

int *return_argument(int num) {
    num = num + 3;
    printf("num's address = %p\n", &num);
    return &num;
}

int *return_dynamic_allocation(int num) {
    int *p;
    p = (int *)malloc(sizeof(int));
    *p = num + 3;
    printf("p's address = %p\n", p);
    return p;
}

int main(void) {
    int *p;

    // p = return_local_variable(3);
    // printf("p = %p \n", p);
    // printf("*p = %d \n", *p);
    // p = return_argument(3);
    // printf("p = %p \n", p);
    // printf("*p = %d \n", *p);
    p = return_dynamic_allocation(3);
    printf("p = %p \n", p);
    printf("*p = %d \n", *p);

    return 0;
}
