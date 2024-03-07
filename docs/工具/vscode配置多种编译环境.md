# VS Code 配置多种编译调试环境

VS Code 是使用语言服务器实现的编译调试，所以可以配置多种编译调试环境。
根据文件选择不同的编译调试命令，可以实现在一个编辑器中编写各种不同的语言，非常方便。

## Python 环境配置

`launch.json` 中添加如下配置

```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python: 当前文件",
            "type": "python",
            "request": "launch",
            "program": "${file}", // ${file} 是内置变量，解析成当前文件路径
            "console": "integratedTerminal"
        }
    ]
}
```

## C, C++ 环境配置

### Windows 下使用 WSL 编译和调试

`task.json` 中配置

```json
{
    "version": "2.0.0",
    "windows": {
        "options": {
            "shell": {
                "executable": "c:\\windows\\System32\\bash.exe",
                "args": ["-c"]
            }
        }
    },
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "-I",
                "/usr/include/c++/8",
                "-o",
                "/mnt/d/FF120/workspace/leetcode/tmp/${fileBasename}.out",
                "/mnt/d/FF120/workspace/leetcode/docs/leetcode/${fileBasenameNoExtension}/${fileBasename}"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": []
        }
    ]
}
```

`launch.json` 中配置

```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "GDB: 当前文件",
            "type": "cppdbg",
            "request": "launch",
            "program": "/mnt/d/FF120/workspace/leetcode/tmp/${fileBasename}.out",
            "args": ["-fThreading"],
            "stopAtEntry": true,
            "cwd": "/mnt/d/FF120/workspace/leetcode/",
            "environment": [],
            "externalConsole": true,
            "windows": {
                "MIMode": "gdb",
                "miDebuggerPath": "/usr/bin/gdb",
                "setupCommands": [
                    {
                        "description": "Enable pretty-printing for gdb",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": true
                    }
                ]
            },
            "pipeTransport": {
                "pipeCwd": "",
                "pipeProgram": "c:\\windows\\System32\\bash.exe",
                "pipeArgs": ["-c"],
                "debuggerPath": "/usr/bin/gdb"
            },
            "sourceFileMap": {
                "/mnt/d": "d://",
                "/usr": "C:\\Users\\FF120\\AppData\\Local\\Packages\\KaliLinux.54290C8133FEE_ey8k8hqnwqnmg\\LocalState\\rootfs\\usr\\"
            },
            "preLaunchTask" : "build"
        }
    ]
}
```

`c_cpp_properties.json` 中配置, 用来支持智能提示和跳转到头文件

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
}
```

### Windows下只运行client, WSL 下安装VS Code Server编译和调试

`task.json` 中配置

```json
{
    "version": "2.0.0",
    "tasks": [
      {
        "type": "shell",
        "label": "g++ build active file",
        "command": "/usr/bin/g++",
        "args": ["-g", "${file}", "-o", "${file}.o"],
        "options": {
          "cwd": "/usr/bin"
        },
        "problemMatcher": ["$gcc"],
        "group": {
          "kind": "build",
          "isDefault": true
        }
      }
    ]
}
```

`launch.json` 中配置

```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "g++ build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${file}.o",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
              {
                "description": "Enable pretty-printing for gdb",
                "text": "-enable-pretty-printing",
                "ignoreFailures": true
              }
            ],
            "preLaunchTask": "g++ build active file",
            "miDebuggerPath": "/usr/bin/gdb"
          }
    ]
}
```

`c_cpp_properties.json` 中配置

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
}
```
