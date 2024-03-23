
MAX_OF_CHARS = 256

def badCharHeuristic(string, size): 
    ''' 
    生成坏字符规则, 记录每个字符出现的索引位置，没有出现的设置为 -1
    '''
    badChar = [-1] * MAX_OF_CHARS 

    for i in range(size): 
        badChar[ ord(string[i]) ] = i

    return badChar

def search(string, pattern): 
    ''' 
    只使用坏字符规则的Boyer Moore字符串匹配算法
    '''
    m = len(pattern) 
    n = len(string) 

    badChars = badCharHeuristic(pattern, m) 

    # s is shift of the pattern with respect to text 
    s = 0
    while s <= n - m: 
        # j 指向 s 最后一个字符，找到第一个不匹配的字符的位置
        j = m - 1
        while j >= 0 and pattern[j] == string[s + j]: 
            j -= 1

        # 如果 j 小于0， 表示找到了一个匹配，输出结果，继续查找下一个匹配
        if j < 0: 
            print("Pattern occur at shift = {}".format(s)) 

            # 如果 s + m 小于 n, 直接对其S中最后一个字符
            if s + m < n:
                s += m - badChars[ ord(string[s + m]) ]
            else:
                s += 1
        else: 
            s += max(1, j - badChars[ ord(string[s + j]) ]) 
    return 0

txt = "ABAAABCD"
pat = "ABC"
search(txt, pat) 