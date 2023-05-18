#include "my_zsh.h"

int my_size(listnode* lst) /* get my_size of listnode  */
{
    int len = 0;
    for (;lst;)
    {
        len++;
        lst = lst->next;
    }
    return len;
}

int find_equals(char* s1, char* s2) /*  check two strings is equals */
{
    if(strlen(s1) != strlen(s2))
    {
        return 0;
    }
    int i = 0;
    while( s1[i] !='\0')
    {
        if(s1[i] != s2[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int check_arg(char *file_namr) 
{
    int result;
    struct stat statinfo;

    result = stat(file_namr, &statinfo);
    if (result < 0)
    {
        return 0;
    }
    if (!S_ISREG(statinfo.st_mode))
    {
        return 0;
    }
    if (statinfo.st_uid == geteuid())
    {
        return statinfo.st_mode & S_IXUSR;
    }
    if (statinfo.st_gid == getegid())
    {
        return statinfo.st_mode & S_IXGRP;
    }
    return statinfo.st_mode & S_IXOTH;
}

int sub_ans(char* arg, char* exec, char* searchpath){
    char *beg, *end;
    int stop;
    int found;
    int len;
    beg = searchpath;
    stop = 0;
    found = 0;
    while(!stop && !found)
    {
        end = strchr(beg, ':');
        if (end == NULL)
        {
            stop = 1;
            strncpy(arg, beg, PATH_MAX);
            len = strlen(arg);
        }
        else
        {
            strncpy(arg, beg, end - beg);
            arg[end - beg] = '\0';
            len = end - beg;
        }
        if (arg[len - 1] != '/')
        {
            strcat(arg, "/");
        }
        strncat(arg, exec, PATH_MAX - len);
        found = check_arg(arg);
        if (!stop)
        {
            beg = end + 1;
        }
    }
    return found;
}

int find_arg(char *arg,char *exec) /*  find  full path  */
{
    char *searchpath;
    if (strchr(exec, '/') != NULL)
    {
        if (realpath(exec, arg) == NULL)
        {
            return 0;
        }
        else
        {
            return check_arg(arg);
        }
    }

    searchpath = getenv("PATH");
    if (searchpath == NULL)
    {
        return 0;
    }
    if (strlen(searchpath) <= 0)
    {
        return 0;
    }
    return sub_ans(arg, exec, searchpath); 
}


void copy(data_env* dest, char** envp)  /* copry eniviromental variables to our data struct */
{
    int i=0;
    while(envp[i]!=NULL)
    {
        dest->env[i] = (char*)malloc(strlen(envp[i]));
        dest->env[i] = envp[i];
        i++;
    }
    dest->size = i;
    dest->env[i] = NULL;
}
int env_variable_realize(const char* new_var, char* curr) // for unset. 
{
    int i=0;
    for(; curr[i] != '='; i++)
    {
        if(new_var[i]=='\0')
        {
            return -1;
        }
        if(new_var[i] != curr[i])
        {
            return -1;
        }
        if((new_var[i] == '=' && curr[i] != '=') || (new_var[i] != '=' && curr[i] == '='))
        {
            return -1;
        }
    }
    return i;
}

char* get_word(char* line, int index)  /*  cut string */
{
    char* result = (char*)malloc(strlen(line) - (strlen(line)-index));
    unsigned int i=0;
    while(i < (unsigned int)index)
    {
        result[i] = line[i];
        i++;
    }
    result[i] = '\0';
    return result;
}

void add_last(listnode** lst, char* elem) /* add new data to listnode */
{
    listnode* new = (listnode*)malloc(sizeof(listnode));
    new->element = elem;
    new->next = NULL;
    if(*lst == NULL)
    {
        *lst = new;
        return;
    }
    else
    {
        listnode* last = *lst;
        while (last->next !=NULL)
        {
            last = last->next;
        }
        last->next = new;
    }
}

listnode* parse_input(char *line) /* Parse command line by space */
{
    int i=0;
    listnode* node = NULL;
    for(;line[i] != '\0';)
    {
        if( line[i]  == ' ' || line[i] =='\n' || line[i]  =='\0')
        {
            char* word = get_word(line, i);
            if(word!=NULL && strlen(word) > 0)
            {
                add_last(&node, word);
            }
            line += i+1;
            i = 0;
        }
        i++;
    }
    return node;
}