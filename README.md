```
# C File Compressor

A simple and small utility written in C for file compression and decompression using Raylib.

## Features
* Command-line argument processing for ease of use in terminals.
* Uses dynamic memory allocation to work with files of various sizes.
* Automatic appending of file extensions (`.compressed` / ` .decompressed`).

## Requirements
* A C compiler (GCC, Clang, etc.)
* Raylib must be installed and linked.

## Compilation
To compile the program on GCC, simply type:

```bash
gcc compress.c -o compress -lraylib -lm
```

## Usage

**To compress a file:**

```bash
./compress my_document.txt
my_document.txt.compressed
```

**To decompress a file:**

```bash
./compress -d my_document.txt.compressed
my_document.txt.compressed.decompressed
```
```
***
