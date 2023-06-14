/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 17:07:46 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_a_builtin(t_parser *list, char *env[])
{
	if (!ft_strcmp(list->args[0], "echo"))
	{
	}
	else if (!ft_strcmp(list->args[0], "pwd"))
	{
	}
	else if (!ft_strcmp(list->args[0], "cd"))
	{
	}
	else if (!ft_strcmp(list->args[0], "export"))
	{
	}
	else if (!ft_strcmp(list->args[0], "unset"))
	{
	}
	else if (!ft_strcmp(list->args[0], "env"))
	{
	}
	else if (!ft_strcmp(list->args[0], "exit"))
	{
	}
	(void)env;
	return (0);
}

static void	determine_cmd(t_parser *list, char *env[])
{
	char	**path;

	path = NULL;
	(void)env;
	if (access(list->args[0], X_OK))
	{
		if (is_a_builtin(list, env) == 0)
		{
		}
	}
	else
		if (execve(list->args[0], list->args, env))
			exit(ft_perror("execve : "));
}

static int	wait_on_all_children(pid_t pid, t_parser	*lst)
{
	pid_t	tmp;
	int		tmpsts;
	int		status;

	tmp = 0;
	tmpsts = 0;
	status = 0;
	while (lst)
	{
		tmp = waitpid(-1, &tmpsts, 0);
		if (tmp == pid)
			status = tmpsts >> 8;
		lst = lst->next;
	}
	return (status);
}

void	executor(t_parser *list, char *env[])
{
	t_parser	*lst;
	pid_t		pid;
	int			pipefd[2];
	int			old_fd;

	old_fd = 0;
	pid = 0;
	lst = list;
	while (list)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			exit(ft_perror("fork : "));
		if (pid == 0)
		{
			dup2(old_fd, STDIN_FILENO);
			if (old_fd)
				close(old_fd);
			if (list->type == __PIPE)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			determine_cmd(list, env);
		}
		close(pipefd[1]);
		if (old_fd)
			close(old_fd);
		old_fd = pipefd[0];
		list = list->next;
	}
	close(old_fd);
	status = wait_on_all_children(pid, lst);
}
