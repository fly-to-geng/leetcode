int* threeEqualParts(int* A, int ASize, int* returnSize){
    int count = 0;
    int c1;
    int i, j, right;
    int *ans;
    ans = (int*)malloc(sizeof(int) * 2);
    ans[0] = -1;
    ans[1] = -1;
    *returnSize = 2;
    for (i = 0; i < ASize; i++) {
        if (A[i] == 1) {
            count++;
        }
    }
    if (count == 0) {
        ans[0] = 0;
        ans[1] = 2;
        return ans;
    }
    if (count % 3 != 0) {
        return ans;
    }
    c1 = count / 3; // 每个值应该包含c1个1
    for (i = ASize - 1; i >= 0; i--) {
        if (A[i] == 1) {
            c1--;
        }
        if (c1 == 0) {
            right = i;
            break;
        }
    }
    // right ... ASize-1 组成的值是最终三个组都应该达到的值
    // 但是right可能不是第三组的开始，如果有0可以提前

    // 从开始找到第一个为1的位置，是否完全能和 right...ASize-1 匹配
    // 如果不能匹配，就返回false
    // 如果可以匹配，就确定了第一组的位置
    i = 0;
    while (i < ASize && A[i] == 0) {
        i++;
    } 
    j = right;
    while (i < ASize && j < ASize && A[i] == A[j]) {
        i++;
        j++;
    }
    if (j < ASize) {
        ans[0] = -1;
        ans[1] = -1;
        return ans;
    }
    // 第一组匹配上了， i 的位置就是第二组开始的位置
    ans[0] = i - 1;
    while (i < ASize && A[i] == 0) {
        i++;
    }
    j = right;
    while (i < ASize && j < ASize && A[i] == A[j]) {
        i++;
        j++;
    }
    if (j < ASize) {
        ans[0] = -1;
        ans[1] = -1;
        return ans;
    }
    if (i == right) {
        ans[1] = i;
    } else {
        ans[1] = i;
    }
    return ans;
}