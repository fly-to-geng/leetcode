void shift(char *S, int i, int count)
{
    int num;
    num = S[i] - 'a';
    num = (num + count % 26 ) % 26;
    S[i] = num + 'a';
}
char * shiftingLetters(char * S, int* shifts, int shiftsSize){
    int i;
    for (i = shiftsSize - 2; i >= 0; i--) {
        shifts[i] = (shifts[i+1] % 26 + shifts[i] % 26) % 26;
    }
    for (i = 0; i < shiftsSize; i++) {
        shift(S, i, shifts[i]);
    }
    return S;
}