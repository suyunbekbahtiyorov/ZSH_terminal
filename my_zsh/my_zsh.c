#include "my_zsh.h"

char** convert_to_array(listnode* list) /* Get 2D array from struct data*/
{
    char** array = (char**)malloc(sizeof(char*) * (my_size(list) + 1));
    int i = 0;
    for (; list ;)
    {
        array[i] = (char*)malloc(strlen(list->element));  // initiaze index size;
        strcpy(array[i++], list->element);                // set string to index;
        list = list->next;                              // jump to next node;
    }
    array[i] = NULL;
    return array;
}

void binary_execute(listnode* commands, data_env* curr_env) /* drive program  as child proccess */
{
    pid_t pid;  //, wpid;
    int status;
    pid = fork();
    char** args = convert_to_array(commands);
    if (pid == 0)
    {
        char path[PATH_MAX + 1]; 
        char* app = strdup(commands->element);
        if (find_arg(path, app)) 
        {
            if(execve(path, args, curr_env->env) == -1)
            {
                printf("my_zsh: command not found: %s\n", args[0]);
            }
        }
        else
        {
            printf("my_zsh: command not found: %s\n", args[0]);
        }
        free(app);
        for (int i = 0; args[i] !=NULL; i++)
        {
            free(args[i]);
        }
        exit(0);
    }
    else
    {
        while (!WIFEXITED(status) && !WIFSIGNALED(status)){
            waitpid(pid, &status, WUNTRACED);
            if(WTERMSIG(status) == SIGSEGV && WIFSIGNALED(status)) 
            {
                puts("Segmentation fault");
            }
        }
    }
}

data_env * current_env;

void head_pr(listnode* commands) /* manage and run program  */
{
    char* cmd = commands->element;
    if(find_equals("echo", cmd))
    {
        my_echo(commands, current_env);
    }
    else if(find_equals("cd", cmd))
    {
        my_cd(commands);
    }
    else if(find_equals("setenv", cmd))
    {
        my_set__env(commands, current_env);
    }
    else if(find_equals( "unsetenv", cmd))
    {
        parse_env(commands, current_env);
    }
    else if(find_equals("env", cmd))
    {
        my_env(current_env);
    }
    else if(find_equals("pwd", cmd))
    {
        my_pwd(commands);
    }
    else if(find_equals("exit", cmd))
    {
        exit(0);
    }
    else if(find_equals("which", cmd))
    {
        my_which(commands);
    }
    else{
        binary_execute(commands, current_env);
    }
}