/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:40:49 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/17 11:14:02 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args)
{
	printf("minishell: pwd: %c%c: invalid option\n", args[1][0], args[1][1]);
	printf("pwd: usage: pwd\n");
	return (EXIT_FAILURE);
}

static int	change_wd_home(char	*new_wd, char *old_wd, char *env[], char *c_old_pwd)
{
	char	*path;

	if (!new_wd)
	{
		ft_free_pointers(old_wd, c_old_pwd, NULL);
		printf ("minishell: cd: HOME not set\n");
		return (EXIT_SUCCESS);
	}
	else if (chdir(new_wd) == -1)
	{
		ft_free_pointers(new_wd, old_wd, c_old_pwd);
		return (ft_perror("minishell: cd:"));
	}
	ft_setenv("PWD", new_wd, env);
	ft_setenv("OLDPWD", old_wd, env);
	path = ft_getenv("PWD", env);
	printf("%s\n", path);
	ft_free_pointers(path, c_old_pwd, NULL);
	return (EXIT_SUCCESS);
}

static int	change_wd_oldpwd(char *new_wd, char *old_wd, char *env[], char *home)
{
	char	*path;

	if (!new_wd)
	{
		ft_free_pointers(old_wd, home, NULL);
		printf ("\n");
		ft_setenv("OLDPWD", getcwd(NULL, 0), env);
		return (EXIT_SUCCESS);
	}
	else if (chdir(new_wd) == -1)
	{
		ft_free_pointers(new_wd, old_wd, home);
		return (ft_perror("minishell: cd:"));
	}
	ft_setenv("PWD", new_wd, env);
	ft_setenv("OLDPWD", old_wd, env);
	path = ft_getenv("PWD", env);
	printf("%s\n", path);
	ft_free_pointers(path, home, NULL);
	return (EXIT_SUCCESS);
}

static int	change_wd(char *new_wd, char *old_wd, char *env[])
{
	char	*path;

	if (chdir(new_wd) == -1)
	{
		ft_free_pointers(new_wd, old_wd, NULL);
		return (ft_perror("minishell: cd: "));
	}
	ft_setenv("PWD", getcwd(NULL, 0), env);
	ft_setenv("OLDPWD", old_wd, env);
	path = ft_getenv("PWD", env);
	printf("%s\n", path);
	ft_free_pointers(path, NULL, NULL);
	return (EXIT_SUCCESS);
}

int	ft_cd(char **args, char *env[], t_parser *list)
{
	char	*home;
	char	*old_wd;
	char	*wd;
	
	if (list->type != __PIPE)
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
	return(change_wd(args[1], wd, env));
}
  