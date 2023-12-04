#include "headers.h"

// Including all functions to main.c file

// declaring these globally for using all over different files

char str[10000];
int cd_num = 0;
char word_last[2][200];
int job_num;
int hist_ptr, histcnt;
char history_commands[20][5000];

struct process
{

    int process_id;
    char word[1000];
    int ordered_job;
    int flag;
};

struct process Process[1000];
int std_in, std_out;
int curr_pid;
int shell_id;

#include "prompt.c"
#include "pwd.c"
#include "echo.c"
#include "cd.c"
#include "ls.c"
#include "pinfo.c"
#include "fore_gp.c"
#include "back_gp.c"
#include "finished_bgp.c"
#include "discover.c"
#include "history.c"
#include "pipe.c"
#include "jobs.c"
#include "sig.c"
#include "fg.c"
#include "bg.c"
#include "signals.c"

void execute(char command[], int commands[], char *total_arg[], int i, int num_args, int num_comms)
{

    // finding the original command entered
    char f_in[1000]; // names of input file and output file
    char f_out[1000];
    char original_command[1000];
    int last_ind; // tofind the last index before ">,<,>>"

    f_in[0] = 0;
    f_out[0] = 0;
    original_command[0] = 0;

    if (i == num_comms - 1) // if we find the last command,make last index as arguments number - 1
    {

        last_ind = num_args - 1;
    }

    else
    {

        last_ind = commands[i + 1] - 1; // to find the index of the next command before index
    }

    int ind1, ind2, j;

    // ind1 for <
    // ind2 for >,>>

    ind1 = -1;
    ind2 = -1;

    for (j = commands[i]; j < last_ind; j++)
    {

        if (strcmp(total_arg[j], ">") == 0) // finding "">"" index
        {

            ind2 = j;
        }

        if (strcmp(total_arg[j], ">>") == 0) // finding ">>" index
        {

            ind2 = j;
        }

        if (strcmp(total_arg[j], "<") == 0) // finding "<" index
        {

            ind1 = j;
        }
    }

    if (ind1 > -1) // concatenationg original command with all arguments untill we encounter "<"
    {

        for (j = 0; j < ind1; j++)
        {

            strcat(original_command, total_arg[j]);
            if (j != ind1 - 1)
            {

                strcat(original_command, " "); // adding space untill last index
            }
        }
    }

    else if (ind2 > -1) // if we dont have "<" , then concatenating untill we encounter ">" or ">>"
    {

        for (j = 0; j < ind2; j++)
        {

            strcat(original_command, total_arg[j]);

            if (j != ind2 - 1)
            {

                strcat(original_command, " "); // adding space untill last argumeht
            }
        }
    }

    else
    {

        strcpy(original_command, command); // if we dont have any of theose redirections just copy
    }

    // printf("%s\n", original_command);

    // opening and closing respected files

    int fd_in, fd_out;

    if (ind1 > -1)
    {

        fd_in = open(total_arg[ind1 + 1], O_RDONLY); // opening the given input file

        if (fd_in < 0)
        {

            perror("Open():"); // error handling
        }
    }

    if (ind2 > -1)
    {

        if (strcmp(total_arg[ind2], ">") == 0)
        {

            fd_out = open(total_arg[ind2 + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); // > --> overwriting requested output into output txt file
        }

        else
        {

            fd_out = open(total_arg[ind2 + 1], O_WRONLY | O_CREAT | O_APPEND, 0644); // --> Appending requensted output into output txt file
        }

        if (fd_out < 0)
        {

            perror("Open():"); // error handling
        }
    }

    // if input redirection is needed backup stdin_file no which is 0, duplicate input file
    // into stdin_fileno

    if (ind1 > -1)
    {
        // opening a duplicated file
        if (dup2(fd_in, 0) < 0)
        {

            perror("dup2():"); // error handling
        }

        // after completion of input redirection, restore stdin_fileno
        close(fd_in); // closing the file
    }

    // if output redirection is required backup stdout_file no which is 1, duplicate output file
    // into stdout_fileno

    if (ind2 > -1)
    {

        if (dup2(fd_out, 1) < 0)
        {

            perror("dup2():"); // error handling
        }

        // after completion of output redirection, restore stdout_fileno

        close(fd_out);
    }

    if (strcmp(total_arg[commands[i]], "echo") == 0)
    {

        echo(original_command);
    }

    else if (strcmp(total_arg[commands[i]], "pwd") == 0)
    {

        pwd();
    }

    else if (strcmp(total_arg[commands[i]], "cd") == 0)
    {
        // printf("%s",command_arr[i]);
        // char s2[100];
        // int k=0;
        // for(int j = 0; j < strlen(command_arr[i])-1;++j){

        //         s2[k]=command_arr[i][j];
        //         ++k;

        // }
        // printf("%s",command_arr[i]);
        // printf("%s",s2);
        cd(original_command);
    }

    else if (strcmp(total_arg[commands[i]], "ls") == 0)
    {

        ls(original_command);
    }

    else if (strcmp(total_arg[commands[i]], "pinfo") == 0)
    {

        pinfo(original_command);
    }

    else if (strcmp(total_arg[commands[i]], "discover") == 0)
    {

        discover(original_command);
    }

    else if (strcmp(total_arg[commands[i]], "history") == 0)
    {

        // history(hist_comm);
        show_history();
    }

    else if (strcmp(total_arg[commands[i]], "exit") == 0 || strcmp(total_arg[commands[i]], "quit") == 0)
    {
        end_history();
        exit(EXIT_SUCCESS);
        // break;
    }

    else if(strcmp(total_arg[commands[i]],"jobs") == 0){

        jobs(original_command);
    }

    else if(strcmp(total_arg[commands[i]],"sig") == 0){

        sig(original_command);
    }

    else if(strcmp(total_arg[commands[i]],"fg") == 0){

        fg(original_command);
    }

    else if(strcmp(total_arg[commands[i]],"bg") == 0){

        bg(original_command);
    }

    else if (strstr(command, "&"))
    {

        back_gp(original_command);
    }

    else
    {

        fore_gp(original_command);
    }

    if (dup2(std_out, 1) < 0 || dup2(std_in, 0) < 0)
    {

        printf("File Error\n"); // error handling
    }
}

int main()
{

    signal(SIGCHLD,Signal);  // for finished background process

    signal(SIGINT,CTRL_C);
    signal(SIGTSTP,CTRL_Z);
    //signal(SIGINT,ctrld);

    curr_pid = -1;
    job_num = 0;

    pid_t proc_id;

    proc_id = getpid();
    shell_id = proc_id;
    

    int i;
    std_in = dup(STDIN_FILENO);
    std_out = dup(STDOUT_FILENO);

    word_last[0][0] = '\0'; // initialising as spaces
    word_last[1][0] = '\0';

    for (i = 0; i < 1000; i++)
    {

        Process[i].flag = 0;
        Process[i].ordered_job = -1;
        Process[i].word[0] = 0;
    }

    if (!getcwd(str, 1000)) // getting current path of the directory and error handling
    {

        perror("getcwd():");
    }

    history();

    // printf("%s\n",str);

    printf("\t--------------------- Welocme to My SHELL-----------------------\t\n");

    while (true)
    {

        displayRequirement(); // Displaying the current directory

        // char command[1000];

        // command[0] = '\0';

        signal(SIGCHLD, Signal);

        size_t buff_size = 500;
        char *command;
        int num = getline(&command, &buff_size, stdin); // Taking command form the user

        add_history(command);
        command[num - 1] = '\0'; // removing "\n" from the end

        char *delim = " \t";
        char *first_arg = strtok(command, delim); // dividing the input command into tokens
        char *total_arg[1000];

        // int num_args = 0;

        int num_args = 0;
        int num_comm = 0;
        int commands[1000];

        while (first_arg)
        {

            if (num_args == 0 && first_arg[0] != ';') // if we encountered ';', increment commands number
            {

                commands[num_comm] = 0;
                num_comm++;
            }

            if (first_arg[0] == ';')
            {

                commands[num_comm] = num_args;
                num_comm++;
                first_arg = strtok(NULL, delim);
                continue;
            }

            total_arg[num_args] = first_arg;
            num_args++; // if we encountered required delimeter increment arguments number
            first_arg = strtok(NULL, delim);
        }

        // for(i = 0;i < num_args;i++){

        //     strcat(hist_comm,total_arg[i]);
        //     strcat(hist_comm," ");
        // }

        // printf("%s\n",hist_comm);

        // for(i =  0; i < num_args-1;i++){

        //     printf("%s ",total_arg[i]);
        // }

        // printf("\n");

        // printf("%s\n",total_arg);

        char command_arr[num_comm][1000]; // create an 2D character array

        for (i = 0; i < num_comm; i++)
        {

            command_arr[i][0] = '\0'; // filling with space
        }

        // command_arr[0][0] = 0; // big string which contains input sting without tabs and spaces

        // iterating over number of commands given
        for (i = 0; i < num_comm; i++)
        {

            if (i == num_comm - 1)
            {

                for (int j = commands[i]; j < num_args; j++)
                {

                    strcat(command_arr[i], total_arg[j]);
                    if (j != num_args - 1)
                    {
                        strcat(command_arr[i], " "); // single spacing between two words
                    }
                }
            }

            else
            {

                for (int j = commands[i]; j < commands[i + 1]; j++)
                {

                    strcat(command_arr[i], total_arg[j]);
                    if (j != commands[i + 1] - 1)
                        strcat(command_arr[i], " ");
                }
            }
        }

        char pipe_com[10];
        pipe_com[0] = 0;
        strcpy(pipe_com, "|");

        // puts(command_arr[0]);

        // for(i = 0; i < )

        /** Reading and Executing commands **/

        // printf("%s",total_arg[0]);

        /**
         * @brief
         *
         * echo --> To print whatever input given after echo. It has to ignore unnecessary spaces and tabs.
         *
         * pwd -->  To print the current working directory path
         *
         * cd  -->  To chanhe the current directory to required directory. It has several flags.
         *
         * ls  -->  To list the files and directories(may be hidden) from the current working directory.
         *
         * exit (or) quit --> It is a user friendly program for exiting the shell.
         *
         * discover --> Find all the directories and files of given appropriate flags
         */

        for (i = 0; i < num_comm; i++)
        {

            if (strstr(command_arr[i], pipe_com))
            {

                Pipe(command_arr[i]);
            }

            else
            {

                std_in = dup(STDIN_FILENO);
                std_out = dup(STDOUT_FILENO);

                execute(command_arr[i], commands, total_arg, i, num_args, num_comm); // this takes care of redirections and above functions
            }

            // printf("%s\n",command);
        }
    }

    end_history();

    return 0;
}