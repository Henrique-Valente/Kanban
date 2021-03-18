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
    short priority;
    time_t made_in;
    time_t date;
    char* info;
    char* person;
} Task;

/*
if you want to create a task without date or person just call as such: create_task(counter,priority,info,NULL,NULL)
Counter and info must not be NULL.
*/
Task* create_task(long* counter, short priority, const char* info, time_t* date, const char* person);
void destroy_task(Task* task, short delete_person);

#endif