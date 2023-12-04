#include "headers.h"

/**
 * @brief 
 * 
 * @param pinfo  -->  prints process-related info of our shell program
 * 
 * @param pinfo <pid>  --> prints the process info of given pid
 */

void pinfo(char command[]){


    char p_id[1000];

    pid_t pid = getpid();

    // it is for pinfo <pid> getting pid number and converting into number

    if(strlen(command) != 5){

        pid = atoi(command+6);
    }

    sprintf(p_id,"%d",pid);

    char path1[1000],path2[1000];

    path1[0] = '\0';
    path2[0] = '\0';

    // concatenating required arguments for path1 and path2

    strcat(path1,"/proc/");
    strcat(path1,p_id);

    strcat(path2,path1);
    strcat(path2,"/");
    strcat(path2,"exe");
    
    strcat(path1,"/");
    strcat(path1,"stat");

    char buf[1000];

    //printf("%s\n",path1);
    //printf("%s\n",path2);

    // opening respected file in reading mode

    FILE * fp = fopen(path1,"r");

    if(fp){

        fgets(buf,1000,fp);

        //printf("buf:%s\n",buf);

        // buf has all the file information given by file pointer

        char *delim = " ";
        char * first_word = strtok(buf,delim);
        char * string[1000];


        // storing each command the string 2D character array

        int i = 0,n;

        while(first_word){

            string[i] = first_word;
            first_word = strtok(NULL,delim);
            i++;
        }



        char *status = string[2];

        if(strlen(command) == 5){

            if(strcmp(status,"R") == 0  || strcmp(status,"S") == 0){

                strcat(status,"+");
            }
        }

        // 22nd argument gives information about vir_mem
        char exepath[1000];
        char *vir_mem = string[22];

        if(readlink(path2,exepath,1000) == -1){

            perror("readlink():"); // error handling
        }

        else{

            
            int flag = 1;
            n = strlen(str);

            if(strlen(exepath) >= n){

                for(i = 0;i < strlen(str);i++){

                    if(exepath[i] != str[i]){

                        flag = 0;
                        break;
                    }
                }
            }

            else{

                n = 0;
            }


            if(!flag){

                n = 0;
            }

            printf("pid : %d\n",pid);
            printf("Process Status : {%s}\n",status);
            printf("memory : %s  {Virtual Memory}\n",vir_mem);
            printf("Executable Path : %s\n",exepath+n);
        }

    }

    else{

        perror("fopen():");   // error handling
    }

}