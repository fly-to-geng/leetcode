void parse(char *string, int *year, int *month, int *day)
{
    int yyyy = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] - '0') * 10 + (string[3] - '0');
    int mm = (string[5] - '0') * 10 + (string[6] - '0');
    int dd = (string[8] - '0') * 10 + (string[9] - '0');

    *year = yyyy, *month = mm, *day = dd;

    return;
}
int getMonthDay(int year, int m)
{
    int ans = 0;
    switch(m){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            ans = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            ans = 30;
            break;
        case 2:
            if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) ans = 29;
            else ans = 28;
            break;
    }
    return ans;
}
int days(int year, int month, int day)
{
    int ans = day;
    for (int i = 1; i < month; i++) {
        ans += getMonthDay(year, i);
    }
    printf("%d-%d-%d : %d\n", year, month, day, ans);
    return ans;
}
int daysBetweenDates(char * date1, char * date2){
    int y1, m1, d1; int y2, m2, d2;
    int ans;

    parse(date1, &y1, &m1, &d1); parse(date2, &y2,&m2,&d2);

    if (y1 >= y2) {
        int dd1 = 0;
        dd1 = days(y1, m1, d1);
        for (int yy = y1 - 1; yy >= y2; yy--) {
            dd1 += days(yy,12,31);
        }

        int dd2 = days(y2, m2, d2);
        if (dd1 > dd2) ans = dd1 - dd2;
        else ans = dd2 - dd1;
        return ans;
    }
    return daysBetweenDates(date2, date1);                                                                                                               
}