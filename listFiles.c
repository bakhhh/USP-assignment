#include "listFiles.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **create2DArray(int row, int col) // UCP reference
{
    int i;
    char **array;
    array = (char **)malloc(sizeof(char *) * row);
    for (i = 0; i < row; i++)
    {
        array[i] = (char *)malloc(sizeof(char) * col);
    }
    return array;
}

char **listFiles(int *countFiles)
{
    struct dirent *dp;
    DIR *directory = opendir(".");
    char **filenames = create2DArray(20, 20);
    dp = readdir(directory);
    int stringLength;
    while (dp != NULL)
    {
        stringLength = strlen(dp->d_name);
        for (int i = 0; i < stringLength; i++)
        {
            if (dp->d_name[i] == '.')
            {
                if (strcmp(&dp->d_name[i], ".usp") == 0)
                {
                    strcpy(filenames[(*countFiles)++], dp->d_name);
                }
            }
        }
        dp = readdir(directory);
    }
    closedir(directory);
    return filenames;
}