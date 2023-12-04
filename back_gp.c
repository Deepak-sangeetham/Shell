#include "headers.h"

void back_gp(char command[]){

    char *list[1000];
    char *delim = " ";

    char * first_word = strtok(command,delim);
    int i=0;
    pid_t pid = getpid();

    while(first_word){

        if(strcmp(first_word,"&") == 0){
            break;
        }

        else{

            list[i] = first_word;
            i++;
            first_word = strtok(NULL,delim);

        }
    }

    list[i] = NULL;   //keeping last token as null
    int flag1 = 0;

    for(i = 0;i < 1000;i++){

        if(Process[i].flag == 0){

            flag1 = 1;
            break;
        }
    }

    if(flag1 == 0){

        printf("Count of background process exceeded 1000\n");
        exit(EXIT_SUCCESS);
    }

    int fork_id = fork();
    int x;

    if(fork_id == 0){

        if(execvp(list[0],list) != 0){

            perror("execvp():");    // error handling
        }
    }

    else{

        for(i = 0; i < 1000;i++){

            if(Process[i].flag == 0){

                Process[i].flag = 1;
                Process[i].process_id = fork_id;
                Process[i].ordered_job = job_num;
                strcpy(Process[i].word,list[0]);
                job_num++;
                break;
            }
        }

        printf("%d\n",fork_id);
    }
    
}