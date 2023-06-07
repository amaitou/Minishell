/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:47:00 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/07 22:28:16 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_builtins(t_dlist *list, char *env[])
{
	if (list->builtin == __ECHO)
		return (ft_echo(list->args));
	else if (list->builtin == __PWD)
		return (ft_pwd());
	else
		return (0);
}

void	executor(t_dlist *list, int *status, char *env[])
{
	t_dlist	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->builtin != _NONE)
			*status = exec_builtins(tmp, env);
		else
			*status = exec_cmd(tmp, env);
		tmp = tmp->next;
	}
}
