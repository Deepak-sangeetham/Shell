#include "headers.h"


/**
 * @brief 
 * 
 * history function everytime opens the hist.txt file and helps us 
 * to copy last 10 arguments into 2-D character array. It opens whenever 
 * the program started
 * 
 */


void history(){    

   hist_ptr = 0;  // initialising number of pointers as 0 when program begins
   FILE *fp = NULL;  // creating a file pointer an dmaking it with null.



   fp = fopen("hist.txt","r");    // opening file hist.txt

   while(fgets(history_commands[hist_ptr],4096,fp)){

      history_commands[hist_ptr][strlen(history_commands[hist_ptr])-1] = 0;  // keeping last place as null instead of \n
      strcat(history_commands[hist_ptr],"\n");  // adding newline to each argument
      hist_ptr++;  //incrementing history pointer

      if(hist_ptr == 20){   // if 2-D character array size is reached, stop copying strings

        break;
      }
   }

   hist_ptr = hist_ptr%20;   // if hist_ptr == 20,re-initialsing hist_ptr = 0
   histcnt = hist_ptr;    // number of arguments into histcnt.

   fclose(fp);

   return ;
}

/**
 * @brief 
 * 
 * add_history() function adds the commands into 2-D character array
 */
void add_history(char command[]){

    
    if(strcmp(history_commands[(hist_ptr+19)%20],command) != 0){

        strcpy(history_commands[hist_ptr],command);
        
        //strcat(history_commands[hist_ptr],"\n");
        hist_ptr = (hist_ptr+1)%20;  // if histptr > 20 then re-initialisng to 20

        if(histcnt <= 19){

            histcnt++;
        }

    }

    return;

}

/**
 * @brief end_history()->this function writes over the last 20 files into the array.
 * 
 */

void end_history(){

    FILE *fptr;
    int i;
    fptr = fopen("hist.txt","w");

    for(i = 20;i > 0;i--){

        fputs(history_commands[(hist_ptr+20-i)%20],fptr);
    }

    fclose(fptr);
    return ;

}

/**
 * @brief 
 * 
 * show_history() function showls the last 10 arguments we have used. 
 * It also shows arguments we have used in last time program execution.
 * 
 */

void show_history(){

    int i,n;

    n = 10;
    
    for(i = n;i > 0;i--){

        printf("%s\n",history_commands[(hist_ptr + 20 -i)%20]);
    }

    return;
}