/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/13 19:46:09 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_builtins(t_dlist *list, char *env[])
{
	if (list->builtin == __ECHO)
		return (ft_echo(list->args));
	else if (list->builtin == __PWD)
		return (ft_pwd());
	else
		return (0);
}

static int	ft_pipe(t_dlist *lst, char *env[])
{
	t_dlist	*list;
	pid_t	pid[2];
	int		pipefd[2];
	int		old_fd;
	int		status[2];

	old_fd = 0;
	pipe(pipefd);
	list = lst;
	while (list)
	{
		if (list->prev == NULL)
		{
			pid[0] = fork();
			if (pid == 0)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				if (execve(list->cmd, list->args, env))
				{
					perror("execve first : ");
					exit(EXIT_FAILURE);
				}
			}
			else
				close(pipefd[1]);
		}
		else if (list->type == __PIPE)
		{
			old_fd = pipefd[0];
			pipe(pipefd);
			pid[0] = fork();
			if (pid == 0)
			{
				close(pipefd[0]);
				dup2(old_fd, STDIN_FILENO);
				close(old_fd);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				if (execve(list->cmd, list->args, env))
				{
					perror("execve mid : ");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				close(pipefd[1]);
				close(old_fd);
			}
		}
		else
		{
			pid[0] = fork();
			if (pid == 0)
			{
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);
				if (execve(list->cmd, list->args, env))
				{
					perror("execve last : ");
					exit(EXIT_FAILURE);
				}
			}
			else
				close(pipefd[0]);
		}
		list = list->next;
	}
	while (lst)
	{
		pid[1] = waitpid(-1, &status[1], 0);
		if (pid[1] == pid[0])
		{
			status[0] = status[1] >> 8;
			printf("%d\n", status[0]);
		}
		lst = lst->next;
	}
	return (0);
}

void	executor(t_dlist *list, int *status, char *env[])
{
	t_dlist	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == __PIPE)
		{
			*status = ft_pipe(tmp, env);
			break ;
		}
		// else if (tmp->builtin != _NONE)
		// 	*status = exec_builtins(tmp, env);
		// else
		// 	*status = exec_cmd(tmp, env);
		tmp = tmp->next;
	}
}

/*

fd[1] -> fd[0]

parent : fd[2]
child1: fd[2] -> close fd[0] | dup2 fd[1], stdout | close fd[1];
close(fd[1])
child2 : fd[2] > close fd[1] | dup2 fd[0], stdin | close fd[0];
close(fd[0])

*/
