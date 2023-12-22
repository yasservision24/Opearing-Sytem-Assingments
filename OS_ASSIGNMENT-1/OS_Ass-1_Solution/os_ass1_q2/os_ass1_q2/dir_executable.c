#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>


int is_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}

void delete_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char entry_path[1024];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", path, entry->d_name);

        if (is_directory(entry_path)) {
            delete_directory(entry_path);
        } else {
            if (remove(entry_path) != 0) {
                perror("remove");
            }
        }
    }

    closedir(dir);

    if (rmdir(path) != 0) {
        perror("rmdir");
    }
}

int changeDirectory(const char *newDir) {
    if (chdir(newDir) == 0) {
        char currentDir[100];
        if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
            printf("Current directory: %s\n", currentDir);
        } else {
            perror("getcwd");
            return 1;
        }
    } else {
        perror("chdir");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp(argv[0], "dir") == 0 && strcmp(argv[1], "-r") == 0) {
             const char *directory_path = argv[2];
             if (is_directory(directory_path)) {
                delete_directory(directory_path);
                if (mkdir(argv[2], 0700) == 0) {
                    printf("new directory created.\n");
                    changeDirectory(argv[2]);

                } else {
                    printf("Error creating new directory.\n");
                }
            

    }  
            else{
                printf("no such file exist \n");
            }
            
            

                
        } 

        else if(strcmp(argv[0], "dir") == 0 && strcmp(argv[1], "-v") == 0){
            
            if (mkdir(argv[2], 0700) == 0) {
            printf("Directory '%s' created successfully.\n",argv[1]);
            changeDirectory(argv[2]);
            printf("STEP3-here is the final step here the new directory is created or old one is replaces by new  or ERROR is given\n ");
    }       else {
            printf("Error: Directory '%s' already exists or couldn't be created.\n", argv[2]);
            
    }
            
        }
        
        else {
            printf("Usage: %s dir -r <directory_name>\n", argv[0]);
        }
    }

    else if (argc==2){
        if (strcmp(argv[0], "dir") == 0) {
            if (mkdir(argv[1], 0700) == 0) {
            printf("Directory '%s' created successfully.\n",argv[1]);
            changeDirectory(argv[1]);
    }       else {
            printf("Error: Directory '%s' already exists or couldn't be created.\n", argv[1]);
    }
    } 
        else{
            printf("invalid command");
        }
    }
    
    else{
         printf("invalid command");
        }
    
    

    return 0;
}
