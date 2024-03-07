int get(int **grid, int gridSize, int col, int i, int j)
{
    int count = 4;
    if (i - 1 >= 0 && grid[i-1][j] == 1) {
        count--;
    }
    if (i + 1 < gridSize && grid[i+1][j] == 1) {
        count--;
    }
    if (j - 1 >= 0 && grid[i][j-1] == 1) {
        count--;
    }
    if (j + 1 < col && grid[i][j+1] == 1) {
        count--;
    }
    //printf("%d ", count);
    return count;
}
int islandPerimeter(int** grid, int gridSize, int* gridColSize){
    int i, j;
    int ans = 0;
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1) {
                ans += get(grid, gridSize, gridColSize[i], i, j);
            }
        }
    }
    return ans;
}