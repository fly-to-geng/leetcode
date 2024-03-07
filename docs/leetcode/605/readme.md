# [605. 种花问题](https://leetcode-cn.com/problems/can-place-flowers/)

## 题目描述

假设你有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花卉不能种植在相邻的地块上，它们会争夺水源，两者都会死去。

给定一个花坛（表示为一个数组包含0和1，其中0表示没种植花，1表示种植了花），和一个数 n 。能否在不打破种植规则的情况下种入 n 朵花？能则返回True，不能则返回False。

示例 1:

    输入: flowerbed = [1,0,0,0,1], n = 1
    输出: True

示例 2:

    输入: flowerbed = [1,0,0,0,1], n = 2
    输出: False

注意:

    数组内已种好的花不会违反种植规则。
    输入的数组长度范围为 [1, 20000]。
    n 是非负整数，且不会超过输入数组的大小。

## 解题思路

先处理只有一个元素的情况
对于两个及以上的元素，判断每个位置是否能种花，如果能种， n - 1 同时将该位置种上花。
最后判断N是否为0.

```
bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n){
    int i;
    // 只有一个元素的单独处理
    if (flowerbedSize == 1 && flowerbed[0] == 0 && n == 1) {
        return true;
    }
    for (i = 0; i < flowerbedSize; i++) {
        if (flowerbed[i] == 1) {
            continue;
        }
        // 如果位于起始位置，只要后面一个不是1，就可以种花
        if (i == 0 && i + 1 < flowerbedSize && flowerbed[i + 1] == 0) {
            n = n - 1;
            flowerbed[i] = 1;
        }
        // 如果位于最后，只要前一个位置不是1，就可以种花
        if (i == flowerbedSize - 1 && i - 1 >= 0 && flowerbed[i - 1] == 0) {
            n = n - 1;
            flowerbed[i] = 1;
        }
        if (i - 1 >= 0 && i + 1 < flowerbedSize && flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
            n = n - 1;
            flowerbed[i] = 1;
        }
    }

    if (n > 0) {
        return false;
    }

    return true;
}
```
