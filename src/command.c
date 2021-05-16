#include "command.h"
#include "common_base.h"
#include <stdio.h>
#include <dirent.h> // opendir() readdir() closedir()
#include <string.h> // strcmp()
#include <stdlib.h> // exit()
#include <unistd.h> // getcwd() write()
#include <sys/types.h>  
#include <sys/stat.h> 
#include <fcntl.h>

void listDir() /*for the ls command*/
{
    char buf [BUFSIZE] = {0};
    if (NULL == getcwd(buf, BUFSIZE)) {
        perror("[SysError]: getcwd() in listDir()s failed.\n");
    }
    DIR *dirp = opendir(buf);
    struct dirent *dp = NULL;
    printf(". .. ");
    while((dp=readdir(dirp))!=NULL){
        if (strcmp(dp->d_name, ".")==0
        || strcmp(dp->d_name, "..")==0){
            continue;
        }
        printf("%s ",dp->d_name);
    }
    closedir(dirp);
    printf("\n");
    return ;
};

void showCurrentDir() /*for the pwd command*/
{
    char buf [BUFSIZE] = {0};
    if (NULL == getcwd(buf, BUFSIZE)) {
        perror("[SysError]: getcwd() in listDir()s failed.\n");
    }
    printf("%s\n", buf);
    return;
};

void makeDir(char *dirName) /*for the mkdir command*/
{
    // printf("makeDir %s\n", dirName);
    // return;

    DIR *mydir = NULL;  
    if(NULL == (mydir = opendir(dirName))) {  
      int ret = mkdir(dirName, S_IRWXU | S_IRWXG | S_IRWXO);
      if (ret != 0){
          return;
      } else {
          printf("mkdir %s sucess\n", dirName);  
      }
    }else{
        printf("%s exists\n", dirName);
    }
    closedir(mydir);
    return ;  
};

void changeDir(char *dirName) /*for the cd command*/
{
    // printf("changeDir %s\n", dirName);
    // return;

    struct stat st;
    if (NULL!=dirName){
        stat(dirName, &st);
        if (S_ISDIR(st.st_mode)){
            chdir(dirName);
        } else{
            printf("No such directory : \'%s\'\n", dirName);
        }
    }
    return;
};

void copyFile(char *sourcePath, char *destinationPath) /*for the cp command*/
{
    size_t sourcePath_len = strlen(sourcePath);
    size_t i = sourcePath_len-1;
    for (; i>0; i--) {
        if (sourcePath[i]=='/'){
            i++;
            break;
        }
    };
    // printf("i = %d",i);
    char* file_name = sourcePath+i;
    // printf("file_name = %s\n", file_name);
    
    struct stat st;
    memset(&st, 0, sizeof st);
    stat(destinationPath, &st);
    char new_destinationPath[BUFSIZE] = {0};
    if (S_ISDIR(st.st_mode)) { // destinationPath is dir
        int old_destinationPath_len = strlen(destinationPath);
        strcpy(new_destinationPath, destinationPath);
        new_destinationPath[old_destinationPath_len] = '/';
        strcat(new_destinationPath, file_name);
        destinationPath = new_destinationPath;
    }

    // printf("destination = %s\n", destinationPath);
    // now, destinationPath is a file
    int infile, outfile;
    char buffer[BUFSIZE] = {0};
    if (-1==(infile = open(sourcePath, O_RDONLY))) {
        printf("Error! Open %s faield in command: cp\n", sourcePath);
        return;
    }
    if (-1==(outfile = open(destinationPath, O_WRONLY|O_CREAT|O_TRUNC, 776))) {
        printf("Error! Open %s faield in command: cp\n", destinationPath);
        close(infile);
        return;
    }
    ssize_t nread;
    while ((nread = read(infile, buffer, BUFSIZE)) > 0) {
        if (write(outfile, buffer, nread) < nread) {
            close(infile);
            close(outfile);
            return ;
        }
    }
    close(infile);
    close(outfile);
    if (-1 == nread)
        printf("Error! Command cp faield\n");
    
    return;
};

void moveFile(char *sourcePath, char *destinationPath) /*for the mv command*/
{
    copyFile(sourcePath, destinationPath);
    deleteFile(sourcePath);
};

void deleteFile(char *filename) /*for the rm command*/
{
    // printf("deleteFile %s\n", filename);
    // return;
    
	char dir_name[BUFSIZE];
	DIR *dirp;
	struct dirent *dp;
	struct stat dir_stat;
    
	if ( 0 != access(filename, F_OK) ) {
        perror(filename);
		return ;
	}
    
	if ( 0 > stat(filename, &dir_stat) ) {
		perror(filename);
		return ;
	}

	if ( S_ISREG(dir_stat.st_mode) ) {
		remove(filename);
	} else if ( S_ISDIR(dir_stat.st_mode) ) {
		dirp = opendir(filename);
		while ( (dp=readdir(dirp)) != NULL ) {
			if ( (0 == strcmp(".", dp->d_name)) 
              || (0 == strcmp("..", dp->d_name)) ) {
				continue;
			}
			
			sprintf(dir_name, "%s/%s", filename, dp->d_name);
			deleteFile(dir_name);
		}
		closedir(dirp);
		rmdir(filename);
	} else {
		perror("rm unknow file type");	
	}
	
	return ;
};

void displayFile(char *filename) /*for the cat command*/
{
    // printf("displayFile %s\n", filename);
    // return;

    size_t fd = open(filename, O_RDONLY);
    if(fd == -1) {
        perror(filename);
        return ;
    }
    size_t r;
    char buf[BUFSIZE];
    while((r = read(fd, buf, BUFSIZE)) > 0) {
        write(STDOUT_FILENO, buf, r);
    }
    close(fd);
    return;
};
