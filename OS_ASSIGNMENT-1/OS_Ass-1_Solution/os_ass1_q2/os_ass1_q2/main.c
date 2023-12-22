#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#define MAX_INPUT_LENGTH 100



int is_dir_present(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1; 
    }
    return 0; 
}




int cd_command(const char *path) {
    return chdir(path);
}

void process_directory_command(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp(argv[0], "dir") == 0 && strcmp(argv[1], "-r") == 0) {
            const char *directory_path = argv[2];
            if (is_dir_present(directory_path)) {
                
                    if (cd_command(argv[2]) == 0) {
                    } 
                
            }
        } else if (strcmp(argv[0], "dir") == 0 && strcmp(argv[1], "-v") == 0) {
           
        
                if (cd_command(argv[2]) == 0) {
                    printf(" ");
                } 
             
        }
    } else if (argc == 2) {
        if (strcmp(argv[0], "dir") == 0) {
            
                if (cd_command(argv[1]) == 0) {
                    printf(" ");
                } 
             
        } 
    } 
}



bool directoryExists(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            return true;  
        } else {
            return false;
        }
    } else {
        return false;     
    }
}

void printCurrentWorkingDirectory() {
    char cwd[1024];  

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s ", cwd);
    } else {
        perror("getcwd");
    }
}
int changeCurrentWorkingDirectory(const char *newDir) {
    if (chdir(newDir) == 0) {
        printf("Current working directory changed to: %s\n", newDir);
        return 0;
    } else {
        perror("chdir");
        return 1;
    }
}

int word_count(const char *filename);
void word_count_without_n(const char *filename);
void functionF(const char *filename1, const char *filename2);

int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;  
    } else {
        return 0; 
    }
}

int main() {
    while (1) {
        
        char input[MAX_INPUT_LENGTH];
        printCurrentWorkingDirectory();
        printf(">> ");
        fgets(input, sizeof(input), stdin);

       
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break; 
        }

        int size = 0;
        char **array = NULL;
        char *token = strtok(input, " ");  

        while (token != NULL) {
            size++;
            array = (char **)realloc(array, size * sizeof(char *));

            if (array == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
            }

            array[size - 1] = strdup(token);  
            token = strtok(NULL, " ");  
        }

        
        int length = size;

        

       if(strcmp(array[0], "word") == 0){
         if(length == 1) {
            printf("No file provided.\n");
        } 
        else if (length == 2) {
            if (fileExists(array[1])) {
                printf("Total no  of words in %s are:- %d\n",array[1] ,word_count(array[1]));
                
            } else {
                printf("File does not exist.\n");
            }
        }
        else if (length == 3 && strcmp(array[1], "-n") == 0) {
            if (fileExists(array[2])) {
                word_count_without_n(array[2]);
            } else {
                printf("File does not exist.\n");
            }
        } 

        else if (length >= 3 && strcmp(array[1], "-d") == 0){
            if(strcmp(array[2], "-n")==0) {
                printf("only one option at a time cant't use -d and -n together \n");
            }
            
            else if (length != 4) {
            printf("Two filenames are required after -d option.\n");
            }   
            else {
                bool file1Exists = fileExists(array[2]);
                bool file2Exists = fileExists(array[3]);

                if (file1Exists && file2Exists) {
                    functionF(array[2], array[3]);
                } 
                else {
                    
                    if (!file1Exists) {
                        printf("%s", array[2]);
                    }
                    if (!file2Exists) {
                        printf("%s", array[3]);
                    }
                    printf(" This  file does not exist:\n");
                }
                }
        }
        else {
            printf("Invalid options or usage. Use word [option (-n/-d/no option)] filename (or two filenames if option is -d)\n");
        }
       }

       else if(strcmp(array[0], "dir") == 0){
        

        












        int rc = fork();
        if (rc < 0){
            if (length == 2 && strcmp(array[1], "-v") == 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
            
        }
            
        }
        else if (rc == 0){
            
            if (length == 3 && strcmp(array[1], "-v") == 0) {
        printf("STEP1-folk function has been called and child has been created\n ");
        printf("STEP2-now execvp is used to call the executable named dir_executable\n ");
    }
            char *args[length];  
        for (int i = 0; i < length; ++i) {
            args[i] = array[i];
        }
        args[length] = NULL;  

        execvp("./dir_executable", args);

       
        perror("execvp");

        return 1;

        }
        else {
        
        int wc = wait(NULL);
       

         if (length ==3  && strcmp(array[1], "-v") == 0) {
          printf("Step4-here using wait parent is waiting for the child to die\n ");
        printf("STEP5-This is parent process of %d (wc:%d) (pid:%d)\n ", rc, wc, (int) getpid());
        printf("COMPLETED\n");
         }

    }
    

    }



     else if (strcmp(array[0], "date") == 0){
        int rc = fork();
        if (rc < 0){
                fprintf(stderr, "fork failed\n");
                exit(1);
            
        }
        else if (rc == 0){
           
            char *args[length]; 
        for (int i = 0; i < length; ++i) {
            args[i] = array[i];
        }
        args[length] = NULL;  

        execvp("./date_executable", args);

        
        perror("execvp");
        return 1;

        }

    else {
        
        int wc = wait(NULL);
        if (1==0){
            printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",rc, wc, (int) getpid());
        }

    
    }
    }
    else {
        printf("Invalid input. Please use word,dir,date\n");
        continue;
    }

    char **argv = array;
    int argc = length;
    process_directory_command(argc, argv);







        for (int i = 0; i < size; i++) {
            free(array[i]);
        }
        free(array);
    }

    return 0;
}





int word_count(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
      
    }

    char word[10000]; 
    int wordCount = 0;

    while (fscanf(file, "%99s", word) == 1) {
        wordCount++;
    }

    fclose(file);
    
    return wordCount;
}












int isStandaloneBackslashn(const char *word) {
    if (strcmp(word, "\\n") == 0) {
        return 1;
    }

    size_t length = strlen(word);
    if (length == 2 && word[0] == '\\' && word[1] == 'n' && !isalnum(word[2])) {
        return 1;
    }

    return 0;
}

void word_count_without_n(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
       
    }

    char word[10000]; // Assuming max word length is 100 characters
    int totalWordCount = 0;
    int validWordCount = 0;

    while (fscanf(file, "%99s", word) == 1) {
        totalWordCount++;
        if (!isStandaloneBackslashn(word)) {
            validWordCount++;
        }
    }

    fclose(file);
    printf("Total Words excluding \\n  in  %s are:-  %d\n", filename, validWordCount);
   
}


void functionF(const char *file1, const char *file2) {
    int count1 = word_count(file1);
    int count2 = word_count(file2);

    int difference = abs(count1 - count2);

    printf("Word difference between %s and %s: %d\n", file1, file2, difference);
}
