/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/15 12:06:08 by bbouagou         ###   ########.fr       */
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

static void	clean_resources(char **var)
{
	int	i;

	i = -1;
	while (var[++i])
		free(var[i]);
	free(var);
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
			clean_resources(path);
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

static void	wait_on_all_children(pid_t pid, t_parser *lst)
{
	pid_t	tmp;
	int		tmpsts;

	tmp = 0;
	tmpsts = 0;
	while (lst)
	{
		tmp = waitpid(-1, &tmpsts, 0);
		if (tmp == pid)
			status = tmpsts >> 8;
		lst = lst->next;
	}
}

static void	redirections_handle(t_list *files)
{
	while (files)
	{
		if (files->type == IN)
			redirect_input(files);
		else if (files->type == OUT)
			redirect_output(files);
		else if (files->type == APPEND)
			append_output(files);
		files = files->next;
	}
}

static void	heredoc_handle(t_list *list, int *heredoc)
{
	char	*string;

	if (list && list->type == HEREDOC)
	{
		pipe(heredoc);
		string = readline("> ");
		while (string)
		{
			if (!strcmp(string, list->name))
			{
				if (string)
					free (string);
				break ;
			}
			ft_putstr_fd(string, *(heredoc + 1));
			ft_putstr_fd("\n", *(heredoc + 1));
			if (string)
				free (string);
			string = readline("> ");
		}
	}
}

void	executor(t_parser *list, char *env[])
{
	t_parser	*lst;
	pid_t		pid;
	int			pipefd[2];
	int			heredoc[2];
	int			old_fd;

	old_fd = 0;
	pid = 0;
	lst = list;
	while (list)
	{
		pipe(pipefd);
		heredoc_handle(list->file, heredoc);
		pid = fork();
		if (pid < 0)
			exit(ft_perror("fork : "));
		if (pid == 0)
		{
			redirections_handle(list->file);
			dup2(old_fd, STDIN_FILENO);
			if (old_fd)
				close(old_fd);
			if (list->type == __PIPE)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (list->file && list->file->type == HEREDOC)
			{
				close(heredoc[1]);
				dup2(heredoc[0], STDIN_FILENO);
				close(heredoc[0]);
			}
			exec_cmd(list, env);
		}
		if (heredoc[0])
		{
			close(heredoc[0]);
			close(heredoc[1]);
			ft_memset(heredoc, 0, 2);
		}
		close(pipefd[1]);
		if (old_fd)
			close(old_fd);
		if (list->type == __PIPE)
			old_fd = pipefd[0];
		else
			close (pipefd[0]);
		list = list->next;
	}
	wait_on_all_children(pid, lst);
}
