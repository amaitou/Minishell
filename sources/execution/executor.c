/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/16 13:56:08 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_builtin(t_parser *list)
{
	if (list->args && !ft_strcmp(list->args[0], "echo"))
		g_status = ft_echo(list->args, list);
	else if (list->args && !ft_strcmp(list->args[0], "pwd"))
		g_status = ft_pwd(list->args, list);
	else if (list->args && !ft_strcmp(list->args[0], "cd"))
	{
	}
	else if (list->args && !ft_strcmp(list->args[0], "export"))
	{
	}
	else if (list->args && !ft_strcmp(list->args[0], "unset"))
	{
	}
	else if (list->args && !ft_strcmp(list->args[0], "env"))
	{
	}
	else if (list->args && !ft_strcmp(list->args[0], "exit"))
	{
	}
	else if (list->args)
		return (0);
	return (1);
}

static int	is_a_builtin(t_parser *list)
{
	if (list->args && (!ft_strcmp(list->args[0], "echo")
			|| !ft_strcmp(list->args[0], "pwd")
			|| !ft_strcmp(list->args[0], "cd")
			|| !ft_strcmp(list->args[0], "export")
			|| !ft_strcmp(list->args[0], "unset")
			|| !ft_strcmp(list->args[0], "env")
			|| !ft_strcmp(list->args[0], "exit")))
		return (1);
	else
		return (0);
}

static char	*search_for_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (cmd && path[++i])
	{
		tmp = string_join(ft_strdup(path[i]), ft_strdup("/"));
		tmp = string_join(tmp, ft_strdup(cmd));
		if (access(tmp, X_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

static void	exec_cmd(t_parser *list, char *env[], t_exec *es)
{
	char	**path;
	char	*cmd;

	if (list->args && access(list->args[0], X_OK) == -1)
	{
		if (exec_builtin(list) == 0)
		{
			path = ft_split(ft_getenv("PATH", env), ':');
			cmd = search_for_cmd(list->args[0], path);
			clean(path);
			if (cmd)
				if (execve(cmd, list->args, env))
					exit(ft_perror("execve : "));
			printf("minishell: %s: command not found\n", list->args[0]);
			if (cmd)
				exit(0);
			exit(127);
		}
		else if (list->type == __PIPE)
			exit(g_status);
	}
	else if (list->args)
		if (execve(list->args[0], list->args, env))
			exit(ft_perror("execve : "));
	dup2(es->saved_stdin, STDIN_FILENO);
	dup2(es->saved_stdout, STDOUT_FILENO);
}

void	executor(t_parser *list, char *env[])
{
	t_exec	*es;

	es = init_struct(list);
	while (list)
	{
		heredoc_handle(list->heredoc, es->heredoc);
		if (!is_a_builtin(list) || (is_a_builtin(list) && list->type == __PIPE))
		{
			pipe(es->pipefd);
			es->nb_commands++;
			es->pid = fork();
			if (es->pid == 0)
			{
				pipes_handle(list, es->old_fd, es->pipefd, es->heredoc);
				exec_cmd(list, env, es);
			}
			close_fds(es, list);
		}
		else
			exec_cmd(list, env, es);
		list = list->next;
	}
	if (es->pipefd[0])
		close(es->pipefd[0]);
	get_exit_status(es->pid, es);
}
