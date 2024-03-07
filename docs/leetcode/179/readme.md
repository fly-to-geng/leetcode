# [179. 最大数](https://leetcode-cn.com/problems/largest-number/)

## 题目描述

给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。

示例 1:

    输入: [10,2]
    输出: 210
  
示例 2:

    输入: [3,30,34,5,9]
    输出: 9534330

说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。

## 解题思路

本质上是确定一种排序时比较大小的方式，确定好大小之后，排序，输出。

1. 注意0转换成字符串的时候需要特殊处理
2. 注意结果是全0的时候输出一个0，而不能输出一串0


```
#define N 100 // 数字的最大位数
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int num2strSubProcess(char *str, int end, int num)
{
    int left = end;
    int right;
    char tmp;

    // 0 需要特殊处理
    if (num == 0) {
        str[end++] = '0';
        return end;
    }

    while (num) {
        str[end++] = (char)(num % 10 + '0');
        num = num / 10;
    }

    right = end - 1;

    while (left < right) {
        tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;
        left += 1;
        right -= 1;
    }

    return end;
}

void num2str(char *str, int num1, int num2)
{
    int end = 0;

    end = num2strSubProcess(str, end, num1);
    end = num2strSubProcess(str, end, num2);
    str[end] = '\0';

    return;
}
// num1 < num2 实现本题的关键比较逻辑
// 比较的方法是比较 num1num2 和 num2num1 的大小
int less(int num1, int num2)
{
    char *str1 = (char*)malloc(sizeof(char) * N * 2);
    char *str2 = (char*)malloc(sizeof(char) * N * 2);
    int i, n;

    num2str(str1, num1, num2);
    num2str(str2, num2, num1);
    n = strlen(str1);

    for (i = 0; i < n; i++) {
        if (str1[i] < str2[i]) {
            return 1;
        } else if (str1[i] > str2[i]) {
            return 0;
        }
    }

    return 0;
}
int partition(int *nums, int begin, int end)
{
    int x, i, j, tmp;

    x = nums[end];
    i = begin - 1;
    for (j = begin; j < end; j++) {
        if (less(nums[j], x) == 1) {
            i = i + 1;
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }

    tmp = nums[i + 1];
    nums[i + 1] = nums[end];
    nums[end] = tmp;

    return i + 1;
}

void sorted(int *nums, int begin, int end)
{
    int mid;

    if (begin > end) {
        return;
    }

    mid = partition(nums, begin, end);
    sorted(nums, begin, mid - 1);
    sorted(nums, mid + 1, end);
    return;
}

char * largestNumber(int* nums, int numsSize){
    int i, num, left, right, digit;
    char tmp;
    char *ans;
    int ansEnd = 0;

    if (numsSize == 0 || nums == NULL) {
        return NULL;
    }

    // 先按照规则从小到大排序
    sorted(nums, 0, numsSize - 1);

    ans = (char*)malloc(sizeof(char) * numsSize * N);

    // 依次取出每个数字，转化成字符拼接在一起
    for (i = numsSize - 1; i >= 0; i--) {
        num = nums[i];

        // 0 需要特殊处理
        if (num == 0) {
            ans[ansEnd++] = '0';
            continue;
        }

        left = ansEnd;
        right = left;
        while (num) {
            digit = num % 10;
            num = num / 10;
            ans[right++] = (char)(digit + '0');
        }
        ansEnd = right;
        right -= 1;
        while (left < right) {
            tmp = ans[left];
            ans[left] = ans[right];
            ans[right] = tmp;
            left++;
            right--;
        }
    }
    ans[ansEnd] = '\0';

    // 如果 ans 中全部都是0 缩写成一个0
    int flag = 1;
    for (i = 0; i < ansEnd; i++) {
        if (ans[i] != '0') {
            flag = 0;
            break;
        }
    }
    if (flag) {
        ans[0] = '0';
        ans[1] = '\0';
    }
    return ans;
}
```
