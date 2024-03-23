# GDB调试技巧

vscode 中使用gdb 命令需要加 `-exec`, 不加默认打印变量的值， 无法执行GDB命令.

## 常用命令

### 设置断点

运行到具体位置的时候停住。

- `break filename:line_number`
- `break filename:function_name`
- `break xxxxx if xxxx` : 条件断点
- `info break` : 显示断点

### 设置观察点

当某个变量的值发生变化的时候停住。

- `watch expr` : 一旦发生变化
- `rwatch expr` : 一旦被读取
- `awatch expr` : 一旦被读取或者写入
- `info watchpoints` : 显示观察点

### 查看变量

- `p var_name`
- `p *arr@arr_len`
- `info args` : 显示函数参数值
- `info locals` : 显示函数中局部变量的值

### 查看内存

- `bt(backtrace)` : 打印函数调用栈
- `info f(frame)` : 显示当前处于哪层函数，默认最顶层
- `up` : 向上移动一层
- `down` : 向下移动一层
- `frame n` : 切换到n层

### 查看源码

- `l(list)` : 列出当前行后面的代码
- `list -` : 显示当前行前面的代码
- `list line_number` : 显示 line_number 附近的代码
- `list line_begin,line_end`
- `list function_name`
- `list filename:function_name`
- `search <regexp>` : 显示后面匹配正则表达式的代码
- `forward search <regexp>` : 显示前面匹配正则表达式的代码

### 控制执行流程

- `si(stepi)` : 单步执行(汇编代码)
- `ni(nexti)` : 单步执行(汇编代码)
- `step` : 进入到函数内部
- `n(next)` : 执行一行，不进入函数
- `u(until)` : 执行完循环体
- `finish` : 执行完本函数
- `c(continue)` : 继续执行
- `r(run)` : 重新运行程序

### 其他

GDB 打印多维数组不易， 可以自己写打印函数，然后在调试的时候调用函数。

- `call function_name(para1, para2)` : 调用函数
- `shell <command>` : 执行 shell 命令