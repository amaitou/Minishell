/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/03 19:27:28 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int check_spaces(char *s)
{
    while (*s && (*s == '\t' || *s == ' '))
        ++s;
    if (*s)
        return (0);
    return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_scanner	*scanner;
	t_prompt	*prompt;
    t_dlist     *head;
	// t_env		*env;

	(void)argc;
	(void)argv;
    (void)envp;
	// env = NULL;
	// env = init_env(env, envp);
	while (1)
	{
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		scanner = (t_scanner *)malloc(sizeof(t_scanner));
		scanner->command = prompt_string(prompt);
        head = NULL;
        if(!scanner->command)
        {
            free(prompt);
            free(scanner);
            exit(1);
        }
        if (check_spaces(scanner->command))
        {
            free(prompt->line);
            free(prompt);
            free(scanner->command);
            free(scanner);
        }
        else
        {
            __scanner(scanner);
            // scanner_traversal(scanner->tokens);
            __lexer(head, scanner);
            // add_history(scanner->command);
            // free(prompt->line);
            // free(prompt);
            // free(scanner->command);
            // free_scanner(scanner->tokens);
            // free(scanner);
        }
	}
	return (0);
}
