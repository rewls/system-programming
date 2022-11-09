#include <stdio.h>
#include <stdlib.h>

#define IS_NULL(p) (!(p))
#define IS_NOT_NULL(p) (p)
#define MALLOC(p, s) \
	p = malloc(s); \
	if (IS_NULL(p)) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}
#define SCANF(s, p) \
	scanf(s, p); \
    while (getchar() != '\n');
#define MAX_OPERATOR_STRING_SIZE 9

typedef struct _calculatorNode {
    int a;
    int b;
    char name;
    int (*fptr) (int, int);
    struct _calculatorNode *next;
} calculatorNode;

typedef enum {_, create, printN, printR, removeAll, exitProgram} menu;

int add(int a, int b);
int sub(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
calculatorNode * createNode(int a, int b, char name, int (*fptr)(int, int));
void addNode(calculatorNode **head, calculatorNode *node);
void printNode(calculatorNode *head);
void printResult(calculatorNode *head);
void freeAll(calculatorNode *head);

int main()
{
    calculatorNode *head;
    menu selectedMenu;
    char operator;
    int a, b;

    do {
        printf("1. 계산 노드 생성\n");
        printf("2. 현재까지 생성된 계산 노드 출력\n");
        printf("3. 현재까지 생성된 계산 노드들의 계산 결과 출력\n");
        printf("4. 전체 삭제\n");
        printf("5. 프로그램 종료\n");
        printf("1~5 중 선택: ");
        SCANF("%d", &selectedMenu);

        switch(selectedMenu) {
            case create:
                printf("+, -, *, / 중 선택: ");
                SCANF("%c", &operator);
                printf("operand1: ");
                SCANF("%d", &a);
                printf("operand2: ");
                SCANF("%d", &b);
                switch (operator) {
                    case '+':
                        addNode(&head, createNode(a, b, operator, add));
                        break;
                    case '-':
                        addNode(&head, createNode(a, b, operator, sub));
                        break;
                    case '*':
                        addNode(&head, createNode(a, b, operator, multiply));
                        break;
                    case '/':
                        addNode(&head, createNode(a, b, operator, divide));
                        break;
                }
                break;
            case printN:
                printNode(head);
                break;
            case printR:
                printResult(head);
                break;
            case removeAll:
                freeAll(head);
                head = NULL;
                printf("\n");
                break;
            case exitProgram:
                return 0;
        }
    } while (1);

    return 0;
}

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}

calculatorNode *createNode(int a, int b, char name, int (*fptr) (int, int))
{
    calculatorNode *node;
    MALLOC(node, sizeof(*node));
    node->a = a;
    node->b = b;
    node->name = name;
    node->fptr = fptr;
    return node;
}

void addNode(calculatorNode **head, calculatorNode *node)
{
    calculatorNode *cur = *head;
    if (IS_NULL(*head))
        *head = node;
    else {
        while (IS_NULL(cur)) {
            cur = cur->next;
        }
        cur->next = node;
    }
}

void printNode(calculatorNode *head)
{
    while (IS_NOT_NULL(head)) {
        printf("%d %c %d\n", head->a, head->name, head->b);
        head = head->next;
    }
    printf("\n");
}

void printResult(calculatorNode *head)
{
    while (IS_NOT_NULL(head)) {
        printf("%d %c %d = %d\n", head->a, head->name, head->b, (head->fptr)(head->a, head->b));
        head = head->next;
    }
    printf("\n");
}

void freeAll(calculatorNode *head)
{
    if (IS_NULL(head))
        return;
    freeAll(head->next);
    free(head);
}
