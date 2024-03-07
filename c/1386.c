int familysInRow(int *seated)
{
    if (seated[1] == 0 && seated[2] == 0 && seated[3] == 0 && seated[4] == 0 &&
        seated[5] == 0 && seated[6] == 0 && seated[7] == 0 && seated[8] == 0) {
        return 2;
    }
    if (seated[1] == 0 && seated[2] == 0 && seated[3] == 0 && seated[4] == 0) {
        return 1;
    }
    if (seated[3] == 0 && seated[4] == 0 && seated[5] == 0 && seated[6] == 0) {
        return 1;
    }
    if (seated[5] == 0 && seated[6] == 0 && seated[7] == 0 && seated[8] == 0) {
        return 1;
    }
    return 0;    
}

int compare(const void *p, const void *q)
{
    int *a = *(int**)p;
    int *b = *(int**)q;
    printf("pp:%d, %d\n", a[0],b[0]);
    return a[0] - b[0];
}
int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize){
    int *row = (int*)malloc(sizeof(int) * 10);
    int rowEnd = 0;
    int ans = 0;

    qsort(reservedSeats, reservedSeatsSize, sizeof(int) * 2, compare);

    int line = 1;
    int iter = 0;
    int count = 0;
    while (iter < reservedSeatsSize) {
        for (int i = 0; i < 10; i++) row[i] = 0;
        if (count > 1) {
            ans += 2 * (count - 1);
        }
        count = 0;
        while (iter < reservedSeatsSize && reservedSeats[iter][0] == line) {
            printf("\n%d,%d\n", reservedSeats[iter][0], iter);
            row[ reservedSeats[iter][1]-1 ] = 1;
            iter++;
        }
        ans += familysInRow(row);
        while (iter < reservedSeatsSize && reservedSeats[iter][0] > line) {
            line++;
            count++;
        } 
    }
    if (n - line > 0) {
        ans += 2 * (n - line);
    }
    free(row);

    return ans;
}