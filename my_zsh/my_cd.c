#include "my_zsh.h"

void my_cd(listnode *cmd)
{
    if(my_size(cmd) > 2)
    {
        printf("cd: string not in pwd: %s\n", cmd->next->element);
    }
    char* path = cmd->next->element;
    if(find_equals("-", path))
    { 
        path = "..";
    }
    if(chdir(path) == -1)
    {
        printf("cd: no such file or directory: %s\n", path);
    }
}