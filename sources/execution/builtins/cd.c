/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:40:49 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/13 06:57:28 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putchar_fd(args[1][0], STDERR_FILENO);
	ft_putchar_fd(args[1][1], STDERR_FILENO);
	ft_putendl_fd(" invalid option", STDERR_FILENO);
	ft_putendl_fd("cd: usage: cd", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	change_wd_home(char	*new_wd, char *old_wd,
	char *env[], char *c_old_pwd)
{
	if (!new_wd)
	{
		ft_free_pointers(old_wd, c_old_pwd, new_wd);
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (chdir(new_wd) == -1)
	{
		ft_free_pointers(new_wd, old_wd, c_old_pwd);
		return (ft_perror("minishell: cd:"));
	}
	ft_setenv("PWD", new_wd, env);
	ft_setenv("OLDPWD", old_wd, env);
	ft_free_pointers(c_old_pwd, NULL, NULL);
	return (EXIT_SUCCESS);
}

static int	change_wd_oldpwd(char *new_wd, char *old_wd,
	char *env[], char *home)
{
	if (!new_wd)
	{
		ft_free_pointers(old_wd, home, new_wd);
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (chdir(new_wd) == -1)
	{
		ft_free_pointers(new_wd, old_wd, home);
		return (ft_perror("minishell: cd:"));
	}
	ft_setenv("PWD", new_wd, env);
	ft_setenv("OLDPWD", old_wd, env);
	ft_free_pointers(home, NULL, NULL);
	return (EXIT_SUCCESS);
}

static int	change_wd(char *new_wd, char *old_wd, char *env[])
{
	if (chdir(new_wd) == -1)
	{
		ft_free_pointers(old_wd, NULL, NULL);
		return (ft_perror("minishell: cd: "));
	}
	ft_setenv("PWD", getcwd(NULL, 0), env);
	ft_setenv("OLDPWD", old_wd, env);
	return (EXIT_SUCCESS);
}

int	ft_cd(char **args, char *env[], t_parser *list)
{
	char	*home;
	char	*old_wd;
	char	*wd;

	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (print_usage(args));
	home = ft_getenv("HOME", env);
	old_wd = ft_getenv("OLDPWD", env);
	wd = getcwd(NULL, 0);
	if (!wd)
	{
		ft_free_pointers(home, old_wd, NULL);
		return (ft_perror("getcwd: "));
	}
	if (!args[1])
		return (change_wd_home(home, wd, env, old_wd));
	else if (args[1][0] == '-')
		return (change_wd_oldpwd(old_wd, wd, env, home));
	ft_free_pointers(home, old_wd, NULL);
	return (change_wd(args[1], wd, env));
	return (1);
}
