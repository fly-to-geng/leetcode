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

