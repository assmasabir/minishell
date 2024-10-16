/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:51:22 by asabir            #+#    #+#             */
/*   Updated: 2024/09/29 10:46:33 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	ft_size(int nb)
{
	unsigned int	len;

	len = 0;
	if (nb < 0)
		len += 1;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static char	*handle_negative(char *res, int n, int len)
{
	int	length;

	length = len;
	n = -n;
	res[0] = '-';
	len--;
	while (len > 0)
	{
		res[len] = n % 10 + '0';
		len--;
		n /= 10;
	}
	res[length] = '\0';
	return (res);
}

static char	*handle_positive(char *res, int n, int len)
{
	int	length;

	length = len;
	len -= 1;
	while (len >= 0)
	{
		res[len] = n % 10 + '0';
		len--;
		n /= 10;
	}
	res[length] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_size(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	if (n < 0)
	{
		res = handle_negative(res, n, len);
	}
	else
	{
		res = handle_positive(res, n, len);
	}
	return (res);
}

void	update_command_env(t_cmd_track *c_track, char *cmd)
{
	char	*join;

	join = ft_join("_=", cmd);
	change_variable(c_track, join);
	free(join);
}
