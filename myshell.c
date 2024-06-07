#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_COMMANDS 100
#define MAX_LENGTH 100
#define PATH "PATH"


// Global variables to store command history
char* command_history[MAX_COMMANDS];
int pid_history[MAX_COMMANDS];
int history_count = 0;


void set_path_env_var(int argc, char *argv[])
{
        char *newPath = getenv(PATH);
        for (int i = 1; i < argc; ++i)
        {
            strcat(newPath, ":");
            strcat(newPath, argv[i]);
        }
        setenv(PATH, newPath, 1);
}

void add_to_history(const char* cmd) {
    if (history_count < MAX_COMMANDS) {
        command_history[history_count] = strdup(cmd);
        if (command_history[history_count] != NULL) {
            history_count++;
        } else {
            perror("strdup failed");
        }
    } else {
        fprintf(stderr, "History limit reached. Cannot store more commands.\n");
    }
}

// Function to print the command history
void print_history() {
    for (int i = 0; i < history_count; i++) {
         printf("%s\n", command_history[i]);
    }
}




void execute_command(char* input) {
  // Create a copy of the input string for tokenization
    char input_copy[MAX_LENGTH];
    strncpy(input_copy, input, MAX_LENGTH);

    // Tokenize the input to get the command and its arguments
    char* argv[MAX_COMMANDS];
    int argc = 0;

    argv[argc] = strtok(input_copy, " ");
    while (argv[argc] != NULL) {
        argc++;
        argv[argc] = strtok(NULL, " ");
    }

    if (argc == 0) return; 
    argv[argc] = NULL;


    // Handle built-in commands

    if (strcmp(argv[0], "cd") == 0) {
        // Change directory
        if (argc > 1) {
            if (chdir(argv[1]) == -1) {
                perror("chdir failed");
            }
            else {
                printf("succsess command: %s\n", input); // Debug print statement


               add_to_history(input);

            }
        } else {
            fprintf(stderr, "cd: missing argument\n");
        }
        return;
    }

    if (strcmp(argv[0], "history") == 0) {
        add_to_history("history");

        print_history();
        return;
    }

    if (strcmp(argv[0], "pwd") == 0) {
        // Print current working directory
        char cwd[MAX_LENGTH];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
            add_to_history("pwd");

        } else {
            perror("getcwd failed");
        }
        return;
    }

    if (strcmp(argv[0], "exit") == 0) {
        // Exit the shell
        exit(0);
    }

    // If the command is not a built-in command, execute it using execvp
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        // Child process
        if (execvp(argv[0], argv) == -1) {
            perror("exec failed");
            exit(1);
        }
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
        add_to_history(input);

    }
}




int main(int argc, char *argv[]) {
    //Initialize command history and count
    char* command_history[MAX_COMMANDS];
   

    set_path_env_var(argc, argv);

    char input[MAX_LENGTH];

    while (1) {
        
        // gets the command 
        printf("$ ");
        fflush(stdout);
        if (fgets(input, MAX_LENGTH, stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        // Remove the newline character from the end of the input
        input[strcspn(input, "\n")] = 0;

 
        // Execute the command (assuming it's an executable)
        printf("Executing command: %s\n", input); // Debug print statement

        execute_command(input);
    }

    // Free command history before exiting
    for (int i = 0; i < history_count; i++) {
        free(command_history[i]);
    }

    return 0;
}