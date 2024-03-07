# KMP 算法

设有字符串T，模式串P，要从T中找出P，通常的做法是逐个比较T和P的第一个字符，如果相同，就比较T和P的第二个字符，一旦匹配失败，T后移一个字符重新开始与P的第一个字符比较。但是这样的方法如果遇到特别"刁钻"的T和P的组合，就会浪费很多比较的时间，例如，每次都是比较到P的最后一个字符才不匹配。KMP算法就是为了减少不必要的比较，使得每次比较不成功的时候，P可以向后移动尽可能远的距离。

每次失败后要向后移动多少呢？这个由P的next数组决定。next数组是一个与P等长，只与模式串P有关系，而与T没有关系的一个整数数组。它的值表示当前这个字符比较失败后，模式串向后移动的距离。

next数组如何求解呢？ P中任何一个字符对应的next数组的值，等于从P开始到它所对应的前缀和后缀的共有元素的长度。举例来说，P="ABCDABD"

"A"的前缀和后缀都是0，共有的长度也是0；

"AB"的前缀是"A",后缀是"B",共有的长度是0；

"ABC"的前缀是"A","AB",后缀是"C","BC",共有的长度为0；

"ABCD"的前缀是"A","AB","ABC",后缀是"D","CD","BCD",共有的长度为0；

"ABCDA"的前缀是"A","AB","ABC","ABCD",后缀是"A","DA","CDA","BCDA",二者都有A，所有共有的长度是1.

"ABCDAB" 共有的长度为2

"ABCDABD" 共有的长度为0.

所以P的next数组为[0,0,0,0,1,2,0]. 可以看到，求解next数组的过程还是很清晰的，但是这个next数组并不是真正在KMP算法中使用的next数组。但是KMP算法中使用的next数组可以可容易的由这个数组生成，规则是：所有的元素右移一位。最右边的元素丢弃不要了，最左边补-1，这样新的next数组为[-1,0,0,0,0,1,2].

直到next数组的值，KMP算法其实就算实现了，接下来只需要在每次匹配失败的时候，模式串向右移动的位数是： 失配字符所在的位置-失配字符对应的next数组的值。

求解next数组的代码：

```c
/**
 *  求解模式串的next数组
 * @param p
 * @return
 */
vector<int> GetNext(string p)
{
    int pLen = p.size();
    vector<int> next(pLen,0);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1)
    {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++k;
            ++j;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
    return next;
}
```

此方法求解next数组其实并不是最优的，因为还有可能存在重复的比较，具体的实例可以参考<http://blog.csdn.net/v_july_v/article/details/7041827>, 优化后的next数组求解方法可以进一步减少比较的次数，只是这个会更不容易理解。

```c
vector<int> OGetNext(string p)
{
    int pLen = p.size();
    vector<int> next(pLen,0);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1)
    {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            //较之前next数组求法，改动在下面4行
            if (p[j] != p[k])
                next[j] = k;   //之前只有这一行
            else
                //因为不能出现p[j] = p[ next[j ]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]
                next[j] = next[k];
        }
        else
        {
            k = next[k];
        }
    }
    return next;
}
```
使用next数组查找模式串第一次出现的位置，并返回索引的函数，不存在会返回-1.

```c
int KmpSearch(string &s, string &p)
{
    int i = 0;
    int j = 0;
    int sLen = s.size();
    int pLen = p.size();
    auto next = OGetNext(p);
    while (i < sLen && j < pLen)
    {
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]
            //next[j]即为j所对应的next值
            j = next[j];
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
}
```

使用next数组比较字符串，返回模式串在S中出现的次数的函数。

```c
int KmpSearch(string &s, string &p)
{
    int i = 0;
    int j = 0;
    int sLen = s.size();
    int pLen = p.size();
    auto next = OGetNext(p);
    int count = 0;
    while(i<sLen){
        while (i < sLen && j < pLen)
        {
            //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
            if (j == -1 || s[i] == p[j])
            {
                i++;
                j++;
            }
            else
            {
                //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]
                //next[j]即为j所对应的next值
                j = next[j];
            }
        }
        if (j == pLen){
            count++;
            j=0;
        }
    }
    return count;
}
```