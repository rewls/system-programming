#include <stdio.h>

// function declaration
int add(int a, int b);
int multiply(int a, int b);
void printData(int a);

int main() {
    // function pointer declaration
    // name: fptr, type: int (*)(int, int)
    // return type: int, parameter type: int, int
    int (*fptr)(int, int);
    // function declaration
    // int *fptr (int, int);
    void (*vptr)(int);
    int a;

    fptr = add;
    vptr = printData;

    a = fptr(4, 5);
    printf("a = %d\n", a);

    fptr = multiply;
    a = fptr(4, 5);
    printf("a = %d\n", a);

    printf("fptr = %p\n", fptr);
    printf("function add = %p \n", add);
    printf("function main = %p \n", main);

    return 0;
}

int add(int a, int b) {
    int result;
    result = a + b;
    return result;
}

int multiply(int a, int b) {
    int result;
    result = a * b;
    return result;
}

void printData(int a) {
    printf("a = %d\n", a);
}
