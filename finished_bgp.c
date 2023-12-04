#include "headers.h"

void Signal()
{

    int stat, pid, i;
    pid = waitpid(-1, &stat, WNOHANG | WUNTRACED); // returns immediatley if no child has exited

    char string[1000];
    string[0] = 0;

    if (pid > 0)
    { // wait for child whose process_id is equal to the value of pid

        if (WIFEXITED(stat) > 0)
        {

            for (i = 0; i < 1000; i++)
            {

                if (Process[i].process_id == pid && Process[i].flag == 1)
                {

                    Process[i].flag = 0;
                    strcpy(string, Process[i].word);
                    break;
                }
            }

            fprintf(stderr, "\n%s of pid %d exitted.\n", string, pid);
        }

        if (WIFSIGNALED(stat) > 0)
        {

            for (i = 0; i < 1000; i++)
            {

                if (Process[i].process_id == pid && Process[i].flag == 1)
                {

                    Process[i].flag = 0;
                    strcpy(string, Process[i].word);
                    break;
                }
            }

            fprintf(stderr, "\n%s of pid %d exitted abnormally.\n", string, pid);
        }
    }
}