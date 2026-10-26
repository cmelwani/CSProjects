# Comp 15 – Data Structures

**School:** Tufts University · **Language:** C++ · **Tooling:** `make`, `clang++`, `valgrind`

## Overview
Comp 15 covers the classic data structures and the trade-offs between them. In this folder I implemented each structure from scratch (no STL containers unless the assignment allowed them), wrote unit tests for it, checked it for memory leaks with valgrind, and used it in a larger application. Each folder has its own `Makefile`, and most have the original assignment README.

## Skills demonstrated
- **Implementing data structures:** dynamic arrays, singly and doubly linked lists, circular buffers, stacks, queues, BSTs, AVL trees, heaps, hash tables, graphs
- **Algorithm analysis:** Big-O trade-offs between structures, plus measured benchmarks of sorting algorithms
- **C++ engineering:** the Rule of Three (deep copy and destructors), move semantics, templates, exceptions, multi-file builds with Makefiles
- **Testing:** per-method unit tests, diffing my output against reference implementations, valgrind leak checks

## Highlighted projects
### `proj1` – CalcYouLater: an RPN calculator and mini-language interpreter
A stack-based Reverse Polish Notation calculator that works as a small programming language. It handles integers, booleans, and code blocks in `{ ... }`. Commands include arithmetic and comparison operators, stack commands (`dup`, `swap`, `drop`, `clear`, `print`), and control flow (`exec`, `file`, `if`), which is enough to write recursive programs like `fact.cyl`. Built from a `DatumStack`, a parser for nested code blocks, and an interpreter loop that reads from any `istream`, so `exec` and `file` simply call the same loop again.

### `proj2` – Road Trip: route finding on a directed graph
`findpath` loads cities (with latitude and longitude) and one-way roads, then answers `list`, `dist <c1> <c2>` (great-circle distance), and `path <c1> <c2> <n>`. The `path` command enumerates up to *n* routes using a **recursive depth-first search with backtracking**. Cities are stored as adjacency lists (`vector<City*>`).

### `hw3` – MetroSim: metro train simulator
Simulates a train looping through a line of stations. Each station has a FIFO queue of waiting passengers. The train is a vector of queues, one per destination, so dropping passengers off at a station means emptying a single queue. Commands come from a file or `stdin`, and arrivals are logged to an output file.

## All projects
| Folder | Topic | Summary |
|--------|-------|---------|
| `hw1` | Dynamic array | `CharArrayList`: resizable array with full copy semantics, `range_error` exceptions, and unit tests |
| `hw2` | Doubly linked list | `CharLinkedList` with the same interface as `hw1` (for comparing the two); recursive `find`; valgrind-clean tests |
| `hw3` | Queues / simulation | MetroSim (see above) |
| `hw4` | Binary search tree | Insert and remove (all three cases), duplicate counts, height, deep copy, sideways tree printer; all recursive |
| `lab1` | Array list | Grocery-list program built on a string `ArrayList` that grows as needed |
| `lab2` | Singly linked list | Planet list: insert at back, reverse a list |
| `lab3` | Circular buffer | Stack and queue built on a wrap-around array with O(1) operations at both ends |
| `lab4` | Recursion | Random maze generator and recursive backtracking solver |
| `lab5` | Makefiles | Gradebook "evil professor" program used to practice separate compilation |
| `lab6` | Tree traversals | In-order, pre-order, level-order, and post-order delete on a BST |
| `lab7` | AVL trees | Self-balancing insertion using left and right rotations |
| `lab8` | Heaps | Array-based min-heap (`upHeap`/`downHeap`, O(n) `buildHeap`) used for heapsort |
| `lab9` | Graph search | Tufts campus map; shortest walking route in hops using BFS |
| `lab10` | Templates | Generic `ArrayList<T>` with copy and move semantics, used by a small "Hookbook" social network |
| `lab11` | Hash tables | Linear probing vs. separate chaining with good vs. bad hash functions; reports collision counts |
| `lab12` | Sorting | Insertion, selection, merge, and quick sort with a timing harness (`./sort -r 10000 quicksort`) |
| `proj1` | Stacks / interpreters | CalcYouLater (see above) |
| `proj2` | Graphs | Road Trip (see above) |

## Building and running
```bash
cd Comp15/proj2
make
./findpath <cities-file> <roads-file>
```
Some course-provided files (for example `Datum.h` and `Location.h`/`.o`) were not saved in this repository, so a few projects need them added back before they will build. Some labs were saved before they were finished; their own READMEs say so.
