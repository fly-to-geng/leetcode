// 不使用额外的空间
void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    int i, j;
    int delFirstRow = 0; // 标记第一行是否应该清0
    int delRow = 0; // 标记该行是否应该清0

    // 第一行是否应该清0
    for (j = 0; j < matrixColSize[0]; j++) {
        if (matrix[0][j] == 0) {
            delFirstRow = 1;
            break;
        }
    }

    // 统计每一行需要清0的列，记录在第一行，然后清零该行
    for (i = 1; i < matrixSize; i++) {
        for (j = 0; j < matrixColSize[i]; j++) {
            if (matrix[i][j] == 0) {
                delRow = 1;
                matrix[0][j] = 0;
            }
        }
        if (delRow) {
            memset(matrix[i], 0, sizeof(int) * matrixColSize[i]);
            delRow = 0;
        }
    }

    // 根据第一行清0列
    for (j = 0; j < matrixColSize[0]; j++) {
        if (matrix[0][j] == 0) {
            for (i = 1; i < matrixSize; i++) {
                matrix[i][j] = 0;
            }
        }
    }

    // 根据最开始统计的标记决定第一行是否清0
    if (delFirstRow) {
        memset(matrix[0], 0, sizeof(int) * matrixColSize[0]);
    }

    return;
}