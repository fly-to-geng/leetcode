#include <stdio.h>
int ABSS(int a, int b)
{
    if (a >= b) {
        return a - b;
    }
    return b - a;
}
char * reformat(char * s){
    if (s == NULL) return NULL;
    const int n = strlen(s);
    char *cs = (char*)malloc(sizeof(char) * n);
    int csEnd = 0;
    char *nums = (char*)malloc(sizeof(char) * n);
    int numsEnd = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] >= '0' && s[i] <= 9) {
            nums[numsEnd++] = s[i];
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            cs[csEnd++] = s[i];
        } else {
            printf("error: %c, ", s[i]);
        }
    }

    char *ans = (char*)malloc(sizeof(char) *(n + 2));
    int ansEnd = 0;
    if (ABSS(numsEnd, csEnd) > 1) {
        ans[ansEnd] = '\0';
        return ans;
    } else {
        if (numsEnd > csEnd) {
            for (int i = 0; i < csEnd; i++) {
                ans[ansEnd++] = nums[i];
                ans[ansEnd++] = cs[i];
            }
            ans[ansEnd++] = nums[numsEnd - 1];
        } else if (csEnd > numsEnd) {
            for (int i = 0; i < numsEnd; i++) {
                ans[ansEnd++] = cs[i];
                ans[ansEnd++] = nums[i];
            }
            ans[ansEnd++] = cs[csEnd - 1];
        } else {
            for (int i = 0; i < csEnd; i++) {
                ans[ansEnd++] = cs[i];
                ans[ansEnd++] = nums[i];
            }
        }
    }
    ans[ansEnd] = '\0';
    return ans;
}