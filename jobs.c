#include "headers.h"

// Swapping function is used to sort processes

void Swap(struct process *a,struct process *b){

    struct process temp = *b;
    *b = *a;
    *a = temp;
}

// we are sorting jobs so that we are giving order of the job based on ordered jobs 

void sort_jobs(){

    int i,j;


    for(i = 0;i < 999;i++){

        for(j =0;j < 999-i;j++){

            if(Process[j].ordered_job  > Process[j+1].ordered_job){

                Swap(&Process[j],&Process[j+1]);

            }
        }
    }

    int cnt = 1;

    for(i = 0;i < 1000;i++){

        if(Process[i].flag){

            Process[i].ordered_job = cnt;
            cnt++;
        }
    }

    for(i = 0;i < 999;i++){

        for(j = 0;j < 999-i;j++){

            if(strcmp(Process[j].word,Process[j+1].word) > 0){

                Swap(&Process[j],&Process[j+1]);
            }
        }
    }
}

/*
    This command prints a list of currently running background processes spawned 
    by the shell in the alphabetical order of the command name, along with their job number,
    pid, and their state. Sometimes it also has to return if there is specification of flags.

*/

void jobs(char command[]){

    
    // Sort the jobs initially

    sort_jobs();

    int run_flag = 0;
    int stop_flag = 0;

    int i,num=1,cnt_args;

    // strstr function finds the first occurence of the substring in main string

    if(strstr(command,"-s")){

        stop_flag = 1;
    }

    if(strstr(command,"-r")){

        run_flag = 1;
    }

    char file[1000];
    char stat[1000];  // creating two strings and initialising to empty.
    stat[0] =0;
    file[0] =0;

    int x  =0;

    for(i = 0;i < 1000;i++){

        // if process exists

        if(Process[i].flag == 1){

            sprintf(file,"/proc/%d/stat",Process[i].process_id);
            FILE * fp = fopen(file,"r");  // opening file in reading mode

            if(fp){

                char buffer[1000];
                buffer[0]=0;

                // pasting the contetn on the file into string buffer

                fgets(buffer,1000,fp);
                fclose(fp);  // closing file

                // Tokenizing the who string with spaces and stroing it in a 2-D character array

                char *delim = " ";
                char * first_word = strtok(buffer,delim);
                char * args[1000];


                cnt_args = 0;

                while(first_word != NULL){

                    args[cnt_args] = first_word;
                    first_word = strtok(NULL,delim);
                    cnt_args++;

                }

                char *stat = args[2];   // 3rd character 

                if(strcmp(stat,"T") ==0){

                    strcpy(stat,"Stopped");
                }

                else{

                    strcpy(stat,"Running");
                }


                if(run_flag == 0 && stop_flag == 0){

                    printf("[%d] %s %s [%d]\n", Process[i].ordered_job,stat,Process[i].word,Process[i].process_id);  // Printing the job info if running and stopping flag is not encountered
                }

                else if(stop_flag == 1 && strcmp(stat,"Stopped") == 0){

                    printf("[%d] %s %s [%d]\n", Process[i].ordered_job,stat,Process[i].word,Process[i].process_id);  // Printing the job info if stopping flag is encountered
                }

                else if(run_flag == 1 && strcmp(stat,"Running") == 0){

                    printf("[%d] %s %s [%d]\n", Process[i].ordered_job,stat,Process[i].word,Process[i].process_id);  // Printing the job info if running flag is encountered
                }



            }

            else{

                perror("fopen():");
            }

            x++;

        }
    }

    if(x == 0){

        printf("No jobs are running currently.\n");
    }

    
    

}

