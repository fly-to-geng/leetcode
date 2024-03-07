#define MIN(a, b) ((a) > (b) ? (b) : (a))

int minPathSum(int** grid, int gridSize, int* gridColSize){
    if (grid == NULL || gridColSize == NULL || gridSize == 0) {
        return 0;
    }

    int i, j;
    for (i = 1; i < gridSize; i++) {
        grid[i][0] = grid[i][0] + grid[i-1][0];
    }
    for (j = 1; j < gridColSize[0]; j++) {
        grid[0][j] = grid[0][j] + grid[0][j-1];
    }
    for (i = 1; i < gridSize; i++) {
        for (j = 1; j < gridColSize[i]; j++) {
            grid[i][j] = grid[i][j] + MIN(grid[i-1][j], grid[i][j-1]);
        }
    }
    return grid[gridSize-1][gridColSize[gridSize-1]-1];
}