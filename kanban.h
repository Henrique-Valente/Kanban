#ifndef KANBAN_H
#define KANBAN_H
#include "list.h"


typedef struct kanban
{
    long counter; //used to assign id to the tasks
    List* to_do;
    List doing;
    List done;
} Kanban;


Kanban* create_kanban();


#endif