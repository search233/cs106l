

<p align="center">
  <img src="docs/marriage_pact.png" alt="Marriage Pact Logo" />
</p>

# 作业 2：Marriage Pact（婚姻契约）

**截止时间：** 4 月 24 日星期五晚 11:59（美西时间）

## 概述

作业 2 快乐！这是一个非常短小精悍的练习，旨在帮您开始使用 STL（标准模板库）的容器和指针。

您需要关注的文件有：

* `main.cpp`：您所有的代码都写在这里 😀！
* `short_answer.txt`：简答题的回答写在这里 📝！

要下载此作业的初始代码（starter code），请参阅课程作业仓库中的 **[入门指南（Getting Started）](https://www.google.com/search?q=../README.md%23getting-started)** 说明。

## 运行您的代码

要运行代码，首先需要对其进行编译。打开终端（如果您使用的是 VSCode，请按 Ctrl+`或点击顶部的 **终端 > 新建终端**）。然后确保您处于`assignment2/` 目录下，并运行：

```sh
g++ -std=c++20 main.cpp -o main
```

假设您的代码在编译时没有出现任何编译器错误，现在您可以运行：

```sh
./main
```

这将会实际执行 `main.cpp` 中的 `main` 函数。

在您按照下文说明进行操作时，我们建议您间歇性地使用自动评分工具（autograder）进行编译和测试，以确保您处于正确的轨道上！

> [!NOTE]
> ### Windows 用户注意
>
> 在 Windows 系统上，您可能需要使用以下命令来编译代码以查看输出：
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp -o main
>
> ```
>
> 此外，编译生成的输出可执行文件可能叫 `main.exe`，这种情况下您需要用以下命令运行代码：
>
> ```sh
> ./main.exe
>
> ```

## Part 0：准备工作

欢迎来到 Marriage Pact！在开始之前，我们需要知道您的姓名。请将 `main.cpp` 顶部的常量 `kYourName` 从 `"STUDENT TODO"` 修改为您的全名（名和姓之间用空格分隔）。

## Part 1：获取所有申请者

今年您等了好几天才收到 Marriage Pact 发来的首字母匹配通知，它们终于送达了您的收件箱！今年他们实施了一条新规则：您的匹配对象**必须**与您拥有相同的首字母缩写才有资格。然而，即使和朋友们讨论了好几个小时，您依然不知道匹配对象可能会是谁！校园里有成千上万的学生，您不可能手动翻阅整个名册来起草潜在灵魂伴侣的名单。幸运的是，您正在修读 CS106L，并且您记得 C++ 有一种非常快速的方法来处理这些收集到的同类数据——容器！

我们包含了一个 `.txt` 文件（`students.txt`），里面有今年报名参加 Marriage Pact 的所有（虚构）学生。每一行包含一名学生的名（First Name）和姓（Last Name）。您首先需要编写 `get_applicants` 函数：

> [!IMPORTANT]
> ### `get_applicants`
>
> 从 `.txt` 文件中解析所有姓名并存入一个集合（set）中。名为 `filename` 的文件中包含的每一行都是单个申请者的姓名。在您的实现中，您可以根据喜好自由选择有序集合（`std::set`）或无序集合（`std::unordered_set`）！如果您选择使用无序集合，请修改相应的函数定义！

此外，请在 `short_answer.txt` 中回答以下简答题：

> [!IMPORTANT]
> ### `short_answer.txt`
>
> **Q1：** 选择使用有序集合还是无序集合由您决定。请用几句话说明两者之间的一些权衡（Tradeoffs）是什么？此外，请举出一个有效的哈希函数示例（课堂上未展示过的），该函数可用于为无序集合中的学生姓名计算哈希值。

> [!NOTE]
> 本作业中出现的所有姓名均为虚构。如有雷同，纯属巧合。

## Part 2：寻找匹配对象

出色的侦探工作！既然您已经缩小了潜在灵魂伴侣的名单，是时候将它付诸实践了。在经历了一天漫长的无伴奏合唱（acapella）和咨询社团会议后，您回到宿舍，从室友那里听说今晚在主方草坪（Main Quad）有一个 Marriage Pact 匹配者的联谊会！您找到真爱的绝佳机会迫在眉睫——只要您能从终极飞盘训练中脱身。您迅速决定在联谊会上面试所有与您首字母相同的每个人，并开始编写一个能自动为您生成排队顺序的函数。

在此部分，您将编写 `find_matches` 和 `get_match` 函数：

> [!IMPORTANT]
> ### `find_matches`
>
> 从集合 `students`（在前一部分中生成）中，提取所有与参数 `name` 拥有相同首字母缩写的姓名，并将**指向这些姓名的指针**放入一个新的 `std::queue` 中。
>
> * 如果您在如何遍历集合方面遇到困难，回顾 [周四关于迭代器和指针的课程讲义](https://office365stanford-my.sharepoint.com/:p:/g/personal/jtrb_stanford_edu/EbOKUV784rBHrO3JIhUSAUgBvuIGn5rSU8h3xbq-Q1JFfQ?e=BlZwa7) 可能会有所帮助。
> * 在本部分中，您需要熟悉 `std::queue` 的操作。可以查看 [cppreference 上的文档](https://en.cppreference.com/w/cpp/container/queue)。
> * 提示：定义一个计算某个学生姓名首字母缩写的辅助函数（helper function）可能会很有用。然后您可以使用该辅助函数将 `name` 的首字母缩写与 `students` 中每个姓名的首字母缩写进行比较。

接下来，请实现 `get_match` 函数来寻找您的“唯一真爱”：

> [!IMPORTANT]
> ### `get_match`
>
> 从包含所有可能匹配对象的队列中获取您的“唯一真爱”。您可以自行决定获取方式；选择某种从队列中获取一名学生的方法，理想情况下是经过一番考量的逻辑，而不是单纯调用一次 `pop()`，但也不必过于复杂！可以考虑随机值或其他选择方法。
> 如果您的首字母缩写在数据集中没有任何匹配项，请打印 `“NO MATCHES FOUND.”`（未找到匹配项）。祝您明年好运 😢

随后，请在 `short_answer.txt` 中回答以下问题：

> [!IMPORTANT]
> ### `short_answer.txt`
>
> **Q2：** 请注意，我们在队列中保存的是**指向姓名的指针**，而不是姓名本身。为什么在这个问题中这样处理可能更好？如果存储姓名的原始集合（set）离开了作用域，而这些指针又被引用了，会发生什么？

## 🚀 提交说明

提交作业步骤：

1. 请完成 [此链接中的反馈表单](https://forms.gle/Zv27LwmtCPz88Kg46)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交您的作业！

您需要交付的文件为：

* `main.cpp`
* `short_answer.txt`

在截止日期之前，您可以根据需要重新提交任意多次。
