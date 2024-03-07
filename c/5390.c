#include <stdio.h>
#include <string.h>

#define MAXN 10000
int minNumberOfFrogs(char * croakOfFrogs){
    if (croakOfFrogs == NULL) return -1;
    const int n = strlen(croakOfFrogs);
    int *label = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) label[i] = 0;
    int labeled = 0;
    int start = 0;
    char cr[] = "croak";
    int crIndex = 0;
    int i = 0;
    int ans = 1;
    int cIndex = -1;
    int kIndex = -1;
    int **cks = (int**)malloc(sizeof(int*) * MAXN);
    int cksEnd = 0;
    for (int i = 0; i < MAXN; i++) {
        cks[i] = (int*)malloc(sizeof(int) * 2);
        cks[i][0] = 0;
        cks[i][1] = 0;
    }
    while (labeled < n) {
        i = start;
        while (i < n) {
            if (crIndex < 5 && label[i] == 0 && croakOfFrogs[i] == cr[crIndex]) {
                if (crIndex == 0) cIndex = i;
                if (crIndex == 4) kIndex = i;
                label[i] = 1;
                labeled += 1;
                crIndex += 1;
            }
            i++;
        }
        // croak没有找全， 直接返回 -1
        if (crIndex < 5) {
            return - 1;
        }
        if (cIndex != -1 && kIndex != -1) {
            cks[cksEnd][0] = cIndex;
            cks[cksEnd][1] = kIndex;
            cksEnd++; 
        }
        crIndex = 0;
        start += 1;
    }

    for (int i = 0; i < cksEnd; i++) {
        printf("%d, %d\n", cks[i][0], cks[i][1]);
    }

    for (int i = 0; i < cksEnd; i++) {
        // 计算落在区间 cks[i][0], cks[i][1] 的区间个数
        int st = cks[i][0];
        int end = cks[i][1];
        int count = 1;
        int j = i + 1;
        while (j < cksEnd && cks[j][0] < end) {
            count++;
        }
        if (count > ans) {
            ans = count;
        }
        
    }
    return ans;
}