#include "list.c"
#include "task.c"
#include "kanban.c"

/*so estou a usar isto para testar*/
int main(int argc, char const *argv[])
{   
   /* time_t t1 = time(NULL);
    //printf("%s",ctime(&t1));

    long counter=0; // Usado para criar o id
    List list = create_list();
    time_t t2 = t1 + 100;
    Task* s1 = create_task(&counter, 1, "info1", &t2, "c");
    sleep(1);
    t2 = t1 + 200;
    Task* s2 = create_task(&counter, 1, "info2", &t2, "b");
    sleep(1);
    t2 = t1 + 300;
    Task* s3 = create_task(&counter, 4, "info3",&t2, "a");
    Task* s4 = create_task(&counter, 1, "info4",&t2, "d");
    Task* s5 = create_task(&counter, 4, "info5",&t2, "e");
    Task* s6 = create_task(&counter, 5, "info6",&t2, "f");
    

    int mode=3;
    insert_list(list, s2, mode);
    print_list(list);
    insert_list(list, s3, mode);
    print_list(list);
    insert_list(list, s5, mode);
    insert_list(list, s1, mode);
    insert_list(list, s6, mode);
    insert_list(list, s4, mode);
    
    destroy_task(remove_from_list(list,2),1);
    print_list(list);
    List res = find_list(list,s2->id);
    if(res != NULL) printf("id=%ld\n", res->task->id);
    printf("counter = %ld\n",counter); */
    time_t t1 = time(NULL);
    Kanban* k = create_kanban(5);
    task_to_do(k, "info1", 3);
    show_board(k);
    printf("-----------------------\n");
    do_task(k,1,"henrique",t1);
    show_board(k);
    printf("-----------------------\n");
    close_task(k,1);
    show_board(k);
    printf("-----------------------\n");
    reopen_task(k,1);
    show_board(k);
   
    return 0;
}
