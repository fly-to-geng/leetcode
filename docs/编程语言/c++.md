# C++ 语言基础知识

C++有关的概念和常用的代码。主要包括内存模型(堆内存，栈内存)，虚函数，虚表，const 的用法，include，sizeof, 构造函数等内容。

## 基础概念

### include (文件包含)

**`include <>` 和 `include ""` 有什么区别？**

`<>`和`""`的区别是系统在搜索头文件的时候顺序不同，`<>`在搜索的时候首先从系统目录开始搜索，然后搜索path环境变量下面，不搜索当前的目录； `""`首先搜索当前目录，然后搜索系统和path目录，所以自己写的文件用双引号，系统自带的库用`<>`,主要是为了搜索快。

**如何避免头文件被重复包含**

按照如下的格式书写头文件：

```c
#ifndef _HEADERNAME_H
#define _HEADERNAME_H

...//(头文件内容)

#endif
```

这样头文件在第一次被包含的时候，_HEADERNAME_H 没有被定义，执行定义_HEADERNAME_H的动作并包含头文件的内容，
第二次包含的时候，_HEADERNAME_H 已经被定义，就不会包含后面的内容；`_HEADERNAME_H`是自定义的名称，需要为每一个头文件起一个不一样的名称，这样才能达到效果。

### 常量(const)

**常量的定义方式和异同？**

有两种定义方式： `define PI 3.14` 和 `const double PI = 3.14`.

`define` 定义的常量是在编译之前的预处理阶段执行的简单的字符串替换，就是把代码中所有出现`PI`的地方替换成`3.14`,不执行语法和类型的检查。 `const`定义的常量是在编译阶段处理的，有类型的检查和语法的检查，更安全。 如果使用`define`定义复杂的常量表达式，需要特别注意括号的使用。

**顶层const和底层const**

`const`既可以修饰普通的变量(整形，字符串等)也可以修饰指针，假设一个指针`p`指向一个变量`a`, 如果指针是常量(`p`中存储的地址不能改变) 叫做顶层const, 如果`a`是常量(`a`中存储的数值不能改变)，叫做底层const.

顶层const的定义： `int *const p = &a;`  p 的值不能改变，但是可以通过p改变它指向的a的值；
底层const的定义： `const int *p = &a;`  p 的值可以改变，但是不能通过p改变它指向的a的值。

既是顶层也是底层：`const int *const p = &a;` p的值不能改变，也不能通过p改变a的值；

**常量表达式**

值不会改变并且在编译的时候可以确定值的表达式就是常量表达式，可以使用`constexpr`声明常量表达式，这样编译器会自己判断表达式是否是常量表达式，如果不是，就会报错。`constexpr int m = 20 + 90;`

`constexpr` 还可以用来修饰函数的返回值，这是一种常量函数，要保证在编译的时候就能得到结果。`constexpr int getIntSize(){return 4;}`这样一个函数在编译的时候就可以确定其返回值，所以该函数可以用来初始化常量。 需要注意的是，并不一定加了constexpr的函数就一定返回常量，也可以返回非常量，如果用返回非常量的`constexpr`函数初始化常量，编译器会报错。

### 虚函数

对于非 虚函数的调用，在编译的时候确定调用哪一个，例如函数的重载，通过函数参数的类型，个数就可以确定调用哪一个；
对于虚函数的调用，直到运行的时候才能确定应该调用哪一个函数。 当使用基类的引用调用基类的虚函数的时候，编译器是无法确定到底调用哪一个函数的，需要等到运行时，了解基类的指针或者引用具体绑定到了哪一个子类上，才能确定下来（调用该子类自己实现的函数版本).

1. 虚函数 不代表 不被实现， 纯虚函数才是不被实现的函数；
2. 虚函数的目的是允许用基类的指针调用子类的这个函数；（在基类中声明为虚函数就可以，子类中不用带virtual）
3. 纯虚函数的目的是定义一个接口，规定所有继承该类的的子类必须实现这个函数；
4. 包含纯虚函数的类是抽象类，不能实例化，不能创建类的实例。

虚析构函数的作用是在销毁对象的时候首先销毁基类指针指向的子类对象的实例，再执行基类对象的析构函数，如果子类不定义程虚析构函数，则不会执行子类的析构函数，容易造成内存泄漏。

### 堆内存和栈内存

http://www.cnblogs.com/yyxt/archive/2015/02/02/4268304.html

