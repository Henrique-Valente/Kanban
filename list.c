#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "list.h"


List create_list(void)
{
    
    List aux;
    aux = (List)malloc(sizeof(List_node));
    if (aux != NULL)
    {
        aux->task = (Task *) malloc(sizeof(Task));
        aux->task->id = 0;
        aux->task->made_in = 0;
        aux->task->date = 0;
        char* person = create_string("");
        if(person != NULL) aux->task->person = person;
        aux->next = NULL;
    }
    return aux;
}


void search_list_made_in(List list, Task* to_find , List *prev, List *cur)
{
    *prev = list;
    *cur = list->next;
    time_t date = to_find->made_in;
    while ( (*cur) != NULL &&  
            ( (*cur)->task->made_in < date ||
            ((*cur)->task->made_in == date &&  (*cur)->task->id < to_find -> id) )
        )
    {
        *prev = *cur;
        *cur = (*cur)->next;
    }
    if ((*cur) != NULL && (*cur)->task->made_in != date)
        *cur = NULL; /* Se elemento não encontrado*/
}

void search_list_date(List list, Task* to_find , List *prev, List *cur)
{
    *prev = list;
    *cur = list->next;
    time_t date = to_find->date;
    while ( (*cur) != NULL &&  
            ( (*cur)->task->date < date ||
            ((*cur)->task->date == date &&  (*cur)->task->id < to_find -> id) )
        )
    {
        *prev = *cur;
        *cur = (*cur)->next;
    }
    if ((*cur) != NULL && (*cur)->task->date != date)
        *cur = NULL; /* Se elemento não encontrado*/
}

void search_list_person(List list, Task* to_find , List *prev, List *cur)
{
    *prev = list;
    *cur = list->next;
    char* person = to_find->person;
    while ( (*cur) != NULL &&  
            ( strcmp((*cur)->task->person,person) < 0 ||
            ( strcmp((*cur)->task->person, person) == 0 &&  (*cur)->task->id < to_find -> id ) )
        )
    {
        *prev = *cur;
        *cur = (*cur)->next;
    }
    if ((*cur) != NULL && strcmp((*cur)->task->person, person) != 0)
        *cur = NULL; /* Se elemento não encontrado*/
}

void search_mode(List list, Task* it , List *prev, List *cur, int mode){
    switch (mode)
        {
        case 1:
            search_list_date(list, it, prev, cur);
            break;

        case 2:
            search_list_person(list, it, prev, cur);
            break;

        default:
            search_list_made_in(list, it, prev, cur);
            break;
        }
}

void insert_list(List list, Task *it, int mode) /* ordenado */
{
    List no;
    List prev, inutil;
    no = (List)malloc(sizeof(List_node));
    if (no != NULL)
    {
        no->task = it;
        search_mode(list, it, &prev, &inutil, mode); 
        no->next = prev->next;
        prev->next = no;
    }
}

void print_list(List list)
{
    List l = list->next; /* Salta o header */
    while (l)
    {
        printf("|%d|%s|%ld ", l->task->id, l->task->person,l->task->date);
        l = l->next;
    }
}

List find_list(List list, Task* it){
    List prev;
    List cur;

    search_list_made_in(list, it, &prev, &cur);

    return (cur);
}






