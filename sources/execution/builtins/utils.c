/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:05:32 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/20 18:27:04 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_env_nb(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_free_pointers(char *ptr1, char *ptr2, char *ptr3)
{
	if (ptr1)
		free (ptr1);
	if (ptr2)
		free (ptr2);
	if (ptr3)
		free (ptr3);
}

char	*setup_variable(char **args, int i, int flag)
{
	char	*string;

	if (!flag)
		string = ft_substr(args[i], 0,
				(size_t)(ft_strchr(args[i], '=') - args[i]));
	else
		string = ft_getenv(ft_substr(args[i], 0,
					(size_t)(ft_strchr(args[i], '=') - args[i])), g_vars->env);
	return (string);
}
