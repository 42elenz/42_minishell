# minishell
This shell was done as a group project with [afrasch](https://github.com/afrasch) at the school 42Heilbronn.
<img src="https://github.com/42elenz/minishell/blob/master/ressources/Screenshot%202022-12-23%20at%2020.22.06.png" alt="Image scroe" width="60">
## Contents
- [Introduction](https://github.com/42elenz/minishell#introduction)
- [Our Minishell](https://github.com/42elenz/minishell#our-minishell)
  - [Lexer and Parser](https://github.com/42elenz/minishell#lexer-and-parser)
  - [Expander](https://github.com/42elenz/minishell#expander)
  - [Executor](https://github.com/42elenz/minishell#executor)
- [Examples](https://github.com/42elenz/minishell#some-example-outputs)
  - [wrong syntax](https://github.com/42elenz/minishell#wrong-syntax)
  - [invalid command](https://github.com/42elenz/minishell#invalid-command)

## Short description of the subject

The goal of the subject was to recreate some of the functionalities of bash (Version 3.2).<br>
To see the exact requirements, check Chapter III and IV of the subject pdf.<br>
## From the subject pdf
### Introduction
Creating our own shell is a task to bring us back and let us face the problems that people had back in the days. <br>

### Some of the restrictions
![subject_restrictions](https://github.com/42elenz/minishell/blob/master/ressources/minishell_from_subject_pdf.png)

## Our Minishell
### The basic functionalities of the project
- this is a shell that can be compiled by running<br>`make all`<br>and then to run it<br>`./minishell`<br>
- now you are greeted with a prompt waiting for input just like any other shell
- this project uses the readline libraries `readline/history.h` and `readline/readline.h` you can install those via `brew install readline` or `apt-get install libreadline-dev`, thanks to those there is a working history of used commands
- there is some memory-leaks caused by the readline-library

### The basic structure of our minishell
Just like most of the other shells we have divided our shell into 3 parts:
1. [Lexer and Parser](https://github.com/42elenz/minishell#lexer-and-parser)
3. [Expander](https://github.com/42elenz/minishell#expander)
4. [Executor](https://github.com/42elenz/minishell#executor)

Those parts all have different tasks.<br>

----------

### Lexer and Parser
In our minishell the lexer and parser are combined. We build the tokens as so called "chunks" and to save computing <br>
we also parse. Some basic expensions are also done in this step. We decieded to use this design despite of what other shells <br>
usually do due to the lesser functionalities of our programm.
[back to contents](https://github.com/42elenz/minishell#contents)<br>
[back to basic structure](https://github.com/42elenz/minishell#the-basic-functionalities-of-the-project)<br>

----------

### Expander
The expander will take the parser tokens as argument.<br>
The expander will interprete the environment variables into their corresponding value.<br>
It also handles subshells, creates pipes and handles all the opening of input-/output-redirections and storing the correct ones in the executor tokens.<br>
Subshells are executed by creating a child process which runs minishell without readline reading the input, but directly handing the correct, unparsed commands to it. And after the lexer is done, it will call the parser and so on.<br>
After passing every of those parts without errors, it calls the executor in a loop and gives the executor the correct values to work with.<br>
After a call of the executor, an error value, similar to errno, is set to the exit code of the executor.<br>
This error value can be checked by running `echo $?` and is used for the `&&` and `||` logic.<br><br>
This is the way the data is stored in the expander tokens and handed to the executor:<br>

[back to contents](https://github.com/42elenz/minishell#contents)<br>
[back to basic structure](https://github.com/42elenz/minishell#the-basic-functionalities-of-the-project)<br>

----------

### Executor
The executor does as it is called, it executes the command.<br>
If the given command is an inbuilt, it will just run the command in the same process, if it isn't it will create a child process to run the command in.<br>
After this is decided, the redirections of input and output are done and the command is executed.<br>
The executor always returns the exit code of whatever it did.<br>

[back to contents](https://github.com/42elenz/minishell#contents)<br>
[back to basic structure](https://github.com/42elenz/minishell/blob/master/ressources/syntax_error.png)<br>

----------

### Some example outputs

#### wrong syntax
If some form of wrong syntax gets detected, `Invalid Syntax at token` is printed and the error value `$?` is set to `258`<br>
![syntax_error](https://github.com/42elenz/minishell/blob/ressources/syntax_error.png)<br>
#### invalid command
If there was an invalid command used, `command not found` is printed and the error value `$?` is set to `127`<br>
![invalid_command](https://github.com/42elenz/minishell/blob/master/ressources/invalid_command.png)<br>
[back to contents](https://github.com/42elenz/minishell#contents)<br>
