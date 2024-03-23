#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize){
	int *stack = (int *)malloc(sizeof(int) * pushedSize);
	int top = 0;
	
	int i = 0;
	int j = 0;
	while (j < poppedSize) {
		// 如果栈顶与popped[j]相同，则弹出
		if (top > 0 && stack[top - 1] == popped[j]) {
			top--;
		} else {
			// popped[j] 之前的都入栈
			while(i < pushedSize && pushed[i] != popped[j]) {
				stack[top++] = pushed[i++];
			}
			if (i >= pushedSize) {
				return false;
			}
			i++;
		}
		j += 1;
	}
	if (top == 0) {
		return true;
	} else {
		return false;
	}
}

int main()
{
    return 0;
}