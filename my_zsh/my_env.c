#include "my_zsh.h"

void my_env(data_env* current_env) /* implement env command */
{
    for(int i=0; current_env->env[i]!=NULL; i++)
    {
        if(current_env->env[i] !=NULL)
        {
            printf("%s\n", (current_env->env[i]));
        }
            
    }
}


void clear_var(int index, data_env* env_var) /* delete variable from enviromental variables data */
{
    if(index == env_var->size-1)
    {
        free(env_var->env[index]);
        env_var->size--;
        return;
    } 
    for(int i = index; i < env_var->size-1; i++)
    {
        env_var->env[i] = strdup(env_var->env[i+1]);
    }
    free(env_var->env[env_var->size-1]);
    env_var->size--;
}


void parse_env(listnode *node, data_env *curr_env) /* implement unsetenv command */
{
    if(my_size(node) != 2)
    {
        printf("error\n");
        return;
    }
    for(int i=0; i < curr_env->size; i++)
    {
        if(env_variable_realize(node->next->element,curr_env->env[i]) != -1 )
        {
            clear_var(i, curr_env);
            return ;
        }
    }
} 