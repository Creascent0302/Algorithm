## 哈希表C++使用方法

`std::unordered_map` 是 C++ 标准库中提供的哈希表实现。它以键值对（key-value pair）的形式存储元素，并允许根据“键”快速检索到对应的“值”。其核心优势在于平均情况下，插入、删除和查找操作的时间复杂度都是常数时间 O(1)。

### 1. 如何引入和定义 `std::unordered_map`

要使用哈希表，你首先需要包含相应的头文件 `<unordered_map>`。

**定义语法：**
```cpp
#include <unordered_map>
#include <string>
#include <iostream>

// 定义一个键为 std::string 类型，值为 int 类型的哈希表
std::unordered_map<std::string, int> myHashMap;
```

-   **`Key`**: 键的类型（例如 `std::string`, `int`, `double` 等）。
-   **`T`**: 值的类型（可以是任何 C++ 类型）。

### 2. 基本操作

下面是 `std::unordered_map` 的一些最核心和常用的操作。

#### a. 插入和更新元素

有多种方式可以向哈希表中添加或更新数据。

```cpp
std::unordered_map<std::string, int> word_counts;

// 1. 使用 [] 操作符 (最常用)
// 如果键"apple"不存在，则创建它并赋值为 3。
// 如果键"apple"已存在，则将其值更新为 3。
word_counts["apple"] = 3;
word_counts["banana"] = 5;

// 2. 使用 insert() 方法
// insert() 返回一个 std::pair，包含一个迭代器和一个bool值。
// 如果插入成功，bool值为true；如果键已存在，则插入失败，bool值为false。
word_counts.insert({"cherry", 10});
word_counts.insert(std::make_pair("apple", 1)); // 这次插入会失败，因为"apple"已经存在

// 3. 使用 emplace() 方法 (C++11, 更高效)
// emplace原地构造元素，避免了额外的拷贝或移动操作。
word_counts.emplace("durian", 7);
```

#### b. 访问元素

访问元素时，需要注意键是否存在。

```cpp
// 1. 使用 [] 操作符
// 如果键存在，返回其值的引用。
// 注意：如果键不存在，[] 会自动创建一个新元素，并进行默认初始化（例如int为0）！
std::cout << "Count of banana: " << word_counts["banana"] << std::endl; // 输出 5
std::cout << "Count of grape: " << word_counts["grape"] << std::endl;  // 输出 0，并且 "grape" 被添加到了哈希表中

// 2. 使用 at() 方法
// at() 会进行边界检查。如果键存在，返回其值的引用。
// 如果键不存在，它会抛出一个 std::out_of_range 异常。
try {
    std::cout << "Count of cherry: " << word_counts.at("cherry") << std::endl; // 输出 10
    std::cout << "Count of peach: " << word_counts.at("peach") << std::endl;  // 这一行会抛出异常
} catch (const std::out_of_range& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

#### c. 检查键是否存在

在访问前检查键是否存在是一个好习惯，可以避免 `[]` 操作符意外创建新元素。

```cpp
// 1. 使用 find() 方法 (最通用)
// find() 返回一个指向元素的迭代器。如果键不存在，它返回指向哈希表末尾的迭代器 (end())。
if (word_counts.find("durian") != word_counts.end()) {
    std::cout << "durian exists!" << std::endl;
} else {
    std::cout << "durian does not exist." << std::endl;
}

// 2. 使用 count() 方法
// 对于 unordered_map，键是唯一的，所以 count() 的返回值只会是 0 或 1。
if (word_counts.count("apple") > 0) {
    std::cout << "apple exists!" << std::endl;
}

// 3. 使用 contains() 方法 (C++20)
// 这是 C++20 引入的新方法，更直观。
if (word_counts.contains("banana")) {
    std::cout << "banana exists!" << std::endl;
}
```

#### d. 删除元素

可以使用 `erase()` 方法来删除一个元素。

```cpp
// 按键删除
size_t elements_erased = word_counts.erase("banana"); // 返回被删除的元素数量 (0或1)
std::cout << "Erased " << elements_erased << " element(s)." << std::endl;

