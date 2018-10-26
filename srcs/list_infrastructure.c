/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_infrastructure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:16:12 by otimofie          #+#    #+#             */
/*   Updated: 2018/10/26 19:29:40 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	delete_list(t_temp **head_ref)
{
	t_temp *current;
	t_temp *next;

	current = *head_ref;
	while (current != NULL)
	{
		next = current->next;
		free(current->d_name);
		free(current);
		current = next;
	}
}

void	add(t_temp **head_ref, char *new_d_name, unsigned char d_type)
{
	t_temp *new_t_temp;
	t_temp *last;

	new_t_temp = (t_temp*)malloc(sizeof(t_temp));
	last = *head_ref;
	new_t_temp->d_name = strdup(new_d_name);
	new_t_temp->d_type = d_type;
	new_t_temp->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_t_temp;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_t_temp;
	return ;
}

void	print_list(t_temp *list)
{
	while (list)
	{
		ft_printf("%s\n", list->d_name);
		list = list->next;
	}
}
