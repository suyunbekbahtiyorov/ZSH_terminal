#ifndef ZSH_LIB_H
#define ZSH_LIB_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <limits.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef DATA_ENV
#define DATA_ENV
typedef struct data_env {
    char** env;
    int size;
} data_env;
#endif

#ifndef COMMAND_ARR_LISTNODE
#define COMMAND_ARR_LISTNODE
typedef struct command_arr_listnode {
    char* element;
    struct command_arr_listnode* next;
}listnode;
#endif

int my_size(listnode* lst);
int find_equals(char* s1, char* s2);
int check_arg(char *file_namr);
int sub_ans(char* arg, char* exec, char* searchpath);
int env_variable_realize(const char* new_var, char* curr);
int find_arg(char *arg,char *exec);
void copy(data_env* dest, char** envp);
char* get_word(char* line, int index);
void add_last(listnode** lst, char* elem); 
listnode* parse_input(char *line);


/* commands */
void my_echo(listnode* command, data_env* curr_env);
void my_cd(listnode *cmd);
void my_set__env(listnode* node, data_env* currenv);
void my_env(data_env* current_env); 
void parse_env(listnode *node, data_env *curr_env);
void my_pwd(listnode* node);
data_env * current_env;
void my_which(listnode *list);
void head_pr(listnode* commands);

#endif