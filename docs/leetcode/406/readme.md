# [406. 根据身高重建队列](https://leetcode-cn.com/problems/queue-reconstruction-by-height/)

## 题目描述

假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。

注意：
总人数少于1100人。

示例

    输入:
    [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

    输出:
    [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

## 解题思路

```c
int compare(const int *p, const int *q)
{
	int *a = *(int **)p;
	int *b = *(int **)q;
	if (a[0] != b[0]) {
		return a[0] - b[0];
	} else {
		return b[1] - a[1];
	}
	return 0;
}
int *deepCopy(int *arr)
{
	int *ans = (int*)malloc(sizeof(int) * 2);
	ans[0] = arr[0], ans[1] = arr[1];
	return ans;
}
	
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, 
						int* returnSize, int** returnColumnSizes){
	int *cols = (int*)malloc(sizeof(int) * peopleSize);
	for (int i = 0; i < peopleSize; i++) cols[i] = 2;
	if (people == NULL || peopleSize == 0 || peopleColSize == NULL) {
		*returnSize = 0;
		*returnColumnSizes = cols;
		return NULL;
	}
	
	int **ans = (int**)malloc(sizeof(int*) * peopleSize);
	for (int i = 0; i < peopleSize; i++) ans[i] = NULL;
	
	qsort(people, peopleSize, sizeof(int) * 2, compare);

	for (int i = 0; i < peopleSize; i++) {
		int pos = people[i][1];
		int blankCount = 0; // 统计空位置的数量
		int j = 0;
		while (blankCount <= pos && j < peopleSize) {
			if (ans[j] == NULL) {
				blankCount++;
			}
			j++;
		}
		if (j <= peopleSize && blankCount > pos) {
            printf("%d : [%d, %d]\n", j - 1, people[i][0], people[i][1]);
			ans[j - 1] = deepCopy(people[i]);
		} else {
			printf("%d, %d, %d\n", blankCount, pos, j);
		}
	}
	
	*returnSize = peopleSize;
	*returnColumnSizes = cols;
	return ans;
}
```
