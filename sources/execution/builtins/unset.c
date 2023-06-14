/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:52:16 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 16:53:22 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (0);
}

static int	ft_unsetenv(char *name, char **env[])
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, ft_strlen(name)))
			new_env[j++] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_free_array(*env);
	*env = new_env;
	return (0);
}

int	ft_unset(char **args, char *env[])
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_unsetenv(args[i], env))
			return (1);
		i++;
	}
	return (0);
}
// Path: execution/builtins/exit.c