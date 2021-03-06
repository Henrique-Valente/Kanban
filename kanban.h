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

void show_to_do(Kanban* kanban, FILE* out);
void show_doing(Kanban* kanban, FILE* out);
void show_done(Kanban* kanban, FILE* out);
void show_board(Kanban* kanban, FILE* out);

Kanban* create_kanban(int max_doing_size);
void task_to_do(Kanban* kanban, char* info, short priority);
int do_task(Kanban* kanban, long id, char* person, time_t deadline);
int close_task(Kanban* kanban, long id);
int abort_task(Kanban* kanban, long id); // Removes a task from Doing and adds it to To Do
int change_name(Kanban* kanban, long id, char* change_to);
int reopen_task(Kanban *kanban, long id);

void view_tasks_of(Kanban* kanban, char* person, FILE* out);
void search_by_made_in(Kanban* kanban, FILE* out);

Kanban* inicialize_tasks(FILE* f);
void save_state(Kanban* kanban, FILE* f);
void destroy_kanban(Kanban* kanban);
void save_list(int list,List l, FILE* f);
#endif
