# 作业 6：探索课程 (Explore Courses)

**截止时间：5 月 22 日星期五 晚上 11:59**

## 概述 (Overview)

在本作业中，你将练习对 `std::optional` 的理解。我们将使用与作业 1 中相同的 `courses.csv` 文件。你的任务是为本作业编写一个函数，该函数尝试在 `CourseDatabase` 对象中查找一个 `Course` 并将其返回。
你还将探索 `std::optional` 类附带的单子操作（Monadic Operations）。请查看代码并复习 `CourseDatabase` 类以了解其接口。

## 运行你的代码 (Running your code)

要运行代码，首先需要对其进行编译。打开终端（如果使用的是 VSCode，请按 `Ctrl+ `，或点击顶部的 **Terminal > New Terminal**）。然后确保你处于 `assignment6/` 目录下，并运行：

```sh
g++ -std=c++23 main.cpp -o main
```

假设你的代码编译成功且没有任何编译器错误，现在可以运行：

```sh
./main
```

这将实际运行 `main.cpp` 中的 `main` 函数。

当你按照下面的说明进行操作时，我们建议你在过程中不定期使用 autograder 进行编译/测试，以确保你的思路正确！

> [!NOTE]
> ### Windows 系统注意事项
>
> 在 Windows 上，你可能需要使用以下命令来编译代码以便查看输出：
>
> ```sh
> g++ -static-libstdc++ -std=c++23 main.cpp -o main
> ```
>
> 此外，输出的可执行文件可能被称为 `main.exe`，在这种情况下，你需要运行：
>
> ```sh
> ./main.exe
> ```

## 第 0 部分：包含 `<optional>` 头文件 (Part 0: Include `<optional>`)

在 `main.cpp` 的顶部包含 `<optional>`，我们将在本次作业中使用 `std::optional`！

## 第 1 部分：编写 `find_course` 函数 (Part 1: Write the `find_course` function)

该函数接收一个字符串 `course_title`，函数应该尝试在 `CourseDatabase` 对象的私有成员 `courses` 中查找该课程（`course`）。返回类型应该是什么？（提示：传入的 `course_title` 可能存在对应的 `Course`，也可能不存在）

> [!NOTE]
> 你需要修改 `find_course` 返回的类型，该类型目前是 `FillMeIn`。

## 第 2 部分：修改 `main` 函数 (Part 2: Modifying the `main` function)

注意我们在 `main` 函数中调用了 `find_course`：

```cpp
auto course = db.find_course(argv[1]);
```

现在，你需要利用[单子操作 (monadic operations)](https://en.cppreference.com/w/cpp/utility/optional) 来正确填充 `output` 字符串。让我们一步步来看如何做到这一点。

以下是你想要重新实现的行为，**且不能使用任何条件语句（如 `if` 语句）**：

```cpp
if (course.has_value()) {
    std::cout << "Found course: " << course->title << ","
              << course->number_of_units << "," << course->quarter << "\n";
} else {
    std::cout << "Course not found.\n";
}
```

简单来说，如果找到了课程，那么 `main` 末尾的这一行：

```cpp
std::cout << output << std::end;
```

应该输出：

```bash
Found course: <title>,<number_of_units>,<quarter>
```

如果没有找到课程，那么：

```cpp
std::cout << output << std::end;
```

应该输出：

```bash
Course not found.
```

### 单子操作 (Monadic Operations)

单子操作主要有三个：[`and_then`](https://en.cppreference.com/w/cpp/utility/optional/and_then)、[`transform`](https://en.cppreference.com/w/cpp/utility/optional/transform) 和 [`or_else`](https://en.cppreference.com/w/cpp/utility/optional/or_else)。请阅读讲座 PPT 中对它们的描述，并查阅[标准库文档](https://en.cppreference.com/w/cpp/utility/optional)。你只需要使用其中 2 个单子操作。

你的代码最终应该看起来像这样：

```cpp
std::string output = course
    ./* 单子函数一 */ (/* ... */)
    ./* 单子函数二 */ (/* ... */)
    .value();                           // 或者 `.value_or(...)`，见下文
```

**思考 `output` 的类型是什么，并由此倒推**会有所帮助。请注意提示中描述的每个单子函数的作用。

> [!NOTE]
> 回顾一下每个单子函数的作用。C++ 官方标准库文档在这方面的解释不够直观，因此我们在下面提供了一个简短的参考说明。假设 `T` 和 `U` 是任意类型。
>
> ```cpp
> /** 
>  * 简而言之：
>  * 如果存在值，则调用一个函数来生成一个新的 optional；否则返回无值状态（nothing）。
>  *
>  * 传递给 `and_then` 的函数接收一个非 optional 的 `T` 类型实例，并返回一个 `std::optional<U>`。
>  * 如果 optional 包含值，`and_then` 会将该函数应用于其值并返回结果。
>  * 如果 optional 没有值（即为 `std::nullopt`），它将返回 `std::nullopt`。
>  */
> template <typename U>
> std::optional<U> std::optional<T>::and_then(std::function<std::optional<U>(T)> func);
>
> /**
>  * 简而言之：
>  * 如果存在值，则将函数应用于存储的值，并将结果包装在 optional 中返回；否则返回无值状态（nothing）。
>  *
>  * 传递给 `transform` 的函数接收一个非 optional 的 `T` 类型实例，并返回一个非 optional 的 `U` 类型实例。
>  * 如果 optional 包含值，`transform` 会将该函数应用于其值，并将结果包装在 `std::optional<U>` 中返回。
>  * 如果 optional 没有值（即为 `std::nullopt`），它将返回 `std::nullopt`。
>  */
> template <typename U>
> std::optional<U> std::optional<T>::transform(std::function<U(T)> func);
>
> /** 
>  * 简而言之：
>  * 如果 optional 本身包含值，则返回自身；否则调用一个函数来生成一个新的 optional。
>  *
>  * 与 `and_then` 相反。
>  * 传递给 `or_else` 的函数不接收任何参数，并返回一个 `std::optional<U>`。
>  * 如果 optional 包含值，`or_else` 会直接返回它。
>  * 如果 optional 没有值（即为 `std::nullopt`），`or_else` 会调用该函数并返回其结果。
>  */
> template <typename U>
> std::optional<U> std::optional<T>::or_else(std::function<std::optional<U>(T)> func);
>
> ```
>
> 例如，给定一个 `std::optional<T> opt` 对象，单子操作可以像这样被调用：
>
> ```cpp
> opt
>    .and_then([](T value) -> std::optional<U> { return /* ... */; })
>    .transform([](T value) -> U { return /* ... */; });
>    .or_else([]() -> std::optional<U> { return /* ... */; })
>
> ```
>
> 注意：Lambda 函数中的 `->` 记法是显式写出函数返回类型的一种方式！
> 请注意，由于每个方法都返回一个 `std::optional`，因此你可以将它们链式调用。如果你确定在调用链末尾 optional 一定包含值，可以调用 [`.value()`](https://en.cppreference.com/w/cpp/utility/optional/value) 来获取该值。否则，你可以调用 [`.value_or(fallback)`](https://en.cppreference.com/w/cpp/utility/optional/value_or) 来获取结果，或者在 optional 没有值时获取预设的备用值（`fallback`）。

## 🚀 提交说明 (Submission Instructions)

如果你通过了所有测试，就可以准备提交了！提交作业步骤如下：

1. 请通过[此链接](https://forms.gle/aGuFqLyhB18mNoPKA)填写反馈表单。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交你的作业！

你需要提交的文件应为：

* `main.cpp`

在截止日期之前，你可以根据需要多次重新提交。
