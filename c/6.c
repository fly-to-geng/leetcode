/*
模拟整个过程，使用一个矩阵存放，使用\0填充空白的地方。 优点是容易想到，不易出错，缺点是占用空间多，代码长。
 */
char * convert(char * s, int numRows){
    if (s == NULL || numRows == 0) {
        return NULL;
    }

    if (strlen(s) == 0 || numRows == 1) {
        return s;
    }

    int col;
    int subrow = numRows;
    int subcol = numRows - 1;
    int sublen = subrow + subcol - 1;
    int nsub = strlen(s) / sublen + 1;
    char **matrix;
    int i, j;
    int sindex = 0;
    int slen = strlen(s);
    int zflag = 0;

    col = nsub * subcol;
    /* 申请 numrows 行 col 列临时存储空间存放模拟过程 */
    matrix = (char**)malloc(sizeof(char*) * numRows);
    for (i = 0; i < numRows; i++) {
        matrix[i] = (char*)malloc(sizeof(char) * col);
        for (j = 0; j < col; j++) {
            matrix[i][j] = '\0';
        }
    }

    /* 模拟之字过程存放字符串 */
    i = 0;
    j = 0;
    while (sindex < slen) {
        matrix[i][j] = s[sindex++];
        if (i == 0) {
            i = i + 1;
            zflag = 0;
        } else if (i == numRows - 1) {
            i = i - 1;
            j = j + 1;
            zflag = 1;
        } else {
            if (zflag) {
                i = i - 1;
                j = j + 1;
            } else {
                i = i + 1;
            }
        }
    }

    /* 按照行遍历取出字符串 */
    char *ans = (char*)malloc(sizeof(char) * (slen + 1));
    int ansEnd = 0;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < col; j++) {
            if (matrix[i][j] != '\0') {
                ans[ansEnd++] = matrix[i][j];
            }
        }
    }
    ans[ansEnd] = '\0';
    return ans;
}


/*
不模拟过程，而是计算下标，直接输出。 第一行和最后一行容易确定，输出的都是间隔 2 * n - 2 的元素，如果当前输出s[i], 那么下一个字母应该输出s[i + 2*n-2].
中间的行i, 距离顶部的距离是i + 1, 距离底部的距离是numRows - i, 都包括自身。把该值记为p, 则任意元素的下一个元素只与向下还是向上有关，我们设置一个标记 down = true, 表示开始的时候是向下的。
对于任意一行i, 起始输出元素是s[i], 下一个输出的元素下标可以计算得到： 向下：i + 2 *p - 2, down = false 向上 : i + 2 *p - 2, down = true 循环上面的直到下标超出字符串的长度
 */
char * convert(char * s, int numRows){
    char *ans;
    int ansEnd = 0;
    int i = 0;
    int slen;
    int sindex = 0;
    int down = 1;
    int step;

    if (s == NULL || numRows == 0) {
        return NULL;
    }

    slen = strlen(s);
    if (slen == 0 || numRows == 1 || numRows >= slen) {
        return s;
    }

    ans = (char*)malloc(sizeof(char) *(strlen(s) + 1));
    for (i = 0; i < numRows; i++) {
        ans[ansEnd++] = s[i];
        sindex = i;
        down = 1;
        while (sindex < slen) {
            if (down) {
                step = 2 * (numRows - i) - 2;
                down = 0;
            } else {
                step = 2 * (i + 1) - 2;
                down = 1;
            }
            /* 第一行和最后一行的时候, step 可能为0 */
            sindex += step;
            if (sindex < slen && step > 0) {
                ans[ansEnd++] = s[sindex];
            }
        }
    }
    ans[ansEnd] = '\0';
    return ans;
}