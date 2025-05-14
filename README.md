# Welcome to My Readline
***************************
`my_readline` - Line Reader in C (system -level)

## Task
Custom implementation of a line-reading function similar to `fgets()` to demonstrate a deep understanding of 
memory management (Heap vs Stack), file descriptors, dynamic buffer handling, and low-level I/O in C

## Description
- How `my_readline` works
1. It maintains a persistent buffer (`storage`) that  retains unprocessed data across call
2. It searches this buffer for a newline (`\n`).
3. If found, it returns everything before the newline, trimming the buffer for the next time.
4. If not found, it reads more data from the file descriptor into a temporary buffer and appends it to `storage`
5. If the end of file is reached and there's leftover data, it returns it as the final line.
6. It supports different types of input sources like files, standard input, redirection.

- There are the only two global variable used in this program.
1. `int READLINE_READ_SIZE` : The number of bytes to read at once from the stream (default: 512)
2. `char *storage` : Dynamically allocated heap memory that holds data across mutiple calls. 

- The following functions are allowed to use
1. `malloc`
2. `free`
3. `read`
4. `open`
5. `close`

- The following functions are strictly forbidden to use
1. `lseek`
2. `fread`
3. `fopen`
4. Any other library functions (e.g., `strcpy`, `strlen`, `realloc`, `snprintf`, etc.)
5. Multiline macros
6. Logic-based macros (e.g., macros using `if`, `while`, etc.)
7. Including other `.c` files


## Installation
```
./make            #buids the program my_tar
./make clean      #removes object files
./make fclean     #removes object files and binary
./make re         #cleans and rebuilds the program
```

## Usage
```
1. Reading from a file via open():
./my_readline test.txt

2. Reading from standard input (stdin with file descriptor 0)
./my_readline 
Hello World
<Ctrl+D> <- It signals end-of-input (EOF) on Unix-like systems

3. Reading from a redirected file (Shell redirection):
./my_readline < test.txt 

```

### The Core Team

-- Prakash Shrestha --