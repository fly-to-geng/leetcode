int Bits(int n)
{
    int count = 0;
    while (n > 0) {
        count++;
        n = n & (n - 1);
    }
    //printf("%d : %d\n", n, count);
    return count;
}
int compare(const void *p, const void *q)
{
    int a = *(int*)p;
    int b = *(int*)q;
    int aBits = Bits(a);
    int bBits = Bits(b);
    if (aBits == bBits) return a - b;
    return aBits - bBits;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortByBits(int* arr, int arrSize, int* returnSize){
    qsort(arr, arrSize, sizeof(int), compare);
    *returnSize = arrSize;
    return arr;
}