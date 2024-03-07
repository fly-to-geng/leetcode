# Python 语言基础知识

记录用 python 刷 leetcode 必须了解的特性，主要是数据结构的表示。

## 基础知识

### import

记录各种需要包含的库

```python
# 后置返回类型 List
from typing import List
```

### string

```python
import regex as re

string = "abcd"

string.ltrsip()
string.rstrip()
string.strip() # 去掉行首， 行尾， 行首和行尾的空格，可传入其他字符

# 查找替换

string.find("substring") # 返回第一次出现的位置 或者 -1
[m.start() for m in re.finditer("test", "test test test")] # 返回test所有出现的位置
[m.start() for m in re.finditer("(?=tt)", "tttttt")] # 返回所有出现的位置，重叠匹配
string.count("substring") # 出现的次数
string.replace("astring", "bstring") # a 替换成 b
string[:start+1] + new_string + string[end:] # [start, end]之间的字符串替换成new_string

# 分割拼接
string.split("seperator", count) # 按照seperator分割string, 最多分割count次
"seperator".join(list[str]) # 使用seperator拼接list中的每个str

# 大写小写
string.isupper()
string.islower()
string.upper()
string.lower()
stirng.title() # 首字母大写

# 输出拼接
"%s, %s" % (string1, string2)
"{0},{1}".format(string1, string2)
```

### list

```python
# create
list1 = []
list2 = [0] * n
list3 = [0 for i in range(n)]
list4 = [[0] *m for i in range(n)] # n行m列

# 插入删除
list1.append(element)
list1.extend(list2)
list1.insert(index, element)
element = list1.pop()
element = list1.pop(index)
del list1[index]
list1.remove(element)
new_list = list(set(a) - set(b)) # 删除a中在b中出现过的值

# 遍历
for elemnt in list1:
    print(element)
for i in range(len(list1)):
    print(list1[i])
for i, element in enumerate(list1):
    print(element)
for element in reversed(list1): # 倒序输出
    print(element)

# 以上遍历都不能修改值，如果需要修改，可以用下面的方法
i = 0
while i < len(list1):
    print(list1[i])
    i += 1
```

### dict

```python
# 创建
dic = {}
dic = {key1:value1, key2:value2}

# 增删改查
if key not in dic:
    dic[key] = value
if key in dic:
    del dic[key]
value = dic.pop(key, default_value)

# 遍历
for key in dic:
    print(key, dic[key])
for key, value in dic.iterms():
    print(key, value)
for key in dic.keys():
    print(key)
for value in dic.values():
    print(value)

# 有序字典
from collection import OrderedDict
odic = OrderedDict()
odic[key1] = 1
odic[key2] = 2
odic[key3] = 3

first_element = odic.popitem(last=False) # 得到key1
list(odic.items())[index] # 根据索引获取字典中的元素
```

### set

内部使用哈希表实现

```python
set1 = set([1,1,2,3])
set2 = {1,2,3}

set1.add(element)

set3 = set1.union(set2) # set1 + set2
set3 = set1.intersecton(set2) # set1 & set2
set3 = set1.difference(set2) # set1 - set2

set1.clear()
if key in set1:
    print(key)

# 固定大小的set
fix_set = frozenset([1,2,3])
```

### 除法运算

```python
c = int(a / b) # 实现与C语言一致的整数除法
```

### 路径操作

```python
os.path.isfile(path) # 是否是文件
os.path.isdir(path) # 是否是目录
os.path.basename(path) # 返回文件名
os.path.dirname(path) # 返回文件所在文件夹
os.path.abspath(__file__) # 返回当前文件绝对路径
os.path.exists(path) # 路径是否存在
os.path.join(path, dirname) # 拼接路径
os.path.splittext(path) # 分割成路径 + 文件扩展名
 
os.listdir(path) # 列出路径下文件和文件夹
os.chdir(path) # 改变当前工作目录位path
os.mkdir(path) # 新建路径，如果已经存在报错
os.remove(path) # 删除文件，path是文件夹会报错
os.removedirs(path) # 递归删除空目录，如果任意目录非空会报错
os.rmdir(path) # 删除path目录，如果path非空会报错
os.rename(olename, newname) # 重命名文件

# 遍历文件夹下所有文件进入子文件夹
# curdir:当前文件夹 dirs:当前文件夹下所有文件夹， files:当前文件夹下所有文件
# True: 从顶层开始输出 False: 从底层开始输出
file_list = []
for curdir, dirs, files in os.walk(root_path, True):
    for file in files:
        file_list.append(os.path.join(curdir, file))

# 获得最新生成的文件
lists = os.listdir(root_path)
lists.sort(key=lambda fn:os.path.getmtime(root_path+'/'+fn))
# lists[-1] 就是最新的文件

# 复制文件夹 src_path 复制到 dst_path
import shutil
if os.path.exist(dst_path):
    shutil.rmtree(dst_path)
os.mkdir(dst_path)
shutil.copytree(src_path)
```

