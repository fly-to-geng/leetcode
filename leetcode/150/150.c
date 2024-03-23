#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int op(char *o, int a, int b)
{
    if (strcmp(o, "+") == 0) return a + b;
    if (strcmp(o, "-") == 0) return a - b;
    if (strcmp(o, "*") == 0) return a * b;
    if (strcmp(o, "/") == 0) return a / b;
    return 0;
}
int evalRPN(char ** tokens, int tokensSize){
    int ans = 0;
    int *stack = (int*)malloc(sizeof(int) * tokensSize);
    int top = 0;

    // 遇到数字入栈，遇到操作符从栈中取数字操作
    for (int i = 0; i < tokensSize; i++) {
        if (strcmp(tokens[i], "+") == 0 ||
            strcmp(tokens[i], "-") == 0 ||
            strcmp(tokens[i], "*") == 0 ||
            strcmp(tokens[i], "/") == 0) {
                int num1 = stack[--top];
                int num2 = stack[--top];
                int num3 = op(tokens[i], num2, num1);
                stack[top++] = num3;
        } else {
            stack[top++] = atoi( tokens[i] );
        }
    }

    ans = stack[0];
    free(stack);
    return ans;
}

int main()
{
    char *tokens[] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    int tokenSize = 13;
    int ans = evalRPN(tokens, tokenSize);
    printf("ans:%d\n", ans);

    return 0;
}