`char a[] = "1234"; ` 是存储在栈上的；

`char *a = "1234";` 是存储在堆上的；

栈内存访问的速度快于堆内存，因为堆内存的指针也是存放在栈上的，需要先访问栈，然后去堆上访问，对的地址也是不连续的，这导致访问的速度下降。

**new malloc**

`new` 和 `malloc` 开辟的内存是存储在堆上的，需要自己去释放内存，否则只有在程序结束之后才有可能被操作系统回收。
`delete` 和 `free` 是用来释放内存的，delete 或调用被释放对象的析构函数，安全的释放内存，`free` 直接释放。

### 静态链接和动态连接

源文件-->预编译-->编译-->汇编--> **链接** -->可执行程序

如果在链接的时候，将源文件中用到的库函数与汇编生成的文件合并生成一个可执行文件，之后的程序仅需要这个可执行文件即可运行，这样的方式叫做静态链接； 缺点是文件可能太大，毕竟一个简单的程序也会包含很多的头文件。

如果在链接的时候，不把源文件中用到的库合并在一起，而是单独编译，在运行的时候，用到的地方在去寻找该库，这种方式叫做动态链接，动态连接可以有效的避免重复，但是可移植性就受到限制，经常遇到的运行某个程序的时候XX找不到的错误就是动态链接库需要的文件丢失后者没有在正确的路径上导致的。

