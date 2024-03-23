#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minAddToMakeValid(char * S){
    int ans = 0;
    char *stack = (char*)malloc(sizeof(char) * (strlen(S)));
    int top = 0;
    for (int i = 0; i < strlen(S); i++) {
        if (S[i] == '(') {
            stack[top++] = S[i];
        } else if (S[i] == ')' && top > 0) {
            top--;
        } else {
            ans += 1;
        }
    }
    

    free(stack);
    return ans + top;
}

int main()
{
    char s[] = "(()()(((()((()))))";
    int ans = minAddToMakeValid(s);
    printf("%d\n", ans);
    return 0;
}