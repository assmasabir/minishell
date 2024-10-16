/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:13:04 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 04:21:46 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45)
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (sign * res);
}

char	**create_mini_copy(t_cmd_track *c_track, int *size)
{
	char	**cp;
	char	*tmp;

	(void)c_track;
	*size = 4;
	cp = safe_malloc(sizeof(char *) * 5);
	tmp = NULL;
	tmp = getcwd(tmp, 0);
	cp[0] = ft_join("PWD=", tmp);
	free(tmp);
	cp[1] = ft_strdup("SHLVL=1");
	cp[2] = ft_strdup("_=0");
	cp[3] = ft_strdup("OLDPWD");
	cp[4] = NULL;
	return (cp);
}

int	check_if_shlvl_valid_nb(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '+' || value[i] == '-')
		i++;
	while (value[i])
	{
		if (value[i] < '0' && value[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

void	reset_shlvl_helper(char *shlvl_env, char **join)
{
	int		nb;
	char	*shlvl_value;

	nb = ft_atoi(shlvl_env);
	if (nb >= 999)
	{
		printf("minishell: warning: shell level ");
		printf("(%d) too high, resetting to 1\n", nb + 1);
		shlvl_value = ft_itoa(1);
	}
	else if (nb < 0)
		shlvl_value = ft_itoa(0);
	else
		shlvl_value = ft_itoa(nb + 1);
	*join = ft_join("SHLVL=", shlvl_value);
	free(shlvl_value);
}

void	reset_shlvl(t_cmd_track *c_track)
{
	char	*shlvl_env;
	char	*join;

	join = NULL;
	shlvl_env = getenv("SHLVL");
	if (shlvl_env == NULL || check_if_shlvl_valid_nb(shlvl_env) == -1)
		join = ft_join("SHLVL=", "1");
	else
		reset_shlvl_helper(shlvl_env, &join);
	change_variable(c_track, join);
	free(join);
}
