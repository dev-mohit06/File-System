# Simple File System

This project implements a simple file system in C. It allows you to create directories and files, navigate between directories, and list the contents of directories.
## Author

Mohit Paddhariya [@dev-mohit06](https://github.com/dev-mohit06)

## Features

- Create directories (`mkdir`)
- Create files (`touch`)
- Change directory (`cd`)
- List contents of the current directory (`ls`)
- Display the directory tree (`tree`)
- Clear the screen (`clear`)
- Exit the program (`exit`)

## Usage

Compile the program using `gcc`:

```sh
gcc -o filesystem filesystem.c
```

Run the program:

```sh
./filesystem
```

## Commands

- `mkdir <directory_name>`: Create a new directory.
- `touch <file_name>`: Create a new file.
- `cd <directory_name>`: Change to the specified directory.
- `cd ..`: Move to the parent directory.
- `ls`: List the contents of the current directory.
- `tree`: Display the directory tree starting from the root.
- `clear`: Clear the screen.
- `exit`: Exit the program.

## Example

```sh
Welcome to the simple file system!

Current Directory: root> mkdir docs
Current Directory: root> cd docs
Current Directory: docs> touch file1.txt
Current Directory: docs> ls
[FILE] file1.txt
Current Directory: docs> cd ..
Current Directory: root> tree
[DIR] root
    [DIR] docs
        [FILE] file1.txt
Current Directory: root> exit
```