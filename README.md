# Custom_Shell


cd /path/to/your/code
gcc -o myshell myshell.c
./myshell


## Overview
This program is a simple shell implementation written in C. It provides a command-line interface where users can execute commands, including built-in commands like `cd`, `pwd`, `history`, and `exit`.
Additionally, users can provide additional paths as arguments when running the shell to add them to the `PATH` environment variable, allowing for more commands to be executed directly from the shell.


## Getting Started
To get started, clone the repository from GitHub:
```bash
git clone https://github.com/edenbdv/Custom_Shell.git
cd Custom_Shell
```

## Features
- Executes external commands using `execvp`.
- Handles built-in commands like `cd`, `pwd`, `history`, and `exit`.
- Maintains a command history with a limit on the number of stored commands.
- Supports setting the `PATH` environment variable dynamically.

## Usage
1. **Compilation**: Compile the program using a C compiler such as GCC.
   ```bash
   gcc -o myshell myshell.c
   ```
2. **Execution**: Run the compiled executable.
   ```bash
   ./myshell
   ```
3. **Commands**:
   - External commands: Enter any external command available in your system.
   - Built-in commands:
     - `cd [directory]`: Change current directory.
     - `pwd`: Print current working directory.
     - `history`: Print command history.
     - `exit`: Exit the shell.

4. **Additional Arguments**: You can provide additional paths as arguments when running the shell to add them to the `PATH` environment variable. For example:
   ```bash
   ./myshell /usr/local/bin /opt/bin
   ```
This allows you to use commands located in /usr/local/bin and /opt/bin directly from the shell.