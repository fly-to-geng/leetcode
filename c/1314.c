int compute(int **matrixSums, int x1, int y1, int x2, int y2)
{
    if (x1 == 0 && y1 == 0) return matrixSums[x2][y2];
    if (x1 == 0) {
        return matrixSums[x2][y2] - matrixSums[x2][y1-1];
    }
    if (y1 == 0) {
        return matrixSums[x2][y2] - matrixSums[x1-1][y2];
    }

    int ans = matrixSums[x2][y2] - matrixSums[x2][y1-1] - matrixSums[x1-1][y2] + matrixSums[x1-1][y1-1];
    return ans;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** matrixBlockSum(int** mat, int matSize, int* matColSize, int K, int* returnSize, int** returnColumnSizes)
{
    int **ans;
    int ansEnd = 0;
    int *colsSize;
    int colsSizeEnd = 0;

    if (mat == NULL || matSize == 0 || matColSize == NULL) {
        *returnColumnSizes = &colsSize;
        *returnSize = 0;
        return NULL;
    }

    if (matSize == 1 || matColSize[0] == 0) {
        *returnColumnSizes = &colsSize;
        *returnSize = 0;
        return NULL;
    }

    if (K == 0) {
        *returnColumnSizes = matColSize;
        *returnSize = matSize;
        return mat;
    }

    // 计算矩阵和存储下来
    int **sums = (int**)malloc(sizeof(int*) * matSize);
    for (int i = 0; i < matSize; i++) {
        sums[i] = (int*)malloc(sizeof(int) * matColSize[i]);
    }
    sums[0][0] = mat[0][0];
    for (int i = 1; i < matSize; i++) {
        sums[i][0] = sums[i-1][0] + mat[i][0];
    }
    for (int j = 1; j < matColSize[0]; j++) {
        sums[0][j] = sums[0][j-1] + mat[0][j];
    }
    for (int i = 1; i < matSize; i++) {
        for (int j = 1; j < matColSize[i]; j++) {
            sums[i][j] = sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] + mat[i][j];
        }
    }

    colsSize = (int*)malloc(sizeof(int) * matSize);
    for (int i = 0; i < matSize; i++) {
        colsSize[i] = matColSize[i];
    }
    ans = (int**)malloc(sizeof(int*) * matSize);
    for (int i = 0; i < matSize; i++) {
        ans[i] = (int*)malloc(sizeof(int) * matColSize[i]);
    }

    // 计算区域和
    int x1, y1, x2, y2;
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[i]; j++) {
            x1 = i - K < 0 ? 0 : i - K;
            y1 = j - K < 0 ? 0 : j - K;
            x2 = i + K >= matSize ? matSize - 1 : i + K;
            y2 = j + K >= matColSize[matSize-1] ? matColSize[matSize-1] - 1 : j + K;
            // (x1,y1) -- (x2, y2) 矩阵的和
            ans[i][j] = compute(sums, x1, y1, x2, y2);
        }
    }

    // 释放不使用的内存
    for (int i = 0; i < matSize; i++) {
        free(sums[i]);
    }
    free(sums);

    *returnSize = matSize;
    *returnColumnSizes = colsSize;
    return ans;
}