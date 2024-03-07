/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize){
    if (digits == NULL || digitsSize <= 0) {
        return digits;
    }

    int i;
    int num = digits[digitsSize - 1] + 1;
    int carry = num / 10;

    digits[digitsSize - 1] = num % 10;

    for (i = digitsSize - 2; i >= 0; i--) {
        num = digits[i] + carry;
        digits[i] = num % 10;
        carry = num / 10;
        if (carry == 0) {
            break;
        }
    }
    if (carry == 0) {
        *returnSize = digitsSize;
        return digits;
    }

    /* 如果加1之后最高位有进位，原来的数组已经无法放下了 */
    /* 申请新的空间返回 */
    int *ans = (int*)malloc(sizeof(int) * (digitsSize + 1));
    ans[0] = carry;
    for (i = 0; i < digitsSize; i++) {
        ans[i+1] = digits[i];
    }
    *returnSize = digitsSize + 1;
    return ans;
}