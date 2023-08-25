#include "shell.h"
char **_parse_input(char *lineptr) {
    const char delimiter[] = " ,;:-|";
    int args_index = 0;
    char *token;
    char **args_input;

    args_input = malloc(sizeof(char *) * (MAX_ARGS + 1));
    if (args_input == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(lineptr, delimiter);
    while (token != NULL && args_index < MAX_ARGS - 1) {
        if (strlen(token) >= MAX_TOTAL_LENGTH) {
            fprintf(stderr, "Argument too long\n");
            break;
        }
        args_input[args_index++] = strdup(token);
        token = strtok(NULL, delimiter);
    }
    args_input[args_index] = NULL;

    return args_input;
}

char **get_path() {
    char *main_path = getenv("PATH");
    if (main_path == NULL) {
        perror("Path does not exist");
        return NULL;
    }

    char *path = strdup(main_path);
    char *dir;
    char **path_tokens = malloc(sizeof(char *) * (MAX_PATHS + 1));
    if (path_tokens == NULL) {
        perror("Error allocating memory");
        return NULL;
    }

    int i = 0;
    dir = strtok(path, ":");
    while (dir != NULL && i < MAX_PATHS - 1) {
        path_tokens[i] = strdup(dir);
        if (path_tokens[i] == NULL) {
            perror("Duplicating tokens failed");
            for (int j = 0; j < i; j++) {
                free(path_tokens[j]);
            }
            free(path_tokens);
            free(path);  // Free allocated 'path' before returning
            return NULL;
        }
        dir = strtok(NULL, ":");
        i++;
    }
    path_tokens[i] = NULL;
    
    free(path);  // Free allocated 'path' after using it

    return path_tokens;
}

void _parse_path(char **path_tokens, char **args_input, char full_paths[][MAX_TOTAL_LENGTH]) {
    int ind = 0, path_len;

    for (ind = 0; path_tokens[ind] != NULL; ind++) {
        path_len = strlen(path_tokens[ind]);

        if (path_len + strlen(args_input[0]) + 1 >= MAX_TOTAL_LENGTH) {
            perror("Path too long, increase buffer.\n");
            return;
        }

        snprintf(full_paths[ind], MAX_TOTAL_LENGTH, "%s/%s", path_tokens[ind], args_input[0]);
    }
}

void cleanup_memory(char **args_input, char **path_tokens) {
    for (int i = 0; args_input[i] != NULL; i++) {
        free(args_input[i]);
    }
    free(args_input);

    for (int i = 0; path_tokens[i] != NULL; i++) {
        free(path_tokens[i]);
    }
    free(path_tokens);
}

void shell() {
    const char prompt[] = "(Myshell) $ ";
    
    while (1) {
        printf("%s", prompt);

        size_t buff_size = 0;
        char *lineptr = NULL;
        ssize_t read_chars = getline(&lineptr, &buff_size, stdin);

        if (read_chars == -1 || read_chars == EOF) {
            printf("Nothing was entered\n");
            free(lineptr);  // Free allocated memory before continuing
            continue;
        }

        if (read_chars == 1) {
            printf("No command entered\n");
            free(lineptr);  // Free allocated memory before continuing
            continue;
        }

        if (lineptr[read_chars - 1] == '\n') {
            lineptr[read_chars - 1] = '\0';
        }

        char **path_tokens = get_path();
        if (path_tokens == NULL) {
            free(lineptr);  // Free allocated memory before continuing
            continue;
        }

        char **args_input = _parse_input(lineptr);
        char full_paths[MAX_PATHS][MAX_TOTAL_LENGTH];
        _parse_path(path_tokens, args_input, full_paths); // Pass full_paths array

        int path_tokens_ind = 0;
        while (path_tokens[path_tokens_ind] != NULL) {
            pid_t PID = fork();
            
            if (PID == 0) {
                // Child process: Execute entered command
                for (int i = 0; full_paths[i][0] != '\0'; i++) {
                    if (access(full_paths[i], X_OK) == 0) {
                        execve(full_paths[i], args_input, NULL);
                    }
                }
                
                fprintf(stderr, "Command not found: %s\n", args_input[0]);
                exit(EXIT_FAILURE);
            } else if (PID == -1) {
                perror("fork");
            } else {
                // Parent process: Wait for the child to finish
                wait(NULL);
            }
            
            path_tokens_ind++;
        }

        cleanup_memory(args_input, path_tokens);
        free(lineptr);
    }
}

