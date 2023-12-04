#include "headers.h"

#define Yellow(string) "\x1b[33m" string "\x1b[0m"
#define Green(string) "\x1b[32m" string "\x1b[0m"


/**
 * @brief
 *
 * @param ls   --> lists all files and directories in the directory
 *
 * @param ls . --> lists all files and directories in the directory
 *
 * @param ls -a --> lists all files and directories in the directory including hidden.
 *
 * @param ls ..  --> lists all files and directories in the directory in the parent directory
 *
 * @param ls ~   --> lists all files and directories in the home directory
 *
 * @param ls -a -l  --> lists all files and directories in the current directory as permission_modes,last modified date and time
 *
 * @param ls -la (or) ls -al  --> lists all files and directories in the current directory as permission_modes,last modified date and time
 *
 * @param ls <dir_name>  --> lists all files and directories in the given directory
 *
 * @param ls <file_name>  --> lists the same file with an error message as it is not as directory(it is a file).
 *
 * @param ls <flags> <dir_name|file_name> --> lists files/directories accordingly to the flags
 *
 */

/**
 * @brief 
 * 
 *          green --> for executables
 *          yellow --> directoires
 */

void ls(char command[])
{

    // printf("%s\n",command);

    // listing the files and directories(may be hidden) int the current working directory

    if (strcmp(command, "ls") == 0 || strcmp(command, "ls .") == 0 || strcmp(command, "ls -a") == 0)
    {

        int flag = 1;

        if (strcmp(command + 3, ".") == 0 || strcmp(command, "ls") == 0)
        {

            flag = 0;
        }

        struct dirent *dir;
        DIR *directory = opendir("."); // used to open a directory and to return a pointer on this directory

        if (directory)
        {

            while ((dir = readdir(directory))) // returns a pointer to a structure representing the directory entry at the current position in the directory stream specified by the argument dirp, and positions the directory stream at the next entry. It returns a null pointer upon reaching the end of the directory stream.
            {

                if (flag == 1 || dir->d_name[0] != '.')
                {

                    struct stat test;

                    stat(dir->d_name, &test);

                    if (S_ISREG(test.st_mode) == 0)
                    {

                        printf(Yellow("%s\n"), dir->d_name);
                    }

                    else if (stat(dir->d_name, &test) == 0 && test.st_mode & S_IXUSR)
                    {

                        printf(Green("%s\n"), dir->d_name);
                    }

                    else
                    {

                        printf("%s\n", dir->d_name);
                    }

                    // printf("%s\n", dir->d_name);
                }
            }
        }

        else
        {

            perror("Opendir():"); // error handling
        }
    }

    // listing directories and files in the parent driectory

    else if (strcmp(command + 3, "..") == 0)
    {

        int flag = 0;
        struct dirent *dir;

        char temp_dir[1000];

        char *res = getcwd(temp_dir, 1000);

        // printf("%s\n",temp_dir);

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

            while ((dir = readdir(directory))) // returns a pointer to a structure representing the directory entry at the current position in the directory stream specified by the argument dirp, and positions the directory stream at the next entry. It returns a null pointer upon reaching the end of the directory stream.
            {

                if (flag == 1 || dir->d_name[0] != '.')
                {

                    struct stat test;

                    stat(dir->d_name, &test);

                    if (S_ISREG(test.st_mode) == 0)
                    {

                        printf(Yellow("%s\n"), dir->d_name);
                    }

                    else if (stat(dir->d_name, &test) == 0 && test.st_mode & S_IXUSR)
                    {

                        printf(Green("%s\n"), dir->d_name);
                    }

                    else
                    {

                        printf("%s\n", dir->d_name);
                    }
                }
            }
        }

        else
        {

            perror("opendir():");
        }

        int change = chdir(temp_dir);

        if (change)
        {

            perror("chdir():");
        }
    }

    // listing files and directories int he home directory
    else if (strcmp(command + 3, "~") == 0)
    {

        char *u_name = (char *)malloc(1000 * sizeof(char));

        uid_t u_id = getuid(); // getting user id

        struct passwd *u_details = getpwuid(u_id); // searches the user database for an entry with a matching uid.

        if (u_details)
        {

            u_name = u_details->pw_name;
            // printf("%s\n",u_name);
        }

        else
        {

            perror("getpwuid():");
        }

        int flag = 0;

        struct dirent *dir;

        char home[1000] = "/home/";
        strcat(home, u_name);
        DIR *directory = opendir(home); // opening home directory

        // printf("%s\n",home);

        if (directory)
        {

            while ((dir = readdir(directory))) // returns a pointer to a structure representing the directory entry at the current position in the directory stream specified by the argument dirp, and positions the directory stream at the next entry. It returns a null pointer upon reaching the end of the directory stream.
            {

                if (flag == 1 || dir->d_name[0] != '.')
                {

                    struct stat test;

                    stat(dir->d_name, &test);

                    if (S_ISREG(test.st_mode) == 0)
                    {

                        printf(Yellow("%s\n"), dir->d_name);
                    }

                    else if (stat(dir->d_name, &test) == 0 && test.st_mode & S_IXUSR)
                    {

                        printf(Green("%s\n"), dir->d_name);
                    }

                    else
                    {

                        printf("%s\n", dir->d_name);
                    }

                    // printf("%s\n", dir->d_name);
                }
            }
        }

        else
        {

            perror("opendir()");
        }
    }

    else
    {

        char *perms_map[8]; // these permissions are for ls -l,ls -a,ls -al,ls -la

        perms_map[0] = "---";
        perms_map[1] = "--x";
        perms_map[2] = "-w-";
        perms_map[3] = "-wx";
        perms_map[4] = "r--"; // these are declaGreen because of performing permissions on files
        perms_map[5] = "r-x";
        perms_map[6] = "rw-";
        perms_map[7] = "rwx";

        char *months[12]; // these are declaGreen becasue of showing months of files

        months[0] = "Jan";
        months[1] = "Feb";
        months[2] = "Mar";
        months[3] = "Apr";
        months[4] = "May";
        months[5] = "Jun";
        months[6] = "Jul";
        months[7] = "Aug";
        months[8] = "Sep";
        months[9] = "Oct";
        months[10] = "Nov";
        months[11] = "Dec";

        char *flags[4]; // this is due to check whether flags are -a, -l, -al,-la
        char *dirs[1000];
        char *delim = " "; // read command is divided into tokens based on spacing
        char *first_word;

        int dirs_num = 0;
        int flags_num = 0; // initialising # flags and # directories to 0

        first_word = strtok(command + 3, delim);

        // printf("%s\n",first_word);
        //  declaring 4 boolean flages

        int f[4] = {0}; // this is an array just to test and modify flags

        while (first_word)
        {

            if (strcmp(first_word, "-a") == 0 && f[0] == 0)
            {

                flags[flags_num] = "-a";
                f[0] = 1;
                flags_num++;
            }

            else if (strcmp(first_word, "-l") == 0 && f[1] == 0)
            {

                flags[flags_num] = "-l";
                f[1] = 1;
                flags_num++;
            }

            else if (strcmp(first_word, "-al") == 0 && f[2] == 0)
            {

                flags[flags_num] = "-al";
                f[2] = 1;
                flags_num++;
            }

            else if (strcmp(first_word, "-la") == 0 && f[3] == 0)
            {

                flags[flags_num] = "-la";
                f[3] = 1;
                flags_num++;
            }

            else if (strcmp(first_word, "-la") != 0 && strcmp(first_word, "-al") != 0 && strcmp(first_word, "-l") != 0 && strcmp(first_word, "-a") != 0)
            {

                dirs[dirs_num] = first_word; // if the given tokens are not flags then they are stoGreen into directories array
                dirs_num++;
            }

            first_word = strtok(NULL, delim);
            // printf("%s\n",first_word);
        }

        // printf("%d\n",flags_num);

        // if we a single flag or none
        if (flags_num <= 1)
        {

            // if it there is no flages then it denotes --> 1. given command is ls (or) 2. given command is ls <dir_name>|<file_name>
            if (flags_num == 0 || strcmp(flags[0], "-a") == 0)
            {

                int i, j;
                // if we don't have directories then directly print the files/directories in the current folder
                if (dirs_num == 0)
                {

                    // it just prints the list of files int he current directory

                    int flag = 1;

                    if (flags_num == 0)
                    {

                        flag = 0;
                    }

                    struct dirent *dir;
                    DIR *directory = opendir(".");

                    if (directory)
                    {

                        while ((dir = readdir(directory)))
                        {

                            if (flag || dir->d_name[0] != '.')
                            {

                                // printf("%s\n", dir->d_name);

                                struct stat test;

                                stat(dir->d_name, &test);

                                if (S_ISREG(test.st_mode) == 0)
                                {

                                    printf(Yellow("%s\n"), dir->d_name);
                                }

                                else if (stat(dir->d_name, &test) == 0 && test.st_mode & S_IXUSR)
                                {

                                    printf(Green("%s\n"), dir->d_name);
                                }

                                else
                                {

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

                else
                {
                    // iterating throughout the given directories and we print each directory name and contents inside it.
                    for (i = 0; i < dirs_num; i++)
                    {

                        int cnt = 0, flag = 1;
                        char files_list[1000][1000]; // creating a list of files all over the directory

                        if (flags_num == 0)
                        {

                            flag = 0;
                        }

                        struct dirent *dir;

                        DIR *directory = opendir(dirs[i]);

                        printf("%s\n", dirs[i]);
                        // storing all directories and files in the respected directory
                        if (directory)
                        {

                            while ((dir = readdir(directory)))
                            {

                                if (flag || dir->d_name[0] != '.')
                                {

                                    struct stat test1;
                                    stat(dir->d_name,&test1);
                                    if(S_ISREG(test1.st_mode) == 1){

                                        printf(Yellow("%s\n"),dir->d_name);
                                    }

                                    else if(stat(dir->d_name, &test1) == 0 && test1.st_mode & S_IXUSR){

                                        printf(Green("%s\n"), dir->d_name);
                                    }

                                    else{

                                        printf("%s\n",dir->d_name);
                                    }

                                    
                                }
                            }
                        }

                        else
                        {

                            perror("opendir():"); // error handling
                        }

                        // printf("%s\n", dirs[i]); // printing the respected directory and printing files and driectories present in respected directory

                        // //printf("not\n");
                        // for (j = 0; j < cnt; j++)
                        // {

                        //     struct stat test;
                        //     struct stat test1;

                        //     int dee = stat(files_list[j], &test);

                        //     if (S_ISREG(test.st_mode) == 0)
                        //     {

                        //         printf(Yellow("%s\n"), files_list[j]);
                        //     }

                        //     else if (stat(files_list[j],&test1) == 0 && test1.st_mode & S_IXUSR)
                        //     {

                        //         printf(Green("%s\n"), files_list[j]);
                        //     }

                        //     else
                        //     {

                        //         printf("%s\n", files_list[j]);
                        //     }

                        //      //printf("%s\n", files_list[j]);
                        // }
                    }
                }
            }

            // if we have flags == 1

            else
            {

                int i, j;

                // printf("%d\n",flags_num);

                // if there is no directories then just print the list according to the flag such that,file permissions,last modified date and time
                if (dirs_num == 0)
                {

                    dirs_num = 1; // initialise number of directories with 1
                    char dirs[1][1000];
                    dirs[0][0] = '\0';

                    char path[1000];

                    if (getcwd(path, 1000) == NULL)
                    {

                        perror("getcwd():"); // error handling
                    }

                    strcpy(dirs[0], path);

                    for (i = 0; i < dirs_num; i++)
                    {

                        char files_list[1000][1000]; // crating a 2D array which stores list of files/directories
                        char file_names[1000][1000]; // it stores the names of those files

                        int cnt1 = 0, cnt2 = 0, flag = 1;

                        for (j = 0; j < 1000; j++)
                        {

                            strcpy(files_list[j], dirs[i]); // making each file as "directory_name/""
                            strcat(files_list[j], "/");
                        }

                        if (strcmp(flags[0], "-l") == 0)
                        {

                            flag = 0;
                        }

                        // printf("%d\n",flag);
                        struct dirent *dir;
                        DIR *directory = opendir(dirs[i]);

                        if (directory)
                        {

                            while ((dir = readdir(directory)))
                            {

                                if (flag || dir->d_name[0] != '.')
                                {

                                    strcat(files_list[cnt1], dir->d_name); // making file name as "directory_name/file_name"
                                    strcpy(file_names[cnt2], dir->d_name); // copying into file name
                                    cnt1++;
                                    cnt2++;
                                }
                            }
                        }

                        else
                        {

                            perror("opendir():"); // error handling
                        }

                        // perimissions handling

                        char perms[cnt1][1000];

                        // these are for showing permissions on respected file, day and hour
                        char *owner[cnt1];
                        char *group[cnt1];
                        char *month[cnt1];
                        char day[cnt1][3];
                        char hr[cnt1][6];

                        // these are to store number of links,size and day
                        int links[cnt1];
                        int size[cnt1];
                        int Day[cnt1];

                        int total = 0; // counts the blocks

                        // printf("t:%d\n",total);

                        // printf("cnt1 :%d\n",cnt1);

                        for (j = 0; j < cnt1; j++)
                        {

                            struct stat file;

                            if (stat(files_list[j], &file) < 0)
                            {

                                perror("stat():"); // error handling
                            }

                            else
                            {

                                total = total + file.st_blocks;

                                int a, b, p;
                                int bits[3];

                                a = file.st_mode;
                                b = 0;
                                p = 1;

                                // converting given octal number to decimal number

                                // printf("a:%d\n",a);
                                while (a != 0)
                                {

                                    b += (a % 8) * p;
                                    a /= 8;
                                    p *= 10;
                                }
                                // printf("a:%d\n",a);
                                //  storing each digit of decimal number into 3 length array

                                for (int k = 2; k >= 0; k--)
                                {

                                    bits[k] = b % 10;
                                    b /= 10;
                                }

                                bool test = S_ISDIR(file.st_mode); // tests whether given input is directory or not

                                if (test)
                                {

                                    perms[j][0] = 'd';
                                    perms[j][1] = '\0';
                                }

                                else
                                {

                                    perms[j][0] = '-';
                                    perms[j][1] = '\0';
                                }

                                // getting permissions of files

                                strcat(perms[j], perms_map[bits[0]]);
                                strcat(perms[j], perms_map[bits[1]]);
                                strcat(perms[j], perms_map[bits[2]]);

                                links[j] = file.st_nlink; // getting number of links of given file

                                // getting owner and group names of files

                                uid_t o_id = file.st_uid;
                                uid_t grp_id = file.st_gid;

                                struct passwd *o_details = getpwuid(o_id);     // taking owner deatils
                                struct passwd *grp_details = getpwuid(grp_id); // getting group details

                                // error handling for owner details
                                if (o_details)
                                {

                                    owner[j] = o_details->pw_name;
                                }

                                else
                                {

                                    perror("getpwuid():");
                                }

                                // error handling for group details

                                if (grp_details)
                                {

                                    group[j] = grp_details->pw_name;
                                }

                                else
                                {

                                    perror("getpwuid():");
                                }

                                size[j] = file.st_size; // getting size of file

                                // getting last modified time of files

                                char t[1000];

                                // strftime is used to show the time, date and month

                                strftime(t, 100, "%d/%m/%Y  %H:%M:%S", localtime(&file.st_mtime)); // storing time date and month in t

                                // char d1 = t[0];
                                // char d2 = t[1];

                                /*

                                    t should be like this --> dd/mm/yyyy hh:mm
                                */

                                for (int k = 0; k < 2; k++)
                                {

                                    day[j][k] = t[k];
                                }

                                day[j][2] = 0;

                                Day[j] = atoi(day[j]); // changing string into integer and getting the day

                                int m1, m2;

                                m1 = t[3] - '0';
                                m2 = t[4] - '0';
                                month[j] = months[m2 + (10 * m1) - 1]; // getting the month

                                for (int k = 0; k < 5; k++)
                                {

                                    hr[j][k] = t[11 + k]; // getting hour
                                }

                                hr[j][5] = '\0';
                            }
                        }

                        // printf("total: %d\n",total);

                        int max_size = -1;

                        for (j = 0; j < cnt1; j++)
                        {

                            if (size[j] > max_size)
                            {

                                max_size = size[j];
                            }
                        }

                        int N = 0;
                        // N is for finding number of digits in max_size
                        while (max_size > 0)
                        {

                            max_size /= 10;
                            N++;
                        }

                        if (N == 0)
                        {

                            N = 1;
                        }

                        printf("total files : %d\n", total / 2); // Displaying number of files

                        // Displaying files/directories permissions last modified day,date and time and name

                        for (j = 0; j < cnt1; j++)
                        {

                            printf("%s %d %s %s %*d %s %2d %s ", perms[j], links[j], owner[j], group[j], N, size[j], month[j], Day[j], hr[j]);

                            struct stat test;

                            stat(file_names[j], &test);

                            if (S_ISREG(test.st_mode) == 0)
                            {

                                printf(Yellow("%s\n"), file_names[j]);
                            }

                            else if (stat(file_names[j], &test) == 0 && test.st_mode & S_IXUSR)
                            {

                                printf(Green("%s\n"), file_names[j]);
                            }

                            else
                            {

                                printf("%s\n", file_names[j]);
                            }
                        }
                    }
                }

                else
                {

                    // iterating throughout all the directories listed from the input command

                    // if we have directories then printing each directory name and printing files/directores accordingly to the flags

                    for (i = 0; i < dirs_num; i++)
                    {

                        char files_list[1000][1000]; // crating a 2D array which stores list of files/directories
                        char file_names[1000][1000]; // it stores the names of those files

                        int cnt1 = 0, cnt2 = 0, flag = 1;

                        for (j = 0; j < 1000; j++)
                        {

                            strcpy(files_list[j], dirs[i]); // making each file as "directory_name/""
                            strcat(files_list[j], "/");
                        }

                        if (strcmp(flags[0], "-l") == 0)
                        {

                            flag = 0;
                        }

                        struct dirent *dir;
                        DIR *directory = opendir(dirs[i]);

                        if (directory)
                        {

                            while ((dir = readdir(directory)))
                            {

                                if (flag || dir->d_name[0] != '.')
                                {

                                    strcat(files_list[cnt1], dir->d_name); // making file name as "directory_name/file_name"
                                    strcpy(file_names[cnt2], dir->d_name); // copying into file name
                                    cnt1++;
                                    cnt2++;
                                }
                            }
                        }

                        else
                        {

                            perror("opendir():"); // error handling
                        }

                        // perimissions handling

                        char perms[cnt1][1000];

                        // these are for showing permissions on respected file, day and hour
                        char *owner[cnt1];
                        char *group[cnt1];
                        char *month[cnt1];
                        char day[cnt1][3];
                        char hr[cnt1][6];

                        // these are to store number of links,size and day
                        int links[cnt1];
                        int size[cnt1];
                        int Day[cnt1];

                        int total = 0; // counts the blocks

                        for (j = 0; j < cnt1; j++)
                        {

                            struct stat file;

                            if (stat(files_list[j], &file) < 0)
                            {

                                perror("stat():"); // error handling
                            }

                            else
                            {

                                total = total + file.st_blocks;

                                int a, b, p;
                                int bits[3];

                                a = file.st_mode;
                                b = 0;
                                p = 1;

                                // converting given octal number to decimal number

                                while (a != 0)
                                {

                                    b += (a % 8) * p;
                                    a = a / 8;
                                    p *= 10;
                                }

                                // storing each digit of decimal number into 3 length array

                                for (int k = 2; k >= 0; k--)
                                {

                                    bits[k] = b % 10;
                                    b /= 10;
                                }

                                bool test = S_ISDIR(file.st_mode); // tests whether given input is directory or not

                                if (test)
                                {

                                    perms[j][0] = 'd';
                                    perms[j][1] = '\0';
                                }

                                else
                                {

                                    perms[j][0] = '-';
                                    perms[j][1] = '\0';
                                }

                                // getting permissions of files

                                strcat(perms[j], perms_map[bits[0]]);
                                strcat(perms[j], perms_map[bits[1]]);
                                strcat(perms[j], perms_map[bits[2]]);

                                links[j] = file.st_nlink; // getting number of links of given file

                                // getting owner and group names of files

                                uid_t o_id = file.st_uid;
                                uid_t grp_id = file.st_gid;

                                struct passwd *o_details = getpwuid(o_id);     // taking owner deatils
                                struct passwd *grp_details = getpwuid(grp_id); // getting group details

                                // error handling for owner details
                                if (o_details)
                                {

                                    owner[j] = o_details->pw_name;
                                }

                                else
                                {

                                    perror("getpwuid():"); // error handling
                                }

                                // error handling for group details

                                if (grp_details)
                                {

                                    group[j] = grp_details->pw_name;
                                }

                                else
                                {

                                    perror("getpwuid():"); // error handling
                                }

                                size[j] = file.st_size; // getting size of file

                                // getting last modified time of files

                                char t[1000];

                                // strftime is used to show the time, date and month

                                strftime(t, 100, "%d/%m/%Y  %H:%M:%S", localtime(&file.st_mtime)); // storing time date and month in t

                                // char d1 = t[0];
                                // char d2 = t[1];

                                /*

                                    t should be like this --> dd/mm/yyyy hh:mm
                                */

                                for (int k = 0; k < 2; k++)
                                {

                                    day[j][k] = t[k];
                                }

                                day[j][2] = 0;

                                Day[j] = atoi(day[j]); // changing string into integer and getting the day

                                int m1, m2;

                                m1 = t[3] - '0';
                                m2 = t[4] - '0';
                                month[j] = months[m2 + (10 * m1) - 1]; // getting the month

                                for (int k = 0; k < 5; k++)
                                {

                                    hr[j][k] = t[11 + k]; // getting hour
                                }

                                hr[j][5] = 0;
                            }
                        }

                        int max_size = -1;

                        for (j = 0; j < cnt1; j++)
                        {

                            if (size[j] > max_size)
                            {

                                max_size = size[j];
                            }
                        }

                        int N = 0;
                        // N is for finding number of digits in max_size
                        while (max_size > 0)
                        {

                            max_size /= 10;
                            N++;
                        }

                        if (N == 0)
                        {

                            N = 1;
                        }

                        printf("total files : %d\n", total / 2); // Displaying number of files

                        // Displaying files/directories permissions last modified day,date and time and name

                        for (j = 0; j < cnt1; j++)
                        {

                            // printf("%s %d %s %s %*d %s %2d %s %s\n", perms[j], links[j], owner[j], group[j], N, size[j], month[j], Day[j], hr[j], file_names[j]);

                            printf("%s %d %s %s %*d %s %2d %s ", perms[j], links[j], owner[j], group[j], N, size[j], month[j], Day[j], hr[j]);

                            struct stat test;

                            stat(file_names[j], &test);

                            if (S_ISREG(test.st_mode) == 0)
                            {

                                printf(Yellow("%s\n"), file_names[j]);
                            }

                            else if (stat(file_names[j], &test) == 0 && test.st_mode & S_IXUSR)
                            {

                                printf(Green("%s\n"), file_names[j]);
                            }

                            else
                            {

                                printf("%s\n", file_names[j]);
                            }
                        }
                    }
                }
            }
        }

        else
        {

            // if flags_num > 1, we do the same thing when we have flags == 1 jsut printing files in the number of directories accordingly

            int i, j;

            if (dirs_num == 0)
            {

                dirs_num = 1; // initialise number of directories with 1
                char dirs[1][1000];
                dirs[0][0] = 0;

                char path[1000];

                if (getcwd(path, 1000) == NULL)
                {

                    perror("getcwd():"); // error handling
                }

                strcpy(dirs[0], path);

                for (i = 0; i < dirs_num; i++)
                {

                    char files_list[1000][1000]; // crating a 2D array which stores list of files/directories
                    char file_names[1000][1000]; // it stores the names of those files

                    int cnt1 = 0, cnt2 = 0, flag = 1;

                    for (j = 0; j < 1000; j++)
                    {

                        strcpy(files_list[j], dirs[i]); // making each file as "directory_name/""
                        strcat(files_list[j], "/");
                    }

                    struct dirent *dir;
                    DIR *directory = opendir(dirs[i]);

                    if (directory)
                    {

                        while ((dir = readdir(directory)))
                        {

                            if (flag || dir->d_name[0] != '.')
                            {

                                strcat(files_list[cnt1], dir->d_name); // making file name as "directory_name/file_name"
                                strcpy(file_names[cnt2], dir->d_name); // copying into file name
                                cnt1++;
                                cnt2++;
                            }
                        }
                    }

                    else
                    {

                        perror("opendir():"); // error handling
                    }

                    // perimissions handling

                    char perms[cnt1][1000];

                    // these are for showing permissions on respected file, day and hour
                    char *owner[cnt1];
                    char *group[cnt1];
                    char *month[cnt1];
                    char day[cnt1][3];
                    char hr[cnt1][6];

                    // these are to store number of links,size and day
                    int links[cnt1];
                    int size[cnt1];
                    int Day[cnt1];

                    int total = 0; // counts the blocks

                    for (j = 0; j < cnt1; j++)
                    {

                        struct stat file;

                        if (stat(files_list[j], &file) < 0)
                        {

                            perror("stat():"); // error handling
                        }

                        else
                        {

                            total = total + file.st_blocks;

                            int a, b, p;
                            int bits[3];

                            a = file.st_mode;
                            b = 0;
                            p = 1;

                            // converting given octal number to decimal number

                            while (a != 0)
                            {

                                b += (a % 8) * p;
                                a = a / 8;
                                p *= 10;
                            }

                            // storing each digit of decimal number into 3 length array

                            for (int k = 2; k >= 0; k--)
                            {

                                bits[k] = b % 10;
                                b /= 10;
                            }

                            bool test = S_ISDIR(file.st_mode); // tests whether given input is directory or not

                            if (test)
                            {

                                perms[j][0] = 'd';
                                perms[j][1] = '\0';
                            }

                            else
                            {

                                perms[j][0] = '-';
                                perms[j][1] = '\0';
                            }

                            // getting permissions of files

                            strcat(perms[j], perms_map[bits[0]]);
                            strcat(perms[j], perms_map[bits[1]]);
                            strcat(perms[j], perms_map[bits[2]]);

                            links[j] = file.st_nlink; // getting number of links of given file

                            // getting owner and group names of files

                            uid_t o_id = file.st_uid;
                            uid_t grp_id = file.st_gid;

                            struct passwd *o_details = getpwuid(o_id);     // taking owner deatils
                            struct passwd *grp_details = getpwuid(grp_id); // getting group details

                            // error handling for owner details
                            if (o_details)
                            {

                                owner[j] = o_details->pw_name;
                            }

                            else
                            {

                                perror("getpwuid():");
                            }

                            // error handling for group details

                            if (grp_details)
                            {

                                group[j] = grp_details->pw_name;
                            }

                            size[j] = file.st_size; // getting size of file

                            // getting last modified time of files

                            char t[1000];

                            // strftime is used to show the time, date and month

                            strftime(t, 100, "%d/%m/%Y  %H:%M:%S", localtime(&file.st_mtime)); // storing time date and month in t

                            // char d1 = t[0];
                            // char d2 = t[1];

                            /*

                                t should be like this --> dd/mm/yyyy hh:mm
                            */

                            for (int k = 0; k < 2; k++)
                            {

                                day[j][k] = t[k];
                            }

                            day[j][2] = 0;

                            Day[j] = atoi(day[j]); // changing string into integer and getting the day

                            int m1, m2;

                            m1 = t[3] - '0';
                            m2 = t[4] - '0';
                            month[j] = months[m2 + (10 * m1) - 1]; // getting the month

                            for (int k = 0; k < 5; k++)
                            {

                                hr[j][k] = t[11 + k]; // getting hour
                            }

                            hr[j][5] = 0;
                        }
                    }

                    int max_size = -1;

                    for (j = 0; j < cnt1; j++)
                    {

                        if (size[j] > max_size)
                        {

                            max_size = size[j];
                        }
                    }

                    int N = 0;
                    // N is for finding number of digits in max_size
                    while (max_size > 0)
                    {

                        max_size /= 10;
                        N++;
                    }

                    if (N == 0)
                    {

                        N = 1;
                    }

                    printf("total files : %d\n", total / 2); // Displaying number of files

                    // Displaying files/directories permissions last modified day,date and time and name

                    for (j = 0; j < cnt1; j++)
                    {

                        // printf("%s %d %s %s %*d %s %2d %s %s\n", perms[j], links[j], owner[j], group[j], N, size[j], month[j], Day[j], hr[j], file_names[j]);

                        printf("%s %d %s %s %*d %s %2d %s ", perms[j], links[j], owner[j], group[j], N, size[j], month[j], Day[j], hr[j]);

                        struct stat test;

                        stat(file_names[j], &test);

                        if (S_ISREG(test.st_mode) == 0)
                        {

                            printf(Yellow("%s\n"), file_names[j]);
                        }

                        else if (stat(file_names[j], &test) == 0 && test.st_mode & S_IXUSR)
                        {

                            printf(Green("%s\n"), file_names[j]);
                        }

                        else
                        {

                            printf("%s\n", file_names[j]);
                        }
                    }
                }
            }

            else
            {

                // iterating throughout all the directories listed from the input command

                for (i = 0; i < dirs_num; i++)
                {

                    char files_list[1000][1000]; // crating a 2D array which stores list of files/directories
                    char file_names[1000][1000]; // it stores the names of those files

                    int cnt1 = 0, cnt2 = 0, flag = 1;

                    for (j = 0; j < 1000; j++)
                    {

                        strcpy(files_list[j], dirs[i]); // making each file as "directory_name/""
                        strcat(files_list[j], "/");
                    }

                    struct dirent *dir;
                    DIR *directory = opendir(dirs[i]);

                    if (directory)
                    {

                        while ((dir = readdir(directory)))
                        {

                            if (flag || dir->d_name[0] != '.')
                            {

                                strcat(files_list[cnt1], dir->d_name); // making file name as "directory_name/file_name"
                                strcpy(file_names[cnt2], dir->d_name); // copying into file name
                                cnt1++;
                                cnt2++;
                            }
                        }
                    }

                    else
                    {

                        perror("opendir():"); // error handling
                    }

                    // perimissions handling

                    char perms[cnt1][1000];

                    // these are for showing permissions on respected file, day and hour
                    char *owner[cnt1];
                    char *group[cnt1];
                    char *month[cnt1];
                    char day[cnt1][3];
                    char hr[cnt1][6];

                    // these are to store number of links,size and day
                    int links[cnt1];
                    int size[cnt1];
                    int Day[cnt1];

                    int total = 0; // counts the blocks

                    for (j = 0; j < cnt1; j++)
                    {

                        struct stat file;

                        if (stat(files_list[j], &file) < 0)
                        {

                            perror("stat():"); // error handling
                        }

                        else
                        {

                            total = total + file.st_blocks;

                            int a, b, p;
                            int bits[3];

                            a = file.st_mode;
                            b = 0;
                            p = 1;

                            // converting given octal number to decimal number

                            while (a != 0)
                            {

                                b += (a % 8) * p;
                                a = a / 8;
                                p *= 10;
                            }

                            // storing each digit of decimal number into 3 length array

                            for (int k = 2; k >= 0; k--)
                            {

                                bits[k] = b % 10;
                                b /= 10;
                            }

                            bool test = S_ISDIR(file.st_mode); // tests whether given input is directory or not

                            if (test)
                            {

                                perms[j][0] = 'd';
                                perms[j][1] = '\0';
                            }

                            else
                            {

                                perms[j][0] = '-';
                                perms[j][1] = '\0';
                            }

                            // getting permissions of files

                            strcat(perms[j], perms_map[bits[0]]);
                            strcat(perms[j], perms_map[bits[1]]);
                            strcat(perms[j], perms_map[bits[2]]);

                            links[j] = file.st_nlink; // getting number of links of given file

                            // getting owner and group names of files

                            uid_t o_id = file.st_uid;
                            uid_t grp_id = file.st_gid;

                            struct passwd *o_details = getpwuid(o_id);     // taking owner deatils
                            struct passwd *grp_details = getpwuid(grp_id); // getting group details

                            // error handling for owner details
                            if (o_details)
                            {

                                owner[j] = o_details->pw_name;
                            }

                            else
                            {

                                perror("getpwuid():");
                            }

                            // error handling for group details

                            if (grp_details)
                            {

                                group[j] = grp_details->pw_name;
                            }

                            size[j] = file.st_size; // getting size of file

                            // getting last modified time of files

                            char t[1000];

                            // strftime is used to show the time, date and month

                            strftime(t, 100, "%d/%m/%Y  %H:%M:%S", localtime(&file.st_mtime)); // storing time date and month in t

                            // char d1 = t[0];
                            // char d2 = t[1];

                            /*

                                t should be like this --> dd/mm/yyyy hh:mm
                            */

                            for (int k = 0; k < 2; k++)
                            {

                                day[j][k] = t[k];
                            }

                            day[j][2] = 0;

                            Day[j] = atoi(day[j]); // changing string into integer and getting the day

                            int m1, m2;

                            m1 = t[3] - '0';
                            m2 = t[4] - '0';
                            month[j] = months[m2 + (10 * m1) - 1]; // getting the month

                            for (int k = 0; k < 5; k++)
                            {

                                hr[j][k] = t[11 + k]; // getting hour
                            }

                            hr[j][5] = 0;
                        }
                    }

                    int max_size = -1;

                    for (j = 0; j < cnt1; j++)
                    {

                        if (size[j] > max_size)
                        {

                            max_size = size[j];
                        }
                    }

                    int N = 0;
                    // N is for finding number of digits in max_size
                    while (max_size > 0)
                    {

                        max_size /= 10;
                        N++;
                    }

                    if (N == 0)
                    {

                        N = 1;
                    }

                    printf("total files : %d\n", total / 2); // Displaying number of files

                    // Displaying files/directories permissions last modified day,date and time and name

                    for (j = 0; j < cnt1; j++)
                    {

                        // printf("%s %d %s %s %*d %s %2d %s %s\n", perms[j], links[j], owner[j], group[j], N, size[j], month[j], Day[j], hr[j], file_names[j]);

                        printf("%s %d %s %s %*d %s %2d %s ", perms[j], links[j], owner[j], group[j], N, size[j], month[j], Day[j], hr[j]);

                        struct stat test;

                        stat(file_names[j], &test);

                        if (S_ISREG(test.st_mode) == 0)
                        {

                            printf(Yellow("%s\n"), file_names[j]);
                        }

                        else if (stat(file_names[j], &test) == 0 && test.st_mode & S_IXUSR)
                        {

                            printf(Green("%s\n"), file_names[j]);
                        }

                        else
                        {

                            printf("%s\n", file_names[j]);
                        }
                    }
                }
            }
        }
    }
}
