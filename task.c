#include <string.h>
#include "task.h"

Task* create_task(long* counter, const char* info, time_t* date, const char* person){
    Task* output = (Task*) malloc(sizeof(Task));
    (*counter)++;
    output->id = (*counter);
    output->info = strdup(info);
    output->made_in = time(NULL);

    if(person != NULL) output->person = strdup(person);
    else output->person = strdup("");
    if(date != NULL) output->date = *date;
    else output->date = 0;

    return output;
}

void destroy_task(Task* task, short delete_person){
    if(delete_person) {
        free(task->person);
    }
    free(task);
}