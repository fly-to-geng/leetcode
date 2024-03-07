# Rabin-Karp 算法

Rabin Karp算法比较模式串P 和 待查找串S 中每个与P长度相同的字串， 比较的时候先计算其哈希值，在比较哈希值是否一致。

## 哈希函数

因为要计算很多次哈希，如果每次都从头开始计算，复杂度会很高，我们希望哈希函数可以根据上一次的结果和本次新增的字符和删除的字符在 O(1) 的时间内计算得出，这样每次移动一个字母，哈希值都可以在O(1) 的时间内得到。

设 `d` 表示字符的种类， d = 128 或者 d = 256 都可以。 如果某个应用场景中字母只有`abcdef`, 那么 `d = 6`.
`p` 表示模式串P计算得到的哈希值， 初始化 `p = 0`.

把一个字符串最终转换成一个数字，容易想到的办法就是每个字母转换成其对应大小的数值，然后偏移一个值，累加。
例如 `abc` 转换成数字可以是 `a * 100 + b * 10 + c = 10779`, 
`cba` 转成数字可以是 `c * 100 + b * 10 + a = 10977`.
这样每个字符串都对应唯一一个数值，而且滑动的时候不用重新计算，只需要减去滑出的字母，加入划入的字母就可以。
例如， `bcd` 转换成数字是 `(10779 - a * 100) * 10 + d = 10890` 与直接计算 `b*100 + c * 10 + d = 10890` 结果是一样的。

上述哈希方法完全满足要求，但是当字符串变长之后，整数会变得非常大，超过整数的表示范围。
我们使用模运算控制最终得到的整数范围，任意选择一个大的素数作为模。设模为 `q = 101`.

我们使用 `d` 作为基数代替上面提到的 10，因为字母的种类可能远大于10，使用10只是为了便于理解，使用 `d` 才能分隔开每个不同的字母。

综上，我们得到的计算最终哈希值的哈希函数就是：

```python
d = 0
for i in range(len(pattern)):
    p = (d * p + pattern[i]) % q
```

滑动更新的时候，类似上面以10为基数举例的时候，先减去最高位，再 乘以 `d`, 然后加上滑入的最低位。
最高位数值 `h = d ^ (M - 1)`, 其中 `M = len(pattern)`.

```python
t = 0
for i in range(len(pattern)):
    t = (d * t + text[i]) % q

i = 0
# 向后滑动一个字符，text[i] 滑出， text[i + M] 滑入， 新的值为
t = ( d * (t - ord(text[i]) * h) + ord(text[i+m]) ) % q
```

因为最终的哈希值是取模之后的结果，所以值不一样的时候可以保证原字符串肯定不相等，但是值一样的时候不能保证原字符串一定相等。
当遇到哈希值一样的两个串的时候，还需要逐个字符比较，看是否相等。


## 算法实现

```python
# Following program is the python implementation of 
# Rabin Karp Algorithm given in CLRS book 

# d is the number of characters in the input alphabet 
d = 256

# pat -> pattern 
# txt -> text 
# q -> A prime number 

def search(pat, txt, q): 
    M = len(pat) 
    N = len(txt) 
    i = 0
    j = 0
    p = 0 # hash value for pattern 
    t = 0 # hash value for txt 
    h = 1

    # The value of h would be "pow(d, M-1)%q" 
    for i in xrange(M-1): 
        h = (h*d)%q 

    # Calculate the hash value of pattern and first window 
    # of text 
    for i in xrange(M): 
        p = (d*p + ord(pat[i]))%q 
        t = (d*t + ord(txt[i]))%q 

    # Slide the pattern over text one by one 
    for i in xrange(N-M+1): 
        # Check the hash values of current window of text and 
        # pattern if the hash values match then only check 
        # for characters on by one 
        if p==t: 
            # Check for characters one by one 
            for j in xrange(M): 
                if txt[i+j] != pat[j]: 
                    break

            j+=1
            # if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1] 
            if j==M: 
                print "Pattern found at index " + str(i) 

        # Calculate hash value for next window of text: Remove 
        # leading digit, add trailing digit 
        if i < N-M: 
            t = (d*(t-ord(txt[i])*h) + ord(txt[i+M]))%q 

            # We might get negative values of t, converting it to 
            # positive 
            if t < 0: 
                t = t+q 

# Driver program to test the above function 
txt = "GEEKS FOR GEEKS"
pat = "GEEK"
q = 101 # A prime number 
search(pat,txt,q) 

# This code is contributed by Bhavya Jain 

```

参考文献：https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/?ref=rp
