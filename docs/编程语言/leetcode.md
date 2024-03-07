# leetcode 常用函数

### 判断x是否是素数

```c
// 判断x是否是素数
bool isPrime(int x){
    int xx = (int)sqrt((double)x);
    for(int i=2;i<=xx;i++){
        if( x % i == 0) return false;
    }
    return true;
}
```

### 找出n以内，2，3，5整除的所有数字

```c
// 返回三个数字中的最小值和最小值的索引
int minThree(vector<int> v, int &index){
    if(v.size()!=3) return -1;
    int minValue = v[0];
    index = 0;
    if(minValue > v[1]){
        minValue = v[1];
        index = 1;
    }
    if(minValue > v[2]){
        minValue = v[2];
        index = 2;
    }
    return minValue;
}
// 找出n以内所有能被2，3，5其中一个或者多个整除的数字
vector<int> getNumbers(int x){
    vector<int> results={1};
    vector<int> index235 = {1,1,1};
    int index = 0;
    int minValue = minThree({2*index235[0],3*index235[1],5*index235[2]},index);
    while(minValue<=x){
        if(minValue != results[results.size()-1]){
            results.push_back(minValue);
        }
        index235[index]++;
        minValue = minThree({2*index235[0],3*index235[1],5*index235[2]},index);
    }
    return results;
}
```

### 找出第1500个只包含2或3或5为因子的数字(从1开始)

```c
// 返回三个数字中的最小值和最小值的索引
int minThree(vector<int> v, int &index){
    if(v.size()!=3) return -1;
    int minValue = v[0];
    index = 0;
    if(minValue > v[1]){
        minValue = v[1];
        index = 1;
    }
    if(minValue > v[2]){
        minValue = v[2];
        index = 2;
    }
    return minValue;
}
// 找到第K个数字（从1开始）
int getNumbers(int k){
    vector<int> index235 = {1,1,1};
    int index = 0;

    int tmp = 1;
    int count = 1;
    int minValue = 1;
    while(count < k){
        minValue = minThree({2*index235[0],3*index235[1],5*index235[2]},index);
        if(minValue != tmp){
            count++;
            tmp = minValue;
        }
        index235[index]++;
    }
    return minValue;
}
```


### 小于等于n的所有素数

```c
// 找出x以内的所有素数
vector<int> getPrimes(int x){
    vector<int> Primes;
    // 初始化 0 - x 都是素数
    vector<bool> isPrime(x+1,true);
    isPrime[0] = false; // 0 不是素数
    isPrime[1] = false; // 1 不是素数
    for(int i=2;i<=x;i++){
        // 如果i是素数，把所有i的倍数设置成不是素数
        if(isPrime[i]){
            Primes.push_back(i);
            for(int j=i*2;j<=x;j=j+i){
                isPrime[j] = false;
            }
        }
    }
    return Primes;
}
```

### 最大公约数

```c
// 最大公约数
int getY(int x,int y){
    int tmp = 0;

    while(y){
        tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}
```

### 整数转换成字符串

```c
#include <sstream>
#include <string>
string Int_to_String(int n)
{
    ostringstream stream;
    stream<<n;  //n为int类型
    return stream.str();
}
```
### 十进制数字转换成K进制之后数位之和

```c
// 10进制数字 转换成K进制之后各个数位的数字之和
int getSum(int n,int k){
    int sum = 0;
    while(n){
        sum += n % k;
        n = n / k;
    }
    return sum;
}
```

### 十进制数字转换成K进制

```c
deque<int> Kin(int n,int k){
    deque<int> result;
    while(n/k != 0){
        result.push_front(n%k);
        n = n / k;
    }
    result.push_front(n);
    return result;
}
```
### K进制数字转换成十进制
```c
/**
 * 将K进制的deque转换成10进制
 * @param v
 * @return
 */
int Kinverse(deque<int> v,int k){
    int s = 0;
    int i = 0;
    while(!v.empty()){
        s += v.back() * std::pow(float(k),i);
        ++i;
    }
    return s;
}
```

### 快速幂和矩阵快速幂

**整数的快速幂**

