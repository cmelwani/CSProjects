# Comp 40 – Machine Structure & Assembly Language Programming

**School:** Tufts University · **Languages:** C, Universal Machine assembly · **Tooling:** `make`, `gcc`, `valgrind`, David Hanson's *C Interfaces and Implementations* (CII) library

## Overview
Comp 40 teaches how programs actually run on a machine: data representation, bit manipulation, caches and locality, building abstractions in C, assembly language, and performance tuning. I did these projects with partners (Anna Wang and Devan Venkataraman for the C projects, Melis Inanc for the assembly calculator). The course culminated in a **Universal Machine (UM) emulator**, which we then profiled and optimized, and an **RPN calculator written in UM assembly** that runs on it.

## Skills demonstrated
- **Systems C:** opaque types, interfaces vs. implementations, function pointers, careful memory ownership (valgrind-clean)
- **Bit manipulation:** packing signed and unsigned fields into 64-bit words, two's complement, overflow detection
- **Performance:** cache locality, blocked memory layouts, measuring CPU time, profiling and optimizing hot paths
- **Computer architecture:** writing an emulator (fetch, decode, execute; registers; segmented memory) and assembly programming with calling conventions

## Projects
### `um` – Universal Machine emulator
An emulator for a 14-instruction virtual machine with 8 registers and segmented memory. The design is split into modules:
- `um_loader` reads the `.um` binary and packs each group of 4 bytes into a 32-bit instruction word.
- `memory` stores memory as a sequence of segments, keeps a stack of unmapped segment IDs for reuse, and implements map, unmap, load, and store.
- `execute` holds the registers and program counter and runs the fetch/decode/dispatch loop.

The folder includes a suite of hand-written `.um` unit tests (`UMTESTS`) for each instruction: arithmetic, NAND, conditional move, I/O, segment mapping and unmapping, and load-program.
```bash
make && ./um midmark.um
```

### `profile` – Profiling and optimizing the UM
The same UM, merged into a single file (`um.c`) and hand-optimized: custom inline segment and sequence structures replace the CII containers, which removes abstraction overhead from the hot path. Profiling showed that the remaining cost was dominated by `malloc`/`free` when mapping segments. Benchmarked with `midmark.um` and `sandmark.umz`.

### `asmcoding` – RPN calculator in UM assembly
A stack-based calculator written in UM assembly (`.ums`). It dispatches on each input character through a **256-entry jump table**, keeps a 15,000-word value stack, and supports `+ - * /`, `| &`, negate (`c`), complement (`~`), `s`wap, `d`up, `p`op, and `z` (clear). It follows explicit calling conventions (`r0` is zero, `r1` holds return values, `r2` is the call stack pointer, `r3` is the value stack pointer). `printd.ums` prints UM words in decimal; `urt0.ums`/`callmain.ums` set up the runtime. Assembled with `./compile`, and runs on the UM above.

### `arith` – Lossy image compression (JPEG-style)
`40image -c` compresses a PPM image into a binary format about 3× smaller; `40image -d` decompresses it. The pipeline:
1. Trim the image to even dimensions.
2. Convert RGB to component video (Y/Pb/Pr) (`cvconversions`).
3. For each 2×2 block, apply a discrete cosine transform (`dctconversions`).
4. Quantize the coefficients and average the chroma (`quantize`).
5. Bit-pack the result into a 32-bit codeword (`pack`, using our `bitpack.c` library).

Decompression runs the same steps in reverse. Reconstructed images differ from the originals by about 2.5% RMS, measured with our `ppmdiff` tool.

### `arith-challenge` – Alternative codeword layout
The same compressor rebuilt (`40image-6`) for a different codeword format: 6 bits for each DCT coefficient (`a`, `b`, `c`, `d`) instead of 9/5/5/5, with new quantization scales. Comparing it with `arith` shows how bit allocation trades off against image quality.

### `locality` – Blocked 2D arrays and cache performance
- `UArray2b` is a **blocked 2D array**: each block is stored contiguously, so pixels that are near each other on screen are near each other in memory.
- `a2plain`/`a2blocked` provide a polymorphic "A2Methods" interface (a table of function pointers), so client code can use either array layout without changes.
- `ppmtrans` rotates images (`-rotate 0|90|180|270`) using `-row-major`, `-col-major`, or `-block-major` traversal and reports timings (`-time`).

The README in that folder contains our measured results. For example, on an 8160×4580 image, a 180° rotation took about **54 ns/pixel row-major vs. 170 ns/pixel column-major** (block-major was about 112 ns), along with an analysis of why.

### `iii` – Interfaces, Implementations & Images
- `UArray2` (a 2D array of any element type) and `Bit2` (a 2D bit array), each with row-major and column-major mapping functions.
- `sudoku` reads a solved 9×9 puzzle as a PGM image and checks it by verifying every row, column, and 3×3 box. Its exit code is the result.
- `unblackedges` removes black border pixels from scanned PBM images using a breadth-first flood fill that starts from the edges.

### `filesnpix` – Files, Pictures & Hashing
- `brightness` reports the average brightness of a PGM image (read from a file or `stdin`), using the `Pnmrdr` reader.
- `readaline` is a hand-written line reader that does its own buffer management.
- `simlines` finds lines that match across multiple files, after normalizing words. It stores lines as CII `Atom`s in a hash `Table` that maps each line to a `Seq` of (file, line number) locations, then prints every group of matching lines.

## Building
Each folder has its own `Makefile`. These projects were built on Tufts' Comp 40 servers and rely on the course-provided Hanson CII library and `netpbm`/`pnmrdr` headers, so they won't build on a regular machine without those dependencies installed.
