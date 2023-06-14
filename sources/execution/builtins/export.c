/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:48:28 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 16:53:14 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_check_export(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_add_env(char *arg, char *const env[])
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	ft_free_array(env);
	g_env = new_env;
	return (0);
}

int	ft_update_env(char *arg, char *const env[])
{
	int		i;
	char	*key;
	char	**new_env;

	i = 0;
	while (env[i])
	{
		key = ft_get_key(env[i]);
		if (!ft_strcmp(key, ft_get_key(arg)))
		{
			free(key);
			new_env = ft_update_env2(arg, env, i);
			ft_free_array(env);
			g_env = new_env;
			return (0);
		}
		free(key);
		i++;
	}
	return (0);
}

int	ft_export(char **args, char *env[])
{
	int	i;

	i = 1;
	if (!args[1])
		return (ft_env(env));
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (ft_check_export(args[i]))
				ft_add_env(args[i], env);
			else
				ft_update_env(args[i], env);
		}
		else
			ft_add_env(args[i], env);
		i++;
	}
	return (0);
}
