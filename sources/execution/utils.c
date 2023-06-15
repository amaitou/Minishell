/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:38:16 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/15 15:53:28 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_on_all_children(pid_t pid, t_parser *lst)
{
	pid_t	tmp;
	int		tmpsts;

	tmp = 0;
	tmpsts = 0;
	while (lst)
	{
		tmp = waitpid(-1, &tmpsts, 0);
		if (tmp == pid)
			g_status = tmpsts >> 8;
		lst = lst->next;
	}
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
	redirections_handle(list->file);
	if (list->heredoc)
	{
		close(heredoc[1]);
		dup2(heredoc[0], STDIN_FILENO);
		close(heredoc[0]);
	}
}

t_exec	*init_struct(t_parser *list)
{
	t_exec	*head;

	head = (t_exec *)malloc(sizeof(t_exec));
	head->lst = list;
	head->pid = 0;
	head->old_fd = 0;
	list->heredoc = mount_heredoc(list->file);
	ft_memset(head->pipefd, 0, 2);
	ft_memset(head->heredoc, 0, 2);
	return (head);
}