// 按迭代器删除
auto it = word_counts.find("apple");
if (it != word_counts.end()) {
    word_counts.erase(it);
}
```

#### e. 遍历哈希表

最简单的方式是使用 C++11 引入的范围`for`循环。

```cpp
std::cout << "\nAll elements in the map:" << std::endl;
for (const auto& pair : word_counts) {
    std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
}
```
`pair.first` 是键（const），`pair.second` 是值。

---

### 3. 使用自定义类型作为键

当你想用自定义的 `struct` 或 `class` 作为哈希表的键时，情况会复杂一些。你需要告诉 `std::unordered_map` 两件事：
1.  **如何计算这个自定义类型的哈希值？**
2.  **如何判断两个自定义类型的对象是否相等？**

这需要你做两步：
1.  为你的自定义类型重载 `operator==`。
2.  提供一个哈希函数。通常做法是特化 `std::hash` 模板。

**示例：**
假设我们有一个 `Student` 结构体，我们想用它作为键来存储每个学生的分数。

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

// 1. 定义你的自定义类型
struct Student {
    std::string first_name;
    std::string last_name;

    // 2. 重载 operator==
    bool operator==(const Student& other) const {
        return first_name == other.first_name && last_name == other.last_name;
    }
};

// 3. 为 std::hash 提供一个特化版本，用于计算 Student 类型的哈希值
namespace std {
    template <> // 
    struct hash<Student> {
        size_t operator()(const Student& s) const {
            // 将多个字段的哈希值组合起来
            // 这是一个简单但有效的组合方法
            size_t h1 = std::hash<std::string>{}(s.first_name);
            size_t h2 = std::hash<std::string>{}(s.last_name);
            return h1 ^ (h2 << 1); // 组合哈希值
        }
    };
}

int main() {
    std::unordered_map<Student, double> student_scores;

    Student alice = {"Alice", "Smith"};
    Student bob = {"Bob", "Johnson"};

    student_scores[alice] = 95.5;
    student_scores.emplace(bob, 88.0);

    // 查找 Alice 的分数
    if (student_scores.count(alice)) {
        std::cout << "Score of " << alice.first_name << " " << alice.last_name
                  << ": " << student_scores.at(alice) << std::endl;
    }

    return 0;
}
```

---

### 4. 性能和 `std::map` 的对比

| 特性               | `std::unordered_map` (哈希表)                    | `std::map` (红黑树)                              |
| :----------------- | :----------------------------------------------- | :----------------------------------------------- |
| **平均时间复杂度** | 插入、删除、查找均为 **O(1)**                    | 插入、删除、查找均为 **O(log N)**                |
| **最坏时间复杂度** | 插入、删除、查找均为 **O(N)**                    | 插入、删除、查找均为 **O(log N)**                |
| **内部顺序**       | 无序。元素根据哈希值存储在不同的桶（bucket）中。 | 有序。元素根据键的排序规则（默认 `<`）自动排序。 |
| **作为键的要求**   | 需要提供哈希函数和等于(`==`)比较函数。           | 需要提供严格弱序比较（例如 `<` 操作符）。        |
| **内存使用**       | 通常比 `map` 更高，因为它需要维护哈希表结构。    | 相对较低。                                       |

**如何选择？**

-   如果你需要 **最快的平均查找速度**，并且 **不关心元素的顺序**，`std::unordered_map` 是最佳选择。
-   如果你需要 **元素保持有序**，或者需要查找一个键的 **前驱/后继**，或者担心哈希碰撞导致的最坏情况性能，那么 `std::map` 更合适。

`std::unordered_map` 的最坏情况性能（O(N)）发生于 **哈希碰撞**，即多个不同的键被哈希到了同一个位置。一个好的哈希函数可以极大地减少碰撞的概率。幸运的是，标准库为常用类型（如 `int`, `double`, `std::string` 等）提供的哈希函数都经过了很好的优化。


# 关于结构体特化问题
当然，我们来逐行深入地剖析这段代码。这块代码是 C++ 中一个非常重要且经典的高级技巧，用于让自定义类型能够被标准库中的哈希容器（如 `std::unordered_map` 或 `std::unordered_set`）使用。

### 总结：这段代码在做什么？

**一句话概括：它在教 C++ 如何为一个自定义的 `Student` 类型计算一个唯一的哈希值（一个整数）。**

`std::unordered_map` 内部通过哈希函数将一个“键”转换成一个整数，然后用这个整数作为数组的索引来快速定位数据。C++ 知道如何为 `int`, `double`, `std::string` 等内置和标准类型计算哈希值，但对于你自定义的 `struct Student`，它一无所知。这段代码就是我们为 `Student` 类型提供的“哈希计算说明书”。

---

### 详细代码分解

```cpp
// 1. 打开 std 命名空间
namespace std {

    // 2. 声明一个模板特化
    template <>

    // 3. 定义 std::hash 模板针对 Student 类型的特化版本
    struct hash<Student> {

        // 4. 实现一个 "函数调用操作符"
        size_t operator()(const Student& s) const {
            // 5. 获取第一个字段的哈希值
            size_t h1 = std::hash<std::string>{}(s.first_name);

            // 6. 获取第二个字段的哈希值
            size_t h2 = std::hash<std::string>{}(s.last_name);

            // 7. 组合并返回最终的哈希值
            return h1 ^ (h2 << 1);
        }
    };
}
```

