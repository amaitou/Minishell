/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/15 15:22:24 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_a_builtin(t_parser *list)
{
	if (!ft_strcmp(list->args[0], "echo"))
		ft_echo(list->args);
	else if (!ft_strcmp(list->args[0], "pwd"))
		ft_pwd();
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
	return (0);
}

static char	*search_for_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (path[++i])
	{
		tmp = string_join(ft_strdup(path[i]), ft_strdup("/"));
		tmp = string_join(tmp, ft_strdup(cmd));
		if (access(tmp, X_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

static void	exec_cmd(t_parser *list, char *env[])
{
	char	**path;
	char	*cmd;

	path = NULL;
	cmd = NULL;
	if (access(list->args[0], X_OK) == -1)
	{
		if (is_a_builtin(list) == 0)
		{
			path = ft_split(ft_getenv("PATH", env), ':');
			cmd = search_for_cmd(list->args[0], path);
			clean(path);
			if (cmd)
				if (execve(cmd, list->args, env))
					exit(ft_perror("execve : "));
			printf("minishell: %s: command not found\n", list->args[0]);
		}
	}
	else
		if (execve(list->args[0], list->args, env))
			exit(ft_perror("execve : "));
}

void	executor(t_parser *list, char *env[])
{
	t_exec	*es;

	es = init_struct(list);
	while (list)
	{
		pipe(es->pipefd);
		heredoc_handle(list->heredoc, es->heredoc);
		es->pid = fork();
		if (es->pid < 0)
			exit(ft_perror("fork : "));
		if (es->pid == 0)
		{
			pipes_handle(list, es->old_fd, es->pipefd, es->heredoc);
			exec_cmd(list, env);
		}
		close_fds(es, list);
		list = list->next;
	}
	close(es->pipefd[0]);
	wait_on_all_children(es->pid, es->lst);
	free (es);
}
