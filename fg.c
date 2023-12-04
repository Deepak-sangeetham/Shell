#include "headers.h"

/*
    Returns the running or stopprd background job corresponding to foreground, and chanegs state 
    to running. It gives error, if no job with given job number exists.
*/

void fg(char command[]){

    // sorting jobs

    sort_jobs();

    char job_com[10];
    char word[1000];

    job_com[0] =0;
    word[0] =0;

    strcpy(job_com,command+3);

    int job_no,pid;
    int index = -1,i;

    job_no = atoi(job_com);
    
    for(i = 0;i < 1000;i++){

        if(Process[i].flag == 1){

            if(Process[i].ordered_job == job_no){

                pid = Process[i].process_id;
                strcpy(word,Process[i].word);
                index = i;
                break;
            }
        }
    }

    if(index == -1){

        printf("Job number is Invalid.\n");
    }

    else{

        int stat;

        signal(SIGTTIN,SIG_IGN); // Ignore the input signal
        signal(SIGTTOU,SIG_IGN); // Ignore the output signal
        tcsetpgrp(STDIN_FILENO,pid);  // sets the process grp ID of foreground process

        kill(pid,SIGCONT); // send signal to a process.

        tcsetpgrp(STDIN_FILENO,getpgrp()); // Geth the process group id and set it to process group id
        signal(SIGTTIN,SIG_DFL); // Default action for input signal
        signal(SIGTTOU,SIG_DFL); // Default action for output signal

        waitpid(pid,&stat,WUNTRACED); // waits for termination of the specific chikd
        // whose process ID is equal to pid.
 
        Process[index].flag = 1;

        if(WIFSTOPPED(stat)){

            printf("%s with PID: %d is suspended.\n",word,pid);
            Process[index].flag = 0;
        }
    }
    
    return;



}