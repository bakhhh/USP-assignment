#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>



char **create2DArray(int row, int col)
{
    int i, j;
    char **array;
    array = (char **)malloc(sizeof(char *) * row);
    /* malloc columns for each row */
    for (i = 0; i < row; i++)
    {
        array[i] = (char *)malloc(sizeof(char) * col);
    }
    return array;
}

void createPipes(int numberOfFiles)
{
    int pipeFd[numberOfFiles][2];
    for (int i = 0; i < numberOfFiles; i++)
    {
        pipe(pipeFd[i]);
    }
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
        for (int i = stringLength; i > 0; i--)
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

int main()
{
    char **filename;
    int countFiles = 0;
    int pid;
    int i;
    char buffer[200];
    
    filename = listFiles(&countFiles);

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
            char result[30];
            close(writingFilenamePipe[i][0]);
            write(writingFilenamePipe[i][1], filename[i], n);
            // close(writingFilenamePipe[i][1]);

            close(writingResultsPipe[i][1]);
            
            int fd2 = open("results.txt",O_WRONLY | O_CREAT |O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            int size = read(writingResultsPipe[i][0], result, sizeof(result));
            result[size] = '\0'; 
            printf("parent result= %s\n",result);
            write(fd2, result, strlen(result));
            write(fd2, "\n", 1);



            close(fd2);
            // close(writingResultsPipe[i][0]);

        }
        else if (pid == 0)
        {
            close(writingFilenamePipe[i][1]);

            int size = read(writingFilenamePipe[i][0], buffer, 200);
            // write(1, buffer, size)
            close(writingFilenamePipe[i][0]);
            printf("Child process received filename: %s\n", buffer);
                        

            int fd1 = open(buffer, O_RDONLY);
            int line = 0;
            int num1=0;
            int num2=0;
            char buf;
            char operator;
            int result=0;
            char id[20];
            char output[30];
            int index =0;
        
            
            while (read(fd1, &buf, 1))
            {
                if (buf== '\n'){
                    line++;
                }
                if (line==0){
                    
                    id[index] =buf;
                    index ++;
                }
                if (line==1)
                {
                    {
                        num1=num1*10+atoi(&buf);   
                    }
                }
                if (line==2){
                    {
                        operator = buf;
                    }
                }
                if (line==3){
                    {
                        num2=num2*10+atoi(&buf);
                    }
                }
                

              
                }
            close(writingResultsPipe[i][0]);
            
            // printf("id= %s\n", id);

            if (strncmp(&operator, "+", 1)==0)
            {
                result=num1+num2;
                char str[10];
                sprintf(str,"%d",result);
                strcat(output,id);
                strcat(output,":");
                strcat(output,str);
                write(writingResultsPipe[i][1], output, strlen(output));
            }
            if (strncmp(&operator,"*",1)==0)
            {
                result=num1*num2;
                char str[10];
                sprintf(str,"%d",result);
                strcat(output,id);
                strcat(output,":");
                strcat(output,str);
                write(writingResultsPipe[i][1], output, strlen(output));
            }
            if (strncmp(&operator,"-",1)==0)
            {
                result=num1-num2;
                char str[10];
                sprintf(str,"%d",result);
                strcat(output,id);
                strcat(output,":");
                strcat(output,str);
                write(writingResultsPipe[i][1], output, strlen(output));
            }
            if (strncmp(&operator,"/",1)==0)
            {
                result=num1/num2;
                char str[10];
                sprintf(str,"%d",result);
                strcat(output,id);
                strcat(output,":");
                strcat(output,str);
                write(writingResultsPipe[i][1], output, strlen(output));
            }
            // printf("result= %s\n", output);
            // char sendToPipe[strlen(output)];
            // strcpy(sendToPipe,output);
            printf("result= %s length %lu\n", output, strlen(output));
            // write(writingResultsPipe[i][1], output, strlen(output));
            // close(writingResultsPipe[i][1]);
            
            close(fd1);
            

            return 0;
        }
        wait(NULL);
    }

    for (i = 0; i < 20; i++)
    {
        free(filename[i]);
    }

    free(filename);

    return 0;
}