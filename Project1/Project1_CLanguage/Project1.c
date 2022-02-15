#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void stringToLower(char *str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

int main() {
    char input[8192];
    char command[8192];
    char arg1[8192];
    char arg2[8192];

    while(true)
    {
        printf("Enter a command or type Ctrl-C to exit: ");
        fgets(input,8192,stdin);

        // //inputCopy gets run later because strtok messed with input variable
        // char inputCopy[8192];
        // strcpy(inputCopy, input);

        char *token = strtok(input, " ");
        strcpy(command, token);

        //You cannot have more than two arguments
        int maxArgs = 0;

        while(token != NULL)
        {
            token = strtok(NULL, " ");
            //printf("TOKEN IS %s\n", token);
            if(maxArgs == 2 && token != NULL)
            {
                printf("Too many arguments entered try again\n");
                break;
            }
            else if(maxArgs == 0 && token != NULL)
            {
                strcpy(arg1,token);
            }
            else if(maxArgs == 1 && token != NULL)
            {
                strcpy(arg2,token);
            }
            maxArgs++;
        }
        // printf("Command is %s\n",command);
        // printf("Arg1 is %s\n", arg1);
        // printf("Arg2 is %s\n",arg2);

        //skip running command in system if input has too many argument
        if(token != NULL){
            printf("Too many arguments entered try again\n");
            memset(command,0,8192*sizeof(char));
            memset(arg1,0,8192*sizeof(char));
            memset(arg2,0,8192*sizeof(char));
            continue;
        }

        stringToLower(command);
        // printf("PROGRAM HITS HERE\n");
        // printf("COMMAND IS %s\n",command);
        // printf("RESULT OF STRCMP with Command %d\n", strcmp(command, "dir"));
        if(strcmp(command,"cd") == 0)
        {
            if(strlen(arg2) != 0)
            {
                printf("Too many arguments entered for cd try again\n");
            }
            else if(strlen(arg1) != 0)
            {
                //printf("arg1 before chdir %s\n",arg1);
                char trimmedArg1[strlen(arg1)];
                memset(trimmedArg1, 0, strlen(arg1)*sizeof(char));

                strncpy(trimmedArg1, arg1, strlen(arg1)-1);
                //printf("Trimmed argument %s\n", trimmedArg1);
                int res = chdir(trimmedArg1);
                //printf("Result of chdir %d\n",res);
                //memset(trimmedArg1,0,(strlen(arg1)-1)*sizeof(char));
            }
        }
        else if(strcmp(command,"dir\n") == 0)
        {
            //printf("dir command recognized\n");
            if(strlen(arg1) != 0 || strlen(arg2) != 0)
            {
                printf("Too many arguments entered for dir try again\n");
            }
            else {
                system("ls");
            }
        }
        else if(strcmp(command, "type") == 0)
        {
            if(strlen(arg2) != 0)
            {
                printf("Too many arguments entered for type try again\n");
            }
            else if(strlen(arg1) == 0)
            {
                printf("Too few arguments entered for type try again\n");
            }
            else
            {
                //printf("Type command about to be interpreted\n");
                char cat[8192] = "cat ";
                char *catCommand = strcat(cat,arg1);
                system(catCommand);
            }
        }
        else if(strcmp(command, "del") == 0)
        {
            if(strlen(arg2) != 0)
            {
                printf("Too many arguments entered for del try again\n");
            }
            else if(strlen(arg1) == 0)
            {
                printf("Too few arguments entered for del try again\n");
            }
            else
            {
                char rm[8192] = "rm ";
                char *rmCommand = strcat(rm,arg1);
                system(rmCommand);
            }
        }
        else if(strcmp(command,"ren") == 0)
        {
            if(strlen(arg1) == 0 || strlen(arg2) == 0)
            {
                printf("Insufficient number of arguments for ren command(requires 2 args)\n");
            }
            else
            {
                char mv[8192] = "mv ";
                char *space = " ";
                char *mvCommand = strcat(mv,arg1);
                mvCommand = strcat(mvCommand,space);
                mvCommand = strcat(mvCommand,arg2);
                system(mvCommand);
            }
        }
        else if(strcmp(command,"copy") == 0)
        {
            if(strlen(arg1) == 0 || strlen(arg2) == 0)
            {
                printf("Insufficient number of arguments for copy command(requires 2 args)\n");
            }
            else
            {
                char cp[8192] = "cp ";
                char *space = " ";
                char *cpCommand = strcat(cp,arg1);
                cpCommand = strcat(cpCommand, space);
                cpCommand = strcat(cpCommand,arg2);
                system(cpCommand);
            }
        }
        else
        {
            printf("Command not recognized or insufficient number of args provided.\n");
        }
        //clear char buffers
        memset(command,0,8192*sizeof(char));
        memset(arg1,0,8192*sizeof(char));
        memset(arg2,0,8192*sizeof(char));
        // if(strlen(command) == 0 && strlen(arg1) == 0 && strlen(arg2) == 0){
        //     printf("CLEARING CHAR BUFFER WORKED\n");
        // }
    }


    return 0;
}