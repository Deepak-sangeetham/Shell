#include "headers.h"

void fore_gp(char command[])
{
   
    
    char *list[1000];
    char *delim = " ";
    char *first_word = strtok(command, delim); // dividing into tokens with spaces

    int i = 0;

    while (first_word)
    {
        /* code */
        // storing each token which is not considered as &(background process)
        if (strcmp(first_word, "&") != 0)
        {

            list[i] = first_word;
            first_word = strtok(NULL, delim);
            i++;
        }
    }

    list[i] = NULL;
    

    int fork_id = fork();


    if(fork_id == 0){

        if(execvp(list[0],list) != 0){

            perror("execvp():");  // error handling
        }
    }

    else{

        curr_pid = fork_id;
        printf("%d\n", fork_id);
        int stat;

        waitpid(fork_id,&stat,WUNTRACED); // blocks parent process until one of its children process has finisehd

        if(WIFSTOPPED(stat)){

            for(i = 0;i < 1000;i++){

                if(Process[i].flag == 0){

                    Process[i].flag = 1;
                    Process[i].ordered_job = job_num;
                    Process[i].process_id = fork_id;
                    job_num++;
                    strcpy(Process[i].word,list[0]);
                    break;
                }
            }

            return;
        }
    }

    
}