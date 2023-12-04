#include "headers.h"

void Recurse(char *Dir_name)
{

    struct dirent *dir;

    DIR *directory = opendir(Dir_name);

    strcat(Dir_name,"/");

    if (directory)
    {

        while (dir = readdir(directory))
        {

            if (dir->d_name[0] != '.')
            {

                struct stat test;

                stat(dir->d_name, &test);

                if (S_ISREG(test.st_mode) == 0)
                {
                    
                    strcat(Dir_name,dir->d_name);

                    Recurse(Dir_name);
                }

                else
                {


                    printf("%s\n", dir->d_name);
                }
            }
        }
    }

    else{

        perror("opendir():");
    }

    return;
}

void discover(char command[])
{

    if (strcmp(command, "discover") == 0 || strcmp(command, "discover .") == 0 || strcmp(command, "discover -d -f") == 0)
    {

        int flag = 1;

        if (strcmp(command + 9, ".") == 0 || strcmp(command, "discover") == 0)
        {

            flag = 0;
        }

        char path[1000];

        //getcwd(path,sizeof(path));

        struct dirent *dir;
        DIR *directory = opendir(".");
        strcat(path,"./");

       

        if (directory)
        {

            while ((dir = readdir(directory)))
            {

                if (flag || dir->d_name[0] != '.')
                {

                    struct stat test;

                    stat(dir->d_name, &test);

                    if (S_ISREG(test.st_mode) == 0)
                    {
                        strcat(path,dir->d_name);
                        Recurse(path);
                    }

                    else
                    {
                         printf("./");

                        printf("%s\n", dir->d_name);
                    }
                }
            }
        }

        else
        {

            perror("opendir():"); // error handling
        }
    }

    else if(strcmp(command + 9, "..") == 0){

        
        int flag = 0;
        struct dirent *dir;

        char temp_dir[1000];

        char *res = getcwd(temp_dir, 1000);

        // printf("%s\n",temp_dir);
        char path[1000];
        strcat(path,"./");


        if (res == NULL)
        {

            perror("getcwd():");
        }

        int x = chdir(".."); // changing directory to previous

        if (x)
        {

            perror("chdir():"); // error handling
        }

        DIR *directory = opendir(".");

         if (directory)
        {

            while ((dir = readdir(directory)))
            {

                if (flag || dir->d_name[0] != '.')
                {

                    struct stat test;

                    stat(dir->d_name, &test);

                    if (S_ISREG(test.st_mode) == 0)
                    {
                        strcat(path,dir->d_name);
                        Recurse(path);
                    }

                    else
                    {
                         printf("./");

                        printf("%s\n", dir->d_name);
                    }
                }
            }
        }

        else
        {

            perror("opendir():"); // error handling
        }

    }
}