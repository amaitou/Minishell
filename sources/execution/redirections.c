/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:12:20 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/23 20:47:33 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_output(t_list *list)
{
	int	fd;

	if (access(list->name, F_OK) == -1)
		fd = open(list->name, O_CREAT | O_WRONLY, 0644);
	else
		fd = open(list->name, O_WRONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_pustr_fd(list->name, STDERR_FILENO);
		ft_pustr_fd(": Permission denied\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
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
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_pustr_fd(list->name, STDERR_FILENO);
		ft_pustr_fd(": Permission denied\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int	append_output(t_list *list)
{
	int	fd;

	if (access(list->name, F_OK) == -1)
		fd = open(list->name, O_CREAT | O_WRONLY, 0644);
	else
		fd = open(list->name, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_pustr_fd(list->name, STDERR_FILENO);
		ft_pustr_fd(": Permission denied\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
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
			if (append_output(files) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		files = files->next;
	}
	return (EXIT_SUCCESS);
}
