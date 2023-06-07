/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:54:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/07 22:25:30 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_dlist *list;
	int		status;

	list = create_node();
	list->cmd = ft_strdup("pwd");
	list->args = ft_split("hello world", ' ');
	list->builtin = __PWD;
	list->type = __NONE;
	list->state = __D_QUOTES;
	executor(list, &status, NULL);
}
