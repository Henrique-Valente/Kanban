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


List cria_lista(void)
{
    List aux;
    aux = (List)malloc(sizeof(List_node));
    if (aux != NULL)
    {
        aux->task = (Task *) malloc(sizeof(Task));
        aux->task->pid = 0;
        aux->task->made_in = 0;
        aux->next = NULL;
    }
    return aux;
}


void procura_lista(List lista, Task* to_find , List *ant, List *atual)
{
    *ant = lista;
    *atual = lista->next;
    time_t date = to_find->made_in;
    while ( (*atual) != NULL &&  
            ( (*atual)->task->made_in < date ||
            ((*atual)->task->made_in == date &&  (*atual)->task->pid < to_find -> pid) )
        )
    {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual) != NULL && (*atual)->task->made_in != date)
        *atual = NULL; /* Se elemento não encontrado*/
}


void insere_lista(List lista, Task *it) /* ordenado */
{
    List no;
    List ant, inutil;
    no = (List)malloc(sizeof(List_node));
    if (no != NULL)
    {

        no->task = it;
        procura_lista(lista, it, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

void imprime_lista(List lista)
{
    List l = lista->next; /* Salta o header */
    while (l)
    {
        printf("|%d|%ld ", l->task->pid, l->task->made_in);
        l = l->next;
    }
}

int main(int argc, char const *argv[])
{   
    time_t t1 = time(NULL);
    printf("%s",ctime(&t1));

    List list = cria_lista();
    Task* s1 = (Task*) malloc(sizeof(Task));
    s1->made_in = t1;
    s1->pid = 1;
    Task* s2 = (Task*) malloc(sizeof(Task));
    s2->made_in = t1+20; 
    s2->pid = 2;

    Task* s3 = (Task*) malloc(sizeof(Task));
    s3->made_in = t1+20; 
    s3->pid = 3;

    insere_lista(list, s1);
    insere_lista(list, s2);
    insere_lista(list, s3);
    imprime_lista(list);
    return 0;
}



