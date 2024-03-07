int lengthOfLastWord(char * s){
    if (s == NULL) {
        return 0;
    }

    int n = strlen(s);
    int end = n - 1;
    while (end >= 0 && s[end] == ' ') {
        end -= 1;
    }
    int start = end;
    while (start >= 0 && s[start] != ' ') {
        start -= 1;
    }
    return end - start;


}