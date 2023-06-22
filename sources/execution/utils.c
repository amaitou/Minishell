/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:38:16 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/22 17:04:06 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_exit_status(pid_t pid, t_exec *es)
{
	int		tmpsts;

	tmpsts = 0;
	if (es->pipefd[0])
		close(es->pipefd[0]);
	while (es->nb_commands)
	{
		if (pid == wait(&tmpsts))
		{
			if (WIFSIGNALED(tmpsts))
				g_vars->exit_status = WTERMSIG(tmpsts) + 128;
			else
				g_vars->exit_status = tmpsts >> 8;
		}
		es->nb_commands--;
	}
	free (es);
}

void	close_fds(t_exec *es, t_parser *list)
{
	if (list->heredoc)
	{
		close(es->heredoc[0]);
		close(es->heredoc[1]);
	}
	close(es->pipefd[1]);
	if (es->old_fd)
		close(es->old_fd);
	if (list->type == __PIPE)
		es->old_fd = es->pipefd[0];
}

void	pipes_handle(t_parser *list, int old_fd, int *pipefd, int *heredoc)
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
	if (list->heredoc)
	{
		close(heredoc[1]);
		dup2(heredoc[0], STDIN_FILENO);
		close(heredoc[0]);
	}
	if (redirections_handle(list->file) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
}

void	multi_purpose_func(t_exec *es, char *string, int flag)
{
	if (!flag)
	{
		dup2(es->saved_stdin, STDIN_FILENO);
		dup2(es->saved_stdout, STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(string, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
}

t_list	*mount_heredoc(t_list *files)
{
	t_list	*file;
	t_list	*heredoc;
	t_list	*traverser;

	file = files;
	heredoc = NULL;
	while (file)
	{
		if (file->type == HEREDOC)
		{
			ft_lstadd_back(&heredoc, ft_lstnew());
			traverser = ft_lstlast(heredoc);
			traverser->name = ft_strdup(file->name);
			traverser->type = HEREDOC;
		}
		file = file->next;
	}
	return (heredoc);
}
