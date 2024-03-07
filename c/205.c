#define MAXV 256
int mapAB[MAXV]; /* 记录从A到B的映射关系 */
int mapBA[MAXV]; /* 记录从B到A的映射关系 */

void init()
{
    int i;
    for (i = 0; i < MAXV; i++) {
        mapAB[i] = -1;
        mapBA[i] = -1;
    }
    return;
}
bool isIsomorphic(char * s, char * t){
    if (s == NULL && t == NULL) return true;
    if (s == NULL || t == NULL) return false;
    if (strlen(s) != strlen(t)) return false;

    int n = strlen(s);
    int i;

    init();
    for (i = 0; i < n; i++) {
        if (mapAB[ s[i] ] == -1 && mapBA[ t[i] ] == -1) {
            mapAB[ s[i] ] = t[i];
            mapBA[ t[i] ] = s[i];
        } else if (mapAB[ s[i] ] == -1) {
            /* s[i] --> t[i] 且 other --> t[i], 两个字符映射到同一个 */
            if (mapBA[ t[i] ] != s[i]) {
                return false;
            }
            mapAB[ s[i] ] = t[i];
        } else {
            /* s[i] --> t[i] 且 s[i] --> other, 一个字符映射到两个 */
            if (mapAB[ s[i] ] != t[i]) {
                return false;
            }
            mapBA[ t[i] ] = s[i];
        }
    }
    return true;
}