#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "getResults.h"
#include "listFiles.h"


int main()
{
    int countFiles = 0;
    char **filename = listFiles(&countFiles);
    int pid;
    int i;
    int writingFilenamePipe[countFiles][2];
    int writingResultsPipe[countFiles][2];

    for (i = 0; i < countFiles; i++)
    {
        pipe(writingFilenamePipe[i]);
        pipe(writingResultsPipe[i]);
    }

    for (i = 0; i < countFiles; i++)
    {
        pid = fork();

        if (pid > 0)
        {
            int n = strlen(filename[i]);
            char *result = malloc(sizeof(char) * 30);

            close(writingFilenamePipe[i][0]);
            write(writingFilenamePipe[i][1], filename[i], n);
            close(writingFilenamePipe[i][1]);

            close(writingResultsPipe[i][1]);
            int fd2 = open("results.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            int size = read(writingResultsPipe[i][0], result, 30);
            result[size] = '\0';
            write(fd2, result, strlen(result));
            write(fd2, "\n", 1);
            close(fd2);
            close(writingResultsPipe[i][0]);

            free(result);
            wait(NULL);
        }
        else if (pid == 0)
        {
            char buffer[200];
            close(writingFilenamePipe[i][1]);
            int size = read(writingFilenamePipe[i][0], buffer, 200);
            close(writingFilenamePipe[i][0]);

            int fd1 = open(buffer, O_RDONLY);

            int line = 0;
            int num1 = 0;
            int num2 = 0;
            char number1[20];
            char number2[20];
            int index2 = 0;
            int index3 = 0;
            char buf;
            char operator;
            int result = 0;
            char id[20];
            char output[30];
            int index = 0;

            while (read(fd1, &buf, 1))
            {
                if (buf == '\n')
                {
                    line++;
                }
                if (line == 0)
                {
                    id[index] = buf;
                    index++;
                }
                if (line == 1)
                {
                    number1[index2] = buf;
                    index2++;
                }
                if (line == 2)
                {
                    operator= buf;
                }
                if (line == 3)
                {
                    number2[index3] = buf;
                    index3++;
                }
            }
            id[index] = '\0';
            number1[index2] = '\0';
            number2[index3] = '\0';
            num1 = atoi(number1);
            num2 = atoi(number2);

            getResult(operator, result, num1, num2, output, id);

            int n = strlen(output);
            close(writingResultsPipe[i][0]);
            write(writingResultsPipe[i][1], output, n);
            close(writingResultsPipe[i][1]);
            close(fd1);
            exit(0);
        }
    }

    for (i = 0; i < 20; i++)
    {
        free(filename[i]);
    }

    free(filename);

    return 0;
}