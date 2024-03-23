#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define MAXN 10000
#define TRUE 1
#define FALSE 0
int isStart(char c)
{
	int ans = FALSE;
	
	switch(c) {
		case 'q':
		case 'a':
		case 'g':
		case 'l':
		case 'f':
			ans = TRUE;
			break;
		default:
			ans = FALSE;
	}
	return ans;
}
char mapStr(char *str)
{
	if (strcmp(str, "&quot;") == 0) {
		return '"';
	}
	if (strcmp(str, "&apos;") == 0) {
		return '\'';
	}
	if (strcmp(str, "&gt;") == 0) {
		return '>';
	}
	if (strcmp(str, "&lt;") == 0) {
		return '<';
	}
	if (strcmp(str, "&frasl;") == 0) {
		return '/';
	}
	if (strcmp(str, "&amp;") == 0) {
		return '&';
	}
	
	return 0;
}
char getMapStr(char *text, int index, int *nextIndex)
{
	int i = index;
	int segflag = FALSE;
	while (i < index + 7) {
		if (text[i] == ';') {
			segflag = TRUE;
			break;
		}
		i++;
	}
	// 如果没有找到分号，不可能是实体
	if (segflag == FALSE) {
		*nextIndex = index + 1;
		return 0;
	}
	// [index, i]可能对应实体，转换成实体返回
	char *substr = (char*)malloc(sizeof(char) *(i - index + 3));
	int substrEnd = 0;
	for (int j = index; j <= i; j++) {
		substr[substrEnd++] = text[j];
	}
	substr[substrEnd++] = '\0';
	
	printf("%s, [%d, %d]", substr, index, i);
	
	char ans = mapStr(substr);
	if (ans == 0) {
		*nextIndex = index + 1;
		return 0;
	} else {
		*nextIndex = i + 1;
		return ans;
	}
	
	return ans;
}
char * entityParser(char * text){
	if (text == NULL) return NULL;
	
	const int n = strlen(text);
	int i = 0;
	char *ans = (char*)malloc(sizeof(char) * (n + 2));
	int ansEnd = 0;
	
	while (i < n) {
		// 如果匹配了实体开头，就继续找最近的结尾;
		if (text[i] == '&' && i+1 < n && isStart(text[i+1])) {
			int next_i = -1;
			char c = getMapStr(text, i, &next_i);
			if (c == 0) {
				ans[ansEnd++] = text[i];
				i++;
			} else {
				ans[ansEnd++] = c;
				i = next_i;
			}
		} else {
			ans[ansEnd++] = text[i];
			i++;
		}
	}
    ans[ansEnd] = '\0';
    return ans;
}