# [1418. 点菜展示表](https://leetcode-cn.com/problems/display-table-of-food-orders-in-a-restaurant/)

## 题目描述

给你一个数组 orders，表示客户在餐厅中完成的订单，确切地说， orders[i]=[customerNamei,tableNumberi,foodItemi] ，其中 customerNamei 是客户的姓名，tableNumberi 是客户所在餐桌的桌号，而 foodItemi 是客户点的餐品名称。

请你返回该餐厅的 点菜展示表 。在这张表中，表中第一行为标题，其第一列为餐桌桌号 “Table” ，后面每一列都是按字母顺序排列的餐品名称。接下来每一行中的项则表示每张餐桌订购的相应餐品数量，第一列应当填对应的桌号，后面依次填写下单的餐品数量。

注意：客户姓名不是点菜展示表的一部分。此外，表中的数据行应该按餐桌桌号升序排列。

 

示例 1：

      输入：orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
      输出：[["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],["3","0","2","1","0"],["5","0","1","0","1"],["10","1","0","0","0"]] 
      解释：
      点菜展示表如下所示：
            Table,Beef Burrito,Ceviche,Fried Chicken,Water
            3    ,0           ,2      ,1            ,0
            5    ,0           ,1      ,0            ,1
            10   ,1           ,0      ,0            ,0
      对于餐桌 3：David 点了 "Ceviche" 和 "Fried Chicken"，而 Rous 点了 "Ceviche"
      而餐桌 5：Carla 点了 "Water" 和 "Ceviche"
      餐桌 10：Corina 点了 "Beef Burrito" 

示例 2：

      输入：orders = [["James","12","Fried Chicken"],["Ratesh","12","Fried Chicken"],["Amadeus","12","Fried Chicken"],["Adam","1","Canadian Waffles"],["Brianna","1","Canadian Waffles"]]
      输出：[["Table","Canadian Waffles","Fried Chicken"],["1","2","0"],["12","0","3"]] 
      解释：
      对于餐桌 1：Adam 和 Brianna 都点了 "Canadian Waffles"
      而餐桌 12：James, Ratesh 和 Amadeus 都点了 "Fried Chicken"

示例 3：

      输入：orders = [["Laura","2","Bean Burrito"],["Jhon","2","Beef Burrito"],["Melissa","2","Soda"]]
      输出：[["Table","Bean Burrito","Beef Burrito","Soda"],["2","1","1","1"]]
 

提示：

      1 <= orders.length <= 5 * 10^4
      orders[i].length == 3
      1 <= customerNamei.length, foodItemi.length <= 20
      customerNamei 和 foodItemi 由大小写英文字母及空格字符 ' ' 组成。
      tableNumberi 是 1 到 500 范围内的整数。

## 解题思路

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uthash.h>

#define STRMAX 22
#define NUMMAX 5
#define ORDERLEN 50001

typedef struct FoodName {
    char strname[STRMAX];
    int index;
    UT_hash_handle hh;
} STR_INDEX;

// foodname 按照字典序排列
int FoodCompare(STR_INDEX *a, STR_INDEX *b)
{
    return strcmp(a->strname, b->strname);
}

// 桌号按照从小到大排列
int TableCompare(STR_INDEX *a, STR_INDEX *b)
{
    int num1 = atoi(a->strname);
    int num2 = atoi(b->strname);
    return num1 - num2;
}

void int2str(int n, char *str)
{
    int end = 0;
    while (n) {
        str[end++] = n % 10 + '0';
        n = n / 10;
    }
    str[end] = '\0';
    int left = 0;
    int right = end - 1;
    char tmp;
    while (left < right) {
        tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;
        left++;
        right--;
    }
}
void addOne(char *str)
{
    printf("%s,", str);
    int a = atoi(str);
    a = a + 1;
    printf("%d, ", a);
    int2str(a, str);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** displayTable(char *** orders, int ordersSize, int* ordersColSize, 
                        int* returnSize, int** returnColumnSizes){
    STR_INDEX *foodNames = NULL;
    STR_INDEX *tableIndexs = NULL;
    STR_INDEX *currFood = NULL;
    STR_INDEX *currTable = NULL;
    for (int i = 0; i < ordersSize; i++) {
        char *foodName = orders[i][2];
        HASH_FIND_STR(foodNames, foodName, currFood);
        if (currFood == NULL) {
            currFood = (STR_INDEX*)malloc(sizeof(STR_INDEX));
            strcpy(currFood->strname, foodName);
            currFood->strname[strlen(foodName)] = '\0';
            currFood->index = -1;
            HASH_ADD_STR(foodNames, strname, currFood);
        }

        char *tableIndex = orders[i][1];
        HASH_FIND_STR(tableIndexs, tableIndex, currTable);
        if (currTable == NULL) {
            currTable = (STR_INDEX*)malloc(sizeof(STR_INDEX));
            strcpy(currTable->strname, tableIndex);
            currTable->strname[strlen(tableIndex)] = '\0';
            HASH_ADD_STR(tableIndexs, strname, currTable);
        }
    }

    int foodCount = HASH_COUNT(foodNames);
    int tableCount = HASH_COUNT(tableIndexs);
    HASH_SORT(foodNames, FoodCompare);
    HASH_SORT(tableIndexs, TableCompare);

    char ***ans = (char***)malloc(sizeof(char**) * (tableCount + 1));
    for (int i = 0; i <= tableCount; i++) {
        ans[i] = (char**)malloc(sizeof(char*) * (foodCount + 1));
        for (int j = 0; j <= foodCount; j++) {
            ans[i][j] = (char*)malloc(sizeof(char) * STRMAX);
            ans[i][j][0] = '0';
            ans[i][j][1] = '\0';
        }
    }
    strcpy(ans[0][0], "Table");
    ans[0][0][5] = '\0';

    int findex = 1;
    for (currFood = foodNames; currFood != NULL; currFood = currFood->hh.next) {
        currFood->index = findex;
        strcpy(ans[0][findex], currFood->strname);
        ans[0][findex][strlen(currFood->strname)] = '\0';
        findex += 1;
    }
    int tindex = 1;
    for (currTable = tableIndexs; currTable != NULL; currTable = currTable->hh.next) {
        currTable->index = tindex;
        strcpy(ans[tindex][0], currTable->strname);
        ans[tindex][0][strlen(currTable->strname)] = '\0';
        tindex += 1;
    }

    for (int i = 0; i < ordersSize; i++) {
        char *tableIndex = orders[i][1];
        char *foodName = orders[i][2];
        findex = -1;
        tindex = -1;
        HASH_FIND_STR(tableIndexs, tableIndex, currTable);
        HASH_FIND_STR(foodNames, foodName, currFood);
        if (currTable != NULL) tindex = currTable->index;
        if (currFood != NULL) findex = currFood->index;
        if (findex != -1 && tindex != -1) {
            addOne(ans[tindex][findex]);
        } else {
            printf("tindex: %d, findex: %d", tindex, findex);
        }
    }

    int *colsSize = (int*)malloc(sizeof(int) * (tableCount + 1));
    for (int i = 0; i <= tableCount; i++) {
        colsSize[i] = foodCount + 1;
    }
    
    *returnSize = tableCount + 1;
    *returnColumnSizes = colsSize;
    return ans;
}
```
