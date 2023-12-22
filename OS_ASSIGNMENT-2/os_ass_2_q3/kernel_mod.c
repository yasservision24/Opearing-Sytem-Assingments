#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

static int __init process_total_init(void) {
    struct task_struct *task;
    int counter_for_no_of_process = 0;

    list_for_each_entry(task, &current->tasks, tasks) {  
        counter_for_no_of_process++;                    
    }

    printk(KERN_INFO " Module loaded successfully,Total running processes: %d\n", counter_for_no_of_process);
    return 0;
}

static void __exit process_total_exit(void) {
    printk(KERN_INFO "Module Unloaded\n");
}

module_init(process_total_init);
module_exit(process_total_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to print total running processes in kernel from using the task_struct");
