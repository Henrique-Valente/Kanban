#include "list.c"
#include "task.c"
#include "kanban.c"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int string_equal(char* a, char* b);

#define MAX_BUFFER 1000
int main(int argc, char const *argv[])
{
    Kanban* board = create_kanban(5);
    char* get_input = malloc(sizeof(char)*MAX_BUFFER);

    while(1){
        printf("Insert your command:\n");
        scanf("%s", get_input);

        if (string_equal(get_input,"insert"))
        {
            scanf ("%[^\n]%*c", get_input);
            char* info = strdup(get_input);
            
            printf("choose a priority:\n");
            scanf("%s", get_input);
            int priority = atoi(get_input);
            if(priority >= 1 && priority <= 10){
                task_to_do(board, info, priority);
            }else{
                printf("%s is not a valid priority\n", get_input);
            }
        }
        else if(string_equal(get_input,"do")){
            scanf("%s", get_input);
            int id = atoi(get_input);

            if(id >= 1){
                scanf("%s", get_input);
                char* person = strdup(get_input);
                scanf("%s", get_input);
                long deadline = atoi(get_input);
                
                if(deadline >= 1){
                    deadline = deadline*86400+ time(NULL); // deadline days from now on
                    int signal = do_task(board, id, person, deadline);
                    
                    if(signal == -1){ printf("The id %d does not exist\n", id); }
                    else if(signal == 1){ printf("Cannot add task, Doing board is full\n"); }

                }else{
                    printf("%s is not a valid deadline\n", get_input);
                }

            }else{
                printf("%s is not a valid id\n", get_input);
            }


        }
        else if(string_equal(get_input,"close")){

        }
        else if(string_equal(get_input,"reopen")){

        }
        else if(string_equal(get_input,"change")){
        }
        else if(string_equal(get_input,"show")){
            scanf("%s",get_input);
            if(string_equal(get_input, "board")){
                show_board(board);
            }else if(string_equal(get_input,"todo")){
                show_to_do(board);
            } else if(string_equal(get_input,"doing")){
                show_doing(board);
            }else if(string_equal(get_input,"done")){
                show_done(board);
            }else{
                printf("%s is not a valid view option\n", get_input);
            }
        }
        else if(string_equal(get_input,"exit")){
            break;
        }
        else{
            printf("%s is not a valid command\n", get_input);
        }
    }
    
    free(get_input);
    return 0;
}

int string_equal(char* a, char* b){ return strcmp(a,b) == 0; }