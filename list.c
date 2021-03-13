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


List create_list(void)
{
    List aux;
    aux = (List)malloc(sizeof(List_node));
    if (aux != NULL)
    {
        aux->task = (Task *) malloc(sizeof(Task));
        aux->task->id = 0;
        aux->task->made_in = 0;
        aux->next = NULL;
    }
    return aux;
}


void search_list(List list, Task* to_find , List *prev, List *cur)
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


void insere_list(List list, Task *it) /* ordenado */
{
    List no;
    List prev, inutil;
    no = (List)malloc(sizeof(List_node));
    if (no != NULL)
    {

        no->task = it;
        search_list(list, it, &prev, &inutil);
        no->next = prev->next;
        prev->next = no;
    }
}

void print_list(List list)
{
    List l = list->next; /* Salta o header */
    while (l)
    {
        printf("|%d|%ld ", l->task->id, l->task->made_in);
        l = l->next;
    }
}

List find_list(List list, Task* it){
    List prev;
    List cur;

    search_list(list, it, &prev, &cur);

    return (cur);
}



int main(int argc, char const *argv[])
{   
    time_t t1 = time(NULL);
    printf("%s",ctime(&t1));

    List list = create_list();
    Task* s1 = (Task*) malloc(sizeof(Task));
    s1->made_in = t1;
    s1->id = 1;

    Task* s2 = (Task*) malloc(sizeof(Task));
    s2->made_in = t1+20; 
    s2->id = 2;

    Task* s3 = (Task*) malloc(sizeof(Task));
    s3->made_in = t1+20; 
    s3->id = 3;

    insere_list(list, s1);
    insere_list(list, s2);
    insere_list(list, s3);
    print_list(list);
    List res = find_list(list,s2);
    printf("\n");
    printf("%d\n", res->task->id);
    print_list(res);
    return 0;
}



