#include<stdio.h>
#include <uthash.h>

#define NAMELEN 22
#define MAXFOOD 1000
struct FoodSet{
    char foodname[NAMELEN]; // 菜名
    char tables[MAXFOOD][10]; // 菜有哪些桌点
    int counts[MAXFOOD]; // 对应桌点了几分
    int end; // 当前tables, count当中元素的个数
    UT_hash_handle hh;
};
typedef struct FoodSet FOOD_SET;

struct TableSet{
    char tablename[10];
    UT_hash_handle hh;
};
typedef struct TableSet TABLE_SET;

char *int2tr(int n)
{
    char *ans = (char*)malloc(sizeof(char) * 100);
    int end = 0;
    while (n) {
        ans[end++] = n % 10 + '0';
        n = n / 10;
    }
    int left = 0;
    int right = end - 1;
    char tmp;
    while (left < right) {
        tmp = ans[left];
        ans[left] = tmp;
        ans[right] = tmp;
        left++;
        right--;
    }
    ans[end] = '\0';
    return ans;
}
int str2int(char *str)
{
    const int n = strlen(str);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = ans * 10 + str[i] - '0';
    }
    return ans;
}
int foodCompare(FOOD_SET *a, FOOD_SET *b)
{
    return strcmp(a->foodname, b->foodname);
}

int tableCompare(TABLE_SET *a, TABLE_SET *b)
{
    int p = str2int(a->tablename);
    int q = str2int(b->tablename);
    return p - q;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** displayTable(char *** orders, int ordersSize, int* ordersColSize, int* returnSize, int** returnColumnSizes){
    FOOD_SET *foodset = NULL;
    TABLE_SET *tableset = NULL;
    FOOD_SET *currFood = NULL;
    TABLE_SET *currTable = NULL;
    for (int i = 0; i < ordersSize; i++) {
        char *tableNumber = orders[i][1];
        char *foodname = orders[i][2];

        // 添加食物名称
        HASH_FIND_STR(foodset, foodname, currFood);
        if (currFood == NULL) {
            currFood = (FOOD_SET*)malloc(sizeof(FOOD_SET));
            strcpy(currFood->foodname, foodname); currFood->foodname[strlen(foodname)] = '\0';
            strcpy(currFood->tables[0], tableNumber); currFood->tables[0][strlen(tableNumber)] = '\0';
            currFood->counts[0] = 1;
            currFood->end = 1;
            for (int i = 1; i < MAXFOOD; i++) currFood->counts[i] = 0;
            HASH_ADD_STR(foodset, foodname, currFood);
        } else {
            int index = -1;
            for (int p = 0; p < currFood->end; p++) {
                if (strcmp(currFood->tables[p], tableNumber) == 0 ) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                strcpy(currFood->tables[currFood->end], tableNumber); 
                currFood->tables[currFood->end][strlen(tableNumber)] = '\0';
                currFood->end++;
            } else {
                currFood->counts[index]++;
            }
        }

        // 添加桌号
        HASH_FIND_STR(tableset, tableNumber, currTable);
        if (currTable == NULL) {
            currTable = (TABLE_SET*)malloc(sizeof(TABLE_SET));
            strcpy(currTable->tablename, tableNumber);
            currTable->tablename[strlen(tableNumber)] = '\0';
            HASH_ADD_STR(tableset, tablename, currTable);
        }
    }

    HASH_SORT(foodset, foodCompare);
    HASH_SORT(tableset, tableCompare);

    for (currFood = foodset; currFood != NULL; currFood = currFood->hh.next) {
        printf("%s, %d\n", currFood->foodname, currFood->end);
    }
    int foodCount = HASH_COUNT(foodset);
    int tableCount = HASH_COUNT(tableset);
    char ***ans = (char ***)malloc(sizeof(char**) * (tableCount + 1));
    for (int i = 0; i <= tableCount; i++) {
        ans[i] = (char**)malloc(sizeof(char*) * (foodCount + 1));
        for (int j = 0; j <= foodCount; j++) {
            ans[i][j] = (char*)malloc(sizeof(char) * NAMELEN);
        }
    }

    // 填写第一行和第一列的表头部分
    strcpy(ans[0][0], "Table"); ans[0][0][5] = '\0';
    int colEnd = 1;
    for (currFood = foodset; currFood != NULL; currFood = currFood->hh.next) {
        strcpy(ans[0][colEnd], currFood->foodname);
        ans[0][colEnd][strlen(currFood->foodname)] = '\0';
        colEnd++;
    }
    int rowEnd = 1;
    for (currTable = tableset; currTable != NULL; currTable = currTable->hh.next) {
        strcpy(ans[rowEnd][0], currTable->tablename);
        ans[rowEnd][0][strlen(currTable->tablename)] = '\0';
        rowEnd++;
    }

    // 按照列填写内容部分
    colEnd = 1;
    for (currFood = foodset; currFood != NULL; currFood = currFood->hh.next) {
        for (int j = 0; j < currFood->end; j++) {
            char *tableIndex = currFood->tables[j];
            for (int k = 1; k <= tableCount; k++) {
                if (strcmp(ans[k][0], tableIndex) == 0) {
                    char *tmpstr = int2tr(currFood->counts[j]);
                    strcpy(ans[k][colEnd], tmpstr);
                    ans[k][colEnd][strlen(tmpstr)] = '\0';
                    free(tmpstr);
                }
            }
        }
        colEnd++;
    }

    int *colsSize = (int*)malloc(sizeof(int) * (foodCount + 1));
    for (int i = 0; i <= foodCount; i++) {
        colsSize[i] = foodCount + 1;
    }
    *returnSize = tableCount + 1;
    *returnColumnSizes = colsSize;
    return ans;
}