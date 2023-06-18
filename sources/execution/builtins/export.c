/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:48:28 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/18 10:23:39 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args)
{
	printf("minishell: export: %c%c: invalid option\n", args[1][0], args[1][1]);
	printf("export: usage: export [name[=value]]\n");
	return (EXIT_FAILURE);
}

static int	get_env_nb(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i + 2);
}

static int	add_variable(char *string, t_vars *vars)
{
	char	**newenv;
	int		i;

	i = 0;
	while (string[i] && (ft_isdigit(string[i])
			|| ft_isalpha(string[i]) || string[i] == '_'))
		i++;
	if (i != 0 && string[i] == '=')
	{
		newenv = (char **)malloc(get_env_nb(vars->env) * sizeof(char *));
		i = -1;
		while (vars->env[++i])
			newenv[i] = ft_strdup(vars->env[i]);
		newenv[i++] = ft_strdup(string);
		newenv[i] = NULL;
		free(vars->env);
		vars->env = newenv;
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("minishell: export: %s: not a valid identifier\n", string);
		return (EXIT_FAILURE);
	}
}

int	ft_export(char **args, t_parser *list, t_vars *vars)
{
	int		i;
	char	**tmp;
	char	*tmp2;

	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (print_usage(args));
	i = 0;
	while (args[++i])
	{
		tmp = ft_split(args[i], '=');
		tmp2 = ft_getenv(tmp[0], vars->env);
		if (tmp2)
			ft_setenv(tmp[0], ft_strdup(tmp[1]), vars->env);
		else if (add_variable(args[i], vars) == EXIT_FAILURE)
		{
			clean(tmp);
			return (EXIT_FAILURE);
		}
		clean(tmp);
		if (tmp2)
			free(tmp2);
	}
	return (EXIT_SUCCESS);
}
