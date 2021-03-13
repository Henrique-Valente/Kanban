#pragma once
#include <string.h>
#include "task.h"

char* create_string(const char* str){
    int l = strlen(str)+1;
    char* output = (char*) malloc(sizeof(char*)*l);
    strcpy(output, str);
    return output;
}


Task* create_task(long* counter, const char* info, time_t* date, const char* person){
    Task* output = (Task*) malloc(sizeof(Task));
    (*counter)++;
    output->id = (*counter);
    output->info = create_string(info);
    output->made_in = time(NULL);

    if(person != NULL) output->person = create_string(person);
    else output->person = create_string("");
    if(date != NULL) output->date = *date;
    else output->date = 0;

    return output;
}