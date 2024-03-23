#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define N 20
void setAns(char *ans, int ipType)
{
    if (ipType == 1) {
        ans[0] = 'I';
        ans[1] = 'P';
        ans[2] = 'v';
        ans[3] = '4';
        ans[4] = '\0';
    } else if (ipType == 2) {
        ans[0] = 'I';
        ans[1] = 'P';
        ans[2] = 'v';
        ans[3] = '6';
        ans[4] = '\0';
    } else {
        ans[0] = 'N';
        ans[1] = 'e';
        ans[2] = 'i';
        ans[3] = 't';
        ans[4] = 'h';
        ans[5] = 'e';
        ans[6] = 'r';
        ans[7] = '\0';
    }
}
int find(char *IP, char c)
{
    const int n = strlen(IP);
    int i;
    for (i = 0; i < n; i++) {
        if (IP[i] == c) {
            return 1;
        }
    }
    return 0;
}
// 是 ipv4地址返回 1
int isIpv4(char *IP)
{
    // 按照 . 分割成4个数字，检查4个数组是否合法
    const int n = strlen(IP);
    int i = 0;
    int num = 0;
    int count = 0;
    while (i < n) {
        if (IP[i] >= '0' && IP[i] <= '9'){
            if (num == 0 && IP[i] == '0') {
                // 有前导0不合法
                if (i+1 < n && IP[i+1] == '.') {
                    i++;
                    continue;
                }
                if (i+1 == n) {
                    i++;
                    continue;
                }
                return 10;
            }
            if (num >= 256) {
                return 10;
            }
            num = num * 10 + IP[i] - '0';
        } else if (IP[i] == '.') {
            count++;
            if (num < 0 || num >= 256) {
                // 超出数据范围不合法
                return 10;
            }
            if (i == n - 1) {
                // 最后一个不能是 .
                return 10;
            }
            if (i + 1 < n && IP[i + 1] == '.') {
                // . 不能直接相连
                return 10;
            }
            num = 0;
        } else {
            return 10;
        }
        i++;
    }
    // 最后一组的数字也要合法
    if (num < 0 || num >= 256) {
        return 10;
    }
    // 应该恰好有 3 个点号，分成4组
    if (count != 3) {
        return 10;
    }
    return 1;
}
// 是 ipv6 地址返回 2
int isIpv6(char *IP)
{
    const int n = strlen(IP);
    int i, j;
    int count = 0; // : 的个数
    int every_count = 0; // 每个组内部不应该超过4位
    i = 0;
    while (i < n) {
        if ( (IP[i] >= '0' && IP[i] <= '9')  ||
              (IP[i] >= 'a' && IP[i] <= 'f') ||
              (IP[i] >= 'A' && IP[i] <= 'F') ) {
                  every_count++;
        } else if (IP[i] == ':') {
            count++;
            if (i == n - 1) {
                return 10;
            } else if (i + 1 < n && IP[i+1] == ':') {
                return 10;
            }
            if (every_count > 4) {
                return 10;
            }
            every_count = 0;
        } else {
            return 10;
        }
        i++;
    }
    if (every_count > 4) {
        return 10;
    }
    if (count >= 8) {
        return 10;
    }
    return 2;
}
char * validIPAddress(char * IP){
    char *ans;
    int ipType;
    ans = (char*)malloc(sizeof(char) * N);
    if (find(IP, '.')) {
        ipType = isIpv4(IP);
    } else if (find(IP, ':')) {
        ipType = isIpv6(IP);
    } else {
        ipType = 3;
    }

    setAns(ans, ipType);
    return ans;
}