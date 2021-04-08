#include "kanban.h"

Kanban* create_kanban(int doing_max_size)
{
    Kanban* output = (Kanban*) malloc(sizeof(Kanban));
    output->counter = 0;
    output->to_do = create_list();
    output->doing = create_list();
    output->done = create_list();
    output->doing_max_size = doing_max_size;
    return output;
}

void show_to_do(Kanban* kanban)
{
    List l = kanban->to_do->next;
    struct tm *info;
    char buffer[80];
    while (l != NULL)
    {
        info = localtime( &(l->task->made_in) );
        strftime(buffer,80,"%x", info);
        
        printf("id:%ld Priority:%2d Begin:%s Description: %s\n",l->task->id,l->task->priority,
        buffer,l->task->info);
        l = l->next;
    }
}

void show_doing(Kanban* kanban)
{
    List l = kanban->doing->next;
    struct tm *info;
    char buffer[80];
    while (l != NULL)
    {
        info = localtime( &(l->task->date) );
        strftime(buffer,80,"%x", info);

        printf("id:%ld Prioridade:%2d Prazo:%s Description: %s Person:%s\n",l->task->id,l->task->priority,
        buffer,l->task->info,l->task->person);
        l = l->next;
    }
}

void show_done(Kanban* kanban)
{
    List l = kanban->done->next;
    struct tm *info;
    char buffer[80];
    while (l != NULL)
    {
        info = localtime( &(l->task->date) );
        strftime(buffer,80,"%x", info);
        
        printf("id:%ld Descricao: %s Conclusao:%s Pessoa:%s\n",l->task->id,l->task->info,
        buffer,l->task->person);
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

void task_to_do(Kanban* kanban, char* info, short priority){
    List l = kanban->to_do;
    Task* t1 = create_task(&(kanban->counter),priority,info,NULL,NULL);
    insert_list(l,t1,3);
}

int do_task(Kanban* kanban, long id, char* person, time_t deadline)
{
    if (kanban->doing_max_size <= list_size(kanban->doing)) return 1;
    Task* cur = remove_from_list(kanban->to_do,id);
    if (cur == NULL) return -1;
    
    cur->person = strdup(person);
    cur->date = deadline;
    insert_list(kanban->doing,cur,2);
    return 0;
}

int close_task(Kanban* kanban, long id)
{
    Task* cur = remove_from_list(kanban->doing,id);
    if (cur == NULL) return -1;
    cur->date = time(NULL);
    insert_list(kanban->done,cur,1);
    return 0;
}

int change_name(Kanban* kanban, long id, char* change_to){
    List l = kanban -> doing;
    List cur = NULL;
    cur = find_list(l,id);
    if(cur == NULL) return -1;
    else cur->task->person = strdup(change_to);
    return 0;
}