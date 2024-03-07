#define MAX_CHAR 256
int map[MAX_CHAR];

bool isUnique(char* astr){
    memset(map, -1, sizeof(int) * MAX_CHAR);
    for (int i = 0; i < strlen(astr); i++) {
        if (map[astr[i]] != -1) {
            return false;
        }
        map[astr[i]] += 1;
    }
    return true;
}