### 中文编码

```python
# utf8 --> gb2312
import codecs
with open(file, 'r', 'utf-8') as fd:
    text = fd.read()
with open(file, 'w', 'gb2312') as fd:
    fd.write(text)

unicode(string).encode("gb2312")
u"中文".encode("gb2312") # 转换编码
```

### 输出

```python
# print不带换行
print(),

# 显示二进制
num = 0b1011
print(b(num))

# 带颜色的打印
print("\033[1;35m This color is pick.\033[0m")
```

### 调用系统shell

```python
import os

ret = os.system(cmd) # ret >> 8 == 0 说明执行成功， 不会再标准输出打印内容
output = os.popen(cmd) # 命令输出会返回到output和标准输出中

# 屏蔽执行的命令再标准输出中的输出
import subprocess
null_dev = open(os.devnull, 'w')
p = subprocess.Popen(cmd, stdout=null_dev, stderr=null_dev)
ret = subprocess.Popen.poll(p)
if ret == None: # 命令未执行完成
if ret == number: # 命令执行完
```

## 正则表达式

```python
import re

regex_pattern = ""
pattern = re.compile(regex_pattern)

matchObj = re.match(regex_pattern, string) # 从string第一个字符开始匹配，如果第一个字符就不匹配，返回None
matchObj2 = re.search(regex_pattern, string) # 从string中查找第一个匹配的模式，匹配到不继续向下查找
matchOnj3 = pattern.search(string, pos='', endpos='') # 从string的pos开始到endpos结束，查找匹配的模式一次
lists = re.findall(regex_pattern, string) # 从string中查找匹配的模式，返回所有匹配的选项为一个list
new_string = re.sub(regex_pattern, replace_pattern, string) # 正则查找替换，返回替换后的新串
(new_stirng, count) = re.subn(regex_pattern, replace_pattern, string) # 多返回一个替换次数

matchObj == None # 未匹配到
matchObj.group(n) #匹配到的内容, 默认是0，整个正则表达式匹配到的内容，如果大于0，就是正则表达式中n组匹配到的内容
matchObj.start(n), matchObj.end(n) # 第n组匹配的开始和结束索引

## 正则语法
(pattern) # 分组且捕获， 使用`\n`引用
(?:pattern) # 分组不捕获
(?P<name>pattern) # 分组捕获并命名，使用`\g<name>` 引用
(?=pattern) # 匹配后面满足pattern模式的，但是不消费(匹配到的内容里面没有pattern匹配到的部分)
(?!pattern) # 匹配后面不满足pattern模式的，不消费
(?<=pattern) # 匹配前面满足pattern模式的，不消费
(?<!pattern) # 匹配前面不满足pattern模式的，不消费
```

## 时间和日期

```python
import time
import datetime

now = datetime.datetime.now() # 当前时间
start = time.clock()
end = time.clock() # end - start 是经过的时间
```

## JSON

```python
import json

Obj = json.loads(json_text, object_paris_hook=OrderDict) # 文本转成结构
json_text = json.dumps(Obj)  # 结构转换成文本
```

## SQLITE

```python
import sqlite3
form sqlite3 import Error

conn = create_connection(db_file) # 从DB文件打开数据库
current = conn.cursor()
current.execute("select * from table_name")
rows = current.fetchall()  # 获得执行SQL语句的结果

```

## 数据结构

### 堆

#### heapq

```python
import heapq

heap = heapq.heapify([1,2,3,4,5,6]) # 创建堆
heapq.heappush(heap, element)
top = heapq.heappop(heap)
list1 = heapq.nlargest(k, heap, key=func) # 返回前K大
list2 = heapq.nsmallest(k, heap, key=func) # 返回前K小
```

#### queue

引入包： `from queue import PriorityQueue`

定义：`minHeap = PriorityQueue()  # 默认建立小顶堆`

判空: `minHeap.empty()`

添加元素：`minHeap.put((key,value))`
不能传入自定义的比较函数，但是可以传入元组，根据key的值建立小顶堆

