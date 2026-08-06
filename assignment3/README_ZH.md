<p align="center">
  <img src="docs/bjarne.jpg" alt="Bjarne Stroustrup writing the declaration of a class on a whiteboard" />
</p>

# 作业 3：创建一个类（Make a Class）

**截止时间：** 5 月 1 日星期五晚 11:59（美西时间）

## 概述

既然我们已经学习了关于类（Class）的知识，是时候由您自己动手来创建一个了！好好享受这个过程，尽情挥洒您的创意吧。您的类可以代表任何事物，如果您愿意，也可以创建多个类。不过这里有一些要求。只要您满足这些要求，就能获得本次作业的满分！🙂

本次作业涉及四个文件：

* `class.h` - 这是您的类的头文件，类的声明（declaration）将写在这里。
* `class.cpp` - 这是您的类的源文件，类的定义/实现（definition）将写在这里。
* `sandbox.cpp` - 您将在其中构造您的类的一个实例（对象）。
* `short_answer.txt` - 您将在其中回答几个简答题。

要下载此作业的初始代码（starter code），请参阅课程作业仓库中的 **[入门指南（Getting Started）](https://www.google.com/search?q=../README.md%23getting-started)** 说明。

## 运行您的代码

要运行代码，首先需要对其进行编译。打开终端（如果您使用的是 VSCode，请按 Ctrl+`或点击顶部的 **终端 > 新建终端**）。然后确保您处于`assignment3/` 目录下，并运行：

```sh
g++ -std=c++20 main.cpp class.cpp -o main
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
> g++ -static-libstdc++ -std=c++20 main.cpp class.cpp -o main
> ```
>
> 此外，编译生成的输出可执行文件可能叫 `main.exe`，这种情况下您需要用以下命令运行代码：
>
> ```sh
> ./main.exe
> ```

## Part 1：创建您的类

尽情挥洒您的创意吧！填写 `class.h` 和 `class.cpp` 来创建您自己的自定义类。更多信息请参考周二关于类的课程讲义。您的类几乎可以代表任何您想要的东西，只要它满足以下要求即可。

> [!IMPORTANT]
> ### 类的要求
>
> 您的类必须：
>
> 1. 拥有一个接收**一个或多个**参数的自定义构造函数。
> 2. 拥有一个默认（无参数）构造函数（即实现构造函数重载）。
> 3. 拥有一个或多个私有（private）成员字段（即变量）。
> 4. 拥有一个或多个私有（private）成员函数。
>
> * 请记住，私有函数就像是汽车引擎盖下发生的事情！它们是类实现中不可或缺的一部分，但不应该暴露在公共接口（public interface）中。尝试思考一个在您的类语境下逻辑合理的私有成员函数。
>
> 5. 拥有**至少一个**针对某个私有字段的公有 Getter（获取器）函数。
>
> * 例如：如果私有字段是 `int data`，您必须有一个名为 `get_data` 或 `getData` 的函数，其函数签名如下：int getData();
> * 该 Getter 函数还应当被标记为 `const`。如果您对此不熟悉，请参考周四关于 `const` 正确性（const correctness）的讲义！
>
> 6. 拥有至少一个针对某个私有字段的公有 Setter（设置器）函数。
>
> * 例如：如果私有字段是 `int data`，您必须有一个名为 `set_data` 或 `setData` 的函数，其函数签名如下：void setData(int value);

请注意，这只是获得作业学分的最低要求。如果您想获得额外的练习，欢迎超出这些要求或创建多个类！

> [!NOTE]
> 想要获得加分（brownie points）的话，您可以选择使用周四讲义中讨论的 `template <typename T>` 语法来创建一个类模板（class template），而不是普通类。这完全是可选的！
> 请注意，如果您决定创建一个类模板，您**必须从编译命令中移除 class.cpp。** 例如，在 Mac/Linux 上，编译命令将变为：
>
> ```sh
> g++ -std=c++20 main.cpp -o main
>
> ```
>
> 同时请记住交换包含关系（include），正如周四讲义中所讨论的那样，让 `.h` 文件在文件末尾包含 `.cpp` 文件。

现在您已经创建好了自己的类，让我们实际使用它。**在 `sandbox.cpp` 的 `sandbox` 函数内部，构造您的类的实例！** 您可以以任何喜欢的方式构造它（调用默认构造函数、使用统一初始化等）。

要查看您是否正确完成了一切，请编译并运行您的代码！自动评分工具（autograder）将为您的类提供反馈，并检查它是否满足上述规范。

## Part 2：简答题

请在 `short_answer.txt` 中回答以下问题。我们期望每个问题回答 2-3 句话左右。

> [!IMPORTANT]
> `short_answer.txt`
>
> * **Q1：** 什么是 const-correctness（const 正确性）？为什么它很重要？
> * **Q2：** 您的类做到 const-correct 了吗？您是如何知道的？

## 🚀 提交说明

提交作业步骤：

1. 请完成 [此链接中的反馈表单](https://forms.gle/GmhzW9NycQ44hyF86)。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交您的作业！

您需要交付的文件为：

* `class.h`
* `class.cpp`
* `sandbox.cpp`
* `short_answer.txt`

在截止日期之前，您可以根据需要重新提交任意多次。
