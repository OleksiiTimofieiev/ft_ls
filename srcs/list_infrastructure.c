/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_infrastructure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:16:12 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 19:20:55 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

long long	get_total_blocks(t_temp *list)
{
	long long sum;

	sum = 0;
	while (list)
	{
		sum += list->blocks_data;
		list = list->next;
	}
	return (sum);
}

void		delete_list(t_temp **head_ref)
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

void		element_constructor(t_temp *new, char *new_d_name, t_data var)
{
	new->blocks_data = var.blocks_buf;
	new->d_name = ft_strdup(new_d_name);
	ft_strcpy(new->type_and_permissions_data, var.type_and_permissions_buf);
	new->hard_links_data = var.hard_links_buf;
	ft_strcpy(new->owner_name_data, var.owner_name_buf);
	ft_strcpy(new->group_name_data, var.group_name_buf);
	new->size_data = var.size_buf;
	str_copy(new->time_data, var.time_buf);
	new->major_data = var.major_buf;
	new->minor_data = var.minor_buf;
	new->mod_time_data = var.mod_time_buf;
	ft_strcpy(new->link_name_data, var.link_name_buf);
	new->next = NULL;
}

void		print_list(t_temp *list, t_flags flags)
{
	int				len;
	t_output_length	length;

	len = 0;
	fill_the_length(list, &length);
	len = length.major + length.minor + 2;
	if (len > length.number_of_bytes)
		length.number_of_bytes = len + 1;
	print_total(&flags, list);
	while (list)
	{
		if (list->d_name[0] == '.' && !flags.include_dot)
		{
			list = list->next;
			continue ;
		}
		if (flags.long_format)
		{
			print_simple_params(list, length, flags);
			print_maj_min(list, &length);
			print_date(list->time_data);
		}
		print_dname(list, &flags);
		list = list->next;
	}
}
