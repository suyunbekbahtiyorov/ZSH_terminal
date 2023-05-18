#include "my_zsh.h"

int var_realize(const char* var, data_env* curr_env) // for set
{
    for(int i=0; i < curr_env->size; i++)
    {
        if(env_variable_realize(var, curr_env->env[i]) != -1)
        {
            curr_env->env[i] = (char*)var;
            return 1;
        }
    }
    return 0;
}

int add_variable(data_env* curr_env, char* new_var) /* add new variable to enviromental variable data  */
{
    curr_env->env[curr_env->size] = (char*)malloc(strlen(new_var));
    if(curr_env->env[curr_env->size] ==NULL)
    {
        return 0;
    }
    curr_env->env[curr_env->size++] = new_var;
    return 1;
}

void my_set__env(listnode* node, data_env* currenv) /* implement setenv */
{
    node = node->next;
    char* var = node->element; 
    if(var_realize(var, currenv) == 0)
    {
        add_variable(currenv, (char*)var);
    }
}