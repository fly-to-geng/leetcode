# [1386. 安排电影院座位](https://leetcode-cn.com/problems/cinema-seat-allocation/)

## 题目描述

如上图所示，电影院的观影厅中有 n 行座位，行编号从 1 到 n ，且每一行内总共有 10 个座位，列编号从 1 到 10 。

给你数组 reservedSeats ，包含所有已经被预约了的座位。比如说，researvedSeats[i]=[3,8] ，它表示第 3 行第 8 个座位被预约了。

请你返回 最多能安排多少个 4 人家庭 。4 人家庭要占据 同一行内连续 的 4 个座位。隔着过道的座位（比方说 [3,3] 和 [3,4]）不是连续的座位，但是如果你可以将 4 人家庭拆成过道两边各坐 2 人，这样子是允许的。

 

示例 1：



        输入：n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
        输出：4
        解释：上图所示是最优的安排方案，总共可以安排 4 个家庭。蓝色的叉表示被预约的座位，橙色的连续座位表示一个 4 人家庭。

示例 2：

        输入：n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
        输出：2

示例 3：

        输入：n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
        输出：4
 

提示：

        1 <= n <= 10^9
        1 <= reservedSeats.length <= min(10*n, 10^4)
        reservedSeats[i].length == 2
        1 <= reservedSeats[i][0] <= n
        1 <= reservedSeats[i][1] <= 10
        所有 reservedSeats[i] 都是互不相同的。

## 解题思路

```c
int familysInRow(int *seated)
{
    if (seated[1] == 0 && seated[2] == 0 && seated[3] == 0 && seated[4] == 0 &&
        seated[5] == 0 && seated[6] == 0 && seated[7] == 0 && seated[8] == 0) {
        return 2;
    }
    if (seated[1] == 0 && seated[2] == 0 && seated[3] == 0 && seated[4] == 0) {
        return 1;
    }
    if (seated[3] == 0 && seated[4] == 0 && seated[5] == 0 && seated[6] == 0) {
        return 1;
    }
    if (seated[5] == 0 && seated[6] == 0 && seated[7] == 0 && seated[8] == 0) {
        return 1;
    }
    return 0;    
}

int compare(const void *p, const void *q)
{
    int *a = *(int**)p;
    int *b = *(int**)q;
    printf("pp:%d, %d\n", a[0],b[0]);
    return a[0] - b[0];
}
int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize){
    int *row = (int*)malloc(sizeof(int) * 10);
    int rowEnd = 0;
    int ans = 0;

    qsort(reservedSeats, reservedSeatsSize, sizeof(int) * 2, compare);

    int line = 1;
    int iter = 0;
    int count = 0;
    while (iter < reservedSeatsSize) {
        for (int i = 0; i < 10; i++) row[i] = 0;
        if (count > 1) {
            ans += 2 * (count - 1);
        }
        count = 0;
        while (iter < reservedSeatsSize && reservedSeats[iter][0] == line) {
            printf("\n%d,%d\n", reservedSeats[iter][0], iter);
            row[ reservedSeats[iter][1]-1 ] = 1;
            iter++;
        }
        ans += familysInRow(row);
        while (iter < reservedSeatsSize && reservedSeats[iter][0] > line) {
            line++;
            count++;
        } 
    }
    if (n - line > 0) {
        ans += 2 * (n - line);
    }
    free(row);

    return ans;
}
```