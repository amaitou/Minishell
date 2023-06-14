/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 10:52:30 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_a_builtin(t_dlist *list, char *env[])
{
	if (!ft_strcmp(list->cmd, "echo"))
	{
	}
	else if (!ft_strcmp(list->cmd, "pwd"))
	{
	}
	else if (!ft_strcmp(list->cmd, "cd"))
	{
	}
	else if (!ft_strcmp(list->cmd, "export"))
	{
	}
	else if (!ft_strcmp(list->cmd, "unset"))
	{
	}
	else if (!ft_strcmp(list->cmd, "env"))
	{
	}
	else if (!ft_strcmp(list->cmd, "exit"))
	{
	}
	else
		return (0);
}

static void	determine_cmd(t_dlist *list, char *env[])
{
	char	**path;

	path = NULL;
	if (access(list->cmd, X_OK))
	{
		if (is_a_builtin(list, env) == 0)
		{
		}
	}
	else
		if (execve(list->cmd, list->args, env))
			exit(ft_perror("execve : "));
}

static int	wait_on_all_children(pid_t pid, t_dlist	*lst)
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

void	executor(t_dlist *list, int *status, char *env[])
{
	t_dlist	*lst;
	pid_t	pid;
	int		pipefd[2];
	int		old_fd;

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
	*status = wait_on_all_children(pid, lst);
}
