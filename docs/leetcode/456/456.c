#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find132pattern(int* nums, int numsSize){
	if (nums == NULL || numsSize < 3) return false;
	int *mins = (int*)malloc(sizeof(int) * numsSize);
	mins[0] = nums[0];
	for (int i = 1; i < numsSize; i++) {
		if (nums[i] < mins[i-1]) {
			mins[i] = nums[i];
		} else {
			mins[i] = mins[i - 1];
		}
	}
    for (int i = 0; i < numsSize; i++) printf("%d, ", mins[i]);
	int *stack = (int*)malloc(sizeof(int) * numsSize);
	int top = 0;
	for (int i = numsSize - 1; i >= 0; i--) {
		if (nums[i] > mins[i]) {
			while (top > 0 && stack[top - 1] <= mins[i]) {
				top--;
			}
			if (top > 0 && stack[top - 1] < nums[i]) {
				return true;
			}
			stack[top++] = nums[i];
		}
	}
	return false;
}

int main()
{
    int nums[] = {1,3,2,4,5,6,9,1,6,5};
    int size = sizeof(nums) / sizeof(int);
    bool ans = find132pattern(nums, size);
    printf("%d\n", ans);
    return 0;
}