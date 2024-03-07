bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    if (matrix == NULL || matrixColSize == NULL || matrixSize <= 0) {
        return false;
    }

    if (matrixSize == 1 && matrixColSize[0] <= 0) {
        return false;
    }

    // 首先使用二分查找查第一列，确定target应该在哪一行
    int left = 0;
    int right = matrixSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (target == matrix[mid][0]) {
            return true;
        } else if (target < matrix[mid][0]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    int line = left <= 0 ? 0 : left - 1;
    left = 0, right = matrixColSize[line] - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (target == matrix[line][mid]) {
            return true;
        } else if (target < matrix[line][mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return false;
}