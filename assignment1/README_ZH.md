# 作业 1：SimpleEnroll

截止时间：4月17日（星期五）深夜 11:59

## 配置 C++ 环境

请前往并按照 [作业环境配置](../assignment-setup/README_ZH.md) 中的说明，为此作业配置好 C++ 编译器和自动评分器（autograder）。

## 概述

又到了这个学期的时候了；是时候使用 SimpleEnroll 了 🤗 哇呼！
每个人在斯坦福的求学生涯中总会意识到一件事：他们最终必须毕业——因此选课就变成了一项策略性任务，既要最大化积累毕业所需经验值（XP），又要保证每晚能睡上 4 个小时以上！

在这个希望不会太长的作业中，我们将使用来自 ExploreCourses API 的数据，找出 ExploreCourses 上哪些 CS 课程在今年开课，哪些不开！我们将利用流（streams），同时练习 C++ 中的初始化和引用（references）。让我们开始吧 ʕ•́ᴥ•̀ʔっ

你只需要关注以下两个文件：

* `main.cpp`：你所有的代码都写在这里 😀！
* `utils.cpp`：包含一些工具函数。你会用到这个文件中定义的函数，但不需要对它进行修改。

## 运行你的代码

要运行你的代码，首先需要对其进行编译。打开终端（如果你使用的是 VSCode，请按 Ctrl+`或点击顶部的 **终端 > 新建终端**）。然后确保你位于`assignment1/` 目录下，并运行：

```sh
g++ -std=c++20 main.cpp -o main
```

假设你的代码编译成功且没有出现任何编译器错误，现在你可以运行：

```sh
./main
```

这会实际执行 `main.cpp` 中的 `main` 函数。它会运行你的代码，随后启动自动评分器以检查代码的正确性。

在按照下面的指示操作时，我们建议你间歇性地进行编译并使用自动评分器进行测试，以确保你一直处于正确的方向上！

> [!NOTE]
> ### Windows 注意事项
>
> 在 Windows 上，你可能需要使用以下命令编译代码才能看到输出：
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp -o main
> ```
>
> 此外，输出的可执行文件可能被称为 `main.exe`，在这种情况下，你需要使用以下命令运行代码：
>
> ```sh
> ./main.exe
> ```

## 第 0 部分：阅读代码并补全 `Course` 结构体

1. 在本次作业中，我们将使用 `Course` 结构体在 C++ 中表示从 ExploreCourses 获取的记录。请查看 `main.cpp` 中 `Course` 结构体的（未完成）定义并补全字段定义。最终，我们将使用流（streams）来生成 `Course` 结构体 —— 还记得流处理哪些类型吗？
2. 查看 `main.cpp` 中的 `main` 函数，并特别注意 `courses` 是如何传递给 `parse_csv`、`write_courses_offered` 和 `write_courses_not_offered` 的。思考一下这些函数在做什么。你需要修改函数定义中的某些内容吗？剧透一下：你需要。

## 第 1 部分：`parse_csv`

查看 `courses.csv`，这是一个 CSV 文件，包含三列：Title（课程名称）、Number of Units（学分数）和 Quarter（开课学期）。实现 `parse_csv`，使其对 csv 文件中的每一行，创建一个包含该行 Title、Number of Units 和 Quarter 的 `Course` 结构体。

你需要思考的几件事：

1. 你将如何读取 `courses.csv`？哼哼哼，或许用流（stream）😏？
2. 你将如何获取文件中的每一行？

### 提示

1. 查看我们在 `utils.cpp` 中提供的 `split` 函数。它可能会派上用场！

* 欢迎查看 `split` 的实现逻辑并向我们提出任何问题 —— 鉴于它使用的是 `stringstream`，你应当能够推导出它的工作原理。

2. 每**行**就是一条记录！*这很重要，所以我们再强调一遍 :>)*
3. 在 CSV 文件中（特别是 `courses.csv` 中），第一行通常是定义列名的行（列头行）。这一行实际上并不对应具体的 `Course`，因此你需要想办法跳过它！

## 第 2 部分：`write_courses_offered`

好了。现在你已经有一个填充完毕的 `courses` vector，其中整洁地将 `courses.csv` 文件中的所有记录存储为 `Course` 结构体！你发现自己只对开课的课程感兴趣，对吧？**如果一门课程的 Quarter 字段不是字符串 `"null"`，则该课程被视为开课。** 在这个函数中，将 Quarter 字段不为 `"null"` 的所有课程写入到 `"student_output/courses_offered.csv"` 中。

> [!IMPORTANT]
> 写入 CSV 文件时，请遵循以下格式：
>
> ```
> <Title>,<Number of Units>,<Quarter>
>
> ```
>
> 注意：逗号两侧**不能有空格**！如果不遵循此格式，自动评分器会报错！
> 此外，**务必将列头行写入**为输出的第一行。这与你在上一步处理 `courses.csv` 时必须跳过的行相同！

一旦调用了 `write_courses_offered`，我们期望所有开课的课程（即你写入输出文件的所有课程）都从 `all_courses` vector 中被移除。**这意味着该函数运行后，`all_courses` 应该只包含不开课的课程！**

实现这一点的一种方法是用另一个 vector 来追踪开课的课程，然后从 `all_courses` 中删除它们。就像在 Python 和许多其他语言中一样，在遍历数据结构的同时删除其中的元素是一个坏主意，因此你可能希望在将所有开课课程写入文件**之后**再进行此操作。

## 第 3 部分：`write_courses_not_offered`

所以你对不开课的课程感到好奇……在 `write_courses_not_offered` 函数中，将 `unlisted_courses` 中的课程写入到 `"student_output/courses_not_offered.csv"` 中。记住，由于你在上一步中删除了开课的课程，`unlisted_courses` 显然只包含不开课的课程 —— 算你幸运。因此，这一步看起来与第 2 部分非常相似，只是更短且更简单一点。

## 🚀 提交说明

编译并运行后，如果你的自动评分器显示如下：

那么你就完成了作业！哇呼！

提交作业步骤：

1. 请填写 [此链接中的反馈表单](https://forms.gle/UeD6zjmUpFbhGgw98)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交你的作业！

你需要提交的文件应为：

* `main.cpp`
