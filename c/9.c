bool isPalindrome(int x){
    long lx = 0;
    long sx = x;

    if (x < 0) {
        return false;
    }

    while (x) {
        lx = lx * 10 + (x % 10);
        x = x / 10;
    }

    if (lx == sx) {
        return true;
    }

    return false;
}