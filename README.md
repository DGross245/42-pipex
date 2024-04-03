# 42-Pipex

![PIPE](img/pipex.png)

Pipex is a project developed as part of the curriculum at 42 school, focusing on the handling of pipes, forks, and input/output redirection in Unix-like environments.

## Mandatory Part
The program is executed with the following syntax:

```bash
./pipex file1 cmd1 cmd2 file2
````

Pipex should mimic the behavior of the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
````

## Bonus Part
In addition to the mandatory functionality, Pipex supports handling multiple pipes and special characters like « and » when the first parameter is "here_doc".

### Multiple Pipes
To handle multiple pipes, use the following syntax:

```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

### Heredoc
A Heredoc (Here document) is a type of redirection that allows you to pass multiple lines of input to a command.

To use heredoc use the following syntax:

```bash
./pipex_bonus here_doc LIMITER cmd cmd1 file
```

## Usage

**Mandatory Part**

```bash
make
```

**Bonus Part**

```bash
make bonus
```
