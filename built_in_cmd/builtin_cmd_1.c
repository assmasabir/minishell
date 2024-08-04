#include "../minishell.h"


char *parent_directory_path(char *current_dir)
{
    int i;
    char *parent_dir;
    int size_path;
    int max;

    i = 1;
    if(current_dir[0] && current_dir[1] == '\0')
        return(current_dir);
    else
    {
        size_path = ft_strlen(current_dir); 
        max = size_path - 1; 
        while(max != '/')
        {
            max--;
        }
        max = size_path - max;
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
        change_or_append_var_value(var_and_value, 1);
        free(var_and_value);
        var_and_value = ft_join("PWD=", old_env);
        change_or_append_var_value(var_and_value, 1);
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
        write(1, "error\n", 6);
        //perror end
    }
    parent_dir = parent_directory_path(current_dir);
    if(chdir(parent_dir) == -1)
    {
        write(1, "error\n", 6);
            //error message
    }
    else
    {
        var_and_value = ft_join("OLDPWD=", current_dir);
        change_or_append_var_value(var_and_value, 1);
        free(var_and_value);
        var_and_value = ft_join("PWD=", parent_dir);
        change_or_append_var_value(var_and_value, 1);
        free(var_and_value);
    }
}

void case_go_home()
{
    
}
// ay envirement variable kaytzad meah new line ms hana testi b \0 temporairement
void ft_cd(t_params *par, int output)
{
    if(par->cmd[1] == NULL || ft_strcmp(par->cmd[1], ".") == 0)
        free_and_exit_succes();
    else if(ft_strcmp(par->cmd[1], "-") == 0)
        case_go_back(output);
    else if(ft_strcmp(par->cmd[1], ".." == 0))
        case_go_up();
    else if(ft_strcmp(par->cmd[1], "~" == 0))
        case_go_home();
}