#### 1. `namespace std { ... }`
- **目的**：将我们的代码“注入”到 C++ 的标准（`std`）命名空间中。
- **解释**：`std::hash` 是定义在 `std` 命名空间下的一个模板。为了给这个模板提供一个我们自己的特定版本（特化），我们必须进入到它的“家”——`std` 命名空间——中去定义。这是 C++ 中少数几个允许且推荐用户向 `std` 命名空间添加内容的场景之一。

#### 2. `template <>`
- **目的**：声明这是一个“模板特化”（Template Specialization）。
- **解释**：`std::hash` 本身是一个通用的模板：`template <class Key> struct hash;`。它是一个蓝图，而不是一个具体的类型。我们现在要做的不是创建一个新的蓝图，而是为这个蓝图提供一个针对特定类型 `Student` 的、具体的、定制化的实现。`template <>` 就表示：“嘿，编译器，接下来我要为一个模板提供一个完全特化的版本，而不是一个通用版本。”

#### 3. `struct hash<Student> { ... };`
- **目的**：定义这个特化版本。
- **解释**：这行代码告诉编译器，我们正在为 `std::hash` 这个模板，当它的模板参数是 `Student` 类型时，提供一个具体的结构体定义。所以，以后任何时候当 `std::unordered_map` 或其他代码需要 `std::hash<Student>` 时，编译器就会找到并使用我们在这里定义的这个版本。

#### 4. `size_t operator()(const Student& s) const`
- **目的**：让我们的 `hash<Student>` 结构体表现得像一个函数。这被称为**函数对象（Functor）**。
- **解释**：`std::unordered_map` 需要一个能接收 `Student` 对象并返回一个哈希值的东西。通过重载 `operator()`（函数调用操作符），我们可以让一个类的实例（对象）像函数一样被调用。
    - `size_t`: 这是哈希函数必须返回的类型，它是一个无符号整数，足以表示内存中任何对象的大小。
    - `operator()`: 这是被重载的操作符的名字。
    - `(const Student& s)`: 这是它的参数。它接收一个 `const` 的 `Student` 对象的引用。使用 `const` 是因为计算哈希值不应该改变对象本身；使用引用 `&` 是为了避免不必要的、昂贵的拷贝操作。
    - `const`: 这个 `const` 放在末尾，表示这个成员函数不会修改 `hash<Student>` 结构体自身的任何成员变量。这也是哈希函数必须遵守的约定。

#### 5. & 6. `std::hash<std::string>{}(s.first_name);`
- **目的**：递归地使用 `std::hash` 来计算 `Student` 内部成员的哈希值。
- **解释**：这行代码非常精妙。
    - `std::hash<std::string>`: 我们获取了标准库中已经为 `std::string` 类型定义好的哈希函数模板的特化版本。
    - `{}`: 这会创建一个该哈希类型的临时匿名对象（一个函数对象）。
    - `(s.first_name)`: 我们立即调用这个临时对象的 `operator()`，并把学生的 `first_name` 作为参数传进去。
- 整个表达式的结果就是 `s.first_name` 这个字符串的哈希值，它是一个 `size_t` 类型的整数。我们用同样的方法计算 `s.last_name` 的哈希值。

#### 7. `return h1 ^ (h2 << 1);`
- **目的**：将多个字段的哈希值组合成一个单一的、最终的哈希值。
- **解释**：这是哈希组合的关键。如果一个对象有多个字段（如 `first_name` 和 `last_name`），你不能简单地把它们的哈希值相加或相乘，因为这样很容易产生冲突（例如，`hash(A,B)` 可能会等于 `hash(B,A)`）。你需要一种更好的方式来“混合”这些值。
    - `h2 << 1`: 这是**位左移**操作。它将 `h2` 的所有二进制位向左移动一位（相当于乘以2）。这有助于打破对称性，确保 `(h1, h2)` 和 `(h2, h1)` 产生的最终哈希值不同。
    - `^`: 这是**按位异或（XOR）**操作。XOR 是一个非常常用的混合哈希值的操作，因为它能很好地将两个数字的位（bits）混合在一起，任何一个输入值的任何一位发生变化，都很有可能导致最终结果发生变化，从而降低哈希碰撞的概率。

这个组合方法是一个简单但有效的方法。对于更复杂的对象，可能会使用更复杂的组合函数（例如，Boost 库中的 `hash_combine` 函数就使用了更精妙的幻数和位运算来达到更好的哈希分布）。
