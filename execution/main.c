/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:54:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/12 23:34:18 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_dlist	*list;
	int		status;

	list = create_node();
	list->cmd = ft_strdup("/bin/cat");
	list->args = ft_split("cat", ' ');
	list->builtin = _NONE;
	list->type = __PIPE;
	list->state = __D_QUOTES;
	append_node(&list, create_node());
	list->next->cmd = ft_strdup("/bin/ls");
	list->next->args = ft_split("ls", ' ');
	list->next->builtin = _NONE;
	list->next->type = __PIPE;
	list->next->state = __D_QUOTES;
	append_node(&list, create_node());
	list->next->next->cmd = ft_strdup("/usr/bin/wc");
	list->next->next->args = ft_split("wc -l", ' ');
	list->next->next->builtin = _NONE;
	list->next->next->type = __NONE;
	list->next->next->state = __D_QUOTES;
	executor(list, &status, NULL);
}
