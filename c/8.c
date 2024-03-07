int myAtoi(char * str){
    int negtive = 0;
    int maxvalue = 0;
    int start, end, i, tmpstart;
    long long tmpans;

    if (str == NULL) {
        return 0;
    }

    int len = strlen(str);
    if (len == 0) {
        return 0;
    }

    /* 跳过开头的空格 */
    start = 0;
    while (start < len && str[start] == ' ') {
        start += 1;
    }

    if (start >= len) {
        return 0;
    }

    /* 第一个非空字符只能是+，-，数字 */
    if (str[start] != '+' && str[start] != '-' && 
            (!(str[start] >= '0' && str[start] <= '9'))) {
        return 0;
    }

    if (str[start] == '-') {
        negtive = 1;
        start += 1;
    } else if (str[start] == '+') {
        negtive = 0;
        start += 1;
    }

    /* 如果正负号后面不是紧跟数字，转换失败 */
    if (start >= len || !(str[start] >= '0' && str[start] <= '9')) {
        return 0;
    }

    /* end 指向最后一个数字之后的位置 */
    for (end = start; end < len; end++) {
        if (!(str[end] >= '0' && str[end] <= '9')) {
            break;
        }
    }

    /* 略过前导0找到第一个数字，先通过位数判断是否超过范围 */
    tmpstart = start;
    while (tmpstart < len && str[tmpstart] == '0') {
        tmpstart += 1;
    }
    if (end - tmpstart > 10) {
        maxvalue = 1;
    } else {
        tmpans = 0;
        for (i = start; i < end; i++) {
            tmpans = tmpans * 10 + (str[i] - '0');
        }
        if (negtive) {
            tmpans = -tmpans;
        }
        if (tmpans > INT_MAX || tmpans < INT_MIN) {
            maxvalue = 1;
        }
    }

    /* 如果超过最大值，返回最值，否则，返回真实值 */
    if (maxvalue) {
        if (negtive) {
            return INT_MIN;
        } else {
            return INT_MAX;
        }
    } else {
        return (int)tmpans;
    }
}