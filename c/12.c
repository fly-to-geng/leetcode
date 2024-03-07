#define N 200
int base[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
char label[27] = "M0CMD0CDC0XCL0XLX0IXV0IVI0";

char * intToRoman(int num){
    char *ans;
    int count, i;
    int end = 0;
    int label_end = 0;
    ans = (char*)malloc(sizeof(char) * N);
    for (i = 0; i < 13; i++) {
        count = num / base[i];
        if (count > 0) {
            while (count--) {
                ans[end++] = label[label_end++];
                if (label[label_end] != '0') {
                    ans[end++] = label[label_end++];
                } else {
                    label_end++;
                }
                label_end = label_end - 2;
            }
            num = num % base[i];
        }
        label_end += 2;
    }
    ans[end] = '\0';
    return ans;
}