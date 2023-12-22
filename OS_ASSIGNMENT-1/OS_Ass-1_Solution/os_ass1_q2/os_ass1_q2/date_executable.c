#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include<string.h>



void functionC(const char *input_file, char *rfc5322Time, size_t bs) {
    struct stat history_of_file;
    if (stat(input_file, &history_of_file) == 0) {
        struct tm *timeinfo = gmtime(&(history_of_file.st_mtime));
        strftime(rfc5322Time, bs, "%a, %d %b %Y %H:%M:%S +0000", timeinfo);
    } else {
        snprintf(rfc5322Time, bs, "Error");
    }
}
void functionA(const char *input_file) {
    struct stat history_of_file;

    if (stat(input_file, &history_of_file) == 0) {
        char *timeStr = ctime(&history_of_file.st_mtime);
        timeStr[strlen(timeStr) - 1] = '\0'; 

        printf("Last modified date and time of file '%s': %s IST %s\n", input_file, timeStr, timeStr + 11);
    } else {
        perror("Error");
    }
}

int this_func_comp_dates(struct tm date1, struct tm date2) {
    return (date1.tm_year == date2.tm_year) &&
           (date1.tm_mon == date2.tm_mon) &&
           (date1.tm_mday == date2.tm_mday);
}


struct tm calculateYesterday() {
    time_t rtime;
    struct tm *yesterday;

    
    time(&rtime);

   
    rtime -= 86400;
    yesterday = localtime(&rtime);

    return *yesterday;
}


void functionB(const char *input_file) {
   
    struct stat history_of_file;
    if (stat(input_file, &history_of_file) == -1) {
        perror("Error getting file status");
        return;
    }
    
   
    struct tm *new_date = localtime(&history_of_file.st_mtime);

   
    struct tm yesterday = calculateYesterday();

   
    printf("Yesterday's Date: %04d-%02d-%02d\n",
           yesterday.tm_year + 1900, yesterday.tm_mon + 1, yesterday.tm_mday);

    if (this_func_comp_dates(*new_date, yesterday)) {
        
        printf("File was modified yesterday.\n");
        printf("File's Modified Date: %04d-%02d-%02d %02d:%02d:%02d\n",
               new_date->tm_year + 1900, new_date->tm_mon + 1, new_date->tm_mday,
               new_date->tm_hour, new_date->tm_min, new_date->tm_sec);
    } else {
        printf("File was not modified yesterday.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        if (strcmp(argv[0], "date") == 0 && strcmp(argv[1], "-d") == 0) {
            if(strcmp(argv[2], "yesterday") == 0 ){
            const char *input_file = argv[3]; 
        functionB(input_file);
        }
        }
         else{
        printf("error wrong command");
    
    }
    }
    else if (argc==3)  {
        if ((strcmp(argv[0], "date") == 0 && strcmp(argv[1], "-R") == 0)){
           const char *input_file = argv[2];  
           char rfc5322Time[128]; 
           functionC(input_file, rfc5322Time, sizeof(rfc5322Time));
           printf("Last modified date and time (RFC 5322 format): %s\n", rfc5322Time);
        

        }
         else{
        printf("error wrong command\n");
    
    }

    }    
           
    
    else if(argc==2){
        const char *input_file = argv[1];  
        functionA(input_file);
    }
    else{
        printf("error wrong command\n");
    
    }

    return 0;
}