堆顶元素：`minHeap.get()` 取得并删除，与C++中的top()不同

**注意**：传入元组的时候如果key相同, 会进一步比较value, 如果value是自定义类型而且没有定义比较函数，会报错，这里要特别注意。

大部分使用情况，可以通过传入元组`(key, data)`控制堆的排序方式， 如果不能满足要求，可以在自己定义的类型上定义比较函数。

## 常用库

### diff

```python
import difflib
# 获取string1, string2的相似度，1说明完全相同
deltas = difflib.SequenceMatcher(None, string1, string2).quick_ratio()

# 比较目录和文件
import filecmp
```

### 序列化

```python
import pickle

pickle.dump(Obj, file_path) # 结构存入文件
Obj = pickle.load(file_path) # 从文件恢复结构
```

### 输入

```python
# 处理输入选项
import getopt

# cli
import click
```

## Python 库

### numpy

```python
import numpy as np

a1 = np.array([1,2,3])
a2 = np.array([(1,2,3), (4,5,6)])
a3 = np.array([[1,2,3], [4,5,6]])

np.zeros((n, m, k)) # n 行 m 列 k 层
np.ones((n, m, k))
np.empty((n , m, k)) # 不初始化，使用内存原来的值

np.arrange([start, end, step]) # 创建范围[start, end], 步长是step的一维数组
np.linespace([start, end, count]) # 创建范围从[start, end], 总数量为count的一维数组
```

### pandas

可以理解为电子表格, 提供了类似SQL语句的强大操作能力。

```python
import pandas as pd

#Series 一维数据
s = pd.Series(data=5, index=['a', 'b', 'c']) # 创建一维带名字的数组 [5,5,5] 列名称为 a, b, c
s = pd.Series(data=[1,2,3], index = ['a', 'b', 'c']) #创建一维带名字的数组 [1, 2, 3] 列名称为 a, b, c
s = pd.Series({"a":1, "b":2, "c":3}) # key 作为列名称， 值作为列的值
s = pd.Series(data=dict, index=[]) # key 如果在index中，加入，如果不在，加入设置值为Nan

# DataFrame 二位数据
df = pd.DataFrame() # 空
df = read_csv(file, names=[]) # 从CSV文件创建， names为每一列的名称
df = DataFrame(data, index=[], columns=[]) # data是二维数据， index为行命名， columns为列命名

df['col_name'], df[['col1_name', 'col2_name']] # 选择某些列
df.loc['row_name'], df.iloc[row_index], df[row_begin_index : row_end_index], df[bool_vector] # 选择某些列

del df['row_name'], del df.loc['row_name'] # 删除某些行， 删除某些列

groups = df.groupby('col_name') # 按照列 col_name 分组
df.sort_values('col_name') # 按照某一列排序

rows_unique = pd.unique(df['col_name']) # 获得某列的所有可能取值
new_df = df[df['col_name'] == 'value'] # 过滤出列值为value的所有行

# 遍历每一行
for row_num, row_content in df.iterrows():
    print(row_num, row_content)

```

### graphviz

一个用来绘制 .dot 格式文件的Python包。

```python
# pip install graphviz
from graphviz import Graph, Digraph

# 支持的输出格式 pdf, svg, png
dot = Digraph(comment="desciption", filename='filename', format='pdf')
dot.attr('node', shape='box') # 为node设置形状
dot.attr(rankdir='LR', size='10,10') # 设置图形布局为从左到右，10X10

dot.node('name1', 'description1')
dot.node('name1', 'description1')
dot.node('name1', 'description1') # 设置节点名称

dot.edge('name1', 'name2') # 设置边

print(dot.source) # 输出生成的.dot格式文件
dot.view() # 查看生成的图片
```

## 发布Pyton库

Pypi 是一个发布的平台， 发布自己写的Python库之后，可以直接使用pip install name 安装，还可以在pypi的网站上找到自己的库的说明。

1. 注册账号并登陆

https://pypi.org

2. 准备文件

去任意一个已经发布的包的 github 包主页上， 把对应的文件拷贝下来修改成自己的内容。

setup.py， README.md， LICENSE 三者是必须的。

3. 打包
在 setup.py 同级下执行 `python setup.py bdist_wheel --universal`

4. 上传

`twine upload dist/*`, 输入用户名和密码之后上传成功。
可以打开给出的页面看看效果。

https://pypi.org/project/mkdocs-render-otherfile-plugin/

5. 安装验证

pip install package-name