/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:04:27 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/22 17:04:39 by amait-ou         ###   ########.fr       */
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
