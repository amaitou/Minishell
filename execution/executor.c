/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/09 23:57:18 by bbouagou         ###   ########.fr       */
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

static int	ft_pipe(t_dlist *list, char *env[], int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execve(list->cmd, list->args, env) == -1)
		{
			perror("ft_pipe : ");
			exit(EXIT_FAILURE);
		}
	}
	list = list->next;
	pid = fork();
	if (!pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		if (execve(list->cmd, list->args, env) == -1)
		{
			perror("ft_pipe : ");
			exit(EXIT_FAILURE);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

void	executor(t_dlist *list, int *status, char *env[])
{
	t_dlist	*tmp;
	int		pipefd[2];

	tmp = list;
	while (tmp)
	{
		if (tmp->type == __PIPE)
		{
			pipe(pipefd);
			*status = ft_pipe(tmp, env, pipefd);
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
