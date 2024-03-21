#include <stdio.h>
#include <string.h>

// Define Date structure
typedef struct {
    int jour;
    int mois;
    int ans;
} Date;

// Define Task structure
typedef struct {
    int id;
    char title[100];
    char description[100];
    Date date;
    Date dueDate;
    enum {ToDo, InProgress, Done} status;
    enum {Low, Medium, High} priority;
} Task;

// Function to auto-increment the ID
int next_id() {
    static int id = 0;
    return ++id;
}

// Function to update an existing task
void updateTask(Task tasks[], int taskCount) {
    // Print tasks
    printf("Current tasks:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s\n", tasks[i].id, tasks[i].title);
    }

    // Prompt user for task ID to modify
    printf("Enter the ID of the task you want to modify: ");
    int taskId;
    scanf("%d", &taskId);

    // Find the task with the given ID
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == taskId) {
            // Prompt user for new task information
            printf("Enter new title: ");
            scanf("%s", tasks[i].title);

            printf("Enter new description: ");
            scanf(" %[^\n]", tasks[i].description);

            printf("Enter new start date (DD MM YYYY): ");
            scanf("%d %d %d", &tasks[i].date.jour, &tasks[i].date.mois, &tasks[i].date.ans);

            printf("Enter new due date (DD MM YYYY): ");
            scanf("%d %d %d", &tasks[i].dueDate.jour, &tasks[i].dueDate.mois, &tasks[i].dueDate.ans);

            printf("Enter new priority (1 to 3): ");
            printf("\n1. Low\n2. Medium\n3. High\n");
            scanf("%d", (int*)&tasks[i].priority);

            printf("Enter new status (1 to 3): ");
            printf("\n1. To Do\n2. In Progress\n3. Done\n");
            scanf("%d", (int*)&tasks[i].status);

            printf("Task updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Task not found!\n");
    }
}

// Function to delete a task
void deleteTask(Task tasks[], int *taskCount , int taskId) {
    for(int i = 0; i < *taskCount; i++) {
        if (tasks[i].id == taskId) {
            for (int j = i; j < *taskCount - 1; j++) {
                tasks[j] = tasks[j+1];
            }
            (*taskCount)--;
            printf("Task deleted successfully !\n");
            return;
        }
    }
    printf("Task not found!\n");
}

// Function to print tasks
void printTasks(Task tasks[], int taskCount) {
    printf("+-----+---------+-----------------+------------+------------+-------------+---------+\n");
    printf("| ID  |  Title  |   Description   |    Date    |  Due Date  |   Status    | Priority|\n");
    printf("+-----+---------+-----------------+------------+------------+-------------+---------+\n");
    for (int i = 0; i < taskCount; i++) {
        char statusString[12];
        switch(tasks[i].status) {
            case Done:
                strcpy(statusString, "Done");
                break;
            case InProgress:
                strcpy(statusString, "In Progress");
                break;
            case ToDo:
                strcpy(statusString, "To Do");
                break;
        }
        char priorityString[7];
        switch(tasks[i].priority) {
            case High:
                strcpy(priorityString, "High");
                break;
            case Medium:
                strcpy(priorityString, "Medium");
                break;
            case Low:
                strcpy(priorityString, "Low");
                break;
        }
        printf("| %2d  | %-7s | %-15s | %02d/%02d/%04d | %02d/%02d/%04d | %-11s |  %s  |\n",
               tasks[i].id, tasks[i].title, tasks[i].description, tasks[i].date.jour,tasks[i].date.mois,tasks[i].date.ans,
               tasks[i].dueDate.jour,tasks[i].dueDate.mois,tasks[i].dueDate.ans, statusString, priorityString);
    }
    printf("+-----+---------+-----------------+------------+------------+-------------+---------+\n");
}

// Function for filtering
void filterTasks(Task tasks[], int taskCount) {
    printf("Filter options:\n");
    printf("1: Filter by Priority\n");
    printf("2: Filter by Due Date\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            int priority;
            printf("Choose the priority you want to filter with: 1. Low, 2. Medium, 3. High\n");
            scanf("%d", &priority);
            printf("Filtered tasks:\n");
            for (int i = 0; i < taskCount; i++) {
                if (priority == tasks[i].priority) {
                    printf("ID: %d, Title: %s\n", tasks[i].id, tasks[i].title);
                }
            }
            break;
        }
        case 2: {
            int day, month, year;
            printf("Enter due date (DD MM YYYY): ");
            scanf("%d %d %d", &day, &month, &year);
            printf("Filtered tasks:\n");
            for (int i = 0; i < taskCount; i++) {
                if (day == tasks[i].dueDate.jour && month == tasks[i].dueDate.mois && year == tasks[i].dueDate.ans) {
                    printf("ID: %d, Title: %s\n", tasks[i].id, tasks[i].title);
                }
            }
            break;
        }
        default:
            printf("Invalid choice\n");
    }
}

void printMenu() {
    printf("Choose an option:\n");
    printf("1. Add a new task\n");
    printf("2. Modify an existing task\n");
    printf("3. Delete a task\n");
    printf("4. Filetring \n");
    printf("Your choice: ");
}

int main() {
    Task tasks[100]; // Array to store tasks
    int taskCount = 0; // Counter for tasks
    char choice; // Variable to store user's choice

    do {
        printMenu();

        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                printf("Enter information for a new task:\n");

                tasks[taskCount].id = next_id();

                printf("Enter a title: ");
                scanf("%99s", tasks[taskCount].title);

                printf("Enter a description: ");
                scanf(" %99[^\n]", tasks[taskCount].description); // Limited input to avoid buffer overflow

                printf("Enter start date (DD MM YYYY): ");
                scanf("%d %d %d", &tasks[taskCount].date.jour, &tasks[taskCount].date.mois, &tasks[taskCount].date.ans);

                printf("Enter due date (DD MM YYYY): ");
                scanf("%d %d %d", &tasks[taskCount].dueDate.jour, &tasks[taskCount].dueDate.mois, &tasks[taskCount].dueDate.ans);

                printf("Enter priority (1 to 3): ");
                printf("\n1. Low\n2. Medium\n3. High\n");
                scanf("%d", (int*)&tasks[taskCount].priority); // Cast to int* to avoid warnings

                printf("Enter status (1 to 3): ");
                printf("\n1. To Do\n2. In Progress\n3. Done\n");
                scanf("%d", (int*)&tasks[taskCount].status); // Cast to int* to avoid warnings

                taskCount++; // Increment task counter
                break;
            case '2':
                updateTask(tasks, taskCount);
                break;
            case '3':
                printf("Enter the ID of the task you want to delete: ");
                int taskId;
                scanf("%d", &taskId);
                deleteTask(tasks, &taskCount, taskId);
                break;
             case '4':
                filterTasks(tasks, taskCount);
                break;

            default:
                printf("Invalid choice\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y'); // Continue as long as the user enters 'y' or 'Y'

    printTasks(tasks, taskCount); // Print all tasks before exiting

    return 0;
}
