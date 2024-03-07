bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n){
    int i;
    // 只有一个元素的单独处理
    if (flowerbedSize == 1 && flowerbed[0] == 0 && n == 1) {
        return true;
    }
    for (i = 0; i < flowerbedSize; i++) {
        if (flowerbed[i] == 1) {
            continue;
        }
        // 如果位于起始位置，只要后面一个不是1，就可以种花
        if (i == 0 && i + 1 < flowerbedSize && flowerbed[i + 1] == 0) {
            n = n - 1;
            flowerbed[i] = 1;
        }
        // 如果位于最后，只要前一个位置不是1，就可以种花
        if (i == flowerbedSize - 1 && i - 1 >= 0 && flowerbed[i - 1] == 0) {
            n = n - 1;
            flowerbed[i] = 1;
        }
        if (i - 1 >= 0 && i + 1 < flowerbedSize && flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
            n = n - 1;
            flowerbed[i] = 1;
        }
    }

    if (n > 0) {
        return false;
    }

    return true;
}