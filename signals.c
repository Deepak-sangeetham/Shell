#include "headers.h"

void CTRL_Z(int sign){

    // it prints new line

    printf("\n");

}

void CTRL_D(int sign){

    // Quits from the current running shell

    exit(0);

}

void CTRL_C(int sign){

    pid_t pid = getpid();

    if(pid < 0){

        perror("getpid():");
    }

    if(pid != shell_id){

        return ;
    }

    else{

        if(curr_pid != -1){

            int x = kill(curr_pid,sign);

            if(x < 0){

                perror("kill():");
                return;
            }
        }

        else{

            printf("\n");
            displayRequirement();
            fflush(stdout);
        }
    }
}