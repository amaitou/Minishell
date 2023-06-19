/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:12:20 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/19 11:58:56 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_output(t_list *list)
{
	int	fd;

	if (access(list->name, F_OK) == 0)
	{
		ft_putstr_fd("minishell: cannot overwrite existing file\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fd = open(list->name, O_CREAT | O_WRONLY, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_input(t_list *list)
{
	int	fd;

	if (access(list->name, F_OK) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fd = open(list->name, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

void	append_output(t_list *list)
{
	int	fd;

	if (access(list->name, F_OK) == -1)
		fd = open(list->name, O_CREAT | O_WRONLY, 0644);
	else
		fd = open(list->name, O_WRONLY | O_APPEND);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	heredoc_handle(t_list *list, int *heredoc)
{
	char	*string;

	while (list)
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
			ft_putendl_fd(string, *(heredoc + 1));
			free (string);
			string = readline("> ");
		}
		if (list->next && list->next->type == HEREDOC)
		{
			close(heredoc[1]);
			close(heredoc[0]);
		}
		list = list->next;
	}
}

int	redirections_handle(t_list *files)
{
	while (files)
	{
		if (files->type == IN)
		{
			if (redirect_input(files) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (files->type == OUT)
		{
			if (redirect_output(files) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (files->type == APPEND)
			append_output(files);
		files = files->next;
	}
	return (EXIT_SUCCESS);
}
