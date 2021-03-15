#include "list.c"
#include "task.c"
#include "kanban.c"

/*so estou a usar isto para testar*/
int main(int argc, char const *argv[])
{   
    time_t t1 = time(NULL);
    //printf("%s",ctime(&t1));

    long counter=0; // Usado para criar o id
    List list = create_list();
    time_t t2 = t1 + 2222;
    Task* s1 = create_task(&counter, "info1", &t2, "c");
    t2 = t1 + 555;
    Task* s2 = create_task(&counter, "info2", &t2, "b");
    t2 = t1 + 1000;
    Task* s3 = create_task(&counter, "info3",&t2, "a");

    int mode=1;
    insert_list(list, s2, mode);
    insert_list(list, s3, mode);
    insert_list(list, s1, mode);
    
    
    print_list(list);
    List res = find_list(list,s2->id);
    printf("\n");
    printf("id=%ld\n", res->task->id);
    printf("counter = %ld\n",counter);
   
    return 0;
}
