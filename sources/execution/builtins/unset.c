/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:52:16 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/17 20:19:42 by bbouagou         ###   ########.fr       */
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
	return (i);
}
// zmoumen was here again

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

static void	remove_variable(t_vars *vars, char *string)
{
	char	**newenv;
	char	**tmp;
	int		i;

	i = -1;
	while (vars->env[++i])
	{
		tmp = ft_split(vars->env[i], '=');
		if (!ft_strcmp(tmp[0], string))
		{
			newenv = (char **)ft_calloc(get_env_nb(vars->env), sizeof(char *));
			copy_env(vars->env, newenv, i);
			copy_env(vars->env + i + 1, newenv + i, get_env_nb(vars->env));
			free (vars->env);
			vars->env = newenv;
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

int	ft_unset(char **args, t_vars *vars, t_parser *list)
{
	int	i;

	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (print_usage(args));
	i = 0;
	while (args[++i])
		remove_variable(vars, args[i]);
	return (EXIT_SUCCESS);
}
