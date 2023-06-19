/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:45:42 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/19 15:48:10 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean(char **var)
{
	int	i;

	i = -1;
	while (var[++i])
		free(var[i]);
	free(var);
}

char	*ft_getenv(char *name, char *env[])
{
	char	**var;
	char	*value;
	int		i;

	var = NULL;
	value = NULL;
	i = -1;
	while (env && env[++i])
	{
		var = ft_split(env[i], '=');
		if (var[0] && !ft_strcmp(name, var[0]))
		{
			if (var[1])
				value = ft_substr(env[i], ft_strlen(var[0]) + 1,
						ft_strlen(env[i]));
			else
				value = NULL;
			clean(var);
			return (value);
		}
		clean(var);
	}
	return (NULL);
}
