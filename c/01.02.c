//第一种思路，排序之后逐个字符比较， 如果完全一样，则可以。
int compare(const void *p, const void *q)
{
    char a = *(char*)p;
    char b = *(char*)q;
    return a - b;
}
bool CheckPermutation(char* s1, char* s2){
    if (s1 == NULL && s2 == NULL) {
        return true;
    }
    if (s1 == NULL || s2 == NULL) {
        return false;
    }
    if (strlen(s1) != strlen(s2)) {
        return false;
    }
    qsort(s1, strlen(s1), sizeof(char), compare);
    qsort(s2, strlen(s2), sizeof(char), compare);
    for (int i = 0; i < strlen(s1); i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}


//第二种思路，使用哈希表存储每个字符的出现次数
#define MAX_CHAR 256
int map[MAX_CHAR];

bool CheckPermutation(char* s1, char* s2){
    if (s1 == NULL && s2 == NULL) {
        return true;
    }
    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    int i;
    memset(map, 0, sizeof(int) * MAX_CHAR);

    for (i = 0; i < strlen(s1); i++) {
        map[ s1[i] ] += 1;
    }
    for (i = 0; i < strlen(s2); i++) {
        map[ s2[i] ] -= 1;
    }
    for (i = 0; i < MAX_CHAR; i++) {
        if (map[i] != 0) {
            return false;
        }
    }
    return true;
}