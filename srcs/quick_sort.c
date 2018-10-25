/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:41:50 by otimofie          #+#    #+#             */
/*   Updated: 2018/10/25 19:41:52 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_temp	*get_tail(t_temp *cur)
{
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	return (cur);
}

t_temp	*partition(t_temp *head, t_temp *end, t_temp **new_head, t_temp **new_end)
{
	t_temp *pivot;
	t_temp *prev;
	t_temp *tail;
	t_temp *cur;
	t_temp *tmp;

	pivot = end;
	prev = NULL;
	cur = head;
	tail = pivot;
	while (cur != pivot)
	{
		if (ft_strcmp(cur->d_name, pivot->d_name) < 0)
		{
			(*new_head == NULL) ? *new_head = cur : 0;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			if (prev)
				prev->next = cur->next;
			tmp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}
	(*new_head == NULL) ? *new_head = pivot : 0;
	(*new_end) = tail;
	return (pivot);
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
	pivot = partition(head, end, &new_head, &new_end);
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
