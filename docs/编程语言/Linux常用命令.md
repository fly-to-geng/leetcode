# Linux 常用命令

## grep

```shell
grep regex filename/dirname # 显示正则匹配到的行
grep -i regex filename/dirname # 忽略大小写
grep -v regex filename/dirname # 显示正则没有匹配到的行
grep -n regex filename/dirname # 显示行号
grep -r regex filename/dirname # 递归查找子文件夹
grep -lr regex filename/dirname # 只显示匹配内容的文件
grep -Lr regex filename/dirname # 只显示没有匹配内容的文件
```

## find

```shell
find dirname -name filename # 搜索文件
```

## sed

```shell
# sed 命令格式
sed [option] '{script}' input_file > output_file # 修改输出到新的文件
sed -i [option] '{script}' input_file # 直接在原文件修改

# 删除
sed 'line_begin,line_end d' filename # 删除指定范围的行
sed '/regex/ d' filename # 删除正则匹配到的行
sed '/regex1/, /regex2/ d' filename # 删除正则1匹配开头 到 正则2匹配结尾 范围内的行

# 查找替换
sed 's/regex1/regex2' filename # regex1查找， 替换成regex2， 只替换第一个找到的
sed `s/regex1/regex2/number` filename # 替换第 number 次出现的实例
sed `s/regex1/regex2/g` filename # 替换所有匹配到的
sed `s/regex1/regex2/p` filename # 打印原始行的内容
sed `s/regex1/regex2/w file` filename # 将替换的结果写入文件
```

## 混合

grep 只能查找， sed只能替换， 综合使用可以实现批量查找替换。

```shell
# 批量替换某个文件夹下的所有文件里面的字符串
sed -i 's/oldstring/newstring/g' `grep oldstring -rl dirname`
```