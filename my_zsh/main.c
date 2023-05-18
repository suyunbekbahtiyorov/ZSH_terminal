#include "my_zsh.h"

int main(int args, char** argv, char** envp)
{
    if(args == 2)
    {
        printf("Hello %s\n",argv[1]); // just for use
    }

    current_env = (data_env*)malloc(sizeof(data_env));
    current_env->env = (char**)malloc(sizeof(envp));
    current_env->size = 0;
    copy(current_env, envp);
    
    size_t max_readline = 256;
    while(1)
    {
        char* input = (char*)malloc(max_readline);
        if(getline(&input, &max_readline, stdin) == -1)
        {
            exit(0);
        }
        listnode* commands;
        if((commands = parse_input(input))  ==NULL)
        {
            printf("Parse error\n");
            continue;
        }
        head_pr(commands);
        free(input);
    } 
}