#include "kanban.h"

List *create_to_do(void)
{
    List* priority = malloc(sizeof(List)*10);
    for (int i = 0; i < 10; i++)
    {
        priority[i] = create_list();
    }
    return priority;
}

