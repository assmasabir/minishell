#include "../minishell.h"


void alter_var(char *new_var, int i)
{
    environ[i] = ft_strdup(new_var);
}

void change_variable(char *new_var)
{
    int i;
    char *key_var;
    char *key_env;

    i = 0;
    key_var = return_key(new_var);
    while(environ[i])
    {   
        key_env = return_key(environ[i]);
        if(ft_strcmp(key_env,key_var) == 0)
        {
            free(key_env);
            break;
        }
        i++;
        free(key_env);
    }
    alter_var(new_var, i);
    free(key_var);
}

char *parent_directory_path(char *current_dir)
{
    char *parent_dir;
    int size_path;
    int max;

    parent_dir = NULL;
    if(current_dir[0] == '/' && current_dir[1] == '\0')
        return(current_dir);
    else
    {
        size_path = ft_strlen(current_dir); 
        max = size_path - 1; 
        while(current_dir[max] != '/')
        {
            max--;
        }
        parent_dir = malloc(sizeof(char)*(max + 1));
        parent_dir  = ft_strncpy(current_dir, parent_dir, max);
    }
    return (parent_dir);
}

void case_go_back(int output)
{
    char *old_env;
    char *current_env;
    char *var_and_value;

    old_env = getenv("OLDPWD");
    current_env = getenv("PWD");
    write(1, "\n", 1);
    if(chdir(old_env) == -1)
    {
        write(1, "error\n", 6);
        //!perro_ end exit failure(ex : if OLDPWD is unset)
        //!exit(1);
    }
    else
    {
        var_and_value = ft_join("OLDPWD=", current_env);
        ft_putstr(old_env, output);
        change_variable(var_and_value);
        free(var_and_value);
        var_and_value = ft_join("PWD=", old_env);
        change_variable(var_and_value);
        free(var_and_value);
    }
}

void case_go_up()
{
    char *current_dir;
    char *parent_dir;
    char *var_and_value;

    current_dir = NULL;
    current_dir = getcwd(current_dir, 0);
    if(current_dir == NULL)
    {
        free(current_dir);
        write(1, "error\n", 6);
        //perror end
    }
    parent_dir = parent_directory_path(current_dir);
    printf("i am parent dir %s\n", parent_dir);
    if(chdir(parent_dir) == -1)
    {
        write(1, "error\n", 6);
        //error message
    }
    else
    {
        var_and_value = ft_join("OLDPWD=", current_dir);
        change_variable(var_and_value);
        free(var_and_value);
        var_and_value = ft_join("PWD=", parent_dir);
        change_variable(var_and_value);
        free(var_and_value);
    }
    free(parent_dir);
    free(current_dir);

}

void case_go_home()
{
    char *home_dir;
    char *var_and_value;
    char *current_dir;

    current_dir = NULL;
    home_dir = getenv("HOME");
    current_dir = getcwd(current_dir, 0);
    if(current_dir == NULL)
    {
        write(1, "error\n", 6);
        //perror
    }
    if(home_dir == NULL)
    {
        //error home is not set
    }
    else
    {
        if(chdir(home_dir) == -1)
        {
            //error message
        }
        else 
        {
            var_and_value = ft_join("PWD=", home_dir);
            change_variable(var_and_value);
            free(var_and_value);
            var_and_value = ft_join("OLDPWD=", current_dir);
            free(current_dir);
            change_variable(var_and_value);
            free(var_and_value);
        }
    }
}

void handle_absolute_paths(t_params *par)
{
    char *current_dir;
    char *var_and_value;

    current_dir = NULL;
    current_dir = getcwd(current_dir, 0);
    if(current_dir == NULL)
    {
        write(1, "error\n", 6);
        //perror end
    }
    if(access(par->cmd[1], X_OK) == -1)
    {
        //error_and_exit
        write(1, "error\n", 6);
        perror(NULL);
        exit(-1);
    }
    else
    {
        if(chdir(par->cmd[1]) == -1)
        {
            //error message
        }
        else
        {
            var_and_value = ft_join("OLDPWD=", current_dir);
            free(current_dir);
            change_variable(var_and_value);
            free(var_and_value);
            var_and_value = ft_join("PWD=", par->cmd[1]);
            change_variable(var_and_value);
            free(var_and_value);
        }
    }
}

// ay envirement variable kaytzad meah new line ms hana testi b \0 temporairement
void ft_cd(t_params *par, int output)
{
    if(par->cmd[1] == NULL || ft_strcmp(par->cmd[1], ".") == 0)
    {
        write(1, "error\n", 6);    
        //free_and_exit_succes();  
    }
    else if(ft_strcmp(par->cmd[1], "-") == 0)
        case_go_back(output);
    else if(ft_strcmp(par->cmd[1], "..") == 0)
        case_go_up();
    else if(ft_strcmp(par->cmd[1], "~") == 0)
        case_go_home();
    else if(ft_strchr(par->cmd[1], '/' ) == 0)
    {
        handle_absolute_paths(par);    
    }
    else
    {
        write(1, "error\n", 6);
        //!error no sush file or directory
    }
}
