#include "../minishell.h"

 //?do you still need it?
// char *uppercase(char *name) 
// {
//     int i;

//     i = 0;
//     while(name[i])
//     {
//         if(name[i] >= 'a' && name[i] <= 'z')
//         {
//             name[i] -= 32;
//         }
//         i++;
//     }
//     return(name);
// }

// char * fill_and_concat(char *name, char *value)
// {
//     int i;
//     int size_name;
//     int size_value;
//     char *new_env;

//     i = 0;
//     size_name =  ft_strlen(name);
//     size_value = ft_strlen(value) + 1;
//     new_env = malloc(ft_strlen(name)+ft_strlen(value)+2);
//     name = capitalize(name);
//     while(i <= size_name)
//     {
//         new_env[i] = name[i];
//         i++;
//     }
//     new_env[i++] = '=';
//     while(i <= size_value)
//     {
//         new_env[i] = value[i];
//         i++;
//     }
//     new_env[i] = '\0';
//     return(new_env);
// }

// int set_env(char *name, char *value)
// {
//     int i;
//     int found;

//     i = 0;
//     found = 0;
//     while(par->myenv[i])
//     {
//         if(ft_strncmp(name, par->myenv[i], ft_strlen(name)) == 0)
//         {   
//             free(par->myenv[i]);
//             par->myenv[i]= fill_and_concat(name, value);
//             found = 1;
//         }
//         i++;
//     }
//     if(found == 0)
//     {

//     }
// }