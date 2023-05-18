#include "my_zsh.h"

void my_pwd(listnode* node) /*  printf current working directory  */
{
    if(my_size(node) > 1)
    {
        printf("pwd: too many arguments\n");
        return;
    }
    char current_dir[PATH_MAX];
    if(getcwd(current_dir, PATH_MAX))
    {
        printf("%s\n", current_dir); 
    }
}
