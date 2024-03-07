int sc[26];
int tc[26];

bool isAnagram(char * s, char * t){
    int n1 = strlen(s);
    int n2 = strlen(t);
    int i;

    if (n1 != n2) {
        return false;
    }

    for (i = 0; i < 26; i++) {
        sc[i] = 0;
        tc[i] = 0;
    }

    for (i = 0; i < n1; i++) {
        sc[ s[i] - 'a' ] += 1;
        tc[ t[i] - 'a' ] += 1;
    }

    for (i = 0; i < 26; i++) {
        if (sc[i] != tc[i]) {
            return false;
        }
    }

    return true;
}