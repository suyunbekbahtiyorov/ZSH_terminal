#include "my_zsh.h"

int built_in(char* cmd_name) /* check program is builtin or not*/
{
    if(find_equals("echo", cmd_name))
    {
        printf("echo: shell built-in command\n");
        return 1;
    }
    else if(find_equals("cd", cmd_name))
    {
        printf("cd: shell built-in command\n");
        return 1;
    }
    else if(find_equals("setenv", cmd_name))
    {
        printf("setenv: shell built-in command\n");
        return 1;
    }
    else if(find_equals( "unsetenv", cmd_name))
    {
        printf("unsetenv: shell built-in command\n");
        return 1;
    }
    else if(find_equals("env", cmd_name))
    {
        printf("env: shell built-in command\n");
        return 1;
    }
    else if(find_equals("pwd", cmd_name))
    {
        printf("pwd: shell built-in command\n");
        return 1;
    }
    else if(find_equals("exit", cmd_name)){
        printf("exit: shell built-in command\n");
        return 1;
    }
    else if(find_equals("which", cmd_name)){
        printf("which: shell built-in command\n");
        return 1;
    } 
    return 0;
}


void my_which(listnode *list) /* implement  which */
{
    while (list->next !=NULL){
        list = list->next;
        if(built_in(list->element)){
            continue;
        }
        char path[PATH_MAX + 1];
        char *progpath = strdup(list->element);
        char *app = list->element;
        if (find_arg(path, app)){
             printf("%s\n", path);
        }
        else{
            printf("'%s' not found\n", app);
        }
        free(progpath);
    }
}