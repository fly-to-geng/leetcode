# [42. 接雨水](https://leetcode-cn.com/problems/trapping-rain-water/)

## 题目描述

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rainwatertrap.png)

上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。

示例:

      输入: [0,1,0,2,1,0,1,3,2,1,2,1]
      输出: 6
      
      
## 解题思路

```c
int trap(int* height, int heightSize){
    int left = 0;
    int right = heightSize - 1;
    int ans = 0;
    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left+1] < height[left] && left + 1 < right) {
                ans += height[left] - height[left+1];
                height[left+1] = height[left];
            }
            left++;
        } else {
            if (height[right] > height[right-1] && right - 1 > left) {
                ans += height[right] - height[right-1];
                height[right-1] = height[right];
            }
            right--;
        }
    }
    return ans;
}
```
