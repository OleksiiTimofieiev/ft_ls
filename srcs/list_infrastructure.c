/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_infrastructure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timofieiev <timofieiev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:16:12 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/11 10:25:05 by timofieiev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static long long	get_total_blocks(t_temp *list)
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

void				delete_list(t_temp **head_ref)
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

void				add(t_temp **head_ref, char *new_d_name,
					unsigned char d_type, t_data var)
{
	t_temp *new;
	t_temp *last;

	new = (t_temp*)malloc(sizeof(t_temp));

	last = *head_ref;

	new->blocks_data = var.blocks_buf;
	new->d_name = ft_strdup(new_d_name);
	ft_strcpy(new->type_and_permissions_data, var.type_and_permissions_buf);
	new->d_type = d_type;
	new->hard_links_data = var.hard_links_buf;
	ft_strcpy(new->owner_name_data, var.owner_name_buf);
	ft_strcpy(new->group_name_data, var.group_name_buf);
	new->size_data = var.size_buf;
	str_copy(new->time_data, var.time_buf);
	new->major_data = var.major_buf;
	new->minor_data = var.minor_buf;
	new->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

void				print_date(char *time_str)
{
	int i;

	i = 4;
	while (i < 16)
		ft_printf("%c", time_str[i++]);
	ft_printf(" ");
}

void				fill_the_length(t_temp *list, t_output_length *length)
{
	length->number_of_links = ft_decimal_length(list->hard_links_data);
	length->owner_name = ft_strlen(list->owner_name_data);
	length->group_name = ft_strlen(list->group_name_data);
	length->number_of_bytes = ft_decimal_length(list->size_data);

	length->major = ft_decimal_length(list->major_data);
	length->minor = ft_decimal_length(list->minor_data);

	while(list)
	{
		if (length->number_of_links < ft_decimal_length(list->hard_links_data))
			length->number_of_links = ft_decimal_length(list->hard_links_data);

		if (length->owner_name < (int)ft_strlen(list->owner_name_data))
			length->owner_name = (int)ft_strlen(list->owner_name_data);

		if (length->group_name < (int)ft_strlen(list->group_name_data))
			length->group_name = (int)ft_strlen(list->group_name_data);

		if (length->number_of_bytes < ft_decimal_length(list->size_data))
			length->number_of_bytes = ft_decimal_length(list->size_data);

		if (length->major && length->major < ft_decimal_length(list->major_data))
			length->major = ft_decimal_length(list->major_data);

		if (length->minor && length->minor < ft_decimal_length(list->minor_data))
			length->minor = ft_decimal_length(list->minor_data);

		list = list->next;
	}
}

void				print_major_minor(t_temp *list, t_output_length *length)
{
	ft_printf("%s", " ");
	// ft_printf("test->|%*d|",4,0); remember this stuff
	if (list->major_data != 0)
		ft_printf("%*d, ", length->major, list->major_data); // do not forget 32
	else
		ft_printf("%*d, ", length->major - 1, list->major_data); // do not forget 32
	
	if (list->minor_data !=0)
		ft_printf("%*d", length->minor, list->minor_data);
	else
		ft_printf("%*d", length->minor - 1, list->minor_data);
	ft_putchar(32);
}

void				print_list(t_temp *list)
{
	t_output_length	length;
	int len;
	int major_minor_case;

	fill_the_length(list, &length);
	// ft_printf("len_major->%d, len_minor->%d\n", length.major, length.minor);
	len = length.major + length.minor;
	major_minor_case = 0;
	if (len > length.number_of_bytes || len + 2 > length.number_of_bytes)
	{
		length.number_of_bytes = len;
		major_minor_case += 3; // quantity of spaces before the size data line;
	}
	ft_printf("total %lld\n", get_total_blocks(list));
	// different func;
	while (list)
	{
		ft_printf("%s ", list->type_and_permissions_data);
		ft_printf("%*d ", length.number_of_links, list->hard_links_data);
		ft_printf("%*-s  ", length.owner_name, list->owner_name_data);
		ft_printf("%*-s  ", length.group_name, list->group_name_data);
		if (list->type_and_permissions_data[0] == 'c' || list->type_and_permissions_data[0] == 'b')
			print_major_minor(list, &length);
		else
		{
			if (list->size_data)
				ft_printf("%*lld ", length.number_of_bytes + major_minor_case, (long long)list->size_data);
			else
				ft_printf("%*lld ", length.number_of_bytes + major_minor_case -1, (long long)list->size_data);
		}
		print_date(list->time_data);
		ft_printf("%s\n", list->d_name);
		list = list->next;
	}
}
