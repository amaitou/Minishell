/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:40:49 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 16:52:52 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_cd_home(char *home, char *pwd, char *oldpwd)
{
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	ft_setenv("OLDPWD", oldpwd, 1);
	ft_setenv("PWD", home, 1);
	free(pwd);
	return (0);
}

static int	ft_cd_oldpwd(char *home, char *pwd, char *oldpwd)
{
	if (!oldpwd)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	ft_setenv("OLDPWD", pwd, 1);
	ft_setenv("PWD", oldpwd, 1);
	free(pwd);
	return (0);
}

static int	ft_cd_path(char *path, char *home, char *pwd, char *oldpwd)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	ft_setenv("OLDPWD", oldpwd, 1);
	ft_setenv("PWD", getcwd(NULL, 0), 1);
	free(pwd);
	free(home);
	return (0);
}

int	ft_cd(char **args, char *env[])
{
	char	*home;
	char	*pwd;
	char	*oldpwd;

	home = get_env("HOME", env);
	pwd = getcwd(NULL, 0);
	oldpwd = get_env("OLDPWD", env);
	if (!args[1])
		return (ft_cd_home(home, pwd, oldpwd));
	else if (args[1][0] == '-' && !args[1][1])
		return (ft_cd_oldpwd(home, pwd, oldpwd));
	else
		return (ft_cd_path(args[1], home, pwd, oldpwd));
}