# -*- coding: utf-8 -*-

import os
import json
import sys

"""
生成 leetcode 题目文件夹结构和题目描述

leetcode
    - [题目ID]
        - xxx.c         C语言题解
        - xxx.cpp       C++语言题解
        - xxx.py        Python题解
        - readme.md     题目描述和思路描述
"""

# https://leetcode.com/api/problems/all/
# 使用上述地址可以获得 json 格式的所有题目描述，复制到文件中

# 用来生成目录结构的json文件名称
leetcode_problems_file_path = 'leetcode_problems_zhCN.json'

# 生成的题目，每个题目一个文件夹
# readme.md 存放题目描述和解题思路
# xxx.c C语言题解
# xxx.cpp C++语言题解
# xxx.py Python语言题解
leetcode_problems_files_path = 'leetcode'


curr_file = os.path.abspath(__file__)
curr_folder = os.path.dirname(curr_file)
leetcode_problems_file = os.path.join(curr_folder, leetcode_problems_file_path)

parent_folder = os.path.dirname(curr_folder)
leetcode_problems_new_path = os.path.join(parent_folder, leetcode_problems_files_path)

# 从文件加载解析成结构化数据
fd = open(leetcode_problems_file, 'r')
problems_obj = json.load(fd)
fd.close()

num_total = problems_obj['num_total']

def create_file(path, name):
    """
    创建一个文件，如果已经存在则输出打印
    """
    abspath = os.path.join(path, name)
    if not os.path.exists(abspath):
        open(abspath, 'a').close()
    else:
        print("{0} is already exist.\n".format(abspath))
    return abspath

def write_content_readme(question_id, question_title, path):
    """
    在readme.md文件中写入标题并设置到leetcode的链接
    """
    fd = open(path, 'w')
    url = 'https://leetcode-cn.com/problems/' + question_title
    line = '# [' + question_title + '](' + url + ')\n'
    fd.write(line)
    fd.close()

for problem in problems_obj['stat_status_pairs']:
    paid_only = problem['paid_only']
    difficulty = problem['difficulty']['level']
    stat = problem['stat']
    question_id = stat['frontend_question_id']
    question_title = stat['question__title_slug']
    if not paid_only: # 先不生成需要付费的题目
        # 创建以题目id为名称的文件夹
        dirname = str(question_id)
        abspath = os.path.join(leetcode_problems_new_path, dirname)
        if not os.path.exists(abspath):
            os.mkdir(abspath)
        else:
            print("{0} already exist.\n".format(abspath))

        # 创建readme.md文件
        readme_file = 'readme.md'
        filepath = create_file(abspath, readme_file)
        write_content_readme(question_id, question_title, filepath)

        # 创建C语言题解文件
        c_file = dirname + '.c'
        create_file(abspath, c_file)

        # 创建C++语言题解文件
        cc_file = dirname + '.cpp'
        create_file(abspath, cc_file)

        # 创建python题解文件
        python_file = dirname + '.py'
        create_file(abspath, python_file)

end = 10