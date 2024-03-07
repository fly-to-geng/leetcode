#define MAX_CHAR 128
#define MAX_ANS 501

int map[MAX_CHAR];
void init()
{
    for (int i = 0; i < MAX_CHAR; i++) {
        map[i] = 0;
    }
}

char * sortString(char * s){
    if (s == NULL) return s;

    int n = strlen(s);
    int i;

    for (i = 0; i < n; i++) {
        map[ s[i] ] ++;
    }

    char *ans = (char*)malloc(sizeof(char) * MAX_ANS);
    int ansEnd = 0;
    while (n > 0) {
        for (i = 0; i < MAX_CHAR; i++) {
            if (map[i] > 0) {
                ans[ansEnd++] = (char)i;
                n--;
                map[i]--;
            }
        }
        for (int i = MAX_CHAR - 1; i >= 0; i--) {
            if (map[i] > 0) {
                ans[ansEnd++] = (char)i;
                n--;
                map[i]--;
            }
        }
    }
    ans[ansEnd++] = '\0';
    return ans;
}