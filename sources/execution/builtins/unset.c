/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:52:16 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/19 20:50:33 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args)
{
	ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	ft_putchar_fd(args[1][0], STDERR_FILENO);
	ft_putchar_fd(args[1][1], STDERR_FILENO);
	ft_putendl_fd(" invalid option", STDERR_FILENO);
	ft_putendl_fd("unset: usage: unset [name]...", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	copy_env(char **env, char **newenv, int len)
{
	int	i;

	i = 0;
	while (env && env[i] && i < len)
	{
		newenv[i] = ft_strdup(env[i]);
		i++;
	}
}

static void	remove_variable(char *string)
{
	char	**newenv;
	char	**tmp;
	int		i;

	i = -1;
	while (g_vars->env[++i])
	{
		tmp = ft_split(g_vars->env[i], '=');
		if (tmp && !ft_strcmp(tmp[0], string))
		{
			newenv = (char **)ft_calloc(get_env_nb(g_vars->env),
					sizeof(char *));
			copy_env(g_vars->env, newenv, i);
			copy_env(g_vars->env + i + 1, newenv + i, get_env_nb(g_vars->env));
			free (g_vars->env);
			g_vars->env = newenv;
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

int	ft_unset(char **args, t_parser *list)
{
	int	i;

	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (print_usage(args));
	i = 0;
	while (args[++i])
		remove_variable(args[i]);
	return (EXIT_SUCCESS);
}
