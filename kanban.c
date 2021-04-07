#include "kanban.h"

Kanban* create_kanban()
{
    Kanban* output = (Kanban*) malloc(sizeof(Kanban));
    output->counter = 0;
    output->to_do = create_list();
    output->doing = create_list();
    output->done = create_list();
    return output;
}

void show_to_do(Kanban* kanban)
{
    List l = kanban->to_do->next;
    while (l != NULL)
    {
        //falta alterar a data
        printf("id:%ld Prioridade:%2d Início:%3ld Descrição: %s\n",l->task->id,l->task->priority,
        l->task->made_in,l->task->info);
        l = l->next;
    }
}

void show_doing(Kanban* kanban)
{
    List l = kanban->doing->next;
    while (l != NULL)
    {
        //falta alterar a data
        printf("id:%ld Prioridade:%2d Prazo:%3ld Descrição: %s Pessoa:%s\n",l->task->id,l->task->priority,
        l->task->date,l->task->info,l->task->person);
        l = l->next;
    }
}

void show_done(Kanban* kanban)
{
    List l = kanban->done->next;
    while (l != NULL)
    {
        //falta data de conclusão e arranjar maneira de converter
        printf("id:%ld Descrição: %s Conclusão:%ld Pessoa:%s\n",l->task->id,l->task->info,
        l->task->date,l->task->person);
        l = l->next;
    }
}

void show_board(Kanban* kanban)
{
    printf("TO DO\n");
    show_to_do(kanban);

    printf("\nDOING\n");
    show_doing(kanban);

    printf("\nDONE\n");
    show_done(kanban);
}

int do_task(Kanban* kanban, long id, char* pessoa, time_t deadline)
{
    Task* cur = remove_from_list(kanban->to_do,id);
    if (cur == NULL) return -1;
    if (kanban->doing_max_size <= list_size(kanban->doing)) return 1;
    cur->person = strdup(pessoa);
    cur->date = deadline;
    insert_list(kanban->doing,cur,2);
    return 0;
}
