ss

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#define MAXN 1000
#define N 100

struct HashTable {
    char key[N + 1]; // N个字母
    int count; // 出现的次数
    UT_hash_handle hh;
};
typedef struct HashTable Map;

/* 拷贝一个字符串 */
char *deepCopy(char *string)
{
    if (string == NULL) return NULL;

    const int n = strlen(string);
    char *newString = (char*)malloc(sizeof(char) * (n + 1));

    for (int i = 0; i < n; i++) {
        newString[i] = string[i];
    }
    newString[n] = '\0';
    return newString;
}

/* 
 * 频率不同按照频率从小到大排列
 * 频率相同按照字典序排列
 */
int compare_function(Map *a, Map *b)
{
    if (a->count != b->count) {
        return a->count - b->count;
    }

    return strcmp(a->key, b->key);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** watchedVideosByFriends(char *** watchedVideos, int watchedVideosSize, int* watchedVideosColSize, 
    int** friends, int friendsSize, int* friendsColSize, int id, int level, int* returnSize)
{
    if (watchedVideos == NULL || watchedVideosColSize == NULL || watchedVideosSize <= 0) {
        *returnSize = 0;
        return NULL;
    }

    if (friends == NULL || friendsColSize == NULL || friendsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }

    int *curr = (int*)malloc(sizeof(int*) * MAXN); // 当前的人
    int currEnd = 0;
    int *next = (int*)malloc(sizeof(int) * MAXN); // 当前人的所有朋友
    int nextEnd = 0;
    int *unique = (int*)malloc(sizeof(int) * MAXN);


    curr[0] = id; 
    currEnd = 1;
    while (level) {
        // 把 curr 中人的朋友放入 next 中
        for (int i = 0; i < MAXN; i++) unique[i] = 0;
        for (int i = 0; i < currEnd; i++) {
            for (int j = 0; j < friendsColSize[i]; j++) {
                if (unique[ friends[i][j] ] == 0) {
                    next[nextEnd++] = friends[i][j];
                    unique[ friends[i][j] ] = 1;
                } 
            }
        }
        // 把 next 放入 curr 中， 然后把 next 清空，继续下一次循环
        currEnd = 0;
        for (int i = 0; i < nextEnd; i++) {
            curr[currEnd++] = next[i];
        }
        nextEnd = 0;
        level--;
    }

    // curr 中保存的是id, level层级的所有朋友
    Map *map = NULL; // 保存每个视频出现的次数
    Map *current = NULL;
    for (int i = 0; i < currEnd; i++) {
        for (int j = 0; j < watchedVideosColSize[i]; j++) {
            char *key = watchedVideos[i][j];
            HASH_FIND_STR(map, key, current);
            if (current == NULL) {
                current = (Map*)malloc(sizeof(Map));
                int len = strlen(watchedVideos[i][j]);
                strncpy(current->key, string, len); current->key[len+1] = '\0';
                current->count = 1;
                HASH_ADD_STR(map, key, current);
            } else {
                current->count++;
            }
        } 
    }

    // 遍历map, 按照出现频率从低到高排列
    HASH_SORT(map, compare_function);

    int ansCount = HASH_COUNT(map);
    char **ans = (char**)malloc(sizeof(char*) * ansCount);
    int ansEnd = 0;

    Map *tmp = NULL;
    for(tmp = map; tmp != NULL; tmp = tmp->hh.next) {
        ans[ansEnd++] = deepCopy(tmp->key);
    }

    // 释放用不到的空间
    Map *current = NULL;
    Map *tmp = NULL;
    HASH_ITER(hh, map, current, tmp) {
        HASH_DEL(map, current);
        free(current);
    }
    free(curr);
    free(next);

    return ans;
}