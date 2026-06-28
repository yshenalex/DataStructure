**[简体中文](./README.zh-CN.md)** | **English**

<div align="center">

# DataStructure

**A collection of classic data structure and algorithm implementations in C and C++**

[![C](https://img.shields.io/badge/Language-C-A8B9CC?style=flat-square&logo=c&logoColor=white)]()
[![C++](https://img.shields.io/badge/Language-C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)]()
[![License](https://img.shields.io/badge/License-Mulan%20PSL%20v2-4CAF50?style=flat-square)](./LICENSE)

Built from scratch for learning and reference purposes.

</div>

---

## Table of Contents

- [Project Structure](#project-structure)
- [Linear Structures](#linear-structures-c)
- [Trees](#trees)
- [Hash Structures](#hash-structures-c)
- [Graph](#graph-c)
- [Heap](#heap-c)
- [Sorting Algorithms](#sorting-algorithms-c--c)
- [String Matching](#string-matching-c)
- [Build & Run](#build--run)
- [License](#license)

---

## Project Structure

<details>
<summary><b>Click to expand directory tree</b></summary>

```
DataStructure/
├── SeqList/                  # Dynamic sequential list (array-based)
├── SList/                    # Singly linked list
├── List/                     # Doubly linked list
├── Stack/                    # Stack
├── Queue/                    # Queue
├── BinaryTree/               # Binary tree
├── BSTree/                   # Binary search tree
├── AVLTree/                  # AVL tree (self-balancing BST)
├── RedBlackTree/             # Red-black tree
├── Heap/                     # Binary heap
├── HashTable/                # Open addressing hash table
├── BloomFilter/              # Bloom filter
├── Graph/                    # Adjacency matrix graph & union-find set
├── Sort/                     # Sorting algorithms
└── StringMatchingAlgorithm/  # String matching algorithms
```

</details>

---

## Linear Structures (C)

> Sequential list, linked list, stack, and queue — the foundation of all data structures.

| Structure | Description | Key Operations |
|:----------|:------------|:---------------|
| **SeqList** | Dynamic array with auto-resizing | `PushBack` `PopBack` `PushFront` `PopFront` `Insert` `Erase` `Find` |
| **SList** | Singly linked list | `PushBack` `PopBack` `PushFront` `PopFront` `Insert` `InsertAfter` `Erase` `EraseAfter` `Find` |
| **List** | Doubly linked list | `PushBack` `PopBack` `PushFront` `PopFront` `Insert` `Erase` `Find` |
| **Stack** | LIFO stack (array-based) | `Push` `Pop` `Top` `Size` `Empty` |
| **Queue** | FIFO queue (linked-list-based) | `Push` `Pop` `Front` `Back` `Size` `Empty` |

---

## Trees

> From basic binary trees to self-balancing search trees — covering the core tree family.

| Structure | Language | Description |
|:----------|:--------:|:------------|
| **BinaryTree** | `C` | Basic binary tree with preorder / inorder / postorder / level-order traversals, node count, height, leaf count, completeness check |
| **BSTree** | `C++` | Binary search tree with key-based insert, find, and erase |
| **AVLTree** | `C++` | Self-balancing BST with automatic rotations (LL, RR, LR, RL) to maintain height balance |
| **RedBlackTree** | `C++` | Self-balancing BST using color-based balancing rules with insert and erase operations |

---

## Hash Structures (C++)

> Efficient lookup structures based on hashing.

| Structure | Description |
|:----------|:------------|
| **HashTable** | Open addressing hash table with linear probing, automatic resizing based on load factor |
| **BloomFilter** | Probabilistic data structure for set membership testing; supports `insert` and `contains` (no delete); built on a custom bitset implementation `mystl::bitset` |

---

## Graph (C++)

> Graph representations and classic graph algorithms.

| Structure | Description |
|:----------|:------------|
| **Graph** | Adjacency matrix representation supporting directed / undirected graphs with weighted edges; includes **BFS**, **DFS**, **Kruskal**, **Prim**, and **Dijkstra** algorithms |
| **UnionFindSet** | Disjoint set with union-by-rank and path compression optimizations |

---

## Heap (C)

> Binary heap (max-heap) implemented with a dynamic array. Supports `push`, `pop`, and **heap sort**.

---

## Sorting Algorithms (C / C++)

> Eight classic sorting algorithms with clean, readable implementations.

| Algorithm | Category | Complexity (Avg) |
|:----------|:---------|:-----------------|
| `InsertSort` | Insertion | O(n^2) |
| `ShellSort` | Insertion | O(n^1.3) |
| `HeapSort` | Selection | O(n log n) |
| `SelectSort` | Selection | O(n^2) |
| `BubbleSort` | Exchange | O(n^2) |
| `QuickSort` | Exchange | O(n log n) |
| `MergeSort` | Merging | O(n log n) |
| `CountSort` | Non-comparison | O(n + k) |

---

## String Matching (C++)

> Pattern matching algorithms for string search.

| Algorithm | Time Complexity | Description |
|:----------|:---------------:|:------------|
| **BruteForce (BF)** | O(n * m) | Naive pattern matching; backtracks both pointers on mismatch |
| **KMP** | O(n + m) | Uses a `next` array to avoid backtracking the main pointer; includes `GetNext` for computing the next array and `GetNextval` for the optimized version |

---


## License

This project is licensed under the **[Mulan Permissive Software License, Version 2 (Mulan PSL v2)](./LICENSE)**.

<div align="center">

**[Back to Top](#datastructure)**

</div>
