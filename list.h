#pragma once
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

/*
mode = 0 search by creation date
mode = 1 search by date
mode = 2 search by person
*/
void search_mode(List list, Task* it , List *prev, List *cur, int mode);

/* Search modes used by search_mode function */
void search_list_made_in(List list, Task* to_find , List *prev, List *cur);
void search_list_date(List list, Task* to_find , List *prev, List *cur);
void search_list_person(List list, Task* to_find , List *prev, List *cur);

void insert_list(List list, Task *it, int mode);
void print_list(List list);
List find_list(List list, Task* it);
