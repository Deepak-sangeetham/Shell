#include "headers.h"

/**
 * @brief pipe() function
 * 
 * @param command 
 * @return int 
 * 
 * Piping is a type of redirection such that processes are interconnected with each other.
 * It is used to combine two or more commands, such that output of one command acts as input
 * for another command.
 * 
 * These pipes are unidirectional. Data flows from left to right through the pipeline.
 * 
 * dup() --> Creates a copy of a file descriptor. Users lower numbered descriptor which is not yet used. Now both files has the same functionality.
 * dup2()--> It has the same functionality, rather than it decides its own file descriptor number.
 *      
 * with the above differences between those two function, we make advantages from it.
 * 
 */

int num_pipes(char command[])
{

    int pipes = 0;

    for (int i = 0; i < strlen(command); i++)
    {

        if (command[i] == '|')
        {

            pipes++;
        }
    }

    return pipes;
}

void Pipe(char command[])
{

    // find number of pipes

    int pipes_num = num_pipes(command);
    int i, cnt;

    // printf("%d\n",pipes_num);

    // for n pipes, we have n+1 commands
    // create a 2-D character array to store each of these commands

    char commands[pipes_num + 1][1000];

    // make each of these commands with space;

    for (i = 0; i < pipes_num + 1; i++)
    {

        commands[i][0] = 0;
    }

    // using strtoken function to find the commands

    char *delim, *word;

    delim = "|";
    word = strtok(command, delim);
    cnt = 0;

    while (word != NULL)
    {

        strcpy(commands[cnt], word);
        word = strtok(NULL, delim);
        cnt++;
    }

    // after performing above operations, we get commands as the all commands we have 
    // excluding pipes

    // making last character of each command to space

    for (i = 0; i < pipes_num + 1; i++)
    {

        if (i == 0)
        {

            commands[i][strlen(commands[i]) - 1] = 0;
        }

        else
        {

            char temp[1000]; // create a string
            temp[0] = 0;

            strcpy(temp, commands[i] + 1);
            strcpy(commands[i], temp); // changing current command with extra character

            if (i != pipes_num)
            {

                commands[i][strlen(commands[i]) - 1] = 0;
            }
        }
    }

    pipes_num++;

    // for(i = 0; i < pipes_num;i++){

    //     printf("%s ",commands[i]);
    // }

    // printf("\n");

    // when pipe() function is called, we get two file descriptors

    int fd[pipes_num][2];

    //printf("%d\n",pipes_num);



    for (i = 0; i < pipes_num; i++)
    {

        pipe(fd[i]);

        // implementing the commands which we did in execute function

        int fd_in, fd_out, num_args;
        char *total_args[1000];
        char original_command[1000];
        original_command[0] = 0;

        num_args = 0;

        char *delim1 = " ";
        char *first_word = strtok(commands[i], delim1);

        while (first_word != NULL)
        {
            total_args[num_args] = first_word;
            first_word = strtok(NULL, delim1);
            num_args++;
        }

        int ind1, ind2;
        // ind1 for <
        // ind2 for >,>>

        ind1 = -1;
        ind2 = -1;

        // if both pipes are redirections included then the following is implemented

        for (int j = 0; j < num_args; j++)
        {

            if (strcmp(total_args[j], ">") == 0)
            {

                ind2 = j;
            }

            else if (strcmp(total_args[j], ">>") == 0)
            {

                ind2 = j;
            }

            else if (strcmp(total_args[j], "<") == 0)
            {

                ind1 = j;
            }
        }

        //printf("%d %d %d\n",num_args,ind1,ind2);
        // extractin original command on one side of pipe

        if (ind1 > -1)
        {

            for (int j = 0; j < ind1; j++)
            {

                strcat(original_command, total_args[j]);

                if (j != ind1 - 1)
                { // if the argument is not he last one add space between those

                    strcat(original_command, delim1);
                }
            }
        }

        else if (ind2 > -1)
        {

            for (int j = 0; j < ind2; j++)
            {

                strcat(original_command, total_args[j]);

                if (j != ind2 - 1)
                { // if the argument is not he last one add space between those

                    strcat(original_command, delim1);
                }
            }
        }

        else
        {

            // concatenate all the arguments into a single string

            for (int j = 0; j < num_args; j++)
            {

                strcat(original_command, total_args[j]);

                if (j != num_args - 1)
                {

                    strcat(original_command, delim1);
                }
            }
        }

        //printf("%s\n",original_command);

        // opening file if redirection is pointed.

        if (ind1 > -1)
        {

            fd_in = open(total_args[ind1 + 1], O_RDONLY);

            if (fd_in < 0)
            {

                perror("open():"); // error handling
                exit(0);
            }
        }

        else if (i != 0)
        {

            fd_in = fd[i - 1][0]; // storing file descriptors
        }

        if (ind2 > -1)
        {

            if (strcmp(total_args[ind2 + 1], ">"))
            {

                fd_out = open(total_args[ind2 + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }

            else
            {

                fd_out = open(total_args[ind2 + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            }

            if(fd_out < 0){

                perror("open():"); // error handling
                exit(0);
            }
        }

        else if (i != pipes_num - 1)
        {

            fd_out = fd[i][1];
        }

        std_in = dup(STDIN_FILENO);
        std_out = dup(STDOUT_FILENO);

        //printf("%s\n",original_command);

        int fork_id;

        fork_id = fork();

        if (fork_id < 0)
        { // 

            perror("fork():"); // error handling
            exit(EXIT_SUCCESS);

            
        }

        // executing child process

        else if (fork_id == 0)
        {

            if (i != 0 || ind1 > -1)
            {

                int a;
                a = dup2(fd_in, 0);

                if (a >= 0)
                {

                    close(fd_in);
                }

                else
                {

                    perror("dup2():");
                    exit(0);
                }
            }

            if (i != pipes_num - 1 || ind2 > -1)
            {

                int b;
                b = dup2(fd_out, 1);

                if (b < 0)
                {

                    perror("dup2():");
                    exit(0);
                }
            }

            if (strcmp(total_args[0], "echo") == 0)
            {

                echo(original_command);
            }

            else if (strcmp(total_args[0], "pwd") == 0)
            {

                pwd();
            }

            else if (strcmp(total_args[0], "cd") == 0)
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

            else if (strcmp(total_args[0], "ls") == 0)
            {

                ls(original_command);
            }

            else if (strcmp(total_args[0], "pinfo") == 0)
            {

                pinfo(original_command);
            }
            

            else{

                
                fore_gp(original_command);
            }

            exit(0);
        }

        // executing parent process
        else{

            int stat;
            waitpid(fork_id, &stat, 0);  // If we have waitpid() pauses current process untill pid argument of a child who has changed.
            close(fd_out);

            int a, b;
            a = dup2(std_in, STDIN_FILENO);   
            b = dup2(std_out, STDOUT_FILENO);
        }
    }
}
