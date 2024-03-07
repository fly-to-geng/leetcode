#define MAX(a,b) ((a) > (b) ? (a) : (b))
int size = 0;

// 字符串转换成数字
int char2int(char *string)
{
    int ans = 0;
    while (*string) {
        ans += 1 << (*string - 'a');
    }
    return ans;
}
// 返回把string中字母加入集合set中的结果
int add(char *string, int set)
{
    int ans = char2int(string);
    ans = ans | set;
    return ans;
}

// 返回string中的任意一个字母是否在set中出现过
int notCanPut(char* string, int set)
{
    int ans = char2int(string);
    ans = ans & set;
    return ans;
}
/*
 * arr[i] 当前检查的单词
 * currentSet : 当前加入的集合
 * oneAns : 深度搜索到底一趟的结果
 * ans : 保存最终的结果
 */
void dfs(char** arr, int i, int currentSet, int *oneAns, int *ans)
{
    // 如果到达了末尾，比较一趟的结果和最终的结果大小
    if (i == size) {
        *ans = MAX(*ans, *oneAns);
        return;
    }

    // 如果arr[i]无法放入，则搜索下一个单词
    if (notCanPut(arr[i], currentSet)) {
        dfs(arr, i+1, currentSet, oneAns, ans);
        return;
    }

    // 如果arr[i]可以放入，那么放入和不放入两种情况都需要递归
    int tmpOneAns = *oneAns + strlen(arr[i]);
    dfs(arr, i + 1, add(arr[i], currentSet), &tmpOneAns, ans);

    dfs(arr, i + 1, currentSet, oneAns, ans);

    return;
}
int maxLength(char ** arr, int arrSize){
    int ans = 0;
    int oneAns = 0;
    int currentSet = 0;

    size = arrSize;
    dfs(arr, 0, &oneAns, &ans);
    return ans;
}