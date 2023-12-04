#include "headers.h"


/**
 * @brief 
 * 
 * @param cd   --> change directory to home
 * @param cd ~  --> change directory to home
 * 
 * @param cd .. --> change directory to parent
 * 
 * @param cd .  --> Do nothing
 * 
 * @param cd -  --> Fluctuate between parent directory and current directory
 * 
 */



void cd(char* command)
{

    // if given command is just cd then change directory to home
    
    if(strcmp(command,"cd") == 0){
       // printf("%s",command);
       int x=chdir(str);           // changes directory to home
       if(x!=0)
       {
            printf("Unable to change directory\n") ;
            perror("chdir()") ;
       }
        if(cd_num>=2)
        {
            strcpy(word_last[0],word_last[1]) ;        // string on word_last[1] is stored to word_last[0] 
            strcpy(word_last[1],str) ;                 // home directory path is stored as string to word_last[1]
        }
        else if(cd_num==0)
        {
            strcpy(word_last[0],str) ;         // home directory path is stored as string to word_last[0]
        }
        else
        {
            strcpy(word_last[1],str) ;          // home directory path is stored as string to word_last[1]
        }
        cd_num++ ;   
    }

    // if flag after cd is . or .. then change directroy accrodingly

    else if(strcmp(command+3,"-")!=0&&strcmp(command+3,"~")!=0)
    {
        char* execute_command=command+3 ;    // now our execute_command = "." or " .."

        //printf("%s",execute_command);
        int x=chdir(execute_command) ;          // it changes directory accroding to flag
        if(x!=0)
        {
            printf("Unable to change Directory\n") ;    // error handling
            perror("chdir()") ;
        }        
        if(cd_num>=2)
        {
            strcpy(word_last[0],word_last[1]) ; //string on word_last[1] is stored to word_last[0] 
            getcwd(word_last[1],200) ;     // get current wroking directory path into word_last[1]
            if(word_last[1]==NULL)
            {
                printf("Unable to retrieve current working directory\n") ;
                perror("getcwd()") ;                
            }
        }
        else if(cd_num==0)
        {
            getcwd(word_last[0],200) ; // get current wroking directory path into word_last[0]
            if(word_last[0]==NULL)
            {
                printf("Unable to retrieve current working directory\n") ;
                perror("getcwd()") ;                
            }            
        }
        else
        {
            getcwd(word_last[1],200) ;// get current wroking directory path into word_last[1]
            if(word_last[1]==NULL)
            {
                printf("Unable to retrieve current working directory\n") ;
                perror("getcwd()") ;                
            }             
        }
        cd_num++ ;
    }

    // print the directory path and change directory to parent
    // cd _num should be greater than 2 to execute this operation perfectly
    else if(strcmp(command+3,"-")==0)
    {
        if(cd_num<2)
        {
            printf("OLDPWD not set\n") ;   
            return ;
        }
        int x=chdir(word_last[0]) ;   // according to the path string on word_last[0] it changes directory
        if(x!=0)
        {
            printf("Unable to change Directory\n") ;
            perror("chdir()") ;
        }
        char temp[200] ;
        temp[0]='\0' ;
        strcpy(temp,word_last[0]) ;
        strcpy(word_last[0],word_last[1]) ;   // swapping strings in word_last[1] and word_last[0]
        strcpy(word_last[1],temp) ;
        cd_num++ ;
    }

    // change directory to home
    else if(strcmp(command+3,"~")==0)
    {
       int x=chdir(str) ;       // changes directory to home
       if(x!=0) 
       {
            printf("Unable to change directory\n") ;
            perror("chdir()") ;
       }
        if(cd_num>=2)
        {
            strcpy(word_last[0],word_last[1]) ;   // string on word_last[1] is stored to word_last[0] 
            strcpy(word_last[1],str) ;           // path of home is stored to word_last[1] 
        }
        else if(cd_num==0)
        {
            strcpy(word_last[0],str) ;         
        }
        else
        {
            strcpy(word_last[1],str) ;          
        }
        cd_num++ ;       
    }
}