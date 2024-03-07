void freeMatrix(int **matrix, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return;
}
// 返回 a 与 b 是否只相差一个字母
int isArrival(char *a, char *b)
{
    int i;
    int count = 0;
    const int m = strlen(a);
    const int n = strlen(b);
    if (n != m) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            count++;
        }
    }
    if (count == 1) {
        return 1;
    }
    return 0;
}
// 宽度优先搜索，返回 start --> end 的最短路径
int BFS(int **graph, int start, int end, int n)
{
    int i;
    int current;
    int road_current;

    int *deque;
    int dequeHead = 0;
    int dequeEnd = 0;

    int *road;
    int roadHead = 0;
    int roadEnd = 0;

    int *color;
    int ans;

    deque = (int*)malloc(sizeof(int) * n);
    road = (int*)malloc(sizeof(int) * n);
    color = (int*)malloc(sizeof(int) * n);

    memset(color, 0, sizeof(int) * n);
    memset(deque, 0, sizeof(int) * n);
    memset(road, 0, sizeof(int) * n);

    deque[dequeHead++] = start;
    color[start] = 1;
    road[roadHead++] = 0;
    while (dequeHead - dequeEnd > 0) {
        current = deque[dequeEnd++];
        road_current = road[roadEnd++];
        for (i = 0; i < n; i++) {
            if (graph[current][i] == 1 && color[i] == 0) {
                if (i == end) {
                    ans =  road_current + 1;
                    free(color);
                    free(deque);
                    free(road);
                    return ans;
                }
                deque[dequeHead++] = i;
                color[i] = 1;
                road[roadHead++] = road_current + 1;
            }
        }
    }
    free(color);
    free(deque);
    free(road);
    return 0;
}
int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){

    const int n = wordListSize;
    int **graph;
    int i, j, start, end;
    int ans = 0;

    // 开辟空间存储无向图
    graph = (int**)malloc(sizeof(int*) * (n + 1));
    for (i = 0; i < n + 1; i++) {
        graph[i] = (int*)malloc(sizeof(int) * (n + 1));
        memset(graph[i], 0, sizeof(int) * (n + 1));
    }
    // 根据单词生成无向图
    for (i = 0; i < n - 1; i++) {
        for (j = i+1; j < n; j++) {
            if (i != j && isArrival(wordList[i], wordList[j])) {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }
    // 找到起点的索引
    start = -1;
    for (i = 0; i < n; i++) {
        if (strcmp(wordList[i], beginWord) == 0) {
            start = i;
        }
    }
    if (start == -1) {
        // beginword 作为第 n 个结点加入图
        for (i = 0; i < n; i++) {
            if (isArrival(beginWord, wordList[i])) {
                graph[n][i] = 1;
                graph[i][n] = 1;
                ans = 1;
            }
        }
        start = n;
    }
    // 找到终点的索引
    end = -1;
    for (i = 0; i < n; i++) {
        if (strcmp(wordList[i], endWord) == 0) {
            end = i;
            break;
        }
    }
    // 终点不在单词列表中，返回0
    if (end == -1) {
        freeMatrix(graph, n + 1);
        ans = 0;
        return ans;
    }
    // 起点是n, 终点是 end, 现在问题转化为搜索两点之间的最短路径
    ans = BFS(graph, start, end, n + 1);
    if (ans == 0) {
        return 0;
    } else {
        return ans + 1;
    }
}