#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>

void listFiles(){
        struct dirent *dp;
        DIR* directory = opendir(".");
        char file[200];
        dp = readdir(directory);
        int n;
         while(dp!=NULL){
             if (dp->d_type == 8){
                strcpy(file,"./");
                strcat(file, dp->d_name);
                strcat(file, "\n");
                n = strlen(file);
                write(1, file, n);
             }
            dp = readdir(directory);
         }
        closedir(directory);
}

int main(){
    listFiles();


    return 0;
}