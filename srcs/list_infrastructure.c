/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_infrastructure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:16:12 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 18:50:55 by otimofie         ###   ########.fr       */
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

void		add(t_temp **head_ref, char *new_d_name, t_data var)
{
	t_temp *new;
	t_temp *last;

	new = (t_temp*)malloc(sizeof(t_temp));
	last = *head_ref;
	element_constructor(new, new_d_name, var);
	if (*head_ref == NULL)
	{
		*head_ref = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void		print_date(char *time_str)
{
	int i;

	i = 4;
	while (i < 16)
		ft_printf("%c", time_str[i++]);
	ft_printf(" ");
}



void		print_dname(t_temp *list, t_flags *flags)
{
	if (list->type_and_permissions_data[0] != 'l')
	{
		if (flags->colors)
			color_printing(list);
		else
			ft_printf("%s\n", list->d_name);
	}
	else
		ft_printf("%s -> %s\n", list->d_name, list->link_name_data);
}

void		print_maj_min(t_temp *list, t_output_length *length)
{
	if (list->type_and_permissions_data[0] == 'c'
		|| list->type_and_permissions_data[0] == 'b')
		print_major_minor(list, length);
	else
		print_number_of_bytes(list, *length);
}

void		print_total(t_flags *flags, t_temp *list)
{
	if (!flags->no_total && get_total_blocks(list) != 0 && flags->long_format)
		ft_printf("total %lld\n", get_total_blocks(list));
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
