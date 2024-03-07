#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define C 256
int map[C];

void init()
{
    int i;

    for (i = 0; i < C; i++) {
        map[i] = -1;
    }
}
int lengthOfLongestSubstring(char * s)
{
    int start = 0;
    int end = 0;
    int ans = 0;
    int i, j;

    if (s == NULL) {
        return ans;
    }

    init();
    for (i = 0; i < strlen(s); i++) {
        if (map[ s[i] ] == -1) {
            map[ s[i] ] = i;
            ans = MAX(ans, i - start + 1);
        } else {
            end = map[ s[i] ];
            for (j = start; j <= end; j++) {
                map[ s[j] ] = -1;
            }
            start = end + 1;
            map[ s[i] ] = i;
        }
    }
    return ans;
}