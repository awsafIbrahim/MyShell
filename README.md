# MyShell

> A lightweight, educational custom shell implemented in C.


## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Build & Run](#build--run)
- [Usage Examples](#usage-examples)
- [Project Structure](#project-structure)
- [Contributing](#contributing)


---

## Overview

**MyShell** is a compact, custom-built Unix-style command-line shell written in C.  
It is designed primarily for **learning purposes**, showing how operating systems launch and manage processes through system calls.

This project demonstrates:
- Parsing and handling user input
- Executing external commands
- Modular shell logic separated into reusable components

---

## Features

- Basic command parsing and execution
- Interactive shell prompt (`shell>`)
- Modular design:
  - `main.c` manages the main shell loop
  - `shell.c` / `shell.h` encapsulate command handling
- Clear, extensible codebase for experimenting with new shell features

Future enhancements could include:
- Built-in commands (`cd`, `exit`, etc.)
- Input/output redirection
- Piping (`|`)
- Environment variables
- Signal handling

---


## How It Works

1. **Startup** – The shell begins by printing a prompt (`shell>`).
2. **Input Handling** – User input is read and tokenized.
3. **Command Execution** – Commands are run using system calls like:
   - `fork()`
   - `execvp()`
   - `wait()`
4. **Looping** – After execution, control returns to the prompt until the user exits.

---

## Getting Started

### Prerequisites
- A Unix-like environment (Linux/macOS recommended)
- GCC or Clang compiler

### Build & Run

```bash
# Clone the repository
git clone https://github.com/awsafIbrahim/MyShell.git
cd MyShell

# Compile the shell
gcc -o myshell main.c shell/shell.c

# Run the shell
./myshell
