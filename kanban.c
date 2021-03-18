#include "kanban.h"

Kanban* create_kanban()
{
    Kanban* output = (Kanban*) malloc(sizeof(Kanban));
    output->counter = 0;
    output->doing = create_list();
    output->done = create_list();
    return output;
}
