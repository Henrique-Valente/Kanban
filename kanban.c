#include "kanban.h"


Kanban* create_kanban()
{
    Kanban* output = (Kanban*) malloc(sizeof(Kanban));
    output->counter = 0;
    output->doing = create_list();
    output->done = create_list();
    return output;
}

List *create_to_do(void)
{
    List* priority = malloc(sizeof(List)*10);
    for (int i = 0; i < 10; i++)
    {
        priority[i] = malloc(sizeof(List));
        priority[i] = create_list();
    }
    return priority;
}
