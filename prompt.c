#include "headers.h"
#define Green(string) "\x1b[32m" string "\x1b[0m"
void displayRequirement(){

    char SystemName[100],UserName[100];                 // delcaring character arrays
    char str1[10000],str2[10000];

    UserName[0] = 0;


    // getting hostname, username and current working path using appropriate library functions

   int host =  gethostname(SystemName,sizeof(SystemName));
   //getlogin_r(UserName,sizeof(UserName));
   getcwd(str2,sizeof(str2));

    //printf("%s\n",UserName);

    uid_t uid = getuid();
    struct passwd* user_details = getpwuid(uid);

    if(user_details){

        strcpy(UserName,user_details->pw_name);
    }

    else{

        perror("getpwuid()");
    }

    // error handling
   if(host == -1){

        perror("gethostname():");
        exit(0);
   }

   // performing display requirement by analysing the main.c directory path and display.c directory path

   if(strcmp(str,str2) == 0){

        printf(Green("<%s@%s:~>"),UserName,SystemName);

   }

   else if(strcmp(str,str2) > 0){

        printf(Green("%s@%s:%s>"),UserName,SystemName,str2);
   }

   else{

        int size = strlen(str),size2 = strlen(str2),i = 0,flag = 0;

        while(size--){

            if(str[i] != str2[i]){

                printf(Green("<%s@%s:%s>"),UserName,SystemName,str2);
                flag = 1;
                break;
            }
        }

        if(flag == 0){

            for(i = 0; i < size2-size;i++){

                str1[i] = str2[size+1+i];
            }

            printf(Green("%s@%s:%s>"),UserName,SystemName,str1);
        }

   }

   //printf("\n");

   return;


}