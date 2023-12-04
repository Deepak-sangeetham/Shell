# Shell

### Implemented a user-defined shell program that can create and manage new processes in C language. Execution of commands in foreground/background, commands like cd,ls,echo, file redirection commands and some user defined commands like pinfo are implemented. Discover and history commands are also implemented.

# MY-Shell

A Linux shell was implemented in C.


## Running

- Run this my typing "gcc main.c"
- Execute by using "./a.out"
- To exit type --> "exit" or "quit"

## Commands those works

- `echo [arguments]`

    * Gives whatever we typed as it is.
    * "echo text" - prints text as it is
    * "echo "text" - prints text with double quotes
    * "echo 'text' - prints text with single quotes

- `pwd`

    * Gives the path of current working directory.

- `history`

    * Prints the last 10 commands.
    * If we use same command multiple times successively, it will print only once.

- `exit` or `quit`

    * To quit from the shell.

- `cd [directory/file] <flags>`

    * `cd .` do nothing
    * `cd ..` goes to parent directory
    * `cd ~` or `cd` goes to home directory
    * `cd -` shuffles between parent and current directory

- `ls [-l -a] [file/directory]`

    * `ls`   --> lists all files and directories in the directory
 
    *  `ls .` --> lists all files and directories in the directory
    
    *  `ls -a` --> lists all files and directories in the directory including hidden.
    
    * `ls ..`  --> lists all files and directories in the directory in the parent directory
    
    * `ls ~`   --> lists all files and directories in the home directory
    
    * `ls -a -l`  --> lists all files and directories in the current directory as permission_modes,last modified date and time
    
    * `ls -la (or) ls -al`  --> lists all files and directories in the current directory as permission_modes,last modified date and time
    
    * `ls <dir_name>`  --> lists all files and directories in the given directory
    
    * `ls <file_name>`  --> lists the same file with an error message as it is not as directory(it is a file).
    
    * `ls <flags> <dir_name|file_name>` --> lists files/directories accordingly to the flags.

- `pinfo [pid]`

    * Displays information related to process.
    * `pinfo`  -->  prints process-related info of our shell program.
    * `pinfo <pid>`  --> prints the process info of given pid.
    
- `discover [target_directory][flags][files/directories]`

    * Target directory specified using `.`,`..`,`~` or directory_name or directory_path.
    * If this argument is not present, then it assumes current directory as tagret directory.
    * `-d` -> searches all directories
    * `-f` -> searches all files


- For all other commands, the shell will fork the current process and create child process and execute the command.
- By including `&` at the end of argument, commands will run in background.
- We can run multiple commands using ";".


## How each file Works

- `prompt.c`

    * It displays the shell prompt user-name and host name.
    * `<User_Name@hostname>`

- `pwd.c`

    * pwd() gives the current working directory path.

- `echo.c`

    * echo()  function works according to echo comamnd.

- `cd.c`

    * cd() function changes directory according to given flags.

- `hsitory.c`

    * It has four functions. This function gives the history of the shell.

- `discover.c` 

    * It searches for all the files and directories from the current directory.

- `fore_gp.c`

    * It is for fore_ground process.

- `back_gp`

    * It is for back_ground process.

- `finished_bgp`

    * It is for finished background process.

- `headers.h`

    * It consists all the headers required

- `main.c`

    * Calls all the functions required.

This shell meets all the commands we incurrs.

## Extending the User-defined shell

* In this part, we are going to implement I/O Redirections, Command pipelines within command pipelines.

* Some user defined commands like jobs, fg, bg, sig.

* Finally, we performed signal handling.

## Working of these functions

- `I/O Redirection`

    * `<` --> Shows the output in the terminal of given file.
    * `>>` --> Appends the content to the output file.
    * `>` --> Overwrites the contents of the file.

- `Command pipelines`

    * `|` --> Redirects the commands on the left side to the command as input to the right side command.
    * I/O redirection can also occur within command pipelines.

- `User-defined Commands`

    * `jobs` -->  Prints all the currently running process.
    * `sig`  -->  Takes job number of a running job and sends 
                  the signal corresponding to signal number to that process.
    * `fg`   -->  Brings the running or stopped background job to       foreground.
    * `bg`   --> changes the state of a stopped background job to running.

- `Signal handling`

    * `CTRL-Z`  --> It should push any currently running fg job into the background, and change its state from runnig to stopped.

    * `CTRL-C`  --> It should interrupt any currently running foreground job.

    * `CTRL-D`  --> It should logout of the shell.
