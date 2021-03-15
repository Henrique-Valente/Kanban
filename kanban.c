#include "kanban.h"


Kanban* create_kanban()
{
    Kanban* output = (Kanban*) malloc(sizeof(Kanban));
    output->counter = 0;
    //Nao Implementado ainda
    //output->to_do = create_to_do();
    output->doing = create_list();
    output->done = create_list();
    return output;
}