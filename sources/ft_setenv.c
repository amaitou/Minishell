/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:05:58 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/17 09:57:40 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_setenv(char *name, char *newval, char *env[])
{
	char	**var;
	int		i;

	var = NULL;
	i = -1;
	while (env && env[++i])
	{
		var = ft_split(env[i], '=');
		if (!strcmp(name, var[0]))
		{
			free (env[i]);
			env[i] = ft_strjoin(var[0], "=");
			env[i] = string_join(env[i], newval);
			clean(var);
			return ;
		}
		clean(var);
	}
}
