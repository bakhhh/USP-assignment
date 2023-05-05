#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>

char **create2DArray(int row, int col){
    int i, j;
    char** array;
    array = (char**) malloc(sizeof(char*) * row);  
    /* malloc columns for each row */
    for (i = 0 ;  i < row ; i++)
    {
        array[i] = (char*) malloc(sizeof(char) * col); 
    }
    return array;
}

char **listFiles(int *countFiles){
        struct dirent *dp;
        DIR* directory = opendir(".");
        char file[200];
        char **filenames= create2DArray(20,20);
        dp = readdir(directory);
        int stringLength;
         while(dp!=NULL){
             if (dp->d_type == 8){
                stringLength = strlen(dp->d_name);
                for (int i=stringLength-1;i>0;i--)
                {
                    if(dp->d_name[i]== '.'){
                        if (strcmp(&dp->d_name[i], ".usp") == 0){
                            strcpy(filenames[(*countFiles)++], dp->d_name);
                    }
                }
                }

             }
            dp = readdir(directory);
         }
        closedir(directory);
        return filenames;
}

int main(){
    char ** array;
    int countFiles=0;
    array = listFiles(&countFiles);
    for (int i=0; i<countFiles; i++){
        printf("%s \n", array[i]);
    }

 
    

    return 0;
}