// 运载量为K的船是否可以在D天之内运送完货物
int canShip(int *weights, int weightsSize, int D, int k)
{
    int i = 0;
    int sum = 0;
    while (i < weightsSize) {
        sum += weights[i];
        if (sum > k) {
            D--;
            sum = 0;
            i = i - 1;
        }
        i++;
    }
    if (sum > 0) {
        D--;
    }
    if (D >= 0) return 1;
    return 0;
}
int shipWithinDays(int* weights, int weightsSize, int D){
    int mink, maxk;
    int maxw = weights[0];
    int sumw = 0;
    int i;
    int k;
    for (i = 0; i < weightsSize; i++) {
        if (weights[i] > maxw) {
            maxw = weights[i];
        }
        sumw += weights[i];
    }
    mink = maxw;
    maxk = sumw;
    while (mink < maxk) {
        k = (mink + maxk) / 2;
        if (canShip(weights, weightsSize, D, k)) {
            maxk = k;
        } else {
            mink = k + 1;
        }
    }
    return mink;
}