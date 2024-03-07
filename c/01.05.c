bool canReach(char* first, char *second)
{
    int i = 0;
    int j = 0;
    while (i < strlen(first) && j < strlen(second) && first[i] == second[j]) {
        i++;
        j++;
    }
    i = i + 1; //跳过一个字符
    while (i < strlen(first) && j < strlen(second)) {
        if (first[i] != second[j]) {
            return false;
        }
        i++;
        j++;
    }
    return true;
}
bool oneEditAway(char* first, char* second){
    if (first == NULL || second == NULL) return true;

    int n1 = strlen(first);
    int n2 = strlen(second);
    int i,j,num;

    if (n1 == n2) {
        num = 0;
        for (i = 0; i < n1; i++) {
            if (first[i] != second[i]) {
                num++;
            }
        }
        if (num <= 1) {
            return true;
        } else {
            return false;
        }
    } else if (n1 - n2 == 1) {
        return canReach(first, second);
    } else if (n2 - n1 == 1) {
        return canReach(second, first);
    } else {
        return false;
    }
}