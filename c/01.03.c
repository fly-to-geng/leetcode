//先统计出空格的数量，计算好移动的位置，从后向前移动，避免重复移动。

char* replaceSpaces(char* S, int length){
    int space = 0;
    int i, j, oldENd, end;

    // 统计空格数量
    for (i = length - 1; i >= 0; i--) {
        if (S[i] == ' ') {
            space++;
        }
    }

    // 计算新字符串的结尾
    end = length + space * 2;
    S[end] = '\0';
    i = length - 1;
    oldENd = length - 1;
    while (i >= 0) {
        if (S[i] == ' ') {
            //一步移动到位，避免重复移动
            for (j = oldENd; j > i; j--) {
                S[--end] = S[j];
            }
            S[--end] = '0';
            S[--end] = '2';
            S[--end] = '%';
            oldENd = i - 1;
        }
        i--;
    }
    return S;
}