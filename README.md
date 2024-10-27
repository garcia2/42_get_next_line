# get_next_line

**get_next_line** is a project from 42 school that focuses on creating a function capable of reading a line from a file descriptor. The goal is to implement a function that reads text line-by-line from a file or standard input, handling memory effectively while managing different buffer sizes and edge cases.

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Limitations and Edge Cases](#limitations-and-edge-cases)
6. [Author](#author)

## Overview

The **get_next_line** project aims to develop a function called `get_next_line` that reads from a file descriptor and returns a single line each time it is called. This project helps in understanding file handling, dynamic memory management, and buffer manipulation in C.

## Features

- Reads one line at a time from a given file descriptor.
- Handles various buffer sizes using the `BUFFER_SIZE` macro.
- Manages dynamic memory allocation and deallocation to avoid memory leaks.

## Installation

To compile `get_next_line`, use the following command in the directory containing `get_next_line.c`, `get_next_line_utils.c`, and `get_next_line.h`:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```

Replace `42` with the desired buffer size, and `main.c` should contain your test code.

## Usage

To use `get_next_line`, include `get_next_line.h` in your code and compile as shown above. Here’s an example of a simple `main.c` test:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd = open("test_file.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

## Limitations and Edge Cases

- The function does not handle multiple file descriptors simultaneously without re-initializing.
- It does not handle extremely large files efficiently if `BUFFER_SIZE` is too small.
- `get_next_line` returns `NULL` upon reaching the end of the file or if an error occurs.

## Author

Project developed by ([Nicolas Garcia ](https://github.com/garcia2)) as part of 42 school.
