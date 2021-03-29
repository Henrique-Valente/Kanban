#ifndef KANBAN_H
#define KANBAN_H
#include "list.h"

/*
Struct that represents Kanban board composed by 3 lists
to_do list that is ordered by priority and creation_date,
doing list that is ordered by name,
done list that is ordered by date.
*/

typedef struct kanban
{
    long counter; //used to assign id to the tasks
    List to_do;
    List doing;
    List done;
} Kanban;

void show_to_do(Kanban*);
void show_doing(Kanban*);
void show_done(Kanban*);
void show_board(Kanban*);
Kanban* create_kanban(void);

#endif