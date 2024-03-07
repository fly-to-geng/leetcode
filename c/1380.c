#define MAX_ANS 1000

int minRows(int **matrix, int row, int rowSize)
{
    int minValue = INT_MAX;
    for (int i = 0; i < rowSize; i++) {
        if (matrix[row][i] < minValue) {
            minValue = matrix[row][i];
        }
    }
    return minValue;
}

int maxCols(int **matrix, int col, int colSize)
{
    int maxValue = INT_MIN;
    for (int i = 0; i < colSize; i++) {
        if (matrix[i][col] > maxValue) {
            maxValue = matrix[i][col];
        }
    }
    return maxValue;
}

int* luckyNumbers (int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    int *ans = NULL;
    int ansEnd = 0;

    if (matrix == NULL || matrixSize == 0) {
        *returnSize = 0;
        return ans;
    }

    if (matrixSize == 1 && matrixColSize[0] == 0) {
        *returnSize = 0;
        return ans;
    }

    ans = (int*)malloc(sizeof(int) * MAX_ANS);
    for (int i = 0; i < matrixSize; i++) {
        int minValue = minRows(matrix, i, matrixColSize[i]);
        for (int j = 0; j < matrixColSize[i]; j++) {
            if (matrix[i][j] == minValue) {
                int maxValue = maxCols(matrix, j, matrixSize);
                if (maxValue == minValue) {
                    ans[ansEnd++] = minValue;
                }
            }
        }
    }

    return ans;
}