#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>



int main() {
    long long difference1;   // differnce1 will store the time difference for other policy
    long long difference2;  // differnce2 will store the time difference for RR policy
    long long difference3;  // differnce3 will store the time difference for FIFO policy

   
    for (int i = 0; i < 3; i++) {
        if (i==0){
            pid_t pid[3];
            int status;

    
    
    struct sched_param parent_param = { .sched_priority = 0 }; // here we are using the other policy with default priority =0
    int ret = sched_setscheduler(getpid(), SCHED_OTHER, &parent_param);
    if (ret == -1) {
        perror("sched_setscheduler");
        return -1;
    }

        struct timespec start_times, end_times;

       
        clock_gettime(0 , &start_times);
    
   
    for (int i = 0; i < 3; i++) {
        
        pid[i] = fork();

        if (pid[i] == -1) {
            perror("fork");
            return 1;
        }

        if (pid[i] == 0) {
            char child_process_for_counting[20];
            sprintf(child_process_for_counting, "./P%d", i+1);
            execl(child_process_for_counting, child_process_for_counting, (char *)NULL);

            perror("exec");
            return 1;
        }
    }

    
     for (int i = 0; i < 3; i++) {
        pid_t wpid = waitpid(pid[i], &status, 0);

        /*if (WIFEXITED(status)) {
            printf("Child process %d terminated normally with status %d.\n", wpid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d.\n", wpid, WTERMSIG(status));
        }*/
        (void)wpid;
    }
    clock_gettime(0, &end_times);

    long long time_difference_ns1 = (end_times.tv_sec - start_times.tv_sec) * 1000000000LL
                              + (end_times.tv_nsec - start_times.tv_nsec);

    difference1 = time_difference_ns1 / 1000000LL;
    }
    
    else if (i==1)
    {
        

    struct sched_param parent_param = { .sched_priority =  1}; // here we are using the fifo policy with default priority =1
    int ret = sched_setscheduler(getpid(), SCHED_RR, &parent_param);
    if (ret == -1) {
        perror("sched_setscheduler");
        return -1;
    } 
        pid_t pid[3];
        int status;
        
    
    

    struct timespec start_times, end_times;

    
    clock_gettime(0 , &start_times);

    for (int i = 0; i < 3; i++) {
        
        pid[i] = fork();

        if (pid[i] == -1) {
            perror("fork");
            return 1;
        }

        if (pid[i] == 0) {
            char child_process_for_counting[20];
            sprintf(child_process_for_counting, "./P%d", i+1);
            execl(child_process_for_counting, child_process_for_counting, (char *)NULL);

            perror("exec");
            return 1;
        }
    }

    

    for (int i = 0; i < 3; i++) {
        pid_t wpid = waitpid(pid[i], &status, 0);

       /*if (WIFEXITED(status)) {
            printf("Child process %d terminated normally with status %d.\n", wpid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d.\n", wpid, WTERMSIG(status));
        }*/
        (void)wpid;
    }
    clock_gettime(0 , &end_times);

    long long time_difference_ns2 = (end_times.tv_sec - start_times.tv_sec) * 1000000000LL
                              + (end_times.tv_nsec - start_times.tv_nsec);

    difference2= time_difference_ns2 / 1000000LL;

    }


else{
    struct sched_param parent_param = { .sched_priority =  1}; // here we are using the fifo policy with default priority =1
    int ret = sched_setscheduler(getpid(), SCHED_FIFO, &parent_param);
    if (ret == -1) {
        perror("sched_setscheduler");
        return -1;
    }
            pid_t pid[3];
            int status;


   

   struct timespec start_times, end_times;

    // Get start time
    clock_gettime(0 , &start_times);

    for (int i = 0; i < 3; i++) {
      
        pid[i] = fork();

        if (pid[i] == -1) {
            perror("fork");
            return 1;
        
        }

        if (pid[i] == 0) {
            char child_process_for_counting[20];
            sprintf(child_process_for_counting, "./P%d", i + 1);
            execl(child_process_for_counting, child_process_for_counting, (char *)NULL);

            perror("exec");
            return 1;
        }
    }

   
    for (int i = 0; i < 3; i++) {
        pid_t wpid = waitpid(pid[i], &status, 0);

        /*if (WIFEXITED(status)) {
            printf("Child process %d terminated normally with status %d.\n", wpid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d.\n", wpid, WTERMSIG(status));
        }*/
        (void)wpid;
    }
    clock_gettime(0, &end_times);

    long long time_difference_ns3 = (end_times.tv_sec - start_times.tv_sec) * 1000000000LL
                              + (end_times.tv_nsec - start_times.tv_nsec);

    difference3 = time_difference_ns3 / 1000000LL;


    
}

    }
   
    FILE *file = fopen("times.txt", "w");
    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    fprintf(file,"SCHED OTHER: %lld\n",difference1);
    fprintf(file,"SCHED RR: %lld\n",difference2);
    fprintf(file,"SCHED FIFO: %lld\n",difference3);
    
    fclose(file);

    return 0;
}
