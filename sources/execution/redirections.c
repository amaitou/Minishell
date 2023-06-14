/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:12:20 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 22:18:32 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_output(t_list *list)
{
	int	fd;

	if (access(list->name, F_OK) == 0)
	{
		ft_putstr_fd("minishell: cannot overwrite existing file\n",
			STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	fd = open(list->name, O_CREAT | O_WRONLY, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_input(t_list *list)
{
	int	fd;

	if (access(list->name, F_OK) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n",
			STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	fd = open(list->name, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
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
