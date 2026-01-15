/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:22 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:22 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lines	*new_line(char *str)
{
	t_lines	*ret;

	if (!str || str[0] == '\0')
		return (NULL);
	ret = malloc(sizeof(t_lines));
	if (!ret)
		return (NULL);
	ret->line = str;
	ret->next = NULL;
	return (ret);
}

void	add_line(t_lines **head, t_lines *line)
{
	t_lines	*tmp;

	tmp = NULL;
	if (!head)
		return ;
	if (!(*head))
	{
		(*head) = line;
		return ;
	}
	tmp = last_line((*head));
	tmp->next = line;
}

t_lines	*last_line(t_lines *head)
{
	t_lines	*ret;

	ret = head;
	if (!ret)
		return (NULL);
	while (ret->next)
		ret = ret->next;
	return (ret);
}

size_t	lines_count(t_lines *head)
{
	t_lines	*tmp;
	size_t	ret;

	tmp = head;
	ret = 0;
	if (!tmp)
		return (ret);
	while (tmp)
	{
		tmp = tmp->next;
		ret++;
	}
	return (ret);
}

void	free_lines(t_lines **head)
{
	t_lines	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->line);
		free(*head);
		(*head) = tmp;
	}
	free(*head);
	*head = NULL;
}
