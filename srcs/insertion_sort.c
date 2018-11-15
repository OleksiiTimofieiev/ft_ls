#include "../includes/ft_ls.h"

void	sortedInsert(t_temp **head_ref, t_temp *new_node)
{
	t_temp  *current;

	if (*head_ref == NULL || (*head_ref)->mod_time_data >= new_node->mod_time_data)
	{
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		current = *head_ref;
		while (current->next!=NULL &&
			current->next->mod_time_data < new_node->mod_time_data) 
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void	insertionSort(t_temp **head_ref)
{
	t_temp *sorted = NULL;

	t_temp *current = *head_ref;
	while (current != NULL)
	{
		t_temp *next = current->next; 
		sortedInsert(&sorted, current);
		current = next;
	}
	*head_ref = sorted; 
}

void	r_sortedInsert(t_temp **head_ref, t_temp *new_node)
{
	t_temp  *current;

	if (*head_ref == NULL || (*head_ref)->d_name >= new_node->d_name)
	{
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		current = *head_ref;
		while (current->next!=NULL &&
			current->next->d_name < new_node->d_name) 
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void	r_insertionSort(t_temp **head_ref)
{
	t_temp *sorted = NULL;

	t_temp *current = *head_ref;
	while (current != NULL)
	{
		t_temp *next = current->next; 
		sortedInsert(&sorted, current);
		current = next;
	}
	*head_ref = sorted; 
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timofieiev <timofieiev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:41:50 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/11 19:35:44 by timofieiev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	init(t_temp **head, t_temp **end, t_qsort *var)
{
	var->pivot = *end;
	var->prev = NULL;
	var->cur = *head;
	var->tail = var->pivot;
}

static t_temp	*get_tail(t_temp *cur)
{
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	return (cur);
}

static t_temp	*delim(t_temp *head, t_temp *end, t_temp **new_head, t_temp **new_end)
{
	t_qsort var;

	init(&head, &end, &var);
	while (var.cur != var.pivot)
	{
		if (var.cur->mod_time_data > var.pivot->mod_time_data)
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

static t_temp	*quick_sort(t_temp *head, t_temp *end)
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

void	r_q_sort(t_temp **head_ref)
{
	(*head_ref) = quick_sort(*head_ref, get_tail(*head_ref));
	return ;
}


