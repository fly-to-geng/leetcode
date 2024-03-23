#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <uthash.h>

#define N 10

struct HashTable {
	char key[N + 1]; // N个字母
	int count; // 出现的次数
	UT_hash_handle hh;
};

typedef struct HashTable Map;

char *deepCopy(char *string, int start, int end)
{
	char *newString = (char*)malloc(sizeof(char) * (end - start + 1));
	int newStringEnd = 0;
	for (int i = start; i < end; i++) {
		newString[newStringEnd++] = string[i];
	}
	newString[newStringEnd] = '\0';
	return newString;
}

char ** findRepeatedDnaSequences(char * s, int* returnSize)
{
	char **ans = NULL;
	*returnSize = 0;
	
	if (s == NULL || strlen(s) <= N) {
		return ans;
	}
	
	Map *map = NULL; // 哈希表
	Map *current = NULL; // 哈希表中的当前元素
	for (int i = 0; i <= strlen(s) - N; i++) {
		char *key = deepCopy(s, i, i + N);
		HASH_FIND_STR(map, key, current);
		if (current == NULL) {
			current = (Map*)malloc(sizeof(Map));
			strncpy(current->key, key, N); current->key[N] = '\0';
			current->count = 1;
			HASH_ADD_STR(map, key, current);
		} else {
			current->count++;
		}
	}

	// 统计结果的数量
	int ansCount = 0;
	for(current = map; current != NULL; current = current->hh.next) {
        if (current->count > 1) {
			ansCount++;
		}
    }
	
	// 根据结果数量开辟空间存储结果
	ans = (char**)malloc(sizeof(char*) * ansCount);
	int ansEnd = 0;
	for(current = map; current != NULL; current = current->hh.next) {
        if (current->count > 1) {
			ans[ansEnd++] = deepCopy(current->key, 0, strlen(current->key));
		}
    }
	
	// 释放掉map所占用的空间
	Map *tmp;
	HASH_ITER(hh, map, current, tmp) {
      HASH_DEL(map, current);
      free(current);
    }
	
	*returnSize = ansCount;
	return ans;
}