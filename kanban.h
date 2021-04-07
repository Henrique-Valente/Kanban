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
    int doing_max_size;
    List done;
} Kanban;

void show_to_do(Kanban*);
void show_doing(Kanban*);
void show_done(Kanban*);
void show_board(Kanban*);
Kanban* create_kanban(int max_doing_size);
void task_to_do(Kanban* kanban, char* info, short priority);
int do_task(Kanban* kanban, long id, char* person, time_t deadline);
int close_task(Kanban*, long);
#endif