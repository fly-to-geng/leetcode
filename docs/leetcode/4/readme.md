## [4. 寻找两个有序数组的中位数](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)

### 题目描述

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。

**示例**

```
示例 1:
nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
示例 2:
nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5
```

### 解题思路1

暴力解法很容易想到，把两个有序数组合并(O(m+n)), 再取出中位数(O(1)),时间复杂度上不符合要求。
不额外开辟空间存储合并之后的数组，只用两个指针记录也是一样的，这样可以节省存储空间和时间，但是不会有
时间复杂度的提升，本质上都是暴力方法。

#### C++

```c
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i = 0;
        int j = 0;
        int size1 = nums1.size();
        int size2 = nums2.size();
        vector<int> merge;
        while (i < size1 && j < size2)
        {
            if (nums1[i] <= nums2[j])
            {
                merge.push_back(nums1[i]);
                i++;
            }
            else
            {
                merge.push_back(nums2[j]);
                j++;
            }
        }
        while (i < size1)
        {
            merge.push_back(nums1[i]);
            i++;
        }
        while (j < size2)
        {
            merge.push_back(nums2[j]);
            j++;
        }
        
        int size3 = merge.size();
        if (size3 % 2 == 0)
        {
            int pos2 = size3 / 2;
            int pos1 = pos2 - 1;
            float ans = (merge[pos1] + merge[pos2]) / 2.0;
            return ans;
        }
        else
        {
            float ans = (float)merge[size3 / 2];
            return ans;
        }
        
        return -1;
    }
};
```

#### python

```python
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        i = 0
        j = 0
        merge = []
        while (i < len(nums1) and j < len(nums2)):
            if nums1[i] <= nums2[j]:
                merge.append(nums1[i])
                i = i + 1
            else:
                merge.append(nums2[j])
                j = j + 1
        while i < len(nums1):
            merge.append(nums1[i])
            i = i + 1
        while j < len(nums2):
            merge.append(nums2[j])
            j = j + 1
            
        if (len(merge) % 2 == 0):
            pos2 = len(merge) // 2
            pos1 = pos2 - 1
            ans = (merge[pos1] + merge[pos2]) / 2.0
            return ans
        else:
            ans = float( merge[len(merge) // 2] )
            return ans
        
```

### 解题思路2

中位数是把数组排序之后，位于中间位置的数字，如果中间位置有两个数字，中位数是中间两个数字的平均值。

设数组 array 元素个数为n, n为奇数时，中位数位置为i; i + 1 = n - i + 1 - 1, 即左侧元素数量 = 右侧元素数量 + 1

如果n为偶数, 中位数的位置为 i, i+1; i = (n - (i+1)) + 1, 即左侧元素数量 = 右侧元素数量

上面两个公式计算出 i = n / 2 (整数除法).

当有两个数组 A, B 的时候， 我们用 i, j 分割 A, B 为前后两个部分, m, n 分别是 A， B的大小。

```
                left_part | right_part
A[0], A[1], ..., A[i - 1] | A[i], A[i+1], ..., A[m-1]
B[0], B[1], ..., B[j - 1] | B[j], B[j+1], ..., B[n-1]
```

当 len(left_part) == len(right_part) 且 max(left_part) <= min(right_part) 的时候， 我们就找到了中位数。
- (m + n) / 2 == 0, midian = (max(left_part) + min(right_part)) / 2
- (m + n) / 2 != 0, midian = max(left_part)

左半部分长度 = 右半部分长度， 就是 i + j = (m - i + n - j) 或者 i + j = (m - i + n - j) + 1, 奇数时右侧少一个元素。
换算之后得到 i + j = (m + n + 1) / 2;

我们遍历i, 从0到m-1, 找到对应的j， 然后检查max(left_part) <= min(right_part)， 一旦满足要求，就可以返回结果。

