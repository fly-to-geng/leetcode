# [386. 字典序排数](https://leetcode-cn.com/problems/lexicographical-numbers/)

## 题目描述

给定一个整数 n, 返回从 1 到 n 的字典顺序。

例如，

    给定 n =1 3，返回 [1,10,11,12,13,2,3,4,5,6,7,8,9] 。

    请尽可能的优化算法的时间复杂度和空间复杂度。 输入的数据 n 小于等于 5,000,000。

## 解题思路

1. 暴力方法， 把数字转换成字符串，按照字符串比较大小。

```c
char *str(int n)
{
	char *ans = (char*)malloc(sizeof(char) * 1000);
	int ansEnd = 0;
	if (n == 0) {
		ans[ansEnd++] = '0';
		ans[ansEnd] = '\0';
		return ans;
	}
	while (n) {
		ans[ansEnd++] = n % 10 + '0';
		n = n / 10;
	}
	ans[ansEnd] = '\0';
	int left = 0;
	int right = ansEnd - 1;
	char tmp;
	while (left < right) {
		tmp = ans[left];
		ans[left] = ans[right];
		ans[right] = tmp;
        left++;
        right--;
	}
	return ans;
}
int compare(const void *p, const void *q)
{
	int a = *(int*)p;
	int b = *(int*)q;
	char *aString = str(a);
	int aSize = strlen(aString);
	char *bString = str(b);
	int bSize = strlen(bString);
	int i = 0;
    int ans = 0;
	while (i < aSize && i < bSize) {
		if (aString[i] != bString[i]) {
			ans = aString[i] - bString[i];
            break;
		} else {
			i++;
		}
	}
    
    free(aString);
    free(bString);
	if (i >= aSize) return -1;
	if (i >= bSize) return 1;

	return ans;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* lexicalOrder(int n, int* returnSize){
	int *ans = (int*)malloc(sizeof(int) * n);

	for (int i = 1; i <= n; i++) {
		ans[i-1] = i;
	}
	
	qsort(ans, n, sizeof(int), compare);
	
	*returnSize = n;
	return ans;
}
```

2. 先序遍历10叉数，直接生成结果。

