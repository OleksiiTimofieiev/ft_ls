/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_infrastructure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:16:12 by otimofie          #+#    #+#             */
/*   Updated: 2018/10/27 16:03:45 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

long long	get_total_blocks(t_temp *list)
{
	long long sum = 0;


	while(list)
	{
		sum += list->blocks_data;
		list = list->next;
	}
	return (sum);
}

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

void add(t_temp **head_ref, char *new_d_name, unsigned char d_type, t_data var/*, char *path*/)
{
	t_temp *new_t_temp;
	t_temp *last;

	new_t_temp = (t_temp*)malloc(sizeof(t_temp));
	last = *head_ref;
	
	new_t_temp->blocks_data = var.blocks_buf;
	new_t_temp->bytes_data = var.bytes_buf;
	new_t_temp->d_name = ft_strdup(new_d_name);
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
	long long total = 0;

	total = get_total_blocks(list);
	ft_printf("total %lld\n", total);
	while (list)
	{
		ft_printf("name-> %s, bytes-> %lld, blocks-> %lld\n", list->d_name, list->bytes_data, list->blocks_data);
		list = list->next;
	}
}
