#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>

int listFiles(){
        struct dirent *dp;
        DIR* directory = opendir(".");
        char file[200];
        dp = readdir(directory);
        int n;
        int stringLength;
        int countFiles=0;
         while(dp!=NULL){
             if (dp->d_type == 8){
                stringLength = strlen(dp->d_name);
                for (int i=stringLength-1;i>0;i--)
                {
                    if(dp->d_name[i]== '.'){
                        if (strcmp(&dp->d_name[i], ".usp") == 0){
                            strcpy(file,"./");
                            strcat(file, dp->d_name);
                            strcat(file, "\n");
                            n = strlen(file);
                            write(1, file, n);
                            countFiles++;
                    }
                }
                }

             }
            dp = readdir(directory);
         }
        closedir(directory);
        return countFiles;
}

int main(){
    int count;
    count = listFiles();
    printf("number of usp files: %d\n",count);


    return 0;
}