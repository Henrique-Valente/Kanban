#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

typedef struct lnode *List;
typedef struct lnode
{
    Task* task;
    List next;
} List_node;


List create_list();
int list_size(List);

/*
mode = 0 search by creation_date
mode = 1 search by date
mode = 2 search by person
mode = 3 search by priority and creation date;
*/
void search_mode(List list, Task* it , List *prev, List *cur, int mode);

/* Search modes used by search_mode function */
void search_list_made_in(List list, Task* to_find , List *prev, List *cur);
void search_list_date(List list, Task* to_find , List *prev, List *cur);
void search_list_person(List list, Task* to_find , List *prev, List *cur);
void search_list_priority(List list, Task* to_find , List *prev, List *cur);


/* the method search_list_id cannot be used to order */
void search_list_id(List list, long id_to_find, List *prev, List *cur); // this method in particular does not require an ordered set
void insert_list(List list, Task *it, int mode);
void print_list(List list);
List find_list(List list, long id_to_find);

/* returns pointer to matching task or null if not found*/
Task* remove_from_list(List list, long id);

#endif
