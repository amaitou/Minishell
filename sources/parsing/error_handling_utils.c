/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:58:53 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 02:00:22 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_error_helper(t_errors *error)
{
	if (error->error_type == error_of_pipeline)
		ft_putendl_fd(PIPE_ERROR, STDERR_FILENO);
	else if (error->error_type == error_of_redirection_heredoc)
		ft_putendl_fd(HEREDOC_ERROR, STDERR_FILENO);
	else if (error->error_type == error_of_redirection_append)
		ft_putendl_fd(APPEND_ERROR, STDERR_FILENO);
	else if (error->error_type == error_of_redirection_in)
		ft_putendl_fd(IN_ERROR, STDERR_FILENO);
	else if (error->error_type == error_of_redirection_out)
		ft_putendl_fd(OUT_ERROR, STDERR_FILENO);
	else if (error->error_type == error_of_single_quotes
		|| error->error_type == error_of_double_quotes)
		ft_putendl_fd(QUOTES_ERROR, STDERR_FILENO);
	g_vars->exit_status = 258;
}
