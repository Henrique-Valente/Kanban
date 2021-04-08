#include "kanban.h"
#include <stdio.h>

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
        strftime(buffer,80,"%d/%m/%y %X", info);

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
        strftime(buffer,80,"%d/%m/%y %X", info);

        printf("id:%ld Priority:%2d Deadline:%s Description: %s Person:%s\n",l->task->id,l->task->priority,
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
        strftime(buffer,80,"%d/%m/%y %X", info);

        printf("id:%ld Description: %s Conclusion:%s Pessoa:%s\n",l->task->id,l->task->info,
        buffer,l->task->person);
        l = l->next;
    }
}

void show_board(Kanban* kanban)
{
    printf("*** Kanban ***\n");
    printf("\nTO DO\n");
    show_to_do(kanban);

    printf("\nDOING(%d)\n",kanban->doing_max_size);
    show_doing(kanban);

    printf("\nDONE\n");
    show_done(kanban);
    printf("\n----------------------------------\n");
}

void task_to_do(Kanban* kanban, char* info, short priority){
    List l = kanban->to_do;
    Task* t1 = create_task(&(kanban->counter),0,priority,info,NULL,NULL);
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

int reopen_task(Kanban *kanban, long id){
    Task* cur = remove_from_list(kanban->done,id);
    if(cur == NULL) return -1;
    cur->person = NULL;
    insert_list(kanban->to_do,cur,3);
    return 0;
}

void delete_newline(char s[]){
    int n = strlen(s);
    if (s[n-1] == '\n')
        s[n-1] = '\0';
}

void view_tasks_of(Kanban* kanban, char* person){
    List doing = kanban -> doing;
    List done = kanban -> done;
    List cur = doing->next;
    struct tm *info;
    char buffer[80];
    printf("%s has the following tasks:\n",person);
    printf("Tasks in Doing:\n");
    while(cur != NULL){
        if(strcmp((cur)->task->person, person) == 0){
            info = localtime( &(cur->task->date) );
            strftime(buffer,80,"%d/%m/%y", info);
            printf("id:%ld Prioridade:%2d Prazo:%s Description: %s\n",cur->task->id,cur->task->priority,
                                                                        buffer,cur->task->info);
        }
        cur = cur->next;
    }

    cur = done->next;

    printf("Tasks in Done:\n");
    while(cur != NULL){
        if(strcmp((cur)->task->person, person) == 0){
            info = localtime( &(cur->task->date) );
            strftime(buffer,80,"%d/%m/%y", info);
            printf("id:%ld Prioridade:%2d Prazo:%s Description: %s\n",cur->task->id,cur->task->priority,
                                                                        buffer,cur->task->info);
        }
        cur = cur->next;
    }
}

Kanban* inicialize_tasks(FILE* f){
    ssize_t read;
    size_t size = 0;
    char *line = NULL;

    int size_doing;
    fscanf(f,"%d",&size_doing);
    fgetc(f);//consume \n
    Kanban* kanban = create_kanban(size_doing);

    int list, priority;
    long id;
    char *info = NULL;
    char person[50];
    long made_in, deadline;

    while ((read = getline(&line,&size, f)) != -1)
    {
        delete_newline(line);
        sscanf(line,"%d %ld %d %ld %ld %s", &list, &id, &priority, &made_in, &deadline,person);

        if ((read = getline(&info,&size, f)) == -1){
            printf("File with data not valid!\n");
            destroy_kanban(kanban);
            return NULL;
        }
        delete_newline(info);
        Task* t1 = create_task(&(kanban->counter),id,priority,info,NULL,NULL);
        t1->made_in = made_in;
        switch (list)
        {
        case 1:
            insert_list(kanban->to_do,t1,3);
            break;
        case 2:
            t1->person = strdup(person);
            t1->date = deadline;
            insert_list(kanban->doing,t1,2);
            break;
        case 3:
            t1->person = strdup(person);
            t1->date = deadline;
            insert_list(kanban->done,t1,1);
        default:
            break;
        }
    }
    return kanban;
}

void destroy_kanban(Kanban* kanban){
    destroy_list(kanban->to_do);
    destroy_list(kanban->doing);
    destroy_list(kanban->done);
    free(kanban);
}

void save_list(int list,List l, FILE* f){
    char temp[100];
    while (l != NULL)
    {
        char* name;
        if (strcmp(l->task->person,"") == 0) name = strdup("\"\"");
        else name = strdup(l->task->person);
        sprintf(temp,"%d %ld %d %ld %ld %s\n%s\n",list,l->task->id,l->task->priority,
        l->task->made_in,l->task->date,name,l->task->info);
        fputs(temp,f);
        l = l->next;
    }
}

void save_state(Kanban *kanban, FILE* f){
    char temp[100];
    sprintf(temp,"%d\n",kanban->doing_max_size);
    fputs(temp,f);

    save_list(1,kanban->to_do->next,f);
    save_list(2,kanban->doing->next,f);
    save_list(3,kanban->done->next,f);
}

void search_by_made_in(Kanban* kanban){
    List store = create_list();
    List cur = kanban->to_do->next;
    struct tm *info;
    char buffer[80];

    while(cur != NULL){
        insert_list(store,cur->task,0);
        cur = cur->next;
    }
     
    cur = kanban->doing->next;

    while(cur != NULL){
        insert_list(store,cur->task,0);
        cur = cur->next;
    }

    cur = kanban->done->next;

    while(cur != NULL){
        insert_list(store,cur->task,0);
        cur = cur->next;
    }

    cur = store->next;
    while(cur != NULL){
            info = localtime( &(cur->task->made_in) );
            strftime(buffer,80,"%d/%m/%y %X", info);
            printf("id:%ld Priority:%d Made in:%s Description:%s\n",cur->task->id,cur->task->priority,
                                                                     buffer,cur->task->info);
            cur = cur->next;
    }
}