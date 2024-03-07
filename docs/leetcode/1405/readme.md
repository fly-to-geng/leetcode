# [1405. 最长快乐字符串](https://leetcode-cn.com/problems/longest-happy-string/)

## 题目描述

如果字符串中不含有任何 'aaa'，'bbb' 或 'ccc' 这样的字符串作为子串，那么该字符串就是一个「快乐字符串」。

给你三个整数 a，b ，c，请你返回 任意一个 满足下列全部条件的字符串 s：

s 是一个尽可能长的快乐字符串。
s 中 最多 有a 个字母 'a'、b 个字母 'b'、c 个字母 'c' 。
s 中只含有 'a'、'b' 、'c' 三种字母。
如果不存在这样的字符串 s ，请返回一个空字符串 ""。

示例 1：

    输入：a = 1, b = 1, c = 7
    输出："ccaccbcc"
    解释："ccbccacc" 也是一种正确答案。

示例 2：

    输入：a = 2, b = 2, c = 1
    输出："aabbc"

示例 3：

    输入：a = 7, b = 1, c = 0
    输出："aabaa"
    解释：这是该测试用例的唯一正确答案。
 

提示：

    0 <= a, b, c <= 100
    a + b + c > 0

## 解题思路

```c
#define N 2000

// 获取除了except之外的最大值得下标
int getMax(int *map, int except)
{
	int index = -1;
	int max = INT_MIN;
	for (int i = 0; i < 3; i++) {
		if (i != except) {
			if (map[i] > max) {
				max = map[i];
				index = i;
			}
		}
	}
	return index;
}
char * longestDiverseString(int a, int b, int c){
	char *ans = (char*)malloc(sizeof(char) * N);
	int ansEnd = 0;
	int *map = (int*)malloc(sizeof(int) * 3);
	map[0] = a, map[1] = b, map[2] = c;
	
	int except = -1;
	int index = -1;
	while (map[0] + map[1] + map[2]) {
		index = getMax(map, except);
		// 如果最大值小于等于前一个字母，消耗一个
		if (except == -1 || map[index] > map[except]) {
			if (map[index] > 0) {
				ans[ansEnd++] = index + 'a';
				map[index]--;
			}
			if (map[index] > 0) {
				ans[ansEnd++] = index + 'a';
				map[index]--;
			}
		} else {
			if (map[index] > 0) {
				ans[ansEnd++] = index + 'a';
				map[index]--;
			}
		}
		except = index;
		if (map[0] + map[1] + map[2] - map[except] == 0) {
			ans[ansEnd] = '\0';
			return ans;
		}
	}
	ans[ansEnd] = '\0';
	free(map);
	return ans;
}
```
