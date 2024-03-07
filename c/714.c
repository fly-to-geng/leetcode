#define max(a, b) ((a) > (b)) ? (a) : (b)
int maxProfit(int* prices, int pricesSize, int fee){
    int unhold = 0;
    int hold = -prices[0];
    int i;
    for (i = 1; i < pricesSize; i++) {
        unhold = max(unhold, hold + prices[i] - fee);
        hold = max(hold, unhold - prices[i]);
    }
    return unhold;
}