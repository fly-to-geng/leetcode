# C 语言基础知识

记录用C语言刷 leetcode 题必须要了解的C语言相关功能

## include

```c
// bool, true, false
#include <stdbool.h>

// UT_hash_handle, HASH_XXX
#include <uthash.h>
```

## 四舍五入

```c
// 四舍五入保留两位小数
float number = 1.2768;
number = (int)(100 * number + 0.5) / 100.0
printf("%.2f", number);
```

## 输入输出

### 读取

- `char c = getchar();` : 读取一个字符
- `gets(string);` : 读取一行字符
- 读取若干行：

当没有指定输入是多少行， 以结束快捷键结束输入的时候，按照下面方式读取

```c
while (scanf("%d", &n) != EOF) {
    printf("%d ", n);
}
```

### 重定向

```c
freopen("input.txt", stdin); // 标准输入重定向到文件
freopen("output.txt", stdout); // 标准输出重定向到文件

fclose(stdin);
fclose(stdout);
```

## 数据结构

### 哈希表(uthash)

C 语言缺乏内置数据结构的支持，但是有一个优秀的哈希库 uthash, 它是用宏实现的，使用的时候只需要包含这个文件即可。

#### 整数为key

```c
HASH_FIND_INT(HashMap, &number, currMap); // 判断是否存在
if (currMap == NULL) {
    currMap = new_map_element;
    HASH_ADD_INT(HashMap, key_name, currMap); // 加入哈希表
}
```

#### 字符串为key

```c
HASH_FIND_STR(HashMap, &number, currMap); // 判断是否存在
if (currMap == NULL) {
    currMap = new_map_element;
    HASH_ADD_STR(HashMap, key_name, currMap); // 加入哈希表
}
```

#### 单字符为key

```c
HASH_FIND(hh, HashMap, &c, sizeof(char), currMap); // 判断是否存在
if (currMap == NULL) {
    currMap = new_map_element;
    HASH_ADD(hh, HashMap, key_name, sizeof(char), currMap); // 加入哈希表
}
```

#### 字符指针为key

```c

```

#### 大小

```c
size = HASH_COUNT(HashMap);
```

#### 遍历和删除

```c
HASH_ITER(hh, HashMap, currMap, tmpMap) {
    free(currMao);
    HASH_DEL(currMap);
}
```

#### 排序

```c
HASH_SORT(HashMap, compare_function);
int compare_fucntion(HashMap *a, HashMap *b) {
    return a->value - b->value;
}
```

#### 二维哈希表

dic['A']['B'] = 1, 实现这样的结构，可以在 O(1) 时间内找到。

用单个字母表示行号和列号的二维矩阵

```c
typedef struct B{
    char col;
    int value;
    UT_hash_handle hh;
}B;

typedef struct A{
    char row;
    B *cols;
    UT_hash_handle hh;
}A;

A *matrix = NULL;
A *currMatrix = NULL;
B *cols = NULL;
B *currCols = NULL;

HASH_FIND(hh, matrix, &c, sizeof(char), currMatrix);
if (currMatrix == NULL) {
    currMatrix->row = row;
    currMatrix->cols = NULL;
    HASH_ADD(hh, matrix, row, currMatrix);
} else {
    HASH_FIND(hh, currMatrix->cols, &c, currCols);
    if (currCols == NULL) {
        currCols = new_element;
        HASH_ADD(hh, currMatrix->cols, col, currCols);
    }
}

```
