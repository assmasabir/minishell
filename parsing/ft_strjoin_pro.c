/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:31:05 by yait-nas          #+#    #+#             */
/*   Updated: 2024/10/05 20:21:24 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_pro(char *s1, char *s2, char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = safe_malloc((len1 + len2 + len3 + 1) * sizeof(char));
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	free(s1);
	free(s2);
	return (result);
}

void	hide_double_single_quotes(char *value)
{
	while (*value)
	{
		if (*value == '"')
			*value = -1;
		if (*value == '\'')
			*value = -2;
		value++;
	}
}

void	found_dolar_sign(char **str, char **new, int *i, char **env)
{
	char	*key;
	char	*value;

	new[0][*i] = '\0';
	(*str)++;
	key = get_key(str);
	value = get_value(key, env, str);
	hide_double_single_quotes(value);
	free(key);
	*new = ft_strjoin_pro(*new, value, *str);
	*i = ft_strlen(*new);
}

void	found_dolar_sign_inside_dq(char **str, char **new, int *i, char **env)
{
	char	*key;
	char	*value;

	(*str)++;
	key = get_key(str);
	value = get_value(key, env, str);
	free(key);
	*new = ft_strjoin_pro(*new, value, *str);
	*i = ft_strlen(*new);
}
