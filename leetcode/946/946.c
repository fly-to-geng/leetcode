#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize){
	int *stack = (int *)malloc(sizeof(int) * pushedSize);
	int top = 0;
	int start = 0;
    for (int i = 0; i < poppedSize; i++) {
        if (start < pushedSize && popped[i] == pushed[start]) {
            start++;
        } else if (top > 0 && stack[top - 1] == popped[i]) {
            top--;
        } else {
            while (start < pushedSize && popped[i] != pushed[start]) {
                stack[top++] = pushed[start++];
            }
            start++;
        }
    }
    if (top > 0) {
        return false;
    }

    return true;
}

int main()
{
    int pushed[] = {1,2,3,4,5};
    int poped[] = {4,5,3,2,1};
    bool ans = validateStackSequences(pushed, 5, poped, 5);
    return 0;
}