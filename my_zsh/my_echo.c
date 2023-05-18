#include "my_zsh.h"

char* to_file(listnode* lst) /* check echo is write to file */
{

    while(lst)
    {
        if(find_equals(">", lst->element) && lst->next !=NULL)
        {
            return lst->next->element;
        }
        lst = lst->next;
    }
    return NULL;
}

void write_to_file(char* file_name, char* text_to_file) /* Write string to file */
{
    if(access(file_name, F_OK) == 0)
    {
        remove(file_name);
    }
    creat(file_name, 0000644);
    int fd = open(file_name, O_WRONLY);
    if( fd == -1)
    {
        printf("Cannot open\n");
        return;
    }
    if(write(fd, text_to_file, strlen(text_to_file)) < 0)
    {
        printf("Cannot write to file\n");
    }
    free(text_to_file);
    close(fd);
}

int env_is_realize(const char* new_var, char* curr) /*  check enviromental variable is exist  */
{
    for(int i=0; curr[i] != '\0'; i++)
    {
        if(new_var[i] == '\0' && curr[i] == '=')
        {
            return 1;
        }
        if(new_var[i]=='\0' || new_var[i] != curr[i]|| (new_var[i] != '=' && curr[i] == '=') || (new_var[i] == '=' && curr[i] != '=') )
        {
            return 0;
        }
    }
    return 1;
}

char* env_s_var(data_env* curr_env, char* var)  /* Get enviromental variable is exist */
{
    var += 1;
    for(int i=0; i < curr_env->size; i++)
    {
        if(env_is_realize(var, curr_env->env[i]))
        {
            return (curr_env->env[i] + ( strlen(var) + 1 ));
        }
    }
    char* res = "";
    return res;
}

char* convert_to_string(listnode* node, data_env* curr_env) /* convert input data to string */
{
    char* result = (char*)malloc(sizeof(node)+my_size(node));
    char* expand = NULL;
    for(;node;)
    {
        if(node->element[0] == '$')
        {
            char* var = env_s_var(curr_env, node->element);
            expand = (char*)realloc(result, strlen(result)+100 + strlen(var)+5);
            strcat(expand, " ");
            strcat(expand, var);
            goto continue_block;
        }
        if(find_equals(node->element, ">"))
        {
            break;
        }
        strcat(result, node->element);
        strcat(result, " ");
        continue_block: 
        node = node->next;
    }
    char* res = (expand !=NULL) ? expand : (strlen(result) > 0) ? result : NULL;
    return res;
}

void my_echo(listnode* command, data_env* curr_env) /* echo command implementation  */
{
    if(my_size(command) == 1)
    {
        printf("\n");
        return;
    }
    command = command->next;
    char* file = NULL;
    if((file = to_file(command)) !=NULL)
    {
        write_to_file(file, convert_to_string(command, curr_env));
        return;
    }
    printf("%s\n",convert_to_string(command, curr_env));

}