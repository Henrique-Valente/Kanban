#include <string.h>
#include "task.h"

Task* create_task(long* counter, int id,  short priority, const char* info,time_t* date, const char* person){
    Task* output = (Task*) malloc(sizeof(Task));
    (*counter)++;

    if (id != 0) output->id = id;
    else output->id = (*counter);

    output->info = strdup(info);
    output->made_in = time(NULL);
    output->priority = priority;

    if(person != NULL) output->person = strdup(person);
    else output->person = strdup("");
    if(date != NULL) output->date = *date;
    else output->date = 0;

    return output;
}

void destroy_task(Task* task, short delete_person){
    if(delete_person)
        free(task->person);
    free(task->info);
    free(task);
}