求$a^b$一般的做法是用一个循环，将a累乘b次，这样需要做b次乘法。快速幂的思想是利用了$a^(b1+b2) = a^b1 + a^b2$的思想，把b表示成二进制，然后拆分开，分别求幂，再求和。举例来说：

假设要求$5^{12}$,传统的方法是12个5相乘，要做12次乘法运算。快速幂的思想是把12表示成二进制，`1100` =$2^2+2^3$,
$$
5^{12} = 5^{(2^2+2^3)} = 5^{2^2} * 5^{2^3}
$$
2的幂的计算可以由十分迅速的移位计算得到，所有原来需要12个乘法运算才能解决的计算问题，现在编程了只需要三次计算节能解决。

```c
int quickPow(int a,int b){
    int ans=1,base=a;
    while(b!=0){
        if(b&1!=0)
        　　ans*=base;
        base*=base;
        b>>=1;
　 }
    return ans;
}
```
按照上面的代码计算出来的实际上是$5^{2^2} * 5^{2^3}$, 因为我们用的是右移，每次都只判断末尾的一个二进制位，如果是1，就乘入当前的结果。每次循环（不管是不是1），base都要翻倍，因为是二进制，每移动一位就意味着乘以2.

另外一个需要注意的问题是，实际使用时需要注意数据的范围，如果int的范围不够，可以使用long long类型。

**矩阵的快速幂**

- 矩阵乘法
一个$m*n$的矩阵  乘以 一个$n*p$的矩阵，会得到一个$m*p$的矩阵。矩阵相乘的规则是：第一个矩阵的每一行乘以第二个矩阵的每一列，对应的元素相乘再相加，作为新矩阵对应位置上的元素。朴素的矩阵乘法的代码如下：
```c
typedef vector<vector<int>> matrix;
matrix MatricMul(matrix A,matrix B){
    int m = A.size();
    int n1 = A[0].size();
    int n2 = B.size();
    int p = B[0].size();
    if(n1 != n2) {cout<<"no cheng of the two matrix."<<endl;return matrix();}
    int n = n1 = n2;
    matrix C(m,vector<int>(p,0));
    for(int i=0;i<m;i++){
        for(int j=0;j<p;j++){
            for(int k=0;k<n;k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main(){
    matrix A = {{1,2,3},{4,5,6}};
    matrix B = {{1,2},{3,4},{5,6}};
    matrix C = MatricMul(A,B);
    return 0;
}
```

-$A^n$快速求矩阵的n次幂，注意这里A只能是方阵
矩阵的快速幂和整数的快速幂是一样的，就是重载一下*这个运算符，使得两侧是矩阵的时候，计算的是矩阵乘法。这里我们就不重载运算符了，直接使用上面定义的矩阵乘法函数`MatricMul`:
```c
matrix quickPowMatrix(matrix A,int n){
    matrix base = A;
    // 初始化成单位矩阵
    int len = A.size();
    matrix ans(len,vector<int>(len,0));
    for(int i=0;i<A.size();i++){
        ans[i][i] = 1;
    }
    while(n!=0){
        if(n&1!=0)
            ans = MatricMul(ans,base);
        base = MatricMul(base,base);
        n>>=1;
    }
    return ans;
}
```

快速幂通常用来求很大的数，这个时候虽然就算速度在可以接受的范围内，但是数据的范围早已经超过了能够表示范围，通常的方法就是mod每个大数，得到一个较小的结果。

为了减少计算的开销（计算小数的乘法要比计算大数的乘法开销小），通常利用模运算的法则：

$$
(a+b) mod c = (a mod c + b mod c) mod c ;
$$

$$
(a*b) mod c = (a mod c * b mod c) mod c ;
$$

上面的代码每一次计算之后就取模，就可以保证数据的范围不溢出，还能保证比较快的计算速度。

