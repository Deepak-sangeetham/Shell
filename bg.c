#include "headers.h"

void bg(char command[]){


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

        kill(Process[index].process_id,SIGCONT);
    }

}