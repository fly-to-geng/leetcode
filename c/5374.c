
char *generate(int n)
{


}

char *next(char *curr)
{

}
char * getHappyString(int n, int k){
    char *start = generate(n);
    while (next(start) && k--) {
        start = next(start);
    }
    return start;
}

