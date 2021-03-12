#include <time.h>


// a task that can be distinguished by its unique identifier 
typedef struct task
{
    int pid; 
    time_t made_in;
    char* info;
} Task;
