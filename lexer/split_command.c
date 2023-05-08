/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:46:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/08 21:25:06 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*split_command(char *s)
{
	int		q;
	char	*p;
	char	*r;

	q = 0;
	p = ft_strtrim(s, "\t ");
	r = p;
	while (*p)
	{
		if (*p == '"')
		{
			q = 1;
			while (!(*p == '"' && *(p + 1) == ' ') && *p)
				++p;
			if (*p == '"' && *(p + 1) == ' ')
			{
				q = 0;
				*(p + 1) = ',';
				++p;
			}
		}
		else if (*p == '\'')
		{
			q = 1;
			while (!(*p == '\'' && *(p + 1) == ' ') && *p)
				++p;
			if (*p == '\'' && *(p + 1) == ' ')
			{
				q = 0;
				*(p + 1) = ',';
				++p;
			}
		}
		else
		{
			if ((*p == '\t' || *p == ' ') && !q)
				*p = ',';
			++p;
		}
	}
	return (r);
}

int main(int ac, char **ag)
{
	char *s = split_command(ag[1]);
	(void)ac;
	char **p = ft_split(s, ',');
	if (p)
	{
		int i = 0;
		while (p[i])
		{
			printf("%s\n", p[i]);
			++i;
		}
	}
	return (0);
}
