/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:41:50 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/11 17:14:30 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	init(t_temp **head, t_temp **end, t_qsort *var)
{
	var->pivot = *end;
	var->prev = NULL;
	var->cur = *head;
	var->tail = var->pivot;
}

t_temp	*get_tail(t_temp *cur)
{
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	return (cur);
}

t_temp	*delim(t_temp *head, t_temp *end, t_temp **new_head, t_temp **new_end)
{
	t_qsort var;

	init(&head, &end, &var);
	while (var.cur != var.pivot)
	{
		if (ft_strcmp(var.cur->d_name, var.pivot->d_name) < 0)
		{
			(*new_head == NULL) ? *new_head = var.cur : 0;
			var.prev = var.cur;
			var.cur = var.cur->next;
		}
		else
		{
			(var.prev) ? var.prev->next = var.cur->next : 0;
			var.tmp = var.cur->next;
			var.cur->next = NULL;
			var.tail->next = var.cur;
			var.tail = var.cur;
			var.cur = var.tmp;
		}
	}
	(*new_head == NULL) ? *new_head = var.pivot : 0;
	(*new_end) = var.tail;
	return (var.pivot);
}

t_temp	*quick_sort(t_temp *head, t_temp *end)
{
	t_temp *new_head;
	t_temp *new_end;
	t_temp *pivot;
	t_temp *tmp;

	if (!head || head == end)
		return (head);
	new_head = NULL;
	new_end = NULL;
	pivot = delim(head, end, &new_head, &new_end);
	if (new_head != pivot)
	{
		tmp = new_head;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		new_head = quick_sort(new_head, tmp);
		tmp = get_tail(new_head);
		tmp->next = pivot;
	}
	pivot->next = quick_sort(pivot->next, new_end);
	return (new_head);
}

void	q_sort(t_temp **head_ref)
{
	(*head_ref) = quick_sort(*head_ref, get_tail(*head_ref));
	return ;
}
