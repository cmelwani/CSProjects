# Comp 11 – Introduction to Computer Science

**School:** Tufts University · **Language:** C++ · **Environment:** Linux command line (`clang++`/`g++`)

## Overview
Comp 11 is Tufts' first programming course. This folder contains my labs and homework. They start with basic string manipulation and work up to pointer-based data structures (linked lists, trees, graphs), recursion, and object-oriented terminal simulations. Every program is a standalone C++ command-line application that reads from `stdin`, files, or command-line arguments.

## Skills demonstrated
- **Core C++:** control flow, functions, `std::string` and C-strings, file I/O, command-line arguments
- **Memory management:** `new`/`delete`, dynamic arrays, structs with pointers, destructors, avoiding leaks
- **Data structures:** 2D arrays, linked lists, binary search trees, and graphs built from pointer-linked structs
- **Algorithms:** recursion, recursive tree traversals, depth- and cost-limited graph search, frequency analysis, sorting
- **Object-oriented design:** classes, encapsulation, and classes made up of other objects in multi-file programs

## Highlighted projects
| Project | What it is | Key concepts |
|---------|-----------|--------------|
| `hw10` – **Aliens vs. Predators** | A real-time terminal game. Aliens and predators move around a battleground; collisions are detected and characters are removed or spawned. | Classes, linked lists of game objects, collision detection, terminal rendering (`termfuncs`) |
| `hw8` – **Gene Lineage** | Models genes and mutations as a directed, weighted graph and answers queries: can gene A mutate into B, in how many steps or at what cost, which genes can evolve into every gene within 10 steps, and so on. | Graphs, recursion, depth- and cost-limited search |
| `hw6` – **Mutations** | Earlier version of the gene graph: loads genes and mutation links from a file and answers single-step mutation queries. | Pointer-linked structs, dynamic memory |
| `hw9` – **Advising Tree** | A binary hierarchy of advisors and students with recursive queries over the tree. | Binary trees, recursion |
| `hw11` – **Splendor** | Framework for a terminal version of the board game Splendor (board rendering and data setup). | Class design. *Gameplay logic is unfinished in this snapshot.* |

## All projects
| Folder | Summary |
|--------|---------|
| `lab0` | Caesar cipher encryption with fixed and arbitrary shifts, wrapping around the ASCII range |
| `lab1` | Checks whether a word ends in "ing" (string indexing) |
| `hw1` | Caesar-cipher decryption and palindrome checker |
| `hw2` | "Snowcrash": unscrambles a 10×10 bitmap by applying inverse transformations in phases (2D arrays) |
| `lab3` | `baby_clang`: checks that curly braces in a source file are balanced; exits with status 0/1 |
| `hw3` | `tradecraft`: cracks a Caesar cipher with letter-frequency analysis; `sorted`: O(n²) descending sort |
| `lab4` / `hw4` | Hand-written C-string utilities (`get_line`, `is_equal`, `is_prefix`, `find_substring`); `lab4` is the starter, `hw4` is complete |
| `hw5` | Phone-tree simulation using `Mom` structs connected by pointers |
| `lab5` | Contact book of dynamically allocated `Contact` structs: lookup, print, update |
| `lab6` | Movie-database data model (unfinished; does not compile as-is) |
| `lab7` | CD area and capacity calculator (breaking a problem into functions) |
| `lab8` | Recursion exercises: `power`, `print_reverse`, `subseq` |
| `lab9` | Binary search tree: insertion, search, and traversal commands |
| `lab10` | "Red Rover": `Player` and `Playground` classes with linked-list teams (`run()` unfinished) |

## Building and running
Each folder is self-contained. Compile its `.cpp` files and run the program:
```bash
cd Comp11/hw10
clang++ -Wall -Wextra -o avp *.cpp
./avp
```
Some folders include sample input or test files to pipe into the program.

> A few labs (noted above) were saved before they were finished.
