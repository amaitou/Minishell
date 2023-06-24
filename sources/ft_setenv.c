/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:05:58 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/24 13:05:53 by amait-ou         ###   ########.fr       */
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
		if (var && !ft_strcmp(name, var[0]))
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
