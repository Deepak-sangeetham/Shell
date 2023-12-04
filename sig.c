#include "headers.h"

/*
    Takes up job number of a runnign job and sends signal corresponding 
    to the signal number to that process. It throws an error if no job 
    with given number is not presented.

*/ 

void sig(char command[]){

    // signal command has 3 paramters of sig "<job_num> <sig_num>"
    char *args[3];
    char *delim = " ";
    char * first_word = strtok(command,delim);

    int arg_cnt = 0,i;

    // tokenizing the given command to get the 2nd and 3rd arguments

    while(first_word != NULL){

        args[arg_cnt] = first_word;
        first_word = strtok(NULL," ");
        arg_cnt++;
    }

    // finding the job number and signal number

    int job_no,sig_no;

    job_no = atoi(args[1]);
    sig_no = atoi(args[2]);

    sort_jobs();

    int index = -1;

    for(i = 0;i < 1000;i++){

        if(Process[i].flag == 1){

            if(Process[i].ordered_job == job_no){

                index = Process[i].process_id;
                break;
            }
        }
    }

    if(index == -1){

        printf("Job ID is Invalid\n");
    
    }

    else{

        kill(index,sig_no); // used to send a signal to the process
    }

    




}