**使用C++的模版技术编写通用的快速幂模版**
```c
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template<class T, int MAXN, T MOD=-1>
class Matrix {
public:
    T m[MAXN][MAXN];
    Matrix(){}
    // 如果MOD不是-1，把num取模
    void init(T num[MAXN][MAXN]){
        for(int i = 0 ; i < MAXN ; i++)
        {
            for(int j = 0 ; j < MAXN ; j++)
            {
                m[i][j] = num[i][j];
                if (MOD!=-1)
                    m[i][j] %= MOD;
            }
        }
    }
    //矩阵乘法的实现
    friend Matrix operator*(const Matrix &m1 ,const Matrix &m2)
    {
        int i, j, k;
        Matrix ret;
        memset(ret.m, 0, sizeof(ret.m));
        for (i = 0; i < MAXN; i++) {
            for (j = 0; j < MAXN; j++)
                if ( m1.m[i][j] )
                {
                    for(k = 0 ; k < MAXN ; k++){
                        ret.m[i][k] += m1.m[i][j] * m2.m[j][k];
                        if (MOD!=-1) ret.m[i][k] %= MOD;
                    }
                }
        }
        return ret;
    }
    // 矩阵加法的实现
    friend Matrix operator+(const Matrix &m1 ,const Matrix &m2) {
        int i, j;
        Matrix ret;
        for (i = 0; i < MAXN; i++) {
            for (j = 0; j < MAXN; j++) {
                ret.m[i][j] = 0;
                ret.m[i][j] = m1.m[i][j]+m2.m[i][j];
                if (MOD!=-1)
                    ret.m[i][j] %= MOD;
            }
        }
        return ret;
    }
    //矩阵快速幂的实现
    friend Matrix operator^(const Matrix &_M , LL nx){
        Matrix ret,M(_M);
        //ret 初始化成单位矩阵
        for(int i = 0 ; i < MAXN ; i++){
            for(int j = 0 ; j < MAXN ; j++){
                if(i == j)
                    ret.m[i][j] = 1;
                else ret.m[i][j] = 0;
            }
        }
        while(nx){
            if(nx & 1)
                ret = ret * M;
            nx = nx >> 1;
            M = M * M;
        }
        return ret;
    }
};

int main(){
    int C[2][2] = {{1,2},{3,4}};
    Matrix<int,2,1000> mm;
    mm.init(C);
    auto add = mm + mm;
    auto cheng = mm * mm;
    auto mi = mm ^ 2 ;
    return 0;
}
```
### 包含一切的头文件

```c
#include <bits/stdc++.h>
```
一个文件包含了所有常用的头文件，你所有使用的函数不再需要引入相应的头文件。该头文件在ACM竞赛中经常被使用，可以减少你包含需要的头文件需要的时间。

需要注意的是，这个头文件并不是标准的，这意味着可能有的编译器不支持它。


### 返回一个无序数组排序之后的下标，不动原来的数组

例如 a = [3,5,2,4,1] , 从小到大排序之后应该是[1,2,3,4,5], 原来在a中的下标是[4,2,0,3,1],我们的目标就是输入a，返回[4,2,0,3,1]
```c
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> getOrderIndex(vector<int> &a){
    vector<int> order(a.size(),0);
    for(int i=0;i<a.size();i++){
        order[i] = i;
    }
    sort(order.begin(), order.begin() + a.size(), [a](const int& x, const int& y)->bool { return a[x] < a[y];});
    return order;
}
```
order中就是我们想要的结果。


### 字符串转换成整数

```c
/**
 * 用空格分割的字符串转换成整数
 * @param s 
 * @return 
 */
vector<int> string2int(string &s){
    istringstream in(s);
    vector<int> v;
    int num;
    while(in >> num){
        v.push_back(num);
    }
    return v;
}
```

### 输入挂

当纯数字的输入规模超过$10^6$时，可以考虑使用输入挂，比系统自带的cin快很多。

```c
inline void q_read(int &num)
{
    char ch; int f = 1;
    while(true)
    {
        ch = getchar();
        if(ch == '-') f = -1;
        if(isdigit(ch))
        {
            num = ch - '0';
            break;
        }
    }
    while(ch = getchar(), isdigit(ch)) num = num*10+ch-'0';
    num *= f;
}
```

还可以在开始的时候加入 `ios::sync_with_stdio(false);`, 它的作用是去掉cin额外的检查开销，达到和scanf相似的输入效率；