参考文章：[http://www.cnblogs.com/52php/p/5681711.html](http://www.cnblogs.com/52php/p/5681711.html)


## 基本操作

### 字符串基本操作

```c
#include <string>

// 末尾添加一个字符
s.push_back('a');
// 末尾追加一个字符串
s.append("aaa");
// 任意位置插入字符

//任意位置插入字符串

//任意位置删除字符

//任意位置删除字符串

```

### 自定义set的比较函数

存入set的元素默认是有序的，但是默认的比较可能不能满足我们的要求，这个时候
就需要自定义比较的函数。 set的排序是使用红黑树的结构，插入删除和取出最小的
元素都比较高效。

```c
struct NumBit{
    int num;
    NumBit(int n) : num(n) {}
    bool operator<(const struct NumBit & right)const   //重载<运算符
    {
        vector<int> vtmp1;
        int n = this->num;
        int b = 0;
        while(n){
            b = n % 10;
            vtmp1.insert(vtmp1.begin(),b);
            n /= 10;
        }
        vector<int> vtmp2;
        int n2 = right.num;
        int b2 = 0;
        while(n2){
            b2 = n2 % 10;
            vtmp2.insert(vtmp2.begin(),b2);
            n2 /= 10;
        }
        int i = 0;
        int j = 0;
        int ilen = vtmp1.size();
        int jlen = vtmp2.size();
        while( i<ilen || j<jlen ){
            if(i<ilen && j<jlen && vtmp1[i] > vtmp2[j]){
                return false;
            }else if(i<ilen && j<jlen && vtmp1[i] < vtmp2[j]){
                return true;
            }else if(i<ilen && j<jlen && vtmp1[i] == vtmp2[j]){
                i++;
                j++;
            }else if(i==ilen){
                if(vtmp2[j] > vtmp2[0]) return true;
                else if(vtmp2[j] < vtmp2[0]) return false;
                else if(j == jlen){
                    return false;
                }else{
                    j++;
                }
            }else if(j==jlen){
                if(vtmp1[i] > vtmp1[0]) return false;
                else if(vtmp1[i] < vtmp1[0]) return  true;
                else if(i == ilen){
                    return true;
                }else{
                    i++;
                }
            }else{
                break;
            }
        }
        return false;
    }
};
```

使用的时候直接使用上面定义的结构体作为set的类型

```c
multiset<NumBit> s; //
```

### 输入输出重定向

有的算法题是从接收的是从控制台的输入，而且输入还很多，这个时候如果每次调试都从控制台一次一次的输入测试数据，就会很麻烦。我们可以把要输入的数据保存在一个文本文件中，然后使用输入重定向[`freopen`](http://www.cplusplus.com/reference/cstdio/freopen/)把标准输入重定向到该文件。以输入一个m行n列的矩阵来说，首先把输入数据存储在文本文件`d:/A.in`中。
```
4 4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
```
然后执行下面的代码：
```c
    freopen("d:\\A.in","r",stdin);// 输入重定向
    int m,n;
    cin>>m>>n;
    vector<vector<int>> v(m,vector<int>(n));
    //读取数据
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>v[i][j];
        }
    }
    //输出读取的数据门这里输出到控制台
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
```
同样，输出也可以重定向到文件，当有大量的输出或者需要保存输出结果的时候，重定向到文件是一个不错的方法。只需要在输出之前加上下面这段代码，输出就会重定向到文件，这个时候运行程序，控制台就看不到输出了。
```c
freopen("d:\\A.out","w",stdout);
```

### 格式化输入输出

C++定义了一些操纵符来控制输出流的状态，endl就是一个常用的操纵符。

**控制布尔值的格式**

`boolalpha`使得布尔值输出`true` or `false`;
`noboolalpha`使得输出变回默认的`0` or `1`.
```c
cout<<"default: "<<true<<" "<<false<<endl;
cout<<boolalpha<<"boolalpha: "<<true<<" "<<false<<noboolalpha<<endl;
```

**控制整数的输出进制**

- 八进制： `oct`
- 十六进制： `hex`
- 十进制： `dec`

**控制固定小数点位数**
```c
#include <iomanip>

cout.precision(6);
cout.setf(ios::fixed);

```

### 读取数量不定的若干个整数

```c
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
/**
 * 读取一行整数，返回数组
 * @param s
 * @return
 */
vector<int> getInt(string &s)
{
    getline(cin,s);
    istringstream iss(s);
    vector<int> v;
    int num;
    while(iss >> num){
        v.push_back(num);
    }
    return v;
}
```

### 数据的表示范围

以下内容来源于`C++ Premier 第五版`

**整型**

包括整数，字符型，和布尔类型；这类数据在计算机的内部都是以二进制位0和1直接保存的。

```c
// 获得整形类型的表示范围， climits
    cout<<"char: "<<CHAR_MIN<<" to "<<CHAR_MAX<<endl;
    cout<<"unsinged char: "<<0<<" to "<<UCHAR_MAX<<endl;
    cout<<"int8: "<<INT8_MIN<<" to "<<INT8_MAX<<endl;
    cout<<"unsinged int8: "<<0<<" to "<<UINT8_MAX<<endl;
    cout<<"int16: "<<INT16_MIN<<" to "<<INT16_MAX<<endl;
    cout<<"unsigned int16: "<<0<<" to "<<UINT16_MAX<<endl;
    cout<<"int32: "<<INT32_MIN<<" to "<<INT32_MAX<<endl;
    cout<<"unsigned int32: "<<0<<" to "<<UINT32_MAX<<endl;
    cout<<"int64: "<<INT64_MIN<<" to "<<INT64_MAX<<endl;
    cout<<"unsigned int64: "<<0<<" to "<<UINT64_MAX<<endl;
    cout<<endl;
```

**浮点型**

在计算机内部，这种类型是把保存数据的空间分成两部分，一部分存储小数部分，一部分存储指数部分，数的实际大小是通过计算得出来的。
浮点类型由四部分组成：
- sign : 符号，正 或 负
- base(radix) : 基数(2,8,10,16)
- significand : 尾数
- exponent ： 指数

浮点类型的大小可以通过包含[`cfloat`](http://www.cplusplus.com/reference/cfloat/)查看。

```c
//获得浮点类型的表示范围  cfloat
   cout<<"float range: "<<FLT_MIN<<" to "<<FLT_MAX<<endl;
   cout<<"float significand: "<<FLT_MANT_DIG<<endl;
   cout<<"float exponent: "<<FLT_MIN_EXP <<" to "<<FLT_MAX_EXP<<endl;

   cout<<"double range: "<<DBL_MIN<<" to "<<DBL_MAX<<endl;
   cout<<"double significant: "<<DBL_MANT_DIG <<endl;
   cout<<"double exponent: "<<DBL_MIN_EXP <<" to "<<DBL_MAX_EXP<<endl;

   cout<<"long double range: "<<LDBL_MIN<<" to "<<LDBL_MAX<<endl;
   cout<<"long double significant: "<<LDBL_MANT_DIG<<endl;
   cout<<"long double exponent"<<LDBL_MIN_EXP<<" to "<<LDBL_MAX_EXP<<endl;

   cout<<"base: "<<FLT_RADIX<<endl;
   cout<<endl;
```

**获得类型所占用的字节数目**

```c
// 获得类型在内存中占的字节数
    cout<<"bool: "<<sizeof(bool)<<endl;
    cout<<"char: "<<sizeof(char)<<endl;
    cout<<"short: "<<sizeof(short)<<endl;
    cout<<"int: "<<sizeof(int)<<endl;
    cout<<"long: "<<sizeof(long)<<endl;
    cout<<"long long : "<<sizeof(long long)<<endl;
    cout<<"float: "<<sizeof(float)<<endl;
    cout<<"long double: "<<sizeof(long double)<<endl;
    cout<<endl;
```

**类型的使用准则**

- 明确知道不可能为负，使用无符号数。
- 整数运算一般使用`int`, 需要大数的时候考虑`long long`.需要小整数的时候考虑`signed char` or `unsigned char`
- 浮点运算用`double`


### 暂停和计时

**暂停**

如果想要让程序暂停几秒继续执行，可以这样使用：

```c
# include <windows.h>
Sleep(2000);  // 暂停2s, 参数的单位是毫秒
```

**计算程序运行的时间**

有的时候可能要看某段程序运行需要多少时间，可以这样使用：

- 秒级计时

```c
#include <ctime>
auto start_time = time(nullptr);
//Sleep(3000);
// ... 代码块
auto end_time = time(nullptr);
cout<<end_time - start_time<<endl;
// 输出的是程序运行的秒数。
```

- 毫秒级计时

```c
// 获取毫秒级别的时间差
auto start_time = clock();
//Sleep(3000);
auto end_time = clock();
cout<<end_time - start_time<<endl;
```


## 数据结构

### 栈

### 队列

### 堆

定义小顶堆：`priority_queue<ListNode*,vector<ListNode*>,bigger> minHeap;`

堆中添加元素：`minHeap.push()`

堆顶元素: `minHeap.top() //不会删除堆顶元素` 

堆中删除元素：`minHeap.pop() //只删除，不返回`

堆是否为空：`minHeap.empty()`

**建立最大堆**

```c
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// v 是一个无序的数组
make_heap(v.begin(),v.end());
// 或者使用
make_heap(v.begin(),v.end(),less<int>());
```

**建立最小堆**

```c
make_heap(v.begin(),v.end(),greater<int>());
```

make_heap()方法的第三个参数其实可以传入一个函数的实例，表示你怎样比较两个元素。例如我们可以自己实现`less`方法。

```c
// 大根堆
bool mless(const int &a,const int &b){
    return a <= b;
}
make_heap(v.begin(),v.end(),mless);

//小根堆
bool mgreater(const int &a,const int &b){
    return a >= b;
}
make_heap(v.begin(),v.end(),mgreater);
```

当堆中存放的数据不是简单的数字，而是复杂的结构体或者类数据的时候，自定义比较函数就十分有用了，可以自定义依据类中哪个字段生成堆。


传入自定义的比较函数：

```c
struct bigger {
	bool operator()(ListNode* l1, ListNode* l2) {
		return l1->val > l2->val;
	}
};
```
```c
// 弹出大根堆的顶部元素，重排堆，注意这个时候顶部元素没有删除，放在了数组的最后
pop_heap(v.begin(),v.end(),less<int>())

// 弹出小根堆的顶部元素
pop_heap(v.begin(),v.end(),greater<int>())

// 把[v.begin(), v.end()-2] 作为大根堆，v.end()-1, 也就是最后一个元素作为插入元素插入到大根堆中，重新调整好顺序
push_heap(v.begin(),v.end(),less<int>())

// 插入小根堆
push_heap(v.begin(),v.end(),less<int>())
```

**优先队列**
`priority_queue<Type, Container, Functional>` 实现了优先队列的结构和相应的操作方法，可以用他来实现大根堆，小根堆，优先队列等数据结构。

**大根堆**

```c
priority_queue<int> q;
// 或者使用完整的声明形式
priority_queue<int,vector<int> less<int>()> q;

// 从无序数组建立大顶堆
vector<int> v = {5,4,10,14,7,9,3,2,8,30};
for (int i = 0; i < v.size(); ++i) {
    q.push(v[i]);
}

// 弹出最大元素
q.pop()
```

**小根堆**

```c
priority_queue<int, vector<int>, greater<int> > q;

// 从无序数组建立小顶堆
vector<int> v = {5,4,10,14,7,9,3,2,8,30};
for (int i = 0; i < v.size(); ++i) {
    q.push(v[i]);
}

// 弹出最大元素
q.pop()
```
### 哈希表

### 排序