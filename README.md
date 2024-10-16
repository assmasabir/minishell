# Minishell Project

Minishell is a custom shell implementation designed to replicate the core functionality of a Unix shell. It allows users to execute commands, manage processes, and utilize pipes for command chaining. By handling key operations like process creation, signal management, and basic built-in commands, Minishell provides an interactive environment similar to `Bash`.

## Features

- Execute commands from the command line
- Handle multiple pipes (`|`)
- Manage child processes with proper use of `fork()`, `execve()`, `waitpid()` and `wait()`
- Implement built-in shell commands : `cd`, `exit`, `echo`, `pwd`, `unset` and `export`
- Environment variable management (`$VAR`, `env`)
- Redirections (`<`, `>`, `>>`, `<<`): Support for input/output redirection.
- Command History: Allow users to navigate through previously executed commands.
- Exit Status Handling: Properly manage and display the exit status of executed commands.
- Quotes Handling: Ensure that quoted strings are processed correctly, allowing for spaces and special characters within arguments.
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+/)

## Getting Started

### Prerequisites

- A Unix-based system (Linux or macOS)
- GCC or any C compiler
- Make
- Basic knowledge of Bash and Unix systems

### Installation

1. Clone the repository:

    ```bash
    https://github.com/assmasabir/minishell.git
    ```

2. Navigate to the project directory:

    ```bash
    cd minishell
    ```

3. Compile the project:

    ```bash
    make
    ```

## Usage

To run the shell, simply execute the binary:

```bash
./minishell
```
You will now be able to run commands as you would in a normal shell. For example:
```bash
 ls -l | grep a | wc -l
```
```bash
$ cd ..
```
```bash
$ echo $HOME
```
### Acknowledgements

I would like to thank my teammate, [yasseraitnasser](https://github.com/yasseraitnasser), for their invaluable support and contributions throughout this project. Their collaboration and insights have been instrumental in the development of **minishell**.
