# mkdocs

使用mkdocs搭建个人博客系统，实现知识管理。
实现的功能：
1. 根据文件夹结构自动生成多级目录(每个文件一个标题，显示在左侧)
2. 根据文章内容自动生成文章目录(显示在右侧)
3. 忽略程序源代码文件(文件夹还是可以使用的vscode工程)
4. 自动导出所有md文件为一个PDF文档，带目录。
5. github托管源码， travis自动构建，在线编辑

## 安装

1. 安装python, pip
2. pip install mkdocs

## 使用

创建配置文件 mkdocs.yml

```shell
site_name: FEIFEI的个人博客
repo_name: FF1204/leetcode
repo_url: https://github.com/FF1204/leetcode
markdown_extensions:
  - markdown.extensions.admonition
  - pymdownx.tabbed
  - codehilite:
      guess_lang: false
      linenums: true
  - markdown.extensions.toc:
      permalink: true
theme: 
    name: material 
    language: zh
    palette:
        primary: teal
        accent: indigo
plugins:
  - search
  - add-number:
        strict_mode: False
        order: 1
        excludes:
            - sql/
            - command/rsync
        includes:
            - sql/MySQL
  - awesome-pages
  - mkpdfs
  - exclude
```

安装配置文件中提到的 material 主题，add-number，awesome-pages，mkpdfs， exclude插件

在该文件对应的目录中运行 mkdocs serve, 启动本地服务器，就可以在localhost:8000 看到网站效果。

## 自动部署

把 .travis.yml 添加到博客根目录，在travis网站上创建项目并关联github仓库。

```shell
dist: bionic
language: python
python:
-  3.7
install:
  - sudo apt-get install build-essential python3-dev python3-pip python3-setuptools python3-wheel python3-cffi libcairo2 libpango-1.0-0 libpangocairo-1.0-0 libgdk-pixbuf2.0-0 libffi-dev shared-mime-info
  - pip install mkdocs
  - pip install mkdocs-material
  - pip install mkdocs-awesome-pages-plugin
  # mkpdfs-mkdocs 存在BUG暂未修复，使用自己修复之后的版本
  #- pip3 install mkpdfs-mkdocs
  - pip install -e git+https://github.com/FF1204/mkpdfs-mkdocs-plugin.git#egg=mkpdfs-mkdocs-plugin
  - pip3 install mkdocs-add-number-plugin
script:
  - mkdocs build --clean
after_success:  |
  if [ -n "$GITHUB_API_KEY" ]; then
    cd "$TRAVIS_BUILD_DIR"
    cd site
    git init
    git add .
    git -c user.name=$GITHUB_NAME -c user.email=$GITHUB_EMAIL commit -m "Auto Deployment"
    git push -f -q https://$GITHUB_NAME:$GITHUB_API_KEY@github.com/FF1204/leetcode.git master:gh-pages
    cd "$TRAVIS_BUILD_DIR"
  fi
```

其中， `GITHUB_NAME`， `GITHUB_EMAIL`， `GITHUB_API_KEY`是在travis网站对应项目中填写的自己的gihub密钥。`TRAVIS_BUILD_DIR`是travis内置的变量，表示配置文件所在的路径。

## 为 table 增加查找和过滤功能

在 `mkdocs.yml` 文件中增加配置

```yml
theme: 
    name: material 
    language: zh
    custom_dir: theme
```

为主题自定自定义的目录， 该目录与 `docs` 同级。创建该目录， 并创建与主题 `material` 相同的目录层级结构。
新目录下的同名文件会自动覆盖掉原来主题中的同名文件，这样就可以实现在不改变原来主题的情况下DIY主题。

`theme` 文件夹结构

```yml
theme
    - assets
        - stylesheets # 放置额外的样式表
        - javascripts # 放置额外的 JS 库
        - images  # 放置额外的图片资源
    - main.html # 会覆盖原来主题中的 main.html
```

`main.html` 可以新增样式表，JS库和 JS 函数。

```html
{% extends "base.html" %}

{% block libs %}
	{{ super() }}
	<script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.4.1.min.js"></script>
	<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js"></script>
	<script src="https://unpkg.com/bootstrap-table@1.16.0/dist/bootstrap-table.min.js"></script>
	<script src="https://unpkg.com/bootstrap-table@1.16.0/dist/extensions/filter-control/bootstrap-table-filter-control.min.js"></script>
	<script src="https://unpkg.com/bootstrap-table@1.16.0/dist/extensions/multiple-sort/bootstrap-table-multiple-sort.js"></script>
{% endblock %}

{% block styles %}
	{{ super() }}
	<link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" rel="stylesheet">
	<link href="https://unpkg.com/bootstrap-table@1.16.0/dist/bootstrap-table.min.css" rel="stylesheet">
{% endblock %}

{% block scripts %}
	{{ super() }}
	<script>
		(function() {
			var table_element = $('div.table_filter_start').nextUntil('div.table_filter_end', 'table');
			table_element.attr('id', 'table_filter');
			table_element.attr('data-filter-control', 'false');
			table_element.attr('data-search', 'true');
			table_element.addClass('table-sm');
			
			var th_element = $('#table_filter thead th');
			var count = th_element.length;
			for (var i = 0; i < count; i++) {
				var th = $("#table_filter thead th:eq(" + i + ")");
				th.attr('data-field','data' + i);
			}
			th_element.attr('data-filter-control', 'input');
			th_element.attr('data-sortable', 'true');
		  })();
	</script>
	<script>
	  $(function() {
		$('#table_filter').bootstrapTable()
	  })
	</script>
{% endblock%}
```

我们通过 libs 引入需要用到的 JS 库， 通过 styles 引入需要用到的样式表， 通过 scripts 定义要执行的 JS 函数，其中 `{{ super() }}` 的含义是继承父亲模板中原来就包含的东西。

我们通过 JS 脚本实现查找 `div.table_filter_start` 和 `div.table_filter_end` 包含的表格， 动态添加表格的属性使它支持搜索和排序。

在书写markdown的时候，如果我们想要给这个表格添加查找和排序的功能，只需要在首尾用 `div` 包裹起来就可以了。

```markdown
<div class="table_filter_start"></div>

| title1 | title2 | title3 |
| ------ | ------ | ------ |
| item1  | item2  | item3  |
| item4  | item5  | item6  |

<div class="table_filter_end"></div>
```