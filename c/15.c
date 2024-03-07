#define MAXANS 1000
#define TRUE 1
#define FALSE 0

int compare(const void *p, const void *q)
{
    int a = *(int *)p;
    int b = *(int *)q;

    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    }

    return 0;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    if (nums == NULL || numsSize <= 0) {
        return NULL;
    }

    int **ans;
    int ansEnd = 0;
    int *returnColumnSizesTmp;
    int returnColumnSizesTmpEnd = 0;
    int i, j, k, tmp;

    ans = (int**)malloc(sizeof(int*) * MAXANS);
    returnColumnSizesTmp = (int*)malloc(sizeof(int) * MAXANS);
    for (i = 0; i < MAXANS; i++) {
        ans[i] = (int*)malloc(sizeof(int) * 3);
        returnColumnSizesTmp[i] = 3;
    }

    qsort(nums, numsSize, sizeof(int), compare);

    for (i = 0; i < numsSize - 2; i++) {
        /* 如果和前面的一样，说明是重复答案 */
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        j = i + 1;
        k = numsSize - 1;
        printf("%d %d, ", j, k);
        while (j < k) {
            tmp = nums[j] + nums[k];
            if (tmp + nums[i] == 0) {
                /* 如果是重复答案，不记录 */
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    j += 1;
                    continue;
                }
                ans[ansEnd][0] = i;
                ans[ansEnd][1] = j;
                ans[ansEnd][2] = k;
                ansEnd += 1;
                j += 1;
            } else if (tmp > -nums[i]) {
                k -= 1;
            } else {
                j += 1;
            }
        }
    }

    *returnSize = ansEnd;
    return ans;
}