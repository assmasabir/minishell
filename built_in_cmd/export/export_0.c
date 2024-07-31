 #include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

int  ft_export(t_params *par, int foutput)
{
    int i;
    char **export;

    i = 0;
    // si empieza con # no importa lo que viene a continuacion lista los variables
    // si # viene al principio de una variable al centro, guarda los de antes y sale
    // si $ viene al principio y es solo lista export
    // si $ viene con otros variables skip y guarda lo de antes y despues
    if(par->cmd[1] == NULL || par->cmd[1][0] == '#' || (par->cmd[1][0] == '$' && par->cmd[2]==NULL))
    {
        export = sort_env(par, par->myenv);
        printf("fiiirst\n");
        while(export[i])
        {
            ft_putstr_exp(export[i], foutput);
            write(foutput, "\n", 1);
            i++;
        }
        free_matrix(export);
    }
    if(par->cmd[1] && par->cmd[1][0] != '#' && (par->cmd[1][0] != '$' || par->cmd[2] !=NULL))
    {
       handle_variables(par, foutput);
    }
    return 0;
}

char **create_copy(char **str, int *size)
{
    int i;
    char **cp;

    while(str[*size])
        (*size)++;
    cp = malloc(sizeof(char *)*(*size+1));
    i = 0;
    while(str[i])
    {
        cp[i]= ft_strdup(str[i]);
        i++;
    }
    cp[i]= NULL;
    return(cp);
}

void loop_over_env(t_params*par, char **cpy_env, char *small, int *index_of_small, int size_env)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while(i < size_env)
    {
        count++;
        while(cpy_env[i] && cpy_env[i][0] == '0')
            i++;
        if(cpy_env[i] && count == 1)
        {
            *index_of_small = i;
            small = cpy_env[i++];
        }
        if(par->myenv[i] && ft_strcmp(small, cpy_env[i]) > 0 && cpy_env[i][0] != '0')
        {
            small = cpy_env[i];
            *index_of_small = i;
        }
        i++;
    }
}

void loop(t_params *par, int size_env, char **export, char **cpy_env)
{
    int j;
    int index_of_small;
    char *small;

    j = 0;
    small = NULL;
    index_of_small = 0;
    while(j < size_env && par->myenv)
    {
        loop_over_env(par, cpy_env, small, &index_of_small, size_env);
        export[j] = ft_join("declare -x ", par->myenv[index_of_small]);
        free(cpy_env[index_of_small]);
        cpy_env[index_of_small]=ft_strdup("0");
        j++;
    }
}

char **sort_env(t_params *par, char **export)
{
    int size_env;
    char **cpy_env;



    size_env = 0;
    cpy_env = create_copy(par->myenv, &size_env);
    export = malloc(sizeof(char *)*(size_env+1));
    loop(par, size_env, export, cpy_env);
    export[size_env]=NULL;
    free_matrix(cpy_env);
    return(export);
}

int main(int argc, char **argv, char **env)
{
    t_params  *par;

    int i;
    i = 0;
    (void)argc;
    (void)argv;
    par = malloc(sizeof(t_params));
    par->cmd = malloc(7 * sizeof(char *));
    int size = size_env(env);
    par->myenv=create_copy(env, &size);
    if (par->cmd == NULL) {
        return 1;
    }
    par->cmd[0] = ft_strdup("export");
    par->cmd[1] = ft_strdup("?ngurp");
    par->cmd[2] = ft_strdup("uuuu=hoooooiiii");
    par->cmd[3] = ft_strdup("uuuu=aaaa");
    par->cmd[4] = ft_strdup("uuuu+=lalala");
    par->cmd[5] = ft_strdup("VSCODE_INJECTION+=miaw");
    par->cmd[6] = NULL;
    int fhgd = ft_export(par, 1);
    (void)fhgd;
    while(par->myenv[i])
    {
        printf("%s\n", par->myenv[i]);
        i++;
    }
    i = 0;
    while(par->cmd[i])
    {
        free(par->cmd[i]);
        i++;
    }
    free(par);

    // printf("%s\n", return_key("assma=thisisvalue"));



}