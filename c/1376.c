#define MAXN 100000


int *managerG;
int *informTimeG;
int managerSizeG;
int informTimeSizeG;
int max(int a, int b)
{
    if (a > b) return a;
    return b;
}

int dfs(int i, int cost)
{
    if (informTimeG[i] == 0) {
        return cost;
    }
    int ans = 0;
    for (int j = 0; j < managerSizeG; j++) {
        if (managerG[j] == i) {
            int tmp = dfs(j, cost + informTimeG[i]);
            ans = max(ans, tmp);
        }
    }
    return ans;
}
int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime, int informTimeSize){
    if (n <= 0 || manager == NULL || managerSize <= 0 || informTime == NULL || informTimeSize <= 0) return 0;

    int ans = 0;
    managerG = manager;
    managerSizeG = managerSize;
    informTimeG = informTime;
    informTimeSizeG = informTimeSize;

    ans = dfs(headID, 0);

    return ans;
}