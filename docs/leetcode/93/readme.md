# [93. 复原IP地址](https://leetcode-cn.com/problems/restore-ip-addresses/)

## 题目描述

给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

有效的 IP 地址正好由四个整数（每个整数位于 0 到 255 之间组成），整数之间用 '.' 分隔。


示例:

    输入: "25525511135"
    输出: ["255.255.11.135", "255.255.111.35"]

## 解题思路

使用深度优先搜索， 判断当前是否可以分割，如果不能分割，向后扫描； 如果可以分割，尝试分割和不分割两种情况。

注意0的特殊处理，前导0是不允许出现的， 00 也不能作为合法的IP地址的组成部分。

```python
class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        def dfs(start, end, count, ip):
            """
            count = len(ip) 表示当前已经解析出来的IP地址的数量， example: len(2.244) = 2
            [start, end] 表示当前的下标， 多维护一个count避免每次都去获取长度
            """
            # 超过 n 直接退出
            if start > n or end > n:
                return

            if start == end == n:
                # 如果没有分割为4个部分，丢弃掉结果
                if count != 4:
                    return
                ipString = [str(num) for num in ip[:]]
                ipString = ".".join(ipString)
                ans.append(ipString)
                return

            # 只有某一个为n，直接退出
            if start == n or end == n:
                return

            max_leave = (3 - count) * 3 # 如果从 end 处断开， 最大剩余数字个数
            # 如果当前剩余的数字数量超过了最大需要的数量， 不能从这里断开， end + 1 向后尝试
            # 例如 s = "2322512225", ip = [23], count = 1, start = 2, end = 2, 
            # max_leave = 6, 从end处断开剩余7个数字， 而剩下的IP地址最多需要 6个数字， 不能从这里断开
            if n - 1 - end > max_leave:
                dfs(start, end + 1, count, ip)
                return
            else:
                # 如果有前导0，必须只包含0一个数字
                # 00， 01， 025 都是非法的
                if s[start] == '0':
                    if end > start:
                        return
                number = int( s[start:end+1] ) # 转换成数字
                # 数字超过范围，说明分割失败，返回
                if number > 255:
                    return
                # 可以从 end 处分割， 尝试分割和不分割两种情况
                # 分割的情况
                ip.append(number)
                dfs(end + 1, end + 1, count + 1, ip)
                ip.pop()

                # 不分割的情况, 位数大于等于3的时候，没有必要尝试不分割的情况
                if end - start + 1 < 3:
                    dfs(start, end + 1, count, ip)
            return

        n = len(s)
        ip = []
        ans = []
        start, end, count = 0, 0, 0
        dfs(start, end, count, ip)
        return ans
```

测试用例： 010010
