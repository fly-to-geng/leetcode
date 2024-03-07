# [973. 最接近原点的 K 个点](https://leetcode-cn.com/problems/k-closest-points-to-origin/)

## 题目描述

我们有一个由平面上的点组成的列表 points。需要从中找出 K 个距离原点 (0, 0) 最近的点。

（这里，平面上两点之间的距离是欧几里德距离。）

你可以按任何顺序返回答案。除了点坐标的顺序之外，答案确保是唯一的。

 

示例 1：

      输入：points = [[1,3],[-2,2]], K = 1
      输出：[[-2,2]]
      解释： 
      (1, 3) 和原点之间的距离为 sqrt(10)，
      (-2, 2) 和原点之间的距离为 sqrt(8)，
      由于 sqrt(8) < sqrt(10)，(-2, 2) 离原点更近。
      我们只需要距离原点最近的 K = 1 个点，所以答案就是 [[-2,2]]。

示例 2：

      输入：points = [[3,3],[5,-1],[-2,4]], K = 2
      输出：[[3,3],[-2,4]]
      （答案 [[-2,4],[3,3]] 也会被接受。）
 

提示：

      1 <= K <= points.length <= 10000
      -10000 < points[i][0] < 10000
      -10000 < points[i][1] < 10000

## 解题思路

```
void swap(int **points, int index1, int index2)
{
    int tmp1, tmp2;

    tmp1 = points[index1][0];
    tmp2 = points[index1][1];

    points[index1][0] = points[index2][0];
    points[index1][1] = points[index2][1];

    points[index2][0] = tmp1;
    points[index2][1] = tmp2;

    return;
}
int less(int *a, int *b)
{
    if ((a[0] * a[0] + a[1] * a[1]) <= (b[0] * b[0] + b[1] * b[1])) {
        return 1;
    }
    return 0;
}

int partition(int **points, int start, int end)
{
    int *x = points[end];
    int i;
    int j = start - 1;

    for (i = start; i < end; i++) {
        if (less(points[i], x) == 1) {
            j = j + 1;
            swap(points, i, j);
        }
    }
    swap(points, j + 1, end);
    return j + 1;
}
void sorted(int **points, int start, int end)
{
    int mid;
    if (start >= end) {
        return;
    }
    mid = partition(points, start, end);
    sorted(points, start, mid - 1);
    sorted(points, mid + 1, end);
    return;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int K, int* returnSize, int** returnColumnSizes){
    int **ans;
    int *cols;
    int i, j;

    // 为答案开辟空间
    ans = (int**)malloc(sizeof(int*) * K);
    for (i = 0; i < K; i++) {
        ans[i] = (int*)malloc(sizeof(int) * 2);
    }
    cols = (int*)malloc(sizeof(int) * K);

    // 按照距离原点的距离排序
    sorted(points, 0, pointsSize - 1);

    // 取前K个放入结果中
    for (i = 0; i < K; i++) {
        ans[i][0] = points[i][0];
        ans[i][1] = points[i][1];
        cols[i] = 2;
    }

    *returnSize = K;
    *returnColumnSizes = cols;
    return ans;
}
```