```c++
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int m = nums1Size;
    int n = nums2Size;
    int i, j, mid1, mid2;
    int left_max, right_min;

    if (m <= 0) {
        if (n % 2 != 0) return (double)nums2[n / 2];
        if (n % 2 == 0) return (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0;
    }

    if (n <= 0) {
        if (m % 2 != 0) return (double)nums1[m / 2];
        if (m % 2 == 0) return (nums1[m / 2 - 1] + nums1[m / 2]) / 2.0;
    }
    // i = 0 时表示 nums1 中不取值， i = m 表示 nums1 中的值全部在left_part
    for (i = 0; i <= m; i++) {
        j = (m + n + 1) / 2 - i;
        // left_max 是 max(A[i-1], B[j-1]), 因为是有序数组，只要比较最后两个的大小
        if (i == 0) left_max = nums2[j - 1];
        else if (j == 0) left_max = nums1[i - 1];
        else {
            left_max = MAX(nums1[i-1], nums2[j-1]);
        }

        // right_min 取最开始两个元素的最小值
        if (i == m) right_min = nums2[j];
        else if (j == n) right_min = nums1[i];
        else right_min = MIN(nums1[i], nums2[j]);

        if (left_max <= right_min) {
            if ((m + n) % 2 == 0) return (left_max + right_min) / 2.0;
            if ((m + n) % 2 != 0) return (double)left_max;
        }
    }

    return 0.0;
}
```

这种方法的时间复杂度是 O(m), 是大于题目要求 $O(log(m + n))$ 的。
只要在查找的时候使用二分查找， 因为数组是有序的， 时间复杂度就可以降低到 $O(log(min(m,n)))$.

```c
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    // i 指向 nums1 的前半部分， j 指向 nums2 的前半部分
    // nums1 + nums2 的前半部分 和 后半部分满足如下条件的时候，可以找到中位数
    // nums1Size + nums2Size 是偶数， len(left_part) == len(right_part) 且 max(left_part) <= min(right_part)
    // nums1Size + nums2Size 是奇数， len(left_part) == len(right_part) + 1 且 max(left_part) <= min(right_part)
    // 如果满足上述条件，可以认为找到中位数，因为中位数的作用就是分割数组为两个数量相等的部分， 使得前面的都小于等于后面的
    // i + j = nums1Size - i + nums2Size - j , 如果 i 是偶数
    // i + j = nums1Size - i + nums2Size - j + 1, 如果 i 是奇数
    // 换算出 i 和 j 的关系： i + j = (nums1Size + nums2Size + 1) / 2, 除是整数除法，不用区分奇数偶数

    int left = 0;
    int right = nums1Size;
    int mid1, mid2; // 存储最中间的两个或者一个数字
    while (left <= right) {
        // 从 nums1 中间位置开始搜索
        int i = (left + right) / 2;
        int j = (nums1Size + nums2Size + 1) / 2 - i;

        // 边界情况的处理，如果是前半部分的边界， 设置成最小值
        // 如果是后半部分的边界，设置成最大值
        // nums[i-1], nums[i], nums[j-1], nums[j] 边界注意
        int nums_i_1 = (i == 0) ? INT_MIN : nums1[i-1];
        int nums_i = (i == nums1Size) ? INT_MAX : nums1[i];
        int nums_j_1 = (j == 0) ? INT_MIN : nums2[j-1];
        int nums_j = (j == nums2Size) ? INT_MAX : nums2[j];

        // nums[i-1] <= nums[j] 且 nums[j - 1] <= nums[i] 的时候，即找到
        // nums[i-1] <= nums[j] 的时候, 继续增加i, 否则减少i
        if (nums_i_1 <= nums_j) {
            mid1 = (nums_i_1 > nums_j_1) ? nums_i_1 : nums_j_1;
            mid2 = (nums_i < nums_j) ? nums_i : nums_j;
            left = i + 1;
        } else {
            right = i - 1;
        }
    }

    float ans = -99999;
    if ((nums1Size + nums2Size) % 2 == 0) {
        ans = (mid1 + mid2) / 2.0;
    } else {
        ans = mid1;
    }
    return ans;
}
```

