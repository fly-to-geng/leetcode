# Boyer Moore

Boyer Moore 算法从模式串的最后一个字符匹配；
Boyer Moore 算法预处理模式串， 生成坏字符规则 和 好后缀规则，每次选取两个规则中向后移动距离最大的那个。
使用坏字符规则 和 好后缀规则任意一个也可以完成算法，只是效率可能略低。

## 坏字符规则

设模式串P， 要搜索的串为S， 对其S和P，从P最后一个字符开始比较，第一个不匹配的字符称为坏字符(在S中)。

1. 如果坏字符在P中， 移动P使得P中的坏字符和S中的坏字符对其；
2. 如果坏字符不在P中，移动P到坏字符的下一位开始比较。(直接向后移动一个|P|的长度)

```python

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
            # 找到坏字符，直接移动到坏字符后面
            s += max(1, j - badChars[ ord(string[s + j]) ])

txt = "ABAAABCD"
pat = "ABC"
search(txt, pat) 
```

参考文献：https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/

## 好后缀规则

S和P对其比较的过程中，从后向前匹配的部分叫做好后缀。例如

```
0123456789
is simple
  example
```

其中 `mple` 是匹配的后缀，叫做好后缀。 `ple, le, e` 也是好后缀。

设 `p` 表示匹配的最大的好后缀部分，
1. 如果 `p` 出现在模式串P中， 那么就向后移动到对其`p`
2. 如果 `p` 没有出现到模式串P中， 查找 `p` 的后缀是否是P的前缀，一旦找到，对其前缀和后缀
3. 如果 `p` 的后缀也不是P的前缀，直接移动|P|长度，进行下一次比较

第一种情况：

```
0 1 2 3 4 5 6 7 8
A B A A B A B A C
C A B A B
```
`AB`是匹配的好后缀，出现在P中的4位置，向前查找可以发现2位置也出现了`AB`, 可以直接把位置2的`AB`与位置4的对其。

```
0 1 2 3 4 5 6 7 8
A B A A B A B A C
    C A B A B
```

第二种情况：

```
0 1 2 3 4 5 6 7 8
A A B A B A B A C
A B[B A B]
```

`BAB` 是好后缀， 但是在P中向前查找，不再包含`BAB`, 查找 `BAB`的后缀`AB`, 发现`AB` 是模式串P的前缀，我们可以直接将P的前缀`AB` 和好后缀的后缀`AB` 对齐。

```
0 1 2 3 4 5 6 7 8
A A B A B A B A C
     [A B]B A B
```

第三种情况：

```
0 1 2 3 4 5 6 7 8 9
A A C A B A B A C D
C B A[A B]
```

`AB`是好后缀，但是P中向前寻找没有找到`AB`, `AB`的后缀 `B` 也不是P的前缀，所以这是情况3，直接移动整个P到后面。

```
0 1 2 3 4 5 6 7 8 9
A A C A B A B A C D
          C B A A B
```


```python
# Python3 program for Boyer Moore Algorithm with 
# Good Suffix heuristic to find pattern in 
# given text string 

# preprocessing for strong good suffix rule 
def preprocess_strong_suffix(shift, bpos, pat, m): 

	# m is the length of pattern 
	i = m 
	j = m + 1
	bpos[i] = j 

	while i > 0: 
		
		'''if character at position i-1 is 
		not equivalent to character at j-1, 
		then continue searching to right 
		of the pattern for border '''
		while j <= m and pat[i - 1] != pat[j - 1]: 
			
			''' the character preceding the occurrence 
			of t in pattern P is different than the 
			mismatching character in P, we stop skipping 
			the occurrences and shift the pattern 
			from i to j '''
			if shift[j] == 0: 
				shift[j] = j - i 

			# Update the position of next border 
			j = bpos[j] 
			
		''' p[i-1] matched with p[j-1], border is found. 
		store the beginning position of border '''
		i -= 1
		j -= 1
		bpos[i] = j 

# Preprocessing for case 2 
def preprocess_case2(shift, bpos, pat, m): 
	j = bpos[0] 
	for i in range(m + 1): 
		
		''' set the border position of the first character 
		of the pattern to all indices in array shift 
		having shift[i] = 0 '''
		if shift[i] == 0: 
			shift[i] = j 
			
		''' suffix becomes shorter than bpos[0], 
		use the position of next widest border 
		as value of j '''
		if i == j: 
			j = bpos[j] 

'''Search for a pattern in given text using 
Boyer Moore algorithm with Good suffix rule '''
def search(text, pat): 

	# s is shift of the pattern with respect to text 
	s = 0
	m = len(pat) 
	n = len(text) 

	bpos = [0] * (m + 1) 

	# initialize all occurrence of shift to 0 
	shift = [0] * (m + 1) 

	# do preprocessing 
	preprocess_strong_suffix(shift, bpos, pat, m) 
	preprocess_case2(shift, bpos, pat, m) 

	while s <= n - m: 
		j = m - 1
		
		''' Keep reducing index j of pattern while characters of 
			pattern and text are matching at this shift s'''
		while j >= 0 and pat[j] == text[s + j]: 
			j -= 1
			
		''' If the pattern is present at the current shift, 
			then index j will become -1 after the above loop '''
		if j < 0: 
			print("pattern occurs at shift = %d" % s) 
			s += shift[0] 
		else: 
			
			'''pat[i] != pat[s+j] so shift the pattern 
			shift[j+1] times '''
			s += shift[j + 1] 

# Driver Code 
if __name__ == "__main__": 
	text = "ABAAAABAACD"
	pat = "ABA"
	search(text, pat) 

# This code is contributed by 
# sanjeev2552 

```

参考文献: 

1. https://www.geeksforgeeks.org/boyer-moore-algorithm-good-suffix-heuristic/
2. http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
