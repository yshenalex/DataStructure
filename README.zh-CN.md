**[English](./README.md)** | **简体中文**

<div align="center">

# DataStructure

**一套经典数据结构与算法的 C / C++ 实现**

[![C](https://img.shields.io/badge/Language-C-A8B9CC?style=flat-square&logo=c&logoColor=white)]()
[![C++](https://img.shields.io/badge/Language-C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)]()
[![License](https://img.shields.io/badge/License-Mulan%20PSL%20v2-4CAF50?style=flat-square)](./LICENSE)

从零手写，适用于学习与参考。

</div>

---

## 目录

- [项目结构](#项目结构)
- [线性结构](#线性结构-c)
- [树](#树)
- [哈希结构](#哈希结构-c)
- [图](#图-c)
- [堆](#堆-c)
- [排序算法](#排序算法-c--c)
- [字符串匹配](#字符串匹配-c)
- [构建与运行](#构建与运行)
- [开源许可](#开源许可)

---

## 项目结构

<details>
<summary><b>点击展开目录树</b></summary>

```
DataStructure/
├── SeqList/                  # 动态顺序表
├── SList/                    # 单链表
├── List/                     # 双向链表
├── Stack/                    # 栈
├── Queue/                    # 队列
├── BinaryTree/               # 二叉树
├── BSTree/                   # 二叉搜索树
├── AVLTree/                  # AVL树（自平衡二叉搜索树）
├── RedBlackTree/             # 红黑树
├── Heap/                     # 堆
├── HashTable/                # 开放寻址哈希表
├── BloomFilter/              # 布隆过滤器
├── Graph/                    # 邻接矩阵图 & 并查集
├── Sort/                     # 排序算法
└── StringMatchingAlgorithm/  # 字符串匹配算法
```

</details>

---

## 线性结构 (C)

> 顺序表、链表、栈、队列 —— 一切数据结构的基石。

| 结构 | 说明 | 主要操作 |
|:-----|:-----|:---------|
| **SeqList** | 动态顺序表，支持自动扩容 | `PushBack` `PopBack` `PushFront` `PopFront` `Insert` `Erase` `Find` |
| **SList** | 单链表 | `PushBack` `PopBack` `PushFront` `PopFront` `Insert` `InsertAfter` `Erase` `EraseAfter` `Find` |
| **List** | 双向链表 | `PushBack` `PopBack` `PushFront` `PopFront` `Insert` `Erase` `Find` |
| **Stack** | 栈（数组实现） | `Push` `Pop` `Top` `Size` `Empty` |
| **Queue** | 队列（链表实现） | `Push` `Pop` `Front` `Back` `Size` `Empty` |

---

## 树

> 从基础二叉树到自平衡搜索树，覆盖树结构核心家族。

| 结构 | 语言 | 说明 |
|:-----|:----:|:-----|
| **BinaryTree** | `C` | 二叉树基础操作：前序 / 中序 / 后序 / 层序遍历，求节点数、高度、叶子数，判断完全二叉树 |
| **BSTree** | `C++` | 二叉搜索树，支持按 key 插入、查找、删除 |
| **AVLTree** | `C++` | 自平衡二叉搜索树，通过 LL / RR / LR / RL 旋转维持高度平衡 |
| **RedBlackTree** | `C++` | 红黑树，基于颜色规则的自平衡二叉搜索树，支持插入和删除 |

---

## 哈希结构 (C++)

> 基于哈希的高效查找结构。

| 结构 | 说明 |
|:-----|:-----|
| **HashTable** | 开放寻址法哈希表，线性探测，根据负载因子自动扩容 |
| **BloomFilter** | 布隆过滤器，用于集合成员的概率性判定；支持 `insert` 和 `contains`（不支持删除）；底层基于自实现的 `mystl::bitset` 位图 |

---

## 图 (C++)

> 图的存储表示与经典图算法。

| 结构 | 说明 |
|:-----|:-----|
| **Graph** | 邻接矩阵存储，支持有向 / 无向带权图；内置 **BFS**、**DFS**、**Kruskal**、**Prim**、**Dijkstra** 算法 |
| **UnionFindSet** | 并查集，支持按秩合并和路径压缩优化 |

---

## 堆 (C)

> 基于动态数组实现的最大堆，支持 `push`、`pop` 和 **堆排序**。

---

## 排序算法 (C / C++)

> 八种经典排序算法，代码清晰易读。

| 算法 | 类别 | 平均时间复杂度 |
|:-----|:-----|:--------------:|
| `InsertSort` | 插入排序 | O(n^2) |
| `ShellSort` | 插入排序 | O(n^1.3) |
| `HeapSort` | 选择排序 | O(n log n) |
| `SelectSort` | 选择排序 | O(n^2) |
| `BubbleSort` | 交换排序 | O(n^2) |
| `QuickSort` | 交换排序 | O(n log n) |
| `MergeSort` | 归并排序 | O(n log n) |
| `CountSort` | 非比较排序 | O(n + k) |

---

## 字符串匹配 (C++)

> 字符串模式匹配算法。

| 算法 | 时间复杂度 | 说明 |
|:-----|:----------:|:-----|
| **BruteForce (BF)** | O(n * m) | 暴力匹配，失配时两个指针均回退 |
| **KMP** | O(n + m) | 利用 `next` 数组避免主串指针回退；包含 `GetNext` 计算 next 数组和 `GetNextval` 优化版 |

---


## 开源许可

本项目基于 **[木兰宽松许可证，第 2 版（Mulan PSL v2）](./LICENSE)** 开源。

<div align="center">

**[回到顶部](#datastructure)**

</div>
