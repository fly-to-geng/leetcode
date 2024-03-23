# SouceInsight宏的使用

## 调用BeyondCompare

使用宏打开Beyond Compare比较文件

```c
macro DiffCurrentFile()
{
    buf = GetCurrentBuf(); // 获得当前文档的句柄
    curr_file_path = GetBufName(); // 获得当前文件的路径
    hprj = GetCurrentProj(); // 获取当前工程实例
    dprj = GetProjDir(); // 获取当前工程根目录

    // 截取工程文件夹名称
    dname = strmid(dprj, offset, strlen(dprj));
    // 替换工程文件夹名称为另外一个，然后拼接成完成文件路径，实现与其他工程中相同路径下相同文件比较
    tmp_buf = NewBuf('tmp')
    AppendBufLine(tmp_buf, cur_file_path);
    ReplaceInBuf(tmp_buf, "@dname@", "new_dir_name", 0,1,0,0,0,0);
    new_file_path = GetBufLine(tmp_buf, 0);

    // 拼接CMD命令
    cmd_line = "\"C:\Program Files\\Beyond Compare 4\\BCompare.exe\" @new_file_path@ @cur_file_path@"

    // 执行CMD命令
    RunCmdLine(cmd_line, Nil, 0);
}
```

## 集成clang-format

用 Python 写一个程序实现调用 clang-format.exe 格式化代码。

```python
# 读取输入，格式化之后输出
import os
import sys
import codecs

if __name__ == "__main__":
    if (len(sys.argv) <= 1):
        sys.exit()
    selected_file = sys.argv[1]
    # utf-8 --> gb2312 Windows上使用需要转换
    with codecs.open(selected_file, 'r', 'utf-8') as fd:
        content = fd.read()
    with codecs.open(selected_file, 'w', 'gb2312') as fd:
        fd.write(content)
    abs_path = os.path.abspath(__file__)
    cur_dir = os.path.dirname(abs_path)
    file = '"' + selected_file + '"'
    clang_path = os.path.join(cur_dir, "clang-format.exe")
    cmd_line = clang_path + "- style=file {0}".format(file)
    output = os.popen(cmd_line)
    outtext = output.read().strip("\n")
    print(outtext)
```

**Source Insight中的配置**
`tools --> Custom Commands --> Add`

    按照如下配置：
    Run: python clang-format.py %s
    Dir: clang-format.py的绝对路径
    Paste Output: OK
    Save File First: OK
    Wait Until Done: OK

`Menu --> Insert` 添加到菜单中

## 克隆工程

基于当前工程克隆一个新工程，仅工程名称不同

```c
function string_replace(string, a, b)
{
    hbuf = NewBuf("tmp");
    if (hbuf == hNil) {
        Msg("open file fail.");
        return;
    }
    AppendBufLine(hbuf, string);
    sel = SearchInBuf(hbuf, a, 0,0,1,0,0);
    part1 = strtrunc(string, sel.ichFisrt);
    part2 = strmid(string, sel.ichLim, strlen(string));

    new_string = cat(part1, b);
    new_string = cat(new_string, part2);
    closeBuf(hbuf);

    return new_string;
}

macro create_project()
{
    curr_proj = "xxxx";
    prj_name = ask("input new project name:");
    hprj = NewProj(prj_name);
    if (hprj == hNil) {
        Msg("create new project fail.");
        return;
    }

    folder_name = ask("input folder name:");
    curr_hprj = GetCurrentProj();
    curr_dir = GetProjDir();
    file_count = GetProjFileCount(curr_hprj);
    file_index = 0;
    while (file_index < file_count) {
        filename = GetProjFileName(curr_hprj, file_index);
        abs_path = cat(curr_dir, "\\");
        file_name = cat(abs_path, filename);
        file_name = string_repalce(file_name, curr_proj, folder_name);
        AddFileToProj(hprj, filename);
        file_index = file_index + 1;
    }

    SyncProj(hprj);
    CloseProj(hprj);
}
```

## 获得符号表

可以利用宏输出整个工程的函数， 函数声明， 全局变量等。

```c
function GetFileSymbol(file_path, hout)
{
    hbuf = OpenBuf(file_path);
    symbol_max = GetBufSymCount(hbuf);
    synbol_index = 0;
    while (symbol_index < symbol_max) {
        symbol_record = GetBufSymLocation(hbuf, symbol_index);
        symbol_index = symbol_index + 1;
        // 记录函数实现名称
        if (symbol_record.Type == "Function") {
            AppendBufLine(hout, file_path # "function:" # symbol_record.Symbol);
        }
        // 记录函数声明名称
        if (symbol_record.Type == "Function Prototype") {
            AppendBufLine(hout, file_path # "function Prototype:" # symbol_record.Symbol);
        }
        // 记录全局变量名称
        if (symbol_record.Type == "Variable") {
            AppendBufLine(hout, file_path # "Variable:" # symbol_record.Symbol);
        }
    }
}

macro GetProjSymbols()
{
    // 打开保存文件列表的文件，文件列表可以使用SourceInsight导出
    files = OpenBuf("d:\\out.csv");
    if (files == hNil) {
        return;
    }

    hout = NewBuf("d:\\out.csv");
    line_max = GetBufLine(files);
    index = 0;
    while (index < line_max) {
        file_path = GetBufLine(files, index);
        GetFileSymbol(file_path, hout);
        index = index + 1;
    }
    SaveBuf(hout);
}
```