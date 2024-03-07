int kthGrammar(int N, int K){
    int count = 0;
    int number;
    int i = N - 2;

    if (N == 1) return 0;
    if (N == 2) return K - 1;

    while (i) {
        number = 1 << i;
        count += K / number;
        K = K % number;
        i--;
    }

    if (count % 2) {
        return K;
    }

    return 1 - K;
}