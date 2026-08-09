

<p align="center">
  <img src="docs/art.png" />
</p>

# 作业 7：独占指针 (Unique Pointer)

**截止时间：5 月 31 日星期日 晚上 11:59**

## 概述 (Overview)

在本作业中，你将实现一个自定义版本的 `unique_ptr`，以便亲身体验本周课堂上介绍的 RAII（资源获取即初始化）和智能指针等概念。此外，你还将练习我们在整个课程中学到的一些技能：模板、运算符重载和移动语义。

本次作业涉及三个文件：

* `unique_ptr.h` - 包含 `unique_ptr` 实现的所有代码。
* `main.cpp` - 包含一些使用你的 `unique_ptr` 的代码。你需要在其中编写一个函数！
* `short_answer.txt` - 包含几个简答题，你需要边完成作业边回答。

## 第 1 部分：实现 `unique_ptr` (Part 1: Implementing `unique_ptr`)

在作业的第一部分，你将实现周四课堂上讨论的一种智能指针：`unique_ptr`。你将实现的 `unique_ptr` 是标准库 [`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr) 的简化版本。回想一下，`unique_ptr` 表示指向动态分配内存的指针，该内存由单个（*独占的*）变量拥有。当该变量离开作用域时，它会自动通过调用 `delete` 来清理其拥有的已分配内存。这种行为被称为 RAII（资源获取即初始化）。**在我们的作业需求中，你可以假设 `unique_ptr` 指向类型为 T 的单个元素。你不需要在任何时候调用 `delete[]` 或处理指向动态分配数组的指针。**

> [!IMPORTANT]
> ##### `short_answer.txt`
>
> **Q1：** 列出使用 RAII 管理内存而非手动调用 `new` 和 `delete` 的一到两个好处。

> [!NOTE]
> 虽然我们的 `unique_ptr` 不支持指向数组的指针，但如果需要的话，我们可以添加这种行为。例如，C++ 标准库的 `std::unique_ptr` 使用*模板特化*（template specialization）来为数组指针实现不同的行为。这种模板特化可能如下所示：
>
> ```cpp
> template <typename T>
> class unique_ptr<T[]>;
> ```
>
> 实际上，我们将拥有两个版本的 `unique_ptr`：一个用于单个元素，另一个用于元素数组。每个版本支持不同的操作；例如，数组版本提供了下标运算符（`operator[]`）来解引用数组中的元素，而单元素版本则没有。

### 实现 `unique_ptr` 的功能

快速浏览一下 `unique_ptr.h` 中提供的 `unique_ptr` 代码。我们已经提供了 `unique_ptr` 的基本接口：你将实现这个接口。请记住，`unique_ptr` 的外观和行为应该像普通指针一样，支持解引用（`operator*`）和成员访问（`operator->`）等操作。为了使我们的类具备完全的常数正确性（const-correctness），其中几个方法同时拥有 `const` 和非 `const` 版本。

你将通过实现以下要点来为 `unique_ptr` 实现基本的指针接口。这些任务中的每一项都应该相对简单，可以通过在 `unique_ptr.h` 中添加/修改 1-2 行代码来完成：

* `unique_ptr` 的 `private` 声明部分
* `unique_ptr(T* ptr)` （构造函数）
* `unique_ptr(std::nullptr_t)` （针对 `nullptr` 的构造函数）
* `T& operator*()`
* `const T& operator*() const`
* `T* operator->()`
* `const T* operator->() const`
* `operator bool() const`

### 实现 RAII

到目前为止，我们的 `unique_ptr` 的行为就像一个裸指针（raw pointer），但它实际上并不会执行任何自动内存管理，例如在 `unique_ptr` 变量离开作用域时释放内存。此外，我们的指针并不是*独占的*（unique）：可以不加限制地创建它的多个副本（全部指向同一块内存）。例如，假设我们的 `unique_ptr` 在离开作用域时能正确清理其数据，请考虑以下代码块：

```cpp
int main() 
{
  unique_ptr<int> ptr1 = make_unique<int>(5);

  // ptr1 指向 5（在堆上动态分配）

  {

    unique_ptr<int> ptr2 = ptr1; // 浅拷贝

  } // <-- ptr2 的数据在此处被释放

  std::cout << *ptr1 << std::endl;
  return 0;
}
```

由于 `ptr1` 和 `ptr2` 指向同一块内存，当 `ptr2` 离开作用域时，它会将 `ptr1` 的数据一并释放！结果，`*ptr1` 会导致未定义行为（undefined behaviour）。

另一方面，我们应该依然能够**移动**（move）一个 `unique_ptr`。回想一下，移动语义允许我们在不进行高昂拷贝的情况下接管对象的资源。移动独占指针是合法的，因为它保留了指针的独占性——在任何时间点，我们对底层内存依然只有一个指针。我们只是改变了谁（哪个变量）拥有该内存。

为了实现这些目标——自动释放内存、禁止拷贝以及移动语义——我们必须在 `unique_ptr` 类中实现一些特殊成员函数（SMF）。**具体来说，请实现以下 SMF：**

* `~unique_ptr()`：释放指针指向的内存
* `unique_ptr(const unique_ptr& other)`：拷贝独占指针。应当被删除（`= delete`）。
* `unique_ptr& operator=(const unique_ptr& other)`：拷贝赋值独占指针。应当被删除（`= delete`）。
* `unique_ptr(unique_ptr&& other)`：移动构造独占指针。
* `unique_ptr& operator=(unique_ptr&& other)`：移动赋值独占指针。

实现上述函数后，你应该可以通过**第 1 部分**的所有 autograder 测试。

> [!IMPORTANT]
> ##### `short_answer.txt`
>
> **Q2：** 当为 `unique_ptr` 实现移动语义时（例如在移动构造函数 `unique_ptr(unique_ptr&& other)` 中），在退出函数之前将 `other` 参数的底层指针设置为 `nullptr` 至关重要。请用你自己的话解释如果不这样做会产生什么问题。

## 第 2 部分：使用 `unique_ptr` (Part 2: Using `unique_ptr`)

现在我们已经实现了 `unique_ptr`，让我们来使用它吧！看一下 `main.cpp`。我们为你提供了一个单链表（`ListNode`）的完整实现，该实现利用 `unique_ptr` 来确保链表中的所有节点都能被正确释放。例如，以下代码会产生如下输出：

```cpp
int main()
{

  auto head = cs106l::make_unique<ListNode<int>>(1);
  head->next = cs106l::make_unique<ListNode<int>>(2);
  head->next->next = cs106l::make_unique<ListNode<int>>(3);

  // head 的内存结构：
  //
  // head -> (1) -> (2) -> (3) -> nullptr
  //
  //

} // <- `head` 在此处被析构！

// 输出：
// Constructing node with value '1'
// Constructing node with value '2'
// Constructing node with value '3'
// Destructing node with value '1'
// Destructing node with value '2'
// Destructing node with value '3'
```

注意，我们不需要调用任何 `delete`！`unique_ptr` 的 RAII 行为保证了链表中的所有内存都会被递归释放。当 `head` 离开作用域时，它会调用节点 `(1)` 的析构函数，后者会调用 `(2)` 的析构函数，进而调用 `(3)` 的析构函数。

> [!IMPORTANT]
> ##### `short_answer.txt`
>
> **Q3：** 这种通过 RAII 进行递归释放的方法对短链表效果很好，但对较长的链表可能会产生问题。为什么？提示：递归函数的调用栈（call stack）增长深度限制是多少？

**你的任务是实现 `create_list` 函数，将 `std::vector<T>` 转换为 `unique_ptr<ListNode<T>>`。** 向量（vector）中元素的顺序应该在链表中得以保留，对于空向量应返回 `nullptr`。实现方法有很多种；其中一种是反向构建链表（从尾部开始，向头部推进）。**注意，你必须使用 `cs106l` 命名空间下的 `cs106l::unique_ptr`，而不是 `std::unique_ptr`！** 以下是你在实现中应该遵循的算法步骤：

1. 初始化 `cs106l::unique_ptr<ListNode<T>> head = nullptr`。
2. **反向**遍历 `std::vector`。对于向量中的每个元素：

* 2a. 创建一个新的 `cs106l::unique_ptr<ListNode<T>> node`，其值为向量中的该元素。
* 2b. 将 `node->next` 设置为 `head`。
* 2c. 将 `head` 设置为 `node`。

3. 最后，返回 `head`。

> [!IMPORTANT]
> ##### `short_answer.txt`
>
> **Q4.** 在实现步骤 2b 和 2c 时，你可能会很难让编译器允许你将 `head` 赋值给（例如）`node->next`，因为编译器会抱怨没有拷贝赋值运算符。这完全正确，因为正如我们之前讨论的那样，`unique_ptr` 不能被拷贝！
> 为了获得我们想要的行为，我们必须强制编译器将 `head` **移动赋值**到 `node->next`，而不是拷贝赋值。回想移动语义讲座的内容，我们可以通过编写 `node->next = std::move(head)` 来实现这一点。
> 在这种情况下，`std::move` 做了什么？为什么在这里使用 `std::move` 和移动语义是安全的？

> [!NOTE]
> 在反向遍历向量时，尽量避免使用 `size_t` 作为循环索引。`size_t` 只能是非负整数，在检查 for 循环边界时尝试递减到零以下会导致未预期的行为（溢出）。
> 要解决这个问题，请尝试改用 `int`。

一旦实现了 `create_list`，我们就可以创建链表并将其打印出来。为了加分（brownie points），可以看看 `map_list()` 和 `linked_list_example()` 函数，它们会共同调用你的 `create_list` 函数，并逐行打印出其中的元素。此时，你应该能通过**第 2 部分**的所有测试。

## 🚀 提交说明 (Submission Instructions)

如果你通过了所有测试，就可以准备提交了！提交作业步骤如下：

1. 请通过[此链接](https://forms.gle/uHr3J8Vm3gECkZpm9)填写反馈表单。
2. 在 [Paperless](https://paperless.stanford.edu) 上提交你的作业！

你需要提交的文件应为：

* `unique_ptr.h`
* `main.cpp`
* `short_answer.txt`

在截止日期之前，你可以根据需要多次重新提交。
