#include "defination.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
char *getfield(char *line, int num)
{
    char *tok;
    for (tok = strtok(line, " ");
         tok && *tok;
         tok = strtok(NULL, " \n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void process()
{
    struct dirent *de; // Pointer for directory entry
    char line[1024];
    FILE *fptr;
    fptr = fopen("output.txt", "w");
    char search1[50];
    char search2[50];
    char op[5];

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(".");

    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory");
    }
    printf("Make sure your file is properly formatted \n");
    printf("Format: <Property>: <value> newline \n");

    printf("Enter Search 1: (Put . if you want to leave it blank)  \n");
    scanf(" %s", search1);
    printf("Enter Search 2: (Put . if you want to leave it blank) \n");
    scanf(" %s", search2);
    printf("Enter Op: (Put . if you want to leave it blank) \n");
    scanf(" %s", op);

    while ((de = readdir(dr)) != NULL)
    {
        if (strstr(de->d_name, ".txt") != NULL)
        {
            //printf("%s ", de->d_name);
            FILE *stream = fopen(de->d_name, "r");

            while (fgets(line, 1024, stream))
            {

                if (strstr(line, search1) != NULL || strstr(line, search2) != NULL)
                {
                    //printf("%s \n", line);
                    fprintf(fptr, "%s %s \n", de->d_name, line);
                }
            }
        }
    }
    fclose(fptr);
    if (strcmp(op, "and") == 0)
    {

        FILE *stream = fopen("output.txt", "r");

        char line1[50];

        while (fgets(line, 1024, stream))
        {
            char *tline1 = strdup(line);
            char *tline2 = strdup(line);

            if (strstr(tline1, search1) != NULL && strstr(tline2, search2) != NULL)
            {
                strcpy(line1, tline1);
                printf("%s \n", getfield(line1, 1));
            }
        }
    }
    else if (strcmp(op, "or") == 0)
    {
        FILE *stream = fopen("output.txt", "r");

        char line1[50];

        while (fgets(line, 1024, stream))
        {
            char *tline1 = strdup(line);
            char *tline2 = strdup(line);

            if (strstr(tline1, search1) != NULL || strstr(tline2, search2) != NULL)
            {
                strcpy(line1, tline1);
                printf("%s \n", getfield(line1, 1));
            }
        }
    }
    else
    {
        FILE *stream = fopen("output.txt", "r");

        char search[50];
        if (strcmp(search1, ".") == 0)
        {
            strcpy(search, search2);
        }
        else
        {
            strcpy(search, search1);
        }

        char line1[50];

        while (fgets(line, 1024, stream))
        {
            char *tline1 = strdup(line);
            char *tline2 = strdup(line);

            if (strstr(tline1, search1) != NULL && strstr(tline2, search2) != NULL)
            {
                strcpy(line1, tline1);
                printf("%s \n", getfield(line1, 1));
            }
        }
    }

    closedir(dr);
}