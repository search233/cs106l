<p align="center">
  <img src="docs/logo.jpeg" alt="A logo of Treebook, a fictional Stanford-based social media startup" style="width: 300px; height: auto;" />
</p>

# 作业 5：Treebook

**截止时间：5月15日（星期五）晚上 11:59（美西时间）**

## 概述

斯坦福最新的社交媒体初创公司是 Treebook，而你是团队的创始成员之一！为了让产品顺利上线并与某款未具名、法律上完全无关的哈佛应用展开竞争，你被分配了实现用户个人资料（User Profiles）的任务。

在本次作业中，你将实现一个类的一部分，以支持运算符重载（Operator Overloads），并修改特殊成员函数（Special Member Functions）的一些行为。

本次作业你将使用两个文件：

* `user.h` - 包含 `User` 类的声明，你将使用特殊成员函数和运算符扩展该类。
* `user.cpp` - 包含 `User` 类的定义。

要下载本次作业的初始代码（Starter code），请参阅课程作业仓库中的 **[入门指南（Getting Started）](https://www.google.com/search?q=../README.md%23getting-started)** 说明。

## 运行你的代码

要运行代码，首先需要对其进行编译。打开终端（如果你使用的是 VSCode，请按 Ctrl+`</kbd> 或点击顶部的 **终端 > 新建终端 / Terminal > New Terminal**）。然后确保你处于 `assign5/` 目录下，并运行：

```sh
g++ -std=c++20 main.cpp user.cpp -o main
```

假设你的代码编译成功且没有任何编译器错误，现在你可以执行：

```sh
./main
```

这将实际运行 `main.cpp` 中的 `main` 函数。

当你按照下面的说明进行操作时，我们建议你间歇性地使用自动评分器（Autograder）进行编译/测试，以确保你处于正确的轨道上！

> [!NOTE]
> ### Windows 系统注意事项
>
> 在 Windows 上，你可能需要使用以下命令来编译代码，才能看到输出：
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp user.cpp -o main
> ```
>
> 此外，输出的可执行文件可能被称为 `main.exe`，在这种情况下，你需要通过以下命令运行代码：
>
> ```sh
> ./main.exe
> ```

## 第一部分：查看个人资料 (Viewing Profiles)

看一眼 `user.h` 头文件。你的同事们已经开始编写一个 `User` 类，用于存储加入社交媒体平台的每个用户的姓名和好友列表！为了保持该类的高效性，他们选择将好友列表表示为 `std::string` 的原始指针数组（raw pointer array）（类似于 `std::vector` 在后台存储元素的方式）。值得庆幸的是，他们已经编写了创建新 `User` 以及向现有 `User` 的好友列表添加好友（`add_friend`）的逻辑，但在使用 `User` 对象时，他们开始遇到一些奇怪的问题。

首先，没有简单的方法将每个 `User` 对象的信息打印到控制台，这使得 Treebook 的调试变得很困难。为了帮助你的同事，请编写一个 `operator<<` 方法，将 `User` 打印到 `std::ostream`。**该运算符应在 `user.h` 中声明为友元函数（friend function），并在 `user.cpp` 中实现。** 例如，名为 `"Alice"` 的用户，其好友为 `"Bob"` 和 `"Charlie"`，在打印到控制台时应得到以下输出：

```
User(name=Alice, friends=[Bob, Charlie])
```

注意：`operator<<` 不应打印任何换行符。

> [!IMPORTANT]
> 在 `operator<<` 的实现中，你需要访问并遍历 `User` 类的 `_friends` 私有字段，以便打印出用户的好友。通常情况下，你无法在非成员函数中访问类内部的私有字段——在这种情况下，我们可以通过将 `operator<<` 标记为 **`User` 类内部的友元函数（friend function）** 来绕过这一限制。详情请参阅周二讲座的幻灯片！

## 第二部分：不友好的行为 (Unfriendly Behaviour)

在你编写的 `operator<<` 的帮助下，你的同事们在社交媒体应用上取得了良好的进展。然而，当他们尝试在内存中复制 `User` 对象时，遇到了一些看似诡异的问题，难以理解。由于你最近刚修过 CS106L，你怀疑这可能与 `User` 类上的特殊成员函数（或缺乏特殊成员函数）有关。为了解决这个问题，我们将实现我们自己版本的 `User` 类特殊成员函数（SMFs），并删除编译器生成的版本不足以应对的某些函数。

具体来说，你需要：

1. 为 `User` 类实现析构函数（Destructor）。为此，请实现 `~User()` 特殊成员函数。
2. 使 `User` 类支持拷贝构造（Copy constructible）。为此，请实现 `User(const User& user)` 特殊成员函数。
3. 使 `User` 类支持拷贝赋值（Copy assignable）。为此，请实现 `User& operator=(const User& user)` 特殊成员函数。
4. 防止 `User` 类被移动构造（Move constructed）。为此，请删除 `User(User&& user)` 特殊成员函数（即使用 `= delete`）。
5. 防止 `User` 类被移动赋值（Move assigned）。为此，请删除 `User& operator=(User&& user)` 特殊成员函数（即使用 `= delete`）。

在完成这些任务时，你需要在 **`user.h` 和 `user.cpp` **两个文件中都做出修改。

> [!IMPORTANT]
> 在实现上述第 2 点和第 3 点时，你需要复制 `_friends` 数组的内容。回想周四关于特殊成员函数的讲座：你可以通过先为新数组分配内存（可以在成员初始化列表中完成），然后使用 for 循环复制元素来完成指针数组的深拷贝。
> 确保你同时也设置了正在修改的实例的 `_size`、`_capacity` 和 `_name`！

## 第三部分：时刻保持加好友 (Always Be Friending)

在对特殊成员函数做出修改后，你已经成功将 Treebook 推广到了整个斯坦福，并且口碑开始在其他大学传播！然而，你和你的同事发现，鉴于目前类的编写方式，`User` 类的一些常见用例要么不方便，要么根本不可能实现，你认为可以通过实现一些自定义运算符来解决这个问题。

你将为 `User` 类重载两个运算符。**请将这两个运算符都实现为成员函数**（即在 `user.h` 中的 `User` 类内部声明它们，并在 `user.cpp` 中提供实现）。

### `operator+=`

`+=` 运算符将代表将一个用户添加到另一个用户的好友列表中。这应该是对称的（symmetric），这意味着将 Charlie 添加到 Alice 的好友列表中，也应该导致 Alice 同时出现在 Charlie 的列表中。例如，考虑以下代码：

```cpp
User alice("Alice");
User charlie("Charlie");

alice += charlie;
std::cout << alice << std::endl;
std::cout << charlie << std::endl;

// 预期输出：
// User(name=Alice, friends=[Charlie])
// User(name=Charlie, friends=[Alice])

```

该运算符的函数签名应为 `User& operator+=(User& rhs)`。请注意，与拷贝赋值运算符一样，它会返回对自身的引用。

### `operator<`

回想一下，在 `std::set` 中存储用户需要 `<` 运算符，因为 `std::set` 是基于比较运算符来实现的。请实现 `operator<`，按姓名的字母顺序（alphabetically）比较用户。例如：

```cpp
User alice("Alice");
User charlie("Charlie");

if (alice < charlie)
  std::cout << "Alice is less than Charlie";
else
  std::cout << "Charlie is less than Alice";

// 预期输出：
// Alice is less than Charlie

```

该运算符的函数签名应为 `bool operator<(const User& rhs) const`。

## 🚀 提交说明 (Submission Instructions)

如果你通过了所有测试，就可以准备提交了！提交作业的步骤如下：

1. 请填写 [此链接](https://forms.gle/tfLJSKnuUbUx9Xdi6) 中的反馈表单。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交你的作业！

你需要提交交付的文件应为：

* `user.h`
* `user.cpp`

在截止日期之前，你可以根据需要重新提交任意多次。
