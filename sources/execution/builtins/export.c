/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:48:28 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/22 17:46:16 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putchar_fd(args[1][0], STDERR_FILENO);
	ft_putchar_fd(args[1][1], STDERR_FILENO);
	ft_putendl_fd(" invalid option", STDERR_FILENO);
	ft_putendl_fd("export: usage: export [name[=value]]...", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	print_err(char *string)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(string, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
}

static int	add_variable(char *string)
{
	char	**newenv;
	int		i;

	i = 0;
	while (string[i] && ((ft_isdigit(string[i]) && i != 0)
			|| ft_isalpha(string[i]) || string[i] == '_'))
		i++;
	if (i != 0 && (string[i] == '=' || !string[i]))
	{
		newenv = (char **)malloc((get_env_nb(g_vars->env) + 2)
				* sizeof(char *));
		i = -1;
		while (g_vars->env[++i])
			newenv[i] = ft_strdup(g_vars->env[i]);
		newenv[i++] = ft_strdup(string);
		newenv[i] = NULL;
		clean(g_vars->env);
		g_vars->env = newenv;
		return (EXIT_SUCCESS);
	}
	else
	{
		print_err(string);
		return (EXIT_FAILURE);
	}
}

static int	print_env(void)
{
	int		i;
	char	*name;
	char	*value;

	i = -1;
	while (g_vars->env && g_vars->env[++i])
	{
		name = ft_substr(g_vars->env[i], 0,
				(size_t)(ft_strchr(g_vars->env[i], '=') - g_vars->env[i]));
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name, STDOUT_FILENO);
		value = ft_substr(g_vars->env[i], ft_strlen(name) + 1,
				ft_strlen(g_vars->env[i]));
		free(name);
		if (g_vars->env[i][ft_strlen(name)] == '=')
			print_variable(value);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(value);
	}
	return (EXIT_SUCCESS);
}

int	ft_export(char **args, t_parser *list)
{
	int		i;
	int		return_value;
	char	*string;
	char	*tmp;

	return_value = EXIT_SUCCESS;
	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (print_usage(args));
	if (!args[1])
		return (print_env());
	i = 0;
	while (args[++i])
	{
		string = setup_variable(args, i, 0);
		tmp = setup_variable(args, i, 1);
		if (tmp)
			ft_setenv(string, ft_substr(args[i],
					(size_t)(ft_strchr(args[i], '=') - args[i]) + 1,
					ft_strlen(args[i])), g_vars->env);
		else
			return_value = add_variable(args[i]);
		ft_free_pointers(tmp, string, NULL);
	}
	return (return_value);
}
