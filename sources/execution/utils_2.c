/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:04:27 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 01:49:45 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	*init_struct(t_parser *list)
{
	t_exec	*head;

	head = (t_exec *)malloc(sizeof(t_exec));
	head->lst = list;
	head->pid = 0;
	head->old_fd = 0;
	head->nb_commands = 0;
	ft_memset(head->pipefd, 0, 2);
	ft_memset(head->heredoc, 0, 2);
	head->saved_stdin = dup(STDIN_FILENO);
	head->saved_stdout = dup(STDOUT_FILENO);
	return (head);
}

int	is_dir(char *filename)
{
	struct stat	path;

	if (stat(filename, &path) == 0)
	{
		if (S_ISDIR(path.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

void	ft_print_error(char *cmd, char *msg, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}
