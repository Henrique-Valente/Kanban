#include "list.c"
#include "task.c"
#include "kanban.c"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void print_options();
int valid_id(char* input, long* output);

#define MAX_BUFFER 1000

int main(int argc, char const *argv[])
{
    int option;
    char* get_input = malloc(sizeof(char)*MAX_BUFFER);
    Kanban* board = create_kanban(5);
    long id;
    while(1){
        printf("Type 9 to see avalible options:");
        // scanf("%d", option) causes a infinite loop when a letter is inputted.
        scanf("%s",get_input); 
        option = atoi(get_input);
        switch (option)
        {
        // Create a new task
        case 1:
            printf("Insert task info:");
            scanf ("\n%[^\n]%*c", get_input);
            char* info = strdup(get_input);
            
            printf("Choose a priority:");
            scanf("%s", get_input);
            int priority = atoi(get_input);
            if(priority >= 1 && priority <= 10){
                task_to_do(board, info, priority);
            } else printf("%s is not a valid priority\n", get_input);
            break;

        // Do task
        case 2 :
            if(valid_id(get_input, &id)){
                printf("Person in charge of the task:");
                scanf("%s",get_input);
                char* person = strdup(get_input);
                printf("Insert a deadline:");
                long deadline;
                scanf("%ld", &deadline);
                if(deadline >= 0) {
                    deadline += deadline*86400 + time(NULL);
                    int signal = do_task(board,id,person,deadline);
                    if(signal == -1) printf("The id does not exist in the To Do List\n");
                    else if(signal == 1) printf("The Doing list is currently full\n");

                } else printf("Invalid deadline\n");
            }
            break;
        
        // Change name
        case 3:
            if(valid_id(get_input,&id)){
                printf("Put this task in charge of:");
                scanf("%s",get_input);
                char* changeto = strdup(get_input);
                if (change_name(board,id,changeto) == -1)
                    printf("there is no task with id %ld currently being worked on\n", id);
            }
            break;

        // Close task
        case 4:
            
            if(valid_id(get_input, &id)) close_task(board, id);
            break;
        
        // Reopen Task
        case 5:
            if(valid_id(get_input,&id)){
                if(reopen_task(board,id)==-1)
                    printf("There is finished task with id %ld\n",id);
            }
            break;

        // Show board
        case 6:
            show_board(board);
            break;

        // Search by person
        case 7:

            break;

        // View all tasks
        case 8:

            break;

        // Print options
        case 9:
            print_options();
            break;

        // Exit
        case 10:
            free(get_input);
            return EXIT_SUCCESS;
        
        // Load Board
        case 11:
            printf("Insert file name:");
            scanf("%s",get_input);
            FILE* f = fopen(get_input,"r");
            if(f != NULL) inicialize_tasks(board,f);
            else printf("File %s was not found\n",get_input);
            break;

        // Invalid option
        default:
            printf("No valid option was selected\n");
            break;
        }
    }

    return 0;
}

int valid_id(char* input, long* output){
    printf("Insert the task id:");
    scanf("%s",input);
    int id = atoi(input);
    if(id >= 1){
        *output = id; 
        return 1;
    }
    printf("%s is not a valid id\n", input);
    return 0;
}

void print_options(){
    printf("Select one of the following options:\n");
    printf("-------------------------------------------------\n");
    printf("1- Create a new task\n");
    printf("2- Work on a task\n");
    printf("3- Change the person in charge of a task\n");
    printf("4- Finish a task that is being worked on\n");
    printf("5- Reopen a task\n");
    printf("6- View board\n");
    printf("7- View all tasks of a person\n");
    printf("8- View all tasks sorted by when it was made\n");
    printf("9- Print options\n");
    printf("10- Exit\n");
}