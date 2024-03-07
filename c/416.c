char *reversed(char *string)
{
    int i, j;
    int len = strlen(string);
    int mid = len / 2;
    char c;
    char *ans;
    ans = (char*)malloc(sizeof(char) * (len + 1));
    strcpy(ans, string);
    i = 0;
    j = len - 1;
    while (i < j) {
        c = ans[i];
        ans[i] = ans[j];
        ans[j] = c;
        i++;
        j--;
    }
    ans[len] = '\0';
    return ans;
}
char * addStrings(char * num1, char * num2){
    int n1, n2, i;
    int carry = 0;
    int sum = 0;
    char *reversedNum1;
    char *reversedNum2;
    char *reversedAns;
    char *ans;

    n1 = strlen(num1);
    n2 = strlen(num2);
    if (n1 < n2) {
        return addStrings(num2, num1);
    }
    if (n1 == 0 && n2 == 0) {
        return num1;
    }
    if (n1 == 0) {
        return num2;
    }
    if (n2 == 0) {
        return num1;
    }

    reversedAns = (char*)malloc(sizeof(char) * (strlen(num1) + 2));
    reversedNum1 = reversed(num1);
    reversedNum2 = reversed(num2);

    for (i = 0; i < n2; i++) {
        sum = reversedNum1[i] - '0' + reversedNum2[i] - '0' + carry;
        reversedAns[i] = sum % 10 + '0';
        carry = sum / 10;
    }
    for (;i < n1; i++) {
        sum = reversedNum1[i] - '0' + carry;
        reversedAns[i] = sum % 10 + '0';
        carry = sum / 10;
    }
    if (carry > 0) {
        reversedAns[i] = carry + '0';
        i++;
    }
    reversedAns[i] = '\0';
    ans = reversed(reversedAns);
    free(reversedNum1);
    free(reversedNum2);
    free(reversedAns);
    return ans;
}