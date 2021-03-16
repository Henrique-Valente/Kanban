#ifndef TASK_H
#define TASK_H
#include <time.h>


/*
A task that identified by its unique identifier (id),
holds the date it was created in, info about the task,
another date that can serve as the date of conclusion
or the date it is expected to be finished,
and finally the person who finished or is working on the task.
*/
typedef struct task
{
    long id;
    time_t made_in;
    time_t date;
    char* info;
    char* person;
} Task;

char* create_string(const char* str);

/*
if you want to create a task without date or person just call as such: create_task(counter,info,NULL,NULL)
Counter and info must not be NULL.
*/
Task* create_task(long* counter, const char* info, time_t* date, const char* person);